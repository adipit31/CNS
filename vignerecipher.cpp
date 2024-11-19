#include <iostream>
#include <string>
#include <cctype>
using namespace std;

class VigenereCipher {
private:
    string plaintext;
    string ciphertext;
    string keyword;

public:
    VigenereCipher() : plaintext(""), ciphertext(""), keyword("") {}

    string encryption(const string &plain, const string &key) {
        plaintext = plain;
        keyword = key;
        ciphertext = "";

        // Adjust keyword length to match plaintext
        while (keyword.size() < plaintext.size())
            keyword += key;
        keyword = keyword.substr(0, plaintext.size());

        for (size_t i = 0; i < plaintext.size(); ++i) {
            char v = tolower(plaintext[i]);
            if (isalpha(v)) {
                int shift = (v - 'a' + tolower(keyword[i]) - 'a') % 26;
                ciphertext += char(shift + 'A'); // Convert to uppercase
            } else {
                ciphertext += v;
            }
        }
        return ciphertext;
    }

    string decryption(const string &cipher, const string &key) {
        ciphertext = cipher;
        keyword = key;
        plaintext = "";

        // Adjust keyword length to match ciphertext
        while (keyword.size() < ciphertext.size())
            keyword += key;
        keyword = keyword.substr(0, ciphertext.size());

        for (size_t i = 0; i < ciphertext.size(); ++i) {
            char v = toupper(ciphertext[i]);
            if (isalpha(v)) {
                int shift = (v - 'A' - (tolower(keyword[i]) - 'a') + 26) % 26;
                plaintext += char(shift + 'a'); // Convert to lowercase
            } else {
                plaintext += v;
            }
        }
        return plaintext;
    }
};

int main() {
    VigenereCipher vc;
    string plaintext, keyword, encrypted, decrypted;

    cout << "Enter plaintext: ";
    getline(cin, plaintext);
    cout << "Enter keyword: ";
    getline(cin, keyword);

    encrypted = vc.encryption(plaintext, keyword);
    cout << "Encrypted text: " << encrypted << endl;

    cout << "Enter ciphertext to decrypt: ";
    getline(cin, encrypted);
    cout << "Enter keyword for decryption: ";
    getline(cin, keyword);

    decrypted = vc.decryption(encrypted, keyword);
    cout << "Decrypted text: " << decrypted << endl;

    return 0;
}
