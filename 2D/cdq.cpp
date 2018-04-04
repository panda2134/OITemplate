#include <bits/stdc++.h>
#define fst first
#define snd second
using namespace std;

struct Point {
    int x, y, z, idx;
    bool operator<(const Point &rhs) const {
        return x == rhs.x ? 
        (
            y == rhs.y ? 
            z < rhs.z : y < rhs.y
        ) : x < rhs.x;
    }
    bool operator==(const Point &rhs) const {
        return x == rhs.x && y == rhs.y && z == rhs.z;
    }
};

struct Query {
    int x, y, z, idx, type;
    bool operator<(const Query &rhs) const {
        return y == rhs.y ? type < rhs.type : y < rhs.y;
    }
};

const int MAXN = 3e5;
map<Point, int> p_cnt;
int n, k, q_cnt, totv[MAXN+10], ans[MAXN+10], anscnt[MAXN+10], bit[MAXN+10];
Query qry[MAXN+10], T[MAXN+10];

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

void init() {
    int x, y, z;
    n = readint(); k = readint();
    for(int i = 1; i <= n; i++) {
        x = readint(); y = readint(); z = readint();
        p_cnt[(Point){ x, y, z, i }]++;
    }
    for(auto p : p_cnt) {
        totv[p.fst.idx] = p.snd; ans[p.fst.idx] = -p.snd;
        qry[++q_cnt] = { p.fst.x, p.fst.y, p.fst.z, p.fst.idx, 1 };
        qry[++q_cnt] = { p.fst.x, p.fst.y, p.fst.z, p.fst.idx, 2 };
    }
}

inline int lowbit(int x) {
    return x & (-x);
}

void add(int p, int val) {
    while(p <= k) {
        bit[p] += val;
        p += lowbit(p);
    }
}

int sum(int p) {
    int ret = 0;
    while(p > 0) {
        ret += bit[p];
        p -= lowbit(p);
    }
    return ret;
}

void solve(int L, int R) {
    if(L + 1 >= R) return;
    
    int pl, pr, M, p;
    M = L + (R - L) / 2;
    pl = L, pr = M; p = L;
    
    solve(L, M); solve(M, R);
    
    while(pl < M || pr < R) {
        if(pr >= R || (pl < M && qry[pl] < qry[pr])) {
            if(qry[pl].type == 1)
                add(qry[pl].z, totv[qry[pl].idx]);
            T[p++] = qry[pl++];
        } else {
            if(qry[pr].type == 2)
                ans[qry[pr].idx] += totv[qry[pr].idx] * sum(qry[pr].z);
            T[p++] = qry[pr++];
        }
    }
    
    pl = L, pr = M;
    while(pl < M || pr < R) {
        if(pr >= R || (pl < M && qry[pl] < qry[pr])) {
            if(qry[pl].type == 1)
                add(qry[pl].z, -totv[qry[pl].idx]);
            pl++;
        } else pr++;
    }
    assert(!sum(k));
    for(int i = L; i < R; i++) qry[i] = T[i];
}

void work() {
    sort(qry + 1, qry + q_cnt + 1, [](const Query &lhs, const Query &rhs) {
        return lhs.x == rhs.x ? lhs.type < rhs.type : lhs.x < rhs.x;
    });
    solve(1, q_cnt + 1);
    for(int i = 1; i <= q_cnt; i++) {
        if(!totv[i]) continue;
        anscnt[ans[i] / totv[i]] += totv[i];
    }
    for(int i = 0; i < n; i++)
        printf("%d\n", anscnt[i]);
}

int main() {
    init(); work();
    return 0;
}
