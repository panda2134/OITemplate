#include <bits/stdc++.h>
using namespace std;

struct Edge{ int v, next; };

const int MAXN = 1e5, MAXM = 1e5;
int n, m, cnt, e_ptr = 1, head[MAXN+10]; Edge E[(MAXM+10)<<1];
int dfs_clk, iscut[MAXN+10], dfn[MAXN+10], low[MAXN+10];

void add_edge(int u, int v) {
	E[++e_ptr] = (Edge) { v, head[u] }; head[u] = e_ptr;
}

void add_pair(int u, int v) {
	add_edge(u, v); add_edge(v, u);
}

inline int readint() {
	int f=1, r=0; char c=getchar();
	while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
	while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
	return f*r;
}

void dfs(int u, int fa) {
	int child = 0;
	dfn[u] = low[u] = ++dfs_clk;
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v; 
		if(v == fa) continue;
		if(!dfn[v]) {
			dfs(v, u); ++child;
			low[u] = min(low[u], low[v]);
			if(low[v] >= dfn[u]) iscut[u] = true;
		} else if(dfn[v] < dfn[u] && v != fa)
			low[u] = min(low[u], dfn[v]);
	}
	if(child == 1 && fa == -1)
		iscut[u] = false;
}

int main() {
	int u, v;
	n = readint(); m = readint();
	for(int i = 1; i <= m; i++) {
		u = readint(); v = readint();
		add_pair(u, v);
	}
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) dfs(i, -1);
	for(int i = 1; i <= n; i++)
		if(iscut[i]) ++cnt;
	printf("%d\n", cnt);
	for(int i = 1; i <= n; i++)
		if(iscut[i]) printf("%d ", i);
	return 0;
}