#include <bits/stdc++.h>
using namespace std;

struct Edge {
	int v, flow, cap, next;
};

const int MAXN = 1e4, MAXM = 1e5, INF = 0x3f3f3f3f;
int n, m, s, t, e_ptr = 1, head[MAXN+10]; Edge E[(MAXM+10)<<1];
int d[MAXN+10], cur[MAXN+10];

void AddEdge(int u, int v, int cap) {
	E[++e_ptr] = (Edge) { v, 0, cap, head[u] }; head[u] = e_ptr;
	E[++e_ptr] = (Edge) { u, 0,   0, head[v] }; head[v] = e_ptr;
}

bool BFS() {
	queue<int> Q;
	memset(d, 0xff, sizeof(d));
	Q.push(s); d[s] = 0;
	while(!Q.empty()) {
		int u = Q.front(); Q.pop();
		for(int j=head[u]; j; j=E[j].next) {
			int v = E[j].v, f = E[j].flow, c = E[j].cap;
			if(f < c && d[v] == -1) {
				d[v] = d[u] + 1;
				if(v == t) return true;
				else Q.push(v);
			}
		}
	}
	return false;
}

int DFS(int u, int flow) {
	if(u == t || flow == 0) return flow; // !!!!!
	int res = flow;
	for(int &j=cur[u]; j; j=E[j].next) { // !!!!!
		int v = E[j].v, f = E[j].flow, c = E[j].cap;
		if(f < c && d[v] == d[u] + 1) {
			int aug = DFS(v, min(res, c-f));
			E[j].flow += aug; E[j^1].flow -= aug;
			res -= aug;
			if(res == 0) break; // !!!!!
		}
	}
	return flow - res;
}

int Dinic() {
	int MaxFlow = 0, CurFlow = 0;
	while(BFS()) {
		memcpy(cur, head, sizeof(head));
		while((CurFlow = DFS(s, INF)))
			MaxFlow += CurFlow;
	}
	return MaxFlow;
}

int main() {
	int u, v, c;
	scanf("%d%d%d%d", &n, &m, &s, &t);
	for(int i = 1; i <= m; i++) {
		scanf("%d%d%d", &u, &v, &c);
		AddEdge(u, v, c);
	}
	printf("%d", Dinic());
	return 0;
}
