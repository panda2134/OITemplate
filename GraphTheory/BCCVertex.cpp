/*
	[UVaOJ1364] Knights of the Round Table
	好题。
	首先，问题可以转化成求无向图中不属于任何一个奇圈的点的数目。
	补集转换一下，变为求至少属于一个奇圈的点数目。
	和圈相关的问题，可以考虑BCC。和圈和点都有关，考虑点双连通分量。
	如果一个点双里面没有奇圈，那么它里面任何一个点显然都不属于任何一个奇圈。
	只要一个点双里面有一个奇圈，那么点双中任何一个点都至少属于一个奇圈，因为我们
	可以利用已有的奇圈来"包含"这个点双内的某个点。
	奇=奇+偶。如果奇圈上有点v1, v2，这个奇圈外有点u，不妨假设有u->v1, u->v2的路径
	（由双连通性质一定存在这样的v1, v2），则不管v1->u->v2含点数的奇偶性如何，总可以构造
	一个u->v2->现有奇圈一部分->v1->u的新奇圈！
	于是只需要找出所有BCC，然后对每个BCC二分图染色，即可得出答案。
	（注意割点bccno无意义）
*/
#include <bits/stdc++.h>
#define CLEAR(x) memset((x), 0, sizeof(x))
using namespace std;

struct Edge {
	int u, v, next;
};

const int MAXN = 1e3, MAXM = 1e6;
int n, m, e_ptr = 1, head[MAXN+10], hate[MAXN+10][MAXN+10];
Edge E[(MAXM+10)<<1];
int dfs_clk, bcc_cnt, dfn[MAXN+10], low[MAXN+10], bccno[MAXN+10], iscut[MAXN+10];
vector<int> bcc[MAXN+10]; int clr[MAXN+10];

void add_edge(int u, int v) {
	E[++e_ptr] = (Edge) { u, v, head[u] }; head[u] = e_ptr;
}

void add_pair(int u, int v) {
	add_edge(u, v); add_edge(v, u);
}

inline int readint(){
	int f=1, r=0; char c=getchar();
	while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
	while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
	return f*r;
}

stack<int> S;
void dfs(int u, int fa) {
	int child = 0;
	dfn[u] = low[u] = ++dfs_clk;
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v; if(v == fa) continue;
		if(!dfn[v]) {
			S.push(j);
			dfs(v, u); ++child;
			low[u] = min(low[u], low[v]);
			if(low[v] >= dfn[u]) {
				iscut[u] = true;
				++bcc_cnt; int cur;
				do {
					cur = S.top(); S.pop();
					if(bccno[E[cur].u] != bcc_cnt) {
						bccno[E[cur].u] = bcc_cnt;
						bcc[bcc_cnt].push_back(E[cur].u);
					}
					if(bccno[E[cur].v] != bcc_cnt) {
						bccno[E[cur].v] = bcc_cnt;
						bcc[bcc_cnt].push_back(E[cur].v);
					}
				} while(E[cur].u != u || E[cur].v != v);
			}
		} else if(dfn[v] < dfn[u] && v != fa) {
			S.push(j);
			low[u] = min(low[u], dfn[v]);
		}
	}
	if(child == 1 && fa == -1)
		iscut[u] = false;
}

void find_bcc() {
	for(int i = 1; i <= n; i++)
		if(!dfn[i]) dfs(i, -1);
}

bool bipartite(int u, int b) {
	for(int j=head[u]; j; j=E[j].next) {
		int v = E[j].v; if(bccno[v] != b) continue;
		if(clr[v] == clr[u]) return false;
		if(!clr[v]) {
			clr[v] = 3 - clr[u];
			if(!bipartite(v, b)) return false;
		}
	}
	return true;
}

bool init() {
	int u, v;
	n = readint(); m = readint();
	if(!n && !m) return false;
	for(int i = 1; i <= m; i++) {
		u = readint(); v = readint();
		hate[u][v] = hate[v][u] = true;
	}
	for(u = 1; u <= n; u++)
		for(v = u + 1; v <= n; v++)
			if(!hate[u][v]) add_pair(u, v);
	return true;
}

void work() {
	int ans = n;
	find_bcc();
	for(int i = 1; i <= bcc_cnt; i++) {
		for(int j = 0; j < (int)bcc[i].size(); j++)
			bccno[bcc[i][j]] = i; // 割点bccno无意义
		CLEAR(clr);
		clr[bcc[i][0]] = 1;
		if(!bipartite(bcc[i][0], i))
			ans -= bcc[i].size();
	}
	printf("%d\n", ans);
}

void clear() {
	for(int i = 1; i <= bcc_cnt; i++) bcc[i].clear();
	n = m = 0; e_ptr = 1; CLEAR(head); CLEAR(hate);
	dfs_clk = bcc_cnt = 0;
	CLEAR(dfn); CLEAR(low); CLEAR(bccno); CLEAR(iscut); CLEAR(clr);
}

int main() {
	while(true) {
		if(!init()) break;
		work(); clear();
	}
	return 0;
}