#include <bits/stdc++.h>
#define Mid(x, y) (((x) + (y)) >> 1)
using namespace std;

const int MAXN = 1e6, BKT = 4e7;

int n, q, cnt, ver, w[MAXN+10], rt[MAXN+10], lc[BKT], rc[BKT], v[BKT];

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

void build_tree(int &o, int L, int R) {
    o = ++cnt;
    if(L == R) v[o] = w[L];
    else {
        build_tree(lc[o], L, Mid(L, R));
        build_tree(rc[o], Mid(L, R)+1, R);
    }
}

void modify(int &o, int his, int L, int R, int p, int val) {
    o = ++cnt;
    if(L == R) v[o] = val;
    else {
        if(p <= Mid(L, R)) {
            rc[o] = rc[his];
            modify(lc[o], lc[his], L, Mid(L, R), p, val);
        } else {
            lc[o] = lc[his];
            modify(rc[o], rc[his], Mid(L, R)+1, R, p, val);
        }
    }
}

int query(int o, int L, int R, int p) {
    if(!o) return 0;
    if(L == R) return v[o];
    else {
        if(p <= Mid(L, R))
            return query(lc[o], L, Mid(L, R), p);
        else
            return query(rc[o], Mid(L, R)+1, R, p);
    }
}

void init() {
    n = readint(); q = readint();
    for(int i = 1; i <= n; i++)
        w[i] = readint();
    build_tree(rt[++ver], 1, n);
}

void work() {
    int op, prv, idx, val;
    while(q--) {
        ++ver;
        prv = readint() + 1;
        op = readint();
        switch(op) {
            case 1:
                idx = readint(); val = readint();
                modify(rt[ver], rt[prv], 1, n, idx, val);
                break;
            case 2:
                idx = readint();
                printf("%d\n", query(rt[prv], 1, n, idx));
                rt[ver] = rt[prv];
                break;
        }
    }
}

int main() {
    init(); work();
    return 0;
}