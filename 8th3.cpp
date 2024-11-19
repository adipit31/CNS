#include <bits/stdc++.h>
using namespace std;

int GCD(int a, int b) {
    if (b == 0)
        return a == 1;
    else
        return GCD(b, a % b);
}

int modular_inverse(int a, int m) {
    int m0 = m, t1 = 0, t2 = 1;
    if (m == 1) return 0;

    while (a > 1) {
        int q = a / m;
        int temp = m;
        m = a % m;-+
        a = temp;
        int t = t1;
        t1 = t2 - q * t1;
        t2 = t;
    }

    if (t2 < 0)
        t2 += m0;

    return t2;
}

// Modular exponentiation function to avoid overflow
int modular_exponentiation(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

void RSA(int p, int q, int msg) {
    int n = p * q;
    int phi = (p - 1) * (q - 1);

    int e = 2;
    while (e < phi) {
        if (GCD(e, phi))
            break;
        else
            e++;
    }

    int d = modular_inverse(e, phi);

    cout << "Public key  (e, n): (" << e << ", " << n << ")" << endl;
    cout << "Private key (d, n): (" << d << ", " << n << ")" << endl;

    cout << "Original message : " << msg << endl;

    int C = modular_exponentiation(msg, e, n);  // Encryption
    cout << "Encrypted message: " << C << endl;

    int M = modular_exponentiation(C, d, n);    // Decryption
    cout << "Decrypted message: " << M << endl;
}

int main() {
    int p, q, msg;
    cout << "Enter prime numbers p and q: ";
    cin >> p >> q;
    cout << "Enter the message to encrypt: ";
    cin >> msg;

    RSA(p, q, msg);

    return 0;
}

