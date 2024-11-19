#include <bits/stdc++.h>
using namespace std;

int modular_inverse(int a, int m) {
    int m0 = m, t1 = 0, t2 = 1;
    if (m == 1) return 0;

    while (a > 1) {
        int q = a / m;
        int temp = m;
        m = a % m;
        a = temp;
        int t = t1;
        t1 = t2 - q * t1;
        t2 = t;
    }

    if (t2 < 0)
        t2 += m0;

    return t2;
}

int chinese_remainder(const vector<int>& modulus, const vector<int>& remainders) {
    int N = 1;
    for (int mod : modulus)
        N *= mod;

    int x = 0;
    for (size_t i = 0; i < modulus.size(); ++i) {
        int mod = modulus[i];
        int rem = remainders[i];
        int Ni = N / mod;
        int inverse = modular_inverse(Ni, mod);
        x += rem * Ni * inverse;
    }

    return x % N;
}

int main() {
    int n;
    cout << "Enter the number of equations: ";
    cin >> n;

    vector<int> modulus(n), remainders(n);
    cout << "Enter modulus values: ";
    for (int i = 0; i < n; ++i) {
        cin >> modulus[i];
    }

    cout << "Enter remainder values: ";
    for (int i = 0; i < n; ++i) {
        cin >> remainders[i];
    }

    int result = chinese_remainder(modulus, remainders);
    cout << "The solution is: " << result << endl;

    return 0;
}
