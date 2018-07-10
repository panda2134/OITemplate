#include <bits/stdc++.h>
using namespace std;

struct Edge { int v, len, next; };

const int MAXN = 1e4, MAXK = 1e7;

int n, q, k, e_ptr = 1, head[MAXN+10]; Edge E[(MAXN+10)<<1];
int ans, root, totsz, vis[MAXN+10], f[MAXN+10], sz[MAXN+10],
	dist[MAXN+10], mp[MAXK+10], pths[MAXN+10];

void add_edge(int u, int v, int len) {
	E[++e_ptr] = (Edge) { v, len, head[u] }; head[u] = e_ptr;
}

void add_pair(int u, int v, int len) {
	add_edge(u, v, len); add_edge(v, u, len);
}

inline int readint() {
	int f=1, r=0; char c=getchar();
	while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
	while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
	return f*r;
}

void get_centroid(int u, int fa) {
	f[u] = 0, sz[u] = 1;
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v;
		if(vis[v] || v == fa) continue;
		get_centroid(v, u); sz[u] += sz[v];
		if(sz[v] > f[u]) f[u] = sz[v];
	}
	f[u] = max(f[u], totsz - sz[u]);
	if(f[u] < f[root]) root = u;
}

void count_nd(int u, int fa) {
	sz[u] = 1;
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v;
		if(vis[v] || v == fa) continue;
		count_nd(v, u); sz[u] += sz[v];
	}
	return;
}

void get_dist(int u, int fa) {
	pths[++pths[0]] = dist[u];
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v, len = E[j].len;
		if(vis[v] || v == fa) continue;
		dist[v] = dist[u] + len;
		get_dist(v, u);
	}
}

int calc(int u, int w) {
	int ret = 0;
	dist[u] = w; pths[0] = 0;
	get_dist(u, -1);
	sort(pths + 1, pths + pths[0] + 1);
	for(int i = 1; i <= pths[0]; i++) {
		if(pths[i] <= k)
			ret += mp[k - pths[i]];
		mp[pths[i]]++;
	}
	for(int i = 1; i <= pths[0]; i++)
		mp[pths[i]]--;
	return ret;
}

void solve(int u) {
	ans += calc(u, 0);
	vis[u] = true;
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v, len = E[j].len;
		if(vis[v]) continue;
		ans -= calc(v, len);
		count_nd(v, -1); totsz = sz[v];
		root = 0;
		get_centroid(v, -1);
		solve(v);
	}
}

int main() {
	int a, b, c;
	n = readint(); q = readint();
	for(int i = 1; i <= n-1; i++) {
		a = readint(); b = readint(); c = readint();
		add_pair(a, b, c);
	}
	while(q--) {
		k = readint();
		f[root=0] = n;
		memset(vis, 0, sizeof(vis));
		get_centroid(1, -1);
		ans = 0;
		solve(root);
		puts(ans ? "AYE" : "NAY");
	}
}
