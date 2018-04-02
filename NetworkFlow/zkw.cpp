#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
struct Edge {
    int u, v;
    int64 flow, cap, cost;
    int next;
};

const int MAXN = 5e3, MAXM = 5e4;
const int64 LL_INF = 0x3f3f3f3f3f3f3f3fLL;
int n, m, s, t, e_ptr = 1, head[MAXN+10]; Edge E[(MAXM+10)<<1]; // ** E[(MAXM+10)<<1] **
int64 MaxFlow, MinCost, dist[MAXN+10], inq[MAXN+10], vis[MAXN+10];

void add_edge(int u, int v, int64 cap, int64 cost) {
    E[++e_ptr] = (Edge) { u, v, 0, cap, cost, head[u] }; head[u] = e_ptr;
    E[++e_ptr] = (Edge) { v, u, 0,  0, -cost, head[v] }; head[v] = e_ptr;
}

bool spfa() {
    queue<int> Q;
    memset(dist, 0x3f, sizeof(dist));
    Q.push(t); dist[t] = 0; inq[t] = true;
    while(!Q.empty()) {
        int u = Q.front(); Q.pop(); inq[u] = false;
        for(int j=head[u]; j; j=E[j].next) {
            int v = E[j].v; int64 f = E[j^1].flow, c = E[j^1].cap, len = E[j^1].cost;
            if(f < c && dist[v] > dist[u] + len) {
                dist[v] = dist[u] + len;
                if(!inq[v]) {
                    inq[v] = true; Q.push(v);
                }
            }
        }
    }
    return dist[s] != LL_INF;
}

int64 dfs(int u, int64 flow) {
    if(u == t || flow == 0) return flow;
    vis[u] = true;
    int64 res = flow;
    for(int j=head[u]; j; j=E[j].next) {
        int v = E[j].v; int64 f = E[j].flow, c = E[j].cap, len = E[j].cost;
        if(f < c && !vis[v] && dist[v] == dist[u] - len) {
            int64 aug = dfs(v, min(res, c-f));
            E[j].flow += aug; E[j^1].flow -= aug;
            res -= aug;
            if(res == 0LL) break;
        }
    }
    return flow - res;
}

void zkw() {
    int64 CurFlow = 0LL;
    while(spfa()) {
        while(memset(vis, 0, sizeof(vis)),
            CurFlow = dfs(s, LL_INF)) { 
            MaxFlow += CurFlow;
            MinCost += dist[s] * CurFlow;
        }
    }
}

template<typename T>
inline void readint(T &x) {
    T f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    x = f*r;
}

int main() {
    int u, v; int64 w, c;
    readint(n); readint(m); readint(s); readint(t);
    for(int i = 1; i <= m; i++) {
        readint(u); readint(v); readint(w); readint(c);
        add_edge(u, v, w, c);
    }
    zkw();
    printf("%lld %lld", MaxFlow, MinCost);
    return 0;
}
