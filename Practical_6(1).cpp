#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

typedef vector<vector<unsigned char>> Matrix;

// S-Box
unsigned char SBox[16][16] = {
    {0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5, 0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76},
    {0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0, 0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0},
    {0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC, 0x34, 0xA5, 0xE5, 0xE3, 0x7A, 0xD3, 0xD2, 0xE0},
    {0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A, 0x07, 0x12, 0x80, 0x2B, 0x3A, 0x4D, 0x9D, 0xFC},
    {0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0x52, 0x3B, 0x29, 0xE3, 0xE2, 0x84, 0x45, 0x2A, 0xA1},
    {0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x61, 0x6A, 0xCB, 0x39, 0x4C, 0x58, 0xB5, 0xBC, 0xA6},
    {0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85, 0xF9, 0x02, 0x7F, 0x50, 0x7B, 0xA3, 0x9F, 0xA8}
};

// RCon
unsigned char Rcon[10] = {0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36};

// Helper function to print the matrix
void printMatrix(const Matrix &matrix) {
    for (const auto &row : matrix) {
        for (unsigned char value : row) {
            cout << hex << setw(2) << setfill('0') << static_cast<int>(value) << " ";
        }
        cout << endl;
    }
}

// Key expansion function
Matrix KeyExpansion(const vector<unsigned char> &key) {
    Matrix expandedKey(44, vector<unsigned char>(4));
    
    for (int i = 0; i < 4; i++) {
        expandedKey[i][0] = key[i * 4];
        expandedKey[i][1] = key[i * 4 + 1];
        expandedKey[i][2] = key[i * 4 + 2];
        expandedKey[i][3] = key[i * 4 + 3];
    }

    for (int i = 4; i < 44; i++) {
        vector<unsigned char> temp(4);
        temp[0] = expandedKey[i - 1][0];
        temp[1] = expandedKey[i - 1][1];
        temp[2] = expandedKey[i - 1][2];
        temp[3] = expandedKey[i - 1][3];

        if (i % 4 == 0) {
            // Rotate
            unsigned char t = temp[0];
            temp[0] = temp[1];
            temp[1] = temp[2];
            temp[2] = temp[3];
            temp[3] = t;

            // SubWord
            for (int j = 0; j < 4; j++) {
                temp[j] = SBox[temp[j] >> 4][temp[j] & 0x0F];
            }

            temp[0] ^= Rcon[i / 4 - 1];
        }

        for (int j = 0; j < 4; j++) {
            expandedKey[i][j] = expandedKey[i - 4][j] ^ temp[j];
        }
    }
    
    return expandedKey;
}

// AES encryption function
Matrix AES_Encrypt(const Matrix &state, const Matrix &key) {
    Matrix currentState = state;
    
    // AddRoundKey
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            currentState[c][r] ^= key[r + 4 * 0][c];
        }
    }

    for (int round = 1; round <= 10; round++) {
        // SubBytes
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                currentState[r][c] = SBox[currentState[r][c] >> 4][currentState[r][c] & 0x0F];
            }
        }

        // ShiftRows
        for (int r = 1; r < 4; r++) {
            vector<unsigned char> temp = currentState[r];
            for (int c = 0; c < 4; c++) {
                currentState[r][c] = temp[(c + r) % 4];
            }
        }

        // MixColumns (only in rounds 1 to 9)
        if (round < 10) {
            for (int c = 0; c < 4; c++) {
                unsigned char a[4];
                unsigned char b[4];

                for (int r = 0; r < 4; r++) {
                    a[r] = currentState[r][c];
                    b[r] = (currentState[r][c] << 1) ^ ((currentState[r][c] & 0x80) ? 0x1B : 0x00);
                }

                currentState[0][c] = b[0] ^ a[1] ^ a[2] ^ b[3];
                currentState[1][c] = a[0] ^ b[1] ^ a[2] ^ a[3];
                currentState[2][c] = a[0] ^ a[1] ^ b[2] ^ a[3];
                currentState[3][c] = a[0] ^ a[1] ^ a[2] ^ b[3];
            }
        }

        // AddRoundKey
        for (int r = 0; r < 4; r++) {
            for (int c = 0; c < 4; c++) {
                currentState[r][c] ^= key[r + 4 * round][c];
            }
        }
    }

    return currentState;
}

int main() {
    // Example 7.6
    vector<unsigned char> key = {
        0x24, 0x75, 0xA2, 0xB3,
        0x34, 0x75, 0x56, 0x88,
        0x31, 0xE2, 0x12, 0x00,
        0x13, 0xAA, 0x54, 0x87
    };

    Matrix expandedKey = KeyExpansion(key);

    // Example 7.6 Key Expansion Output
    cout << "Round Keys for Example 7.6:\n";
    for (int i = 0; i < 11; i++) {
        cout << "Round " << i << " key:\n";
        printMatrix(Matrix(expandedKey.begin() + i * 4, expandedKey.begin() + (i + 1) * 4));
    }

    // Example 7.9
    cout << "\nExample 7.9:\n";
    Matrix plaintext1 = {
        {0x00, 0x04, 0x12, 0x14},
        {0x12, 0x04, 0x12, 0x00},
        {0x0C, 0x00, 0x13, 0x11},
        {0x08, 0x23, 0x19, 0x19}
    };

    Matrix ciphertext1 = AES_Encrypt(plaintext1, expandedKey);
    cout << "Ciphertext 1: ";
    printMatrix(ciphertext1);

    // Example 7.10
    cout << "\nExample 7.10:\n";
    Matrix plaintext2 = {
        {0x00, 0x12, 0x0C, 0x08},
        {0x04, 0x04, 0x00, 0x23},
        {0x12, 0x12, 0x13, 0x19},
        {0x14, 0x00, 0x11, 0x19}
    };

    Matrix ciphertext2 = AES_Encrypt(plaintext2, expandedKey);
    cout << "Ciphertext 2: ";
    printMatrix(ciphertext2);

    // Example 7.13
    cout << "\nExample 7.13 (Avalanche Effect):\n";
    Matrix avalanchePlaintext1 = {
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00}
    };

    Matrix avalanchePlaintext2 = {
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x00},
        {0x00, 0x00, 0x00, 0x01}
    };

    Matrix avalancheCiphertext1 = AES_Encrypt(avalanchePlaintext1, expandedKey);
    Matrix avalancheCiphertext2 = AES_Encrypt(avalanchePlaintext2, expandedKey);

    cout << "Ciphertext 1: ";
    printMatrix(avalancheCiphertext1);
    cout << "Ciphertext 2: ";
    printMatrix(avalancheCiphertext2);

    // Example 7.14
    cout << "\nExample 7.14 (All-Zero Key):\n";
    Matrix allZeroKey(16, vector<unsigned char>(1, 0x00));
    Matrix plaintext3 = {
        {0x00, 0x04, 0x12, 0x14},
        {0x12, 0x04, 0x12, 0x00},
        {0x0C, 0x00, 0x13, 0x11},
        {0x08, 0x23, 0x19, 0x19}
    };

    // All-zero key
    vector<unsigned char> zeroKey(16, 0x00);
    Matrix zeroKeyExpanded = KeyExpansion(zeroKey);

    Matrix ciphertext3 = AES_Encrypt(plaintext3, zeroKeyExpanded);
    cout << "Ciphertext: ";
    printMatrix(ciphertext3);

    return 0;
}
