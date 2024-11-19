#include <iostream>
#include <vector>

using namespace std;


int feistelFunction(int halfBlock, int roundKey) {
    return halfBlock ^ roundKey; 
}

pair<int, int> split(int inputBits, int n) {
    int left = inputBits >> (n / 2); 
    int right = inputBits & ((1 << (n / 2)) - 1); 
    return {left, right};
}

int combine(int left, int right, int n) {
    return (left << (n / 2)) | right;
}

int feistelRound(int inputBits, int roundKey, int n) {
    pair<int, int> splitResult = split(inputBits, n);
    int tempLeft = splitResult.first;
    int tempRight = splitResult.second;
    
    tempLeft = tempLeft ^ feistelFunction(tempRight, roundKey);
    swap(tempLeft, tempRight);
    
    return combine(tempLeft, tempRight, n);
}

int main() {
    int n, inputBits, roundKey1, roundKey2;

    cout << "Enter the number of bits (n): ";
    cin >> n;

    cout << "Enter the input bits (as decimal): ";
    cin >> inputBits;

    cout << "Enter the first round key: ";
    cin >> roundKey1;

    cout << "Enter the second round key: ";
    cin >> roundKey2;

    int result = feistelRound(inputBits, roundKey1, n);
    result = feistelRound(result, roundKey2, n);

    cout << "Encrypted bits after 2 rounds: " << result << endl;

    return 0;
}
