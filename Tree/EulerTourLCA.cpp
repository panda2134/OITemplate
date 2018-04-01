#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;

struct Edge {
	int v, next;
};

int n, q, s, e_ptr = 1, dfs_clock, head[MAXN+10]; Edge E[(MAXN+10)<<1];
int dfn[MAXN+10], dfs_seq[MAXN+10], idx[MAXN+10], euler_seq[(MAXN+10)<<1], st[(MAXN+10)<<1][22];
/* 
	dfn: dfs-clock of vertex u
	idx: the index of vertex u in euler-tour sequence
	dfs_seq: the dfs sequence
*/

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
	euler_seq[++euler_seq[0]] = dfn[u] = ++dfs_clock;
	idx[u] = euler_seq[0]; dfs_seq[dfs_clock] = u;
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v;
		if(v == fa) continue;
		dfs(v, u);
		euler_seq[++euler_seq[0]] = dfn[u];
	}
}

void init_lca() {
	memset(st, 0x3f, sizeof(st));
	for(int i = 1; i <= euler_seq[0]; i++)
		st[i][0] = euler_seq[i];
	for(int j = 1; j <= 21; j++)
		for(int i = 1; i <= euler_seq[0] - (1<<j) + 1; i++) // bounds of sparse-table!
			st[i][j] = min(st[i][j-1], st[i + (1 << (j-1))][j-1]);
}

int query(int l, int r) {
	if(l > r) swap(l, r);
	int j;
	for(j = 0; (1 << (j+1)) <= (r-l+1); j++);
	return min(st[l][j], st[r - (1<<j) + 1][j]);
}

int lca(int u, int v) {
	return dfs_seq[query(idx[u], idx[v])];
}

int main() {
	int u, v;
	n = readint(); q = readint(); s = readint();
	for(int i = 1; i <= n-1; i++) {
		u = readint(); v = readint();
		add_pair(u, v);
	}
	dfs(s, -1); init_lca();
	while(q--) {
		u = readint(); v = readint();
		printf("%d\n", lca(u, v));
	}
	return 0;
}