#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5;

int n, q, a[MAXN+10];

inline int lowbit(int x) { return x & (-x); }

void add(int p, int val) {
    while(p <= n) {
        a[p] += val;
        p += lowbit(p);
    }
}

int query(int p) {
    int ret = 0;
    while(p > 0) {
        ret += a[p];
        p -= lowbit(p);
    }
    return ret;
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

int main() {
    n = readint(); q = readint();
    for(int i = 1; i <= n; i++)
        add(i, readint());
    while(q--) {
        int op, x, y;
        op = readint(); x = readint(); y = readint();
        switch(op) {
            case 1:
                add(x, y);
                break;
            case 2:
                printf("%d\n", query(y) - query(x-1));
                break;
        }
    }
    return 0;
}
