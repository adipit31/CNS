#include <bits/stdc++.h>
using namespace std;

// Function to compute GCD
bool gcd(int a, int b) {
    if (b == 0) return a == 1;
    return gcd(b, a % b);
}

// Euler Totient Function (ETF)
int ETF(int number) {
    int count = 0;
    for (int i = 1; i < number; ++i) {
        if (gcd(number, i)) count++;
    }
    return count;
}

// Function to perform modular exponentiation: (base^exp) % mod
int modExp(int base, int exp, int mod) {
    int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

// Fermat's Little Theorem (FLT)
int FLT(int a, int p) {
    if (gcd(a, p) == 1) {
        return modExp(a, p - 1, p);
    }
    return 0;
}

// Euler's Theorem (ET)
int ET(int num, int mod) {
    if (gcd(num, mod)) {
        int etf_val = ETF(mod);
        return modExp(num, etf_val, mod);
    }
    return -1;
}

int main() {
    int choice;
    while (true) {
        cout << "\nPress:\n  1 -> Euler Totient Function\n  2 -> Fermat Little Theorem\n  3 -> Euler Theorem\nEnter your choice: ";
        cin >> choice;
        
        switch (choice) {
            case 1: {
                int number;
                cout << "Enter a Number: ";
                cin >> number;
                cout << "Euler Totient of Φ(" << number << ") : " << ETF(number) << endl;
                break;
            }
            case 2: {
                int a, p;
                cout << "Enter a: ";
                cin >> a;
                cout << "Enter p (a prime number): ";
                cin >> p;
                int result = FLT(a, p);
                if (result == 1)
                    cout << "Fermat's Little Theorem holds true for a=" << a << " and p=" << p << endl;
                else
                    cout << "Does NOT follow Fermat's Little Theorem for a=" << a << " and p=" << p << endl;
                break;
            }
            case 3: {
                int num, mod;
                cout << "Enter Number: ";
                cin >> num;
                cout << "Enter moduli (a prime number): ";
                cin >> mod;
                int result = ET(num, mod);
                if (result != -1)
                    cout << "Euler's Theorem result for " << num << "^Φ(" << mod << ") % " << mod << " : " << result << endl;
                else
                    cout << "Euler's Theorem does not hold as gcd(" << num << ", " << mod << ") != 1" << endl;
                break;
            }
            default:
                return 0;
        }
    }
    return 0;
}
1
