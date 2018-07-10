#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e5, LOG = 50;
int cnt, lc[MAXN * LOG + 10], rc[MAXN * LOG + 10], sz[MAXN * LOG + 10], val[MAXN * LOG + 10], r[MAXN * LOG + 10];
int rt[MAXN + 10];

inline int newnode(int v = 0) {
    ++cnt;
    lc[cnt] = rc[cnt] = 0;
    sz[cnt] = 1;
    val[cnt] = v;
    r[cnt] = rand();
    return cnt;
}

inline void copy_node(int dest, int src) {
    dest[lc] = src[lc], dest[rc] = src[rc];
    dest[sz] = src[sz], dest[val] = src[val];
    dest[r] = src[r];
}

void split(int o, int v, int &a, int &b) {
    if(!o) a = b = 0;
    else {
        if(v < val[o]) {
            b = newnode();
            copy_node(b, o);
            split(lc[o], v, a, lc[b]);
            sz[b] = sz[lc[b]] + sz[rc[b]] + 1;
        } else {
            a = newnode();
            copy_node(a, o);
            split(rc[o], v, rc[a], b);
            sz[a] = sz[lc[a]] + sz[rc[a]] + 1;
        }
    }
}

int merge(int a, int b) {
    if(!a && !b) {
        return 0;
    } else {
        int o = newnode();
        if(!a || !b) {
            copy_node(o, a|b);
            return o;
        } else {
            if(r[a] < r[b]) {
                copy_node(o, a);
                rc[o] = merge(rc[o], b);
            } else {
                copy_node(o, b);
                lc[o] = merge(a, lc[o]);
            }
            sz[o] = sz[lc[o]] + sz[rc[o]] + 1;
            return o;
        }
    }
}

inline void insert(int v, int &o, int his) {
    int a, b, c;
    split(his, v, b, c), split(b, v-1, a, b);
    o = merge(a, merge(newnode(v), merge(b, c)));
}

inline void erase(int v, int &o, int his) {
    int a, b, c;
    split(his, v, b, c), split(b, v-1, a, b);
    o = merge(a, merge(merge(lc[b], rc[b]), c));
}

inline int get_rank(int o, int v) {
    int ret = 1;
    while(o) {
        if(val[o] < v) {
            ret += sz[lc[o]] + 1;
            o = rc[o];
        } else o = lc[o];
    }
    return ret;
}

inline int kth(int o, int k) {
    while(k != sz[lc[o]] + 1) {
        if(k < sz[lc[o]] + 1) o = lc[o];
        else {
            k -= sz[lc[o]] + 1;
            o = rc[o];
        }
    }
    return val[o];
}

inline int suc(int o, int v) {
    int ret = 2147483647;
    while(o) {
        if(val[o] > v) {
            ret = val[o]; o = lc[o];
        } else o = rc[o];
    }
    return ret;
}

inline int prv(int o, int v) {
    int ret = -2147483647;
    while(o) {
        if(val[o] < v) {
            ret = val[o]; o = rc[o];
        } else o = lc[o];
    }
    return ret;
}

int q, op;

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

int main() {
    srand(time(NULL));
    q = readint();

    for(int cur = 1; cur <= q; cur++) {
        int his, op, x;
        his = readint(), op = readint(), x = readint();
        rt[cur] = rt[his];
        switch(op) {
            case 1:
                insert(x, rt[cur], rt[his]); break;
            case 2:
                erase(x, rt[cur], rt[his]); break;
            case 3:
                cout << get_rank(rt[cur], x) << '\n'; break;
            case 4:
                cout << kth(rt[cur], x) << '\n'; break;
            case 5:
                cout << prv(rt[cur], x) << '\n'; break;
            case 6:
                cout << suc(rt[cur], x) << '\n'; break;
        }
    }
    return 0;
}