#include <bits/stdc++.h>
#define fst first
#define snd second
using namespace std;

typedef pair<int, int> pii;
const int MAXN = 1e5, INF = 0x3f3f3f3f;

struct Graph {
    struct Edge {
        int v, next;
    };
    
    int n, m, e_ptr = 1, head[MAXN+10]; Edge E[(MAXN+10)<<1];
    
    void add_edge(int u, int v) {
        E[++e_ptr] = (Edge) { v, head[u] }; head[u] = e_ptr;
    }
} G1, G2;

int dfs_clock, scc_cnt, sccno[MAXN+10], dfn[MAXN+10], low[MAXN+10];
int ans, topo_cnt, topo_seq[MAXN+10], w[MAXN+10], 
    tot[MAXN+10], vis[MAXN+10], dp[MAXN+10];

stack<int> S;
void dfs(int u) {
    dfn[u] = low[u] = ++dfs_clock;
    S.push(u);
    for(int j=G1.head[u]; j; j=G1.E[j].next) {
        int v = G1.E[j].v;
        if(!dfn[v]) {
            dfs(v);
            low[u] = min(low[u], low[v]);
        } else if(!sccno[v])
            low[u] = min(low[u], dfn[v]);
    }
    if(low[u] == dfn[u]) {
        int v; ++scc_cnt;
        do {
            v = S.top(); S.pop();
            sccno[v] = scc_cnt;
            tot[scc_cnt] += w[v];
        } while(u != v);
    }
}

void Tarjan() {
    for(int u = 1; u <= G1.n; u++)
        if(!dfn[u]) dfs(u);
}

void scc_graph() {
    set<pii> evis;
    for(int u = 1; u <= G1.n; u++)
        for(int j=G1.head[u]; j; j=G1.E[j].next) {
            int v = G1.E[j].v;
            if(sccno[u] == sccno[v] || evis.count(make_pair(sccno[u], sccno[v])))
                continue;
            else {
                evis.insert(make_pair(sccno[u], sccno[v]));
                G2.add_edge(sccno[u], sccno[v]);
            }
        }
    G2.n = scc_cnt;
}

bool topo_dfs(int u) {
    vis[u] = -1;
    for(int j=G2.head[u]; j; j=G2.E[j].next) {
        int v = G2.E[j].v;
        if(vis[v] == -1 || (vis[v] == 0 && !topo_dfs(v)))
            return false;
    }
    vis[u] = 1;
    topo_seq[topo_cnt--] = u;
    return true;
}

bool toposort() {
    topo_cnt = G2.n;
    for(int u = G2.n; u >= 1; u--)
        if(vis[u] == 0 && !topo_dfs(u)) return false;
    return true;
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

void init() {
    int u, v;
    G1.n = readint(); G1.m = readint();
    for(int i = 1; i <= G1.n; i++)
        w[i] = readint();
    for(int i = 1; i <= G1.m; i++) {    
        u = readint(); v = readint();
        G1.add_edge(u, v);
    }
    Tarjan(); scc_graph();
    assert(toposort());
}

void work() {
    for(int i = G2.n; i >= 1; i--) {
        int u = topo_seq[i], maxv = 0;
        for(int j=G2.head[u]; j; j=G2.E[j].next) {
            int v = G2.E[j].v;
            if(dp[v] > maxv) maxv = dp[v];
        }
        dp[u] = tot[u] + maxv;
        ans = max(ans, dp[u]);
    }
    printf("%d", ans);
}

int main() {
    init(); work();
    return 0;
}
