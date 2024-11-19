#include<iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    vector<int> enkey;
    int num;
    cout << "Enter your key (space-separated integers): ";
    while (cin >> num) {
        enkey.push_back(num);
        if (cin.peek() == '\n') break;
    }

    vector<pair<int, int>> indexed_enkey;
    for (int i = 0; i < enkey.size(); ++i) {
        indexed_enkey.emplace_back(i + 1, enkey[i]);
    }

    vector<pair<int, int>> dekey = indexed_enkey;
    sort(dekey.begin(), dekey.end(), [](const auto& a, const auto& b) {
        return a.second < b.second;
    });

    cout << "Encryption Key: ";
    for (const auto& p : indexed_enkey) cout << p.second << " ";

    cout << "\nDecryption Key: ";
    for (const auto& p : dekey) cout << p.first << " ";

    return 0;
}
