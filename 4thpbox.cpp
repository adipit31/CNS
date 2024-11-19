#include <bits/stdc++.h>
using namespace std;

vector<int> pBox(const vector<int>& inputBits, const vector<int>& table, int n, int m) {
    vector<int> outputBits(n);
    int i = 1;
    while (i <= m) {
        outputBits[i - 1] = inputBits[table[i - 1] - 1];
        i++;
    }
    return outputBits;
}

int main() {
    int n, m;
    cout << "Enter the number of bits (n): ";
    cin >> n;
    
    cout << "Enter the number of positions to permute (m): ";
    cin >> m;

    vector<int> inputBits(n), table(m);

    cout << "Enter " << n << " input bits (0 or 1): ";
    for (int i = 0; i < n; i++) {
        cin >> inputBits[i];
    }

    cout << "Enter " << m << " positions for the table (1-based indexing): ";
    for (int i = 0; i < m; i++) {
        cin >> table[i];
    }

    vector<int> outputBits = pBox(inputBits, table, n, m);

    cout << "Output bits after P-box permutation: ";
    for (int bit : outputBits) {
        cout << bit << " ";
    }
    cout << endl;

    return 0;
}
