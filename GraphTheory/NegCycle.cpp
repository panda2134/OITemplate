#include <bits/stdc++.h>
using namespace std;

struct Edge {
    int v, len, next;
};

const int MAXN = 2e5, MAXM = 2e5, INF = 0x3f3f3f3f;

int T, cz, e_ptr = 1, n, m, head[MAXN+10], ins[MAXN+10]; Edge E[(MAXM+10)<<1];
int dist[MAXN+10];

void add_edge(int u, int v, int len) {
    E[++e_ptr] = (Edge) { v, len, head[u] }; head[u] = e_ptr;
}

void add_pair(int u, int v, int len) {
    add_edge(u, v, len); add_edge(v, u, len);
}

bool spfa(int u) {
    ins[u] = true;
    for(int j=head[u]; j; j=E[j].next) {
        int v = E[j].v, len = E[j].len;
        if(dist[v] > dist[u] + len) {
            dist[v] = dist[u] + len;
            if(ins[v] || (!ins[v] && !spfa(v)))
                return false;
        }
    }
    ins[u] = false; // 回溯 
    return true;
}

bool neg_cycle() {
    memset(ins, 0, sizeof(ins));
    fill(dist + 1, dist + n + 1, .0);
    for(int i = 1; i <= n; i++)
        if(!spfa(i)) return true;
    return false;
}

void init() {
    int u, v, w;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; i++) {
        scanf("%d%d%d", &u, &v, &w);
        if(w < 0)
            add_edge(u, v, w);
        else
            add_pair(u, v, w);
    }
}

void work() {
    puts(neg_cycle() ? "YE5" : "N0");
}

void clear() {
    e_ptr = 2;
    memset(head, 0, sizeof(head));
}

int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        init(); work(); clear();
    }
    return 0;
}
