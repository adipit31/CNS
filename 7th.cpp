#include <bits/stdc++.h>
using namespace std;

void swap(vector<int>& sArray, int i, int j) {
    int temp = sArray[i];
    sArray[i] = sArray[j];
    sArray[j] = temp;
}

vector<int> keyScheduling(vector<int>& sArray, vector<int>& tArray) {
    int j = 0;
    int size = sArray.size();
    for (int i = 0; i < size; i++) {
        j = (j + sArray[i] + tArray[i]) % size;
        while (j < 0) {
            j += size;
        }
        swap(sArray, i, j);
    }
    return sArray;
}

vector<int> Encryption(vector<int>& plainText, vector<int>& tArray) {
    vector<int> encrypt;
    for (size_t i = 0; i < plainText.size(); i++) {
        encrypt.push_back(plainText[i] ^ tArray[i]);
    }
    return encrypt;
}

vector<int> streamGeneration(vector<int>& sArray, vector<int>& plainText) {
    int slen = sArray.size();
    int size = plainText.size();
    int i = 0, j = 0;
    vector<int> key;
    for (i = 1; i <= size; i++) {
        j = (j + sArray[i]) % slen;
        swap(sArray, i, j);
        int t = (sArray[i] + sArray[j]) % slen;
        key.push_back(sArray[t]);
    }
    return key;
}

int main() {
    try {
        vector<int> sArray, plainText, key, tArray;
        int temp, i = 0;
        
        cout << "Enter S-Array (in DEC format X X ...): ";
        while (cin.peek() != '\n' && cin >> temp) sArray.push_back(temp);
        cin.ignore();

        cout << "Enter PlainText (in DEC format X X ...): ";
        while (cin.peek() != '\n' && cin >> temp) plainText.push_back(temp);
        cin.ignore();

        cout << "Enter Key Array (in DEC format X X ...): ";
        while (cin.peek() != '\n' && cin >> temp) key.push_back(temp);
        cin.ignore();

        int keysize = key.size();
        while (sArray.size() != tArray.size()) {
            tArray.push_back(key[i]);
            i = (i + 1) % keysize;
        }

        sArray = keyScheduling(sArray, tArray);
        vector<int> genKey = streamGeneration(sArray, plainText);
        vector<int> encryptedText = Encryption(plainText, genKey);

        cout << "Encrypted PlainText: ";
        for (int enc : encryptedText) cout << enc << " ";
        cout << endl;
        
    } catch (const exception& e) {
        cerr << "Error in Handling " << e.what() << endl;
    }

    return 0;
}
