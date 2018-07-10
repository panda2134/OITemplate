#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
const int MAXN = 1e5;
int T, n, m, p, fact[MAXN+10], factinv[MAXN+10];

int C(int n, int m) {
    if(m < 0 || m > n) return 0;
    return ((int64)fact[n] * factinv[m]) % p * factinv[n-m] % p;
}

int lucas(int n, int m) {
    if(n < p && m < p) return C(n, m);
    return C(n % p, m % p) * (int64)lucas(n / p, m / p) % p;
}

inline int64 fastpow(int64 a, int64 x) {
    int64 ret = 1;
    while(x) {
        if(x & 1) ret = ret * a % p;
        x >>= 1; a = a * a % p;
    }
    return ret;
}

void init_inv() {
    fact[0] = factinv[0] = 1;
    for(int i = 1; i <= p-1; i++)
        fact[i] = (int64)fact[i-1] * i % p;
    factinv[p-1] = fastpow(fact[p-1], p-2);
    for(int i = p-2; i >= 1; i--)
        factinv[i] = factinv[i+1] * (int64)(i+1) % p;
}

int main() {
    cin >> T;
    while(T--) {
        cin >> n >> m >> p; init_inv();
        cout << lucas(n+m, m) << '\n';
    }
    return 0;
}