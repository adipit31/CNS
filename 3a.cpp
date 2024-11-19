#include<bits/stdc++.h>
using namespace std;

tuple<int, int, int> EEA(int a, int b) {
    int r1 = a, r2 = b;
    int t1 = 0, t2 = 1;
    int s1 = 1, s2 = 0;

    cout << string(70, '-') << endl;
    cout << "|" << setw(6) << "q" << "|" << setw(6) << "r1" << "|" << setw(6) << "r2" << "|" << setw(6) << "r" 
         << "|" << setw(6) << "t1" << "|" << setw(6) << "t2" << "|" << setw(6) << "t" << "|" << setw(6) << "s1" 
         << "|" << setw(6) << "s2" << "|" << setw(6) << "s" << "|" << endl;
    cout << string(70, '-') << endl;

    while (r2 > 0) {
        int q = r1 / r2;
        cout << "|" << setw(6) << q << "|" << setw(6) << r1 << "|" << setw(6) << r2 << "|";

        int r = r1 - q * r2;
        r1 = r2;
        r2 = r;
        cout << setw(6) << r << "|";

        cout << setw(6) << t1 << "|" << setw(6) << t2 << "|";
        int t = t1 - q * t2;
        t1 = t2;
        t2 = t;
        cout << setw(6) << t << "|";

        cout << setw(6) << s1 << "|" << setw(6) << s2 << "|";
        int s = s1 - q * s2;
        s1 = s2;
        s2 = s;
        cout << setw(6) << s << "|" << endl;
    }

    cout << "|" << setw(6) << " " << "|" << setw(6) << r1 << "|" << setw(6) << r2 << "|" << setw(6) << " " 
         << "|" << setw(6) << t1 << "|" << setw(6) << t2 << "|" << setw(6) << " " 
         << "|" << setw(6) << s1 << "|" << setw(6) << s2 << "|" << setw(6) << " " << "|" << endl;
    cout << string(70, '-') << endl;

    return make_tuple(r1, t1, s1);
}

int main() {
   
    int a, b;
    cout << "Enter A: ";
    cin >> a;
    cout << "Enter B: ";
    cin >> b;

    auto result = EEA(a, b);
    cout << "GCD(" << a << "," << b << ") = " << get<0>(result) << endl;
    cout << "Coefficients of Bezout's Identity:" ;
    cout << "t: " << get<1>(result)<<",";
    cout << "s: " << get<2>(result) << endl;
    

    return 0;
}
