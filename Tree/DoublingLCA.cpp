#include <bits/stdc++.h>
using namespace std;

struct Edge { int v, next; };

const int MAXN = 1e6, LOG = 20;
int n, q, s, e_ptr = 1, head[MAXN+10]; Edge E[(MAXN+10)<<1];
int dep[MAXN+10], anc[MAXN+10][LOG+1];

void add_edge(int u, int v) { E[++e_ptr] = (Edge) { v, head[u] }; head[u] = e_ptr; }
void add_pair(int u, int v) { add_edge(u, v); add_edge(v, u); }

void dfs(int u) {
	for(int i = 1; i <= LOG; i++)
		anc[u][i] = anc[anc[u][i-1]][i-1];
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v;
		if(v == anc[u][0]) continue;
		anc[v][0] = u; dep[v] = dep[u] + 1;
		dfs(v);
	}
}

int lca(int u, int v) {
	if(dep[u] < dep[v]) swap(u, v);
	for(int i = LOG; i >= 0; i--)
		if(dep[anc[u][i]] >= dep[v])
			u = anc[u][i];
	if(u == v) return u;
	for(int i = LOG; i >= 0; i--)
		if(anc[u][i] != anc[v][i])
			u = anc[u][i], v = anc[v][i];
	u = anc[u][0], v = anc[v][0];
	return u;
}

inline int readint() {
	int f=1, r=0; char c=getchar();
	while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
	while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
	return f*r;
}

int main() {
	int u, v;
	n = readint(); q = readint(); s = readint();
	for(int i = 1; i <= n-1; i++) {
		u = readint(); v = readint();
		add_pair(u, v);
	}
	dep[s] = 1; dfs(s);
	while(q--) {
		u = readint(); v = readint();
		printf("%d\n", lca(u, v));
	}
	return 0;
}