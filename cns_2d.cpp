#include <bits/stdc++.h>
using namespace std;

// Function to encrypt or decrypt the text using the hybrid transposition cipher
void hybridTransposition(const string& inputText, vector<int>& enkey) {
    vector<pair<int, int>> sortedKey(enkey.size());
    for (size_t i = 0; i < enkey.size(); ++i) {
        sortedKey[i] = {i + 1, enkey[i]};
    }
    sort(sortedKey.begin(), sortedKey.end(), [](const auto& a, const auto& b) { return a.second < b.second; });

    vector<int> dekey(enkey.size());
    for (size_t i = 0; i < sortedKey.size(); ++i) {
        dekey[sortedKey[i].first - 1] = i + 1;
    }

    int col = enkey.size();
    int row = (inputText.size() + col - 1) / col; // ceiling division

    string modifiedText = inputText;
    if (inputText.find_first_of("abcdefghijklmnopqrstuvwxyz") != string::npos) {
        if (modifiedText.size() < row * col) {
            modifiedText.append(row * col - modifiedText.size(), 'a');
        }

        cout << "Encrypted Key: ";
        for (int e : enkey) cout << e << " ";
        cout << "\n";

        vector<string> matrix(row, string(col, ' '));
        for (int i = 0; i < modifiedText.size(); ++i) {
            matrix[i / col][i % col] = modifiedText[i];
        }
        for (const auto& row : matrix) {
            for (char ch : row) cout << ch << " ";
            cout << "\n";
        }

        string result;
        for (int e : enkey) {
            for (const auto& row : matrix) {
                result += toupper(row[e - 1]);
            }
        }
        cout << "Encrypted: " << result << "\n";
    } else {
        if (modifiedText.size() < row * col) {
            modifiedText.append(row * col - modifiedText.size(), 'A');
        }

        cout << "Decrypted Key: ";
        for (int d : dekey) cout << d << " ";
        cout << "\n";

        vector<string> matrix(row, string(col, ' '));
        for (int i = 0; i < modifiedText.size(); ++i) {
            matrix[i / col][i % col] = modifiedText[i];
        }
        for (const auto& row : matrix) {
            for (char ch : row) cout << ch << " ";
            cout << "\n";
        }

        string result;
        for (const auto& row : matrix) {
            for (int d : dekey) {
                result += tolower(row[d - 1]);
            }
        }
        cout << "Decrypted: " << result << "\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(nullptr)));

    cout << "Start\n";
    string inputText;
    cout << "Enter your String: ";
    getline(cin, inputText);
    inputText.erase(remove(inputText.begin(), inputText.end(), ' '), inputText.end());

    cout << "Enter Your key: ";
    vector<int> enkey;
    int key;
    while (cin >> key) {
        enkey.push_back(key);
        if (cin.peek() == '\n') break;
    }

    hybridTransposition(inputText, enkey);
    cout << "End\n";

    return 0;
}
