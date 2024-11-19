#include <iostream>
#include <algorithm>
#include <string>

using namespace std;

string generateKey(const string& str, const string& key) {
    string extended_key = key;
    while (extended_key.size() < str.size()) {
        extended_key += key;
    }
    return extended_key.substr(0, str.size());
}

string cipherText(const string& text, const string& key) {
    string cipher_text;
    for (size_t i = 0; i < text.size(); ++i) {
        char x = (text[i] + key[i] - 2 * 'A') % 26 + 'A';
        cipher_text += x;
    }
    return cipher_text;
}

string originalText(const string& cipher_text, const string& key) {
    string orig_text;
    for (size_t i = 0; i < cipher_text.size(); ++i) {
        char x = (cipher_text[i] - key[i] + 26) % 26 + 'A';
        orig_text += x;
    }
    return orig_text;
}

int main() {
    string str, keyword;

    cout << "Enter the plaintext: ";
    getline(cin, str);
    cout << "Enter the keyword: ";
    getline(cin, keyword);

    str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
    keyword.erase(remove_if(keyword.begin(), keyword.end(), ::isspace), keyword.end());
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    transform(keyword.begin(), keyword.end(), keyword.begin(), ::toupper);

    string key = generateKey(str, keyword);
    string cipher_text = cipherText(str, key);
    string decrypted_text = originalText(cipher_text, key);

    cout << "Ciphertext: " << cipher_text << "\n";
    cout << "Original/Decrypted Text: " << decrypted_text << "\n";

    return 0;
}
