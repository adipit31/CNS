#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

void displayKey(const vector<int>& key) {
    for (int i : key) {
        cout << i << ' ';
    }
    cout << endl;
}

vector<int> invertKey(const vector<int>& key) {
    int n = key.size();
    vector<pair<int, int>> keyWithIndex(n);

    for (int i = 0; i < n; ++i) {
        keyWithIndex[i] = { key[i], i };
    }

    sort(keyWithIndex.begin(), keyWithIndex.end());

    vector<int> invertedKey(n);
    for (int i = 0; i < n; ++i) {
        invertedKey[keyWithIndex[i].second] = i + 1;
    }

    return invertedKey;
}

int main() {
    int n;
    cout << "Enter the number of elements in the key: ";
    cin >> n;

    vector<int> key(n);
    cout << "Enter the key elements: ";
    for (int i = 0; i < n; ++i) {
        cin >> key[i];
    }

    cout << "Original Key: ";
    displayKey(key);

    vector<int> invertedKey = invertKey(key);

    cout << "Inverted Key: ";
    displayKey(invertedKey);

    return 0;
}
