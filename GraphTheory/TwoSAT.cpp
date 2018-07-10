/*
    3*n 个变量，即最多 50000*3 * 2 个点，表示每场是否用某个车
    注意 i--, j--
*/
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 * 3 * 2, MAXM = 100000;

int n, d, m, x[20]; char S[MAXN + 10];
struct {
    int i, j, hi, hj;
} rule[MAXM+10];

namespace TwoSAT {
    int n, sel[MAXN+10], stk[MAXN+10], vis[MAXN+10];
    vector<int> G[MAXN+10];

    void add_clause(int x, int xval, int y, int yval) {
        // x=xval 推导出 y=yval, 一定要建反向边！！！
        x <<= 1, y <<= 1;
        G[x|xval].push_back(y|yval);
        G[y|(yval^1)].push_back(x|(xval^1));
    }

    void xor_clause(int x, int y) {
        x <<= 1, y <<= 1;
        G[x].push_back(y|1), G[y|1].push_back(x);
        G[x|1].push_back(y), G[y].push_back(x|1);
    }

    bool dfs(int u) {
        if(vis[u]) return true;
        if(vis[u^1]) return false;
        sel[(u >> 1)] = u & 1;
        vis[u] = true; stk[++stk[0]] = u;
        for(size_t j = 0; j < G[u].size(); j++)
            if(!dfs(G[u][j])) return false;
        return true;
    }

    void clear() {
        memset(vis, 0, sizeof(vis));
        memset(sel, 0, sizeof(sel));
        stk[0] = 0;
        for(int i = 0; i < n * 2; i++)
            G[i].clear();
    }

    bool solve() {
        static int p[MAXN+10]; // mapping
        for(int i = 0; i < n; i++) p[i] = i;
        random_shuffle(p, p + n);
        for(int i = 0; i < 2 * n; i++) {
            random_shuffle(G[i].begin(), G[i].end());
        }
        for(int cur = 0; cur < n; cur++) {
            int i = p[cur];
            if(!vis[i<<1] && !vis[i<<1|1]) {
                stk[0] = 0; sel[i] = 0;
                if(!dfs(i<<1)) {
                    for(; stk[0]; --stk[0])
                        vis[stk[stk[0]]] = false;
                    sel[i] = 1;
                    if(!dfs(i<<1|1))
                        return false;
                }
            }
        }
        return true;
    }
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

inline char readch() {
    char c=getchar();
    while(!isalnum(c) && !ispunct(c)) c=getchar();
    return c;
}

inline void readstr(char *str) {
    char c=getchar(); int p=0;
    while(!isalnum(c) && !ispunct(c)) c=getchar();
    while(isalnum(c) || ispunct(c)) {
        str[p++]=c;
        c=getchar();
    }
    str[p] = '\0';
}

void init() {
    n = readint(); d = readint();
    readstr(S); TwoSAT::n = n;
    m = readint();
    for(int i = 0; i < m; i++) {
        rule[i].i = readint() - 1, rule[i].hi = readch() - 'A';
        rule[i].j = readint() - 1, rule[i].hj = readch() - 'A';
    }
}

inline int do_map(int i, int type) {
    switch(S[i]) {
        case 'a':
            assert(type != 0);
            if(type == 1) return 0;
            else return 1;
            break;
        case 'b':
            assert(type != 1);
            if(type == 0) return 0;
            else return 1;
            break;
        case 'c':
            assert(type != 2);
            if(type == 0) return 0;
            else return 1;
            break;
        default: 
            assert(false);
    }
    return -1;
}

bool judge() {
    using TwoSAT::xor_clause;
    using TwoSAT::add_clause;
    using TwoSAT::sel;
    TwoSAT::clear();
    // rules
    for(int cur = 0; cur < m; cur++)
        if(rule[cur].hi != S[rule[cur].i] - 'a') {
            int p = do_map(rule[cur].i, rule[cur].hi);
            if(rule[cur].hj != S[rule[cur].j] - 'a') {
                int q = do_map(rule[cur].j, rule[cur].hj);
                add_clause(rule[cur].i, p, rule[cur].j, q);
            } else // 特判！
                add_clause(rule[cur].i, p, rule[cur].i, p^1);
        }
    if(!TwoSAT::solve()) return false;
    else {
        for(int i = 0; i < n; i++) {
            switch(S[i]) {
                case 'a':
                    if(!sel[i]) putchar('B');
                    else putchar('C');
                    break;
                case 'b':
                    if(!sel[i]) putchar('A');
                    else putchar('C');
                    break;
                case 'c':
                    if(!sel[i]) putchar('A');
                    else putchar('B');
                    break;
                default: assert(false);
            }
        }
        return true;
    }
}

void dfs(int cur) {
    if(cur == d) {
        if(judge()) exit(0);
        else return;
    } else {
        S[x[cur]] = 'a'; dfs(cur+1);
        S[x[cur]] = 'b'; dfs(cur+1);
        S[x[cur]] = 'c'; dfs(cur+1);
    }
}

void work() {
    {
        int cur = 0;
        for(int i = 0; i < n; i++)
            if(S[i] == 'x') x[cur++] = i;
        
        assert(cur == d);
    }
    dfs(0);
    puts("-1");
}

int main() {
    srand(768750956U);
    init(); work();
    return 0;
}