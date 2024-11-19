#include <iostream>
using namespace std;

void processText(string text, int k, bool encryptMode) {
    if (text.empty()) {
        cout << "Enter Something" << endl;
        return;
    }

    string result;
    int processedText[100];
    
    for(int i = 0; i < text.length(); i++) {
        if (encryptMode) {
            processedText[i] = (int(text[i]) - 97 + k) % 26;  
            result += char(processedText[i] + 97); 
        } else {
            processedText[i] = (int(text[i]) - 97 - k + 26) % 26;  
            result += char(processedText[i] + 97);  
        }
    }
    
    if (encryptMode) {
        cout << "Cipher Text: " << result << endl;
    } else {
        cout << "Plain Text: " << result << endl;
    }
}

int main() {
    cout << "Select cipher type: \n";
    cout << "1. Caesar Cipher\n";
    cout << "2. Modified Caesar Cipher\n";
    int cipherChoice;
    cin >> cipherChoice;

    if (cipherChoice != 1 && cipherChoice != 2) 
    {
        cout << "Invalid choice" << endl;
        return 1;
    }

    bool isCaesar = (cipherChoice == 1);
    int key = 0;

    if (isCaesar) {
        key = 3;
    } else {
        cout << "Enter value of k for Modified Caesar Cipher: ";
        cin >> key;
    }

    cout << "Select operation: \n";
    cout << "1. Encrypt\n";
    cout << "2. Decrypt\n";
    int operationChoice;
    cin >> operationChoice;

    if (operationChoice != 1 && operationChoice != 2) {
        cout << "Invalid choice" << endl;
        return 1;
    }

    cin.ignore();  // To ignore the newline character left by cin
    
    cout << "Enter text: ";
    string text;
    getline(cin, text);

    bool encryptMode = (operationChoice == 1);

    processText(text, key, encryptMode);

    return 0;
}


