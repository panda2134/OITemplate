#include <bits/stdc++.h>
using namespace std;
const int MAXP = 1e7;

int T, p, phi[MAXP+10];

void InitPhi() {
    phi[1] = 1; //do not set phi[2], for it is a prime
    for(int i=2; i<=MAXP; i++)
        if(!phi[i]) {
            for(int j=i; j<=MAXP; j+=i) {
                if(!phi[j]) phi[j] = j; 
                phi[j] = phi[j] / i * (i-1);
            }
        }
}

inline int fastmul(int a, int x, int mod) {
    int ret = 0;
    while(x) {
        if(x&1) ret = ((ret%mod) + (a%mod))%mod;
        x>>=1; a = ((a%mod) + (a%mod)) %mod;
    }
    return ret;
}

inline int fastpow(int a, int x, int mod) {
    int ret = 1;
    while(x) {
        if(x&1) ret = fastmul(ret, a, mod) % mod;
        x>>=1; a = fastmul(a, a, mod) % mod;
    }
    return ret;
}

int solve(int mod) {
    if(mod == 1) return 0;
    return fastpow(2, solve(phi[mod])+phi[mod], mod);
}

int main() {
    InitPhi();
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &p);
        printf("%d\n", solve(p));
    }
}