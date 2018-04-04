#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

int n, q, a[MAXN+10], st[MAXN+10][22];

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

void init_st() {
    for(int i = 1; i <= n; i++) st[i][0] = a[i];
    for(int j = 1; j <= 20; j++)
        for(int i = 1; i <= n - (1<<j) + 1; i++)
            st[i][j] = max(st[i][j-1], st[i+(1<<(j-1))][j-1]);
}

int query(int L, int R) {
    if(L > R) return 0;
    int j;
    for(j = 0; (1<<(j+1)) <= (R-L+1); j++);
    return max(st[L][j], st[R-(1<<j)+1][j]);
}

int main() {
    int l, r;
    n = readint(); q = readint();
    for(int i = 1; i <= n; i++) a[i] = readint();
    init_st();
    while(q--) {
        l = readint(); r = readint();
        printf("%d\n", query(l, r));
    }
    return 0;
}
