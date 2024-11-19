#include <bits/stdc++.h>
using namespace std;

string swapWord(string word, int n) {
    if (n % 2 != 0) {
        word += '0';  
        n++;
    }

    string temp = word;  
    int i = 0;

    while (i < n / 2) {
        
        temp[i + n / 2] = word[i];
        temp[i] = word[i + n / 2];
        i++;
    }

    return temp;
}

int main() {
    string word;
    cout << "Enter a word: ";
    cin >> word;

    int n = word.size();
    string result = swapWord(word, n);

    cout << "Swapped word: " << result << endl;

    return 0;
}
