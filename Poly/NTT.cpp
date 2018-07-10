#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
const int MAXN = 4e6, MOD = 998244353, G = 3;

int n, m, A[MAXN+10], B[MAXN+10], C[MAXN+10], R[MAXN+10];

int64 fastpow(int64 a, int64 x) {
    int64 ret = 1; a %= MOD;
    while(x) { 
        if(x & 1) ret = ret * a % MOD;
        x >>= 1; a = a * a % MOD;
    }
    return ret;
}

int get_rt(int step, bool inv) {
    return !inv ? fastpow(G, (MOD-1) / step) : fastpow(G, (MOD-1) / step * (step-1));
}

void ntt(int A[], int len, bool inv) {
    for(int i = 0; i < len; i++)
        if(R[i] > i) swap(A[R[i]], A[i]);
    for(int step = 1; step < len; step <<= 1) {
        for(int i = 0; i < len; i += (step << 1)) {
            int64 omega = 1, rt = get_rt(step << 1, inv);
            for(int j = 0; j < step; j++, omega = (omega * rt) % MOD) {
                int t = omega * A[i+j+step] % MOD;
                A[i+j+step] = ((A[i+j] - t) % MOD + MOD) % MOD;
                A[i+j] = (A[i+j] + t) % MOD;
            }
        }
    }
    if(inv) {
        int64 inv_ele = fastpow(len, MOD-2);
        for(int i = 0; i < len; i++) A[i] = (A[i] * inv_ele) % MOD;
    }
}

void conv(int A[], int B[], int deg1, int deg2, int C[]) {
    int len; for(len = 1; len < deg1+deg2+1; len <<= 1);
    R[0] = 0;
    for(int i = 1; i < len; i++)
        R[i] = ((R[i>>1]>>1) | (len >> (i & 1))) & (len-1);
    ntt(A, len, false); ntt(B, len, false);
    for(int i = 0; i < len; i++) C[i] = int64(A[i]) * B[i] % MOD;
    ntt(A, len, true); ntt(B, len, true); ntt(C, len, true);
}

template<typename T>
inline void readint(T &x) {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    x = f*r;
}

template<typename T>
inline void writeint(T &x) {
    static char buf[32];
    char *ptr = buf;
    if(x < 0) putchar('-'), x = -x;
    do {
        *ptr++ = (x % 10) + '0';
        x /= 10;
    } while(x);
    do
        putchar(*--ptr);
    while(ptr != buf);
}

int main() {
    readint(n); readint(m);
    for(int i = 0; i <= n; i++) readint(A[i]);
    for(int i = 0; i <= m; i++) readint(B[i]);
    conv(A, B, n, m, C);
    for(int i = 0; i <= n+m; i++) writeint(C[i]), putchar(' ');
    return 0;
}
