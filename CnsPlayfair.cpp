#include<iostream>
#include<bits/stdc++.h>
#include<unordered_set>

using namespace std;

vector<vector<char>> createMatrix(string key) {
    vector<char> matrix;
    unordered_set<char> used_chars;
    string alphabet = "ABCDEFGHIKLMNOPQRSTUVWXYZ";

    for (char& c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (used_chars.find(c) == used_chars.end() && alphabet.find(c) != string::npos) {
            matrix.push_back(c);
            used_chars.insert(c);
        }
    }

    for (char c : alphabet) {
        if (used_chars.find(c) == used_chars.end()) {
            matrix.push_back(c);
            used_chars.insert(c);
        }
    }

    vector<vector<char>> finalMatrix(5, vector<char>(5));
    for (int i = 0; i < 25; ++i) {
        finalMatrix[i / 5][i % 5] = matrix[i];
    }

    return finalMatrix;
}

pair<int, int> findPosition(vector<vector<char>>& matrix, char c) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 5; ++j) {
            if (matrix[i][j] == c) {
                return make_pair(i, j);
            }
        }
    }
    return make_pair(-1, -1);
}

string formatText(string text) {
    for (char& c : text) {
        c = toupper(c);
        if (c == 'J') c = 'I';
    }

    string newText;
    int i = 0;
    while (i < text.length()) {
        newText += text[i];
        if (i + 1 < text.length() && text[i] == text[i + 1]) {
            newText += 'X';
        } else if (i + 1 < text.length()) {
            newText += text[i + 1];
            ++i;
        }
        ++i;
    }

    if (newText.length() % 2 != 0) {
        newText += 'X';
    }

    return newText;
}

string encryptPair(vector<vector<char>>& matrix, string pair) {
    auto [row1, col1] = findPosition(matrix, pair[0]);
    auto [row2, col2] = findPosition(matrix, pair[1]);

    if (row1 == row2) {
        return string(1, matrix[row1][(col1 + 1) % 5]) + matrix[row2][(col2 + 1) % 5];
    } else if (col1 == col2) {
        return string(1, matrix[(row1 + 1) % 5][col1]) + matrix[(row2 + 1) % 5][col2];
    } else {
        return string(1, matrix[row1][col2]) + matrix[row2][col1];
    }
}

string playfairEncrypt(string plaintext, string key) {
    vector<vector<char>> matrix = createMatrix(key);
    string preparedText = formatText(plaintext);
    string cipherText;

    for (int i = 0; i < preparedText.length(); i += 2) {
        cipherText += encryptPair(matrix, preparedText.substr(i, 2));
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
    string key = "monarchy";
    string plaintext = "instruments";

    vector<vector<char>> matrix = createMatrix(key);
    printMatrix(matrix);

    string formattedText = formatText(plaintext);
    cout << "Formatted Text: " << formattedText << endl;

    string encryptedText = playfairEncrypt(plaintext, key);
    cout << "Encrypted Text: " << encryptedText << endl;

    return 0;
}
