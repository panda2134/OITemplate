#include <bits/stdc++.h>
using namespace std;
const int MAXN = 3e6;
int n, p, inv[MAXN+10];
int main() {
    cin >> n >> p;
    inv[1] = 1; printf("%d\n", inv[1]);
    for(int i = 2; i <= n; i++) 
        printf("%d\n", inv[i] = (p - (long long)(p / i) * inv[p % i] % p) % p);
    return 0;
}
