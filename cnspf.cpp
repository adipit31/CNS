#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<char> filler_matrix;

vector<vector<char>> createMatrix(const string& key) {
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";
    unordered_set<char> used_chars;
    vector<char> matrix;

    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (used_chars.find(c) == used_chars.end() && isalpha(c)) {
            matrix.push_back(c);
            used_chars.insert(c);
        }
    }

    for (char c : alphabet) {
        if (used_chars.find(c) == used_chars.end()) {
            matrix.push_back(c);
            filler_matrix.push_back(c);
        }
    }

    vector<vector<char>> finalMatrix(5, vector<char>(5));
    for (int i = 0; i < 25; ++i) {
        finalMatrix[i / 5][i % 5] = matrix[i];
    }

    return finalMatrix;
}

pair<int, int> findPosition(const vector<vector<char>>& matrix, char c) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == c) {
                return make_pair(i, j);
            }
        }
    }
    return make_pair(-1, -1);
}

string formatText(const string& text) {
    string formatted;
    for (char c : text) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (isalpha(c)) formatted += c;
    }

    string newText;
    for (size_t i = 0; i < formatted.length(); ++i) {
        newText += formatted[i];
        if (i + 1 < formatted.length() && formatted[i] == formatted[i + 1]) {
            newText += filler_matrix.back();
        } else if (i + 1 < formatted.length()) {
            newText += formatted[i + 1];
            ++i;
        }
    }

    if (newText.length() % 2 != 0) {
        newText += 'X';
    }

    return newText;
}

string encryptPair(const vector<vector<char>>& matrix, char a, char b) {
    pair<int, int> pos1 = findPosition(matrix, a);
    pair<int, int> pos2 = findPosition(matrix, b);

    if (pos1.first == pos2.first) {
        return string(1, matrix[pos1.first][(pos1.second + 1) % 5]) + matrix[pos2.first][(pos2.second + 1) % 5];
    } else if (pos1.second == pos2.second) {
        return string(1, matrix[(pos1.first + 1) % 5][pos1.second]) + matrix[(pos2.first + 1) % 5][pos2.second];
    } else {
        return string(1, matrix[pos1.first][pos2.second]) + matrix[pos2.first][pos1.second];
    }
}

string playfairEncrypt(const string& plaintext, const string& key) {
    auto matrix = createMatrix(key);
    auto formattedText = formatText(plaintext);
    string cipherText;

    for (size_t i = 0; i < formattedText.length(); i += 2) {
        cipherText += encryptPair(matrix, formattedText[i], formattedText[i + 1]);
    }

    return cipherText;
}

void printMatrix(const vector<vector<char>>& matrix) {
    for (const auto& row : matrix) {
        for (char c : row) {
            cout << c << " ";
        }
        cout << endl;
    }
}

int main() {
    string key, plaintext;

    cout << "Enter the key: ";
    getline(cin, key);
    cout << "Enter the plaintext: ";
    getline(cin, plaintext);

    // Convert key and plaintext to uppercase
    transform(key.begin(), key.end(), key.begin(), ::toupper);
    transform(plaintext.begin(), plaintext.end(), plaintext.begin(), ::toupper);

    auto matrix = createMatrix(key);
    printMatrix(matrix);

    cout << "Bogus Char = " << filler_matrix.back() << endl;
    for (char c : filler_matrix) {
        cout << c << " ";
    }
    cout << endl;

    string formattedText = formatText(plaintext);
    cout << "Formatted Text: " << formattedText << endl;

    string encryptedText = playfairEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encryptedText << endl;

    return 0;
}
