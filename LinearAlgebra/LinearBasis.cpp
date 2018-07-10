#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long u64;

const int MAX_N = 50, MAX_BASE = 50;
int n;
u64 ans, a[MAX_N + 10], b[MAX_BASE + 10];

int main() {
    cin >> n;
    for(int i = 1; i <= n; i++) {
        cin >> a[i];
        for(int j = MAX_BASE; j >= 0; j--) {
            if(!((a[i] >> j) & 1)) continue;
            if(b[j]) a[i] ^= b[j];
            else {
                b[j] = a[i];
                for(int k = 0; k <= j-1; k++)
                    if((b[j] >> k) & 1) b[j] ^= b[k];
                for(int k = j+1; k <= MAX_BASE; k++)
                    if((b[k] >> j) & 1) b[k] ^= b[j];
                break;
            }
        }
    }
    for(int i = MAX_BASE; i >= 0; i--) ans ^= b[i];
    cout << ans;
    return 0;
}