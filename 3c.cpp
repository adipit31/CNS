#include <bits/stdc++.h>
using namespace std;

int EEA(int a, int b) {
    int r1 = a, r2 = b, t1 = 0, t2 = 1;
    while (r2 > 0) {
        int q = r1 / r2;
        int r = r1 - q * r2;
        r1 = r2;
        r2 = r;
        int t = t1 - q * t2;
        t1 = t2;
        t2 = t;
    }
    return t1;
}

void hillCipher(string text, vector<int>& matrix) {
    int size = 2;
    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    bool flag = isupper(text[0]);
    
    for (int& v : matrix) {
        while (v < 0) {
            v += 26;
        }
    }

    if (flag) {
        transform(text.begin(), text.end(), text.begin(), ::tolower);
        int a = matrix[0], b = matrix[1], c = matrix[2], d = matrix[3];
        int det = (a * d) - (b * c);
        while (det < 0) {
            det += 26;
        }
        int detinv = EEA(26, det);
        while (detinv < 0) {
            detinv += 26;
        }
        vector<int> adjoint = {d, -b, -c, a};
        for (int& v : adjoint) {
            while (v < 0) {
                v += 26;
            }
        }
        for (int i = 0; i < adjoint.size(); i++) {
            matrix[i] = adjoint[i] * detinv % 26;
        }
    }

    while (text.size() % size != 0) {
        char randomChar = 'a' + (rand() % 26);
        if (text.find(randomChar) == string::npos) {
            text += randomChar;
        }
    }

    vector<string> textlist;
    for (int i = 0; i < text.size(); i += size) {
        textlist.push_back(text.substr(i, size));
    }

    string result = "";
    for (string txt : textlist) {
        vector<int> plist;
        for (char ch : txt) {
            plist.push_back(alphabet.find(ch));
        }
        int x = plist[0], y = plist[1];
        int a = matrix[0], b = matrix[1], c = matrix[2], d = matrix[3];
        vector<int> clist = {(a * x + c * y) % 26, (b * x + d * y) % 26};
        for (int v : clist) {
            result += alphabet[v];
        }
    }

    if (flag) {
        cout << "Decrypted: " << result << endl;
    } else {
        transform(result.begin(), result.end(), result.begin(), ::toupper);
        cout << "Encrypted: " << result << endl;
    }
}

int main() {

    
    vector<int> matrix(4);
    cout << "Enter Your Matrix a, b, c, d: ";
    for (int i = 0; i < 4; i++) {
        cin >> matrix[i];
    }

    string inputText;
    cout << "Enter Your String: ";
    cin >> inputText;


    hillCipher(inputText, matrix);

    return 0;
}
