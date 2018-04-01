// call Dfs1(1) and Dfs2(1, 1)
const int MAXN = 1e5;
int dfs_clock, Fa[MAXN+10], Son[MAXN+10], Sz[MAXN+10],
	Dep[MAXN+10], Top[MAXN+10], Dfn[MAXN+10];

void Dfs1(int u) { // Fa Son Sz Dep
	int maxsz = 0; Sz[u] = 1;
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v;
		if(v == Fa[u]) continue;
		Fa[v] = u; Dep[v] = Dep[u] + 1; // !
		Dfs1(v); Sz[u] += Sz[v];
		if(Sz[v] > maxsz) {
			maxsz = Sz[v];
			Son[u] = v;
		}
	}
}

void Dfs2(int u, int anc) { // Top Dfn
	Dfn[u] = ++dfs_clock; Top[u] = anc;
	if(Son[u]) Dfs2(Son[u], anc);
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v;
		if(v == Fa[u] || v == Son[u]) continue;
		Dfs2(v, v);
	}
}

int LCA(int u, int v) {
	while(Top[u] != Top[v]) {
		if(Dep[Top[u]] < Dep[Top[v]]) swap(u, v);
		u = Fa[Top[u]];
	}
	if(Dep[u] > Dep[v]) swap(u, v);
	return u;
}

int HLDQuery(int u, int v) {
	int ret = -INF;
	while(Top[u] != Top[v]) {
		if(Dep[Top[u]] < Dep[Top[v]]) swap(u, v);
		ret = max(ret, st_query(1, 1, n, Dfn[Top[u]], Dfn[u]));
		u = Fa[Top[u]];
	}
	if(Dep[u] > Dep[v]) swap(u, v);
	ret = max(ret, st_query(1, 1, n, Dfn[u], Dfn[v]));
	return ret;
}