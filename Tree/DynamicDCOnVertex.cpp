#include <bits/extc++.h>
#include <bits/stdc++.h>
#define fst first
#define snd second
using namespace std;

const int MAXN = 2e5;

struct Edge {
    int v, len, next;
};

struct dctree_fa_t {
    int node, adj_node;
};

typedef __gnu_pbds::tree<pair<int, int64_t>, __gnu_pbds::null_type, less<pair<int, int64_t> >,
                         __gnu_pbds::rb_tree_tag,
                         __gnu_pbds::tree_order_statistics_node_update>
    rank_tree_t;

int n;
int64_t last_ans, rbt_time;
int e_ptr = 1, head[MAXN + 10];
Edge E[(MAXN + 10) << 1];

int64_t ans[MAXN + 10];
int sz[MAXN + 10], w[MAXN + 10];

int vis[MAXN + 10];
dctree_fa_t dctree_fa[MAXN + 10];
rank_tree_t tr[MAXN + 10];
map<int, rank_tree_t> adj_tr[MAXN + 10];

vector<int> dctree_sons[MAXN + 10];

void add_edge(int u, int v, int len) {
    E[++e_ptr] = (Edge){v, len, head[u]};
    head[u] = e_ptr;
}

void add_pair(int u, int v, int len) {
    add_edge(u, v, len), add_edge(v, u, len);
}

//-------dynamic tree div and conquer start-------------

int ctrd, ctrd_sz, tot_sz;
int get_ctrd(int u, int fa) {
    int sz = 1, son_sz = 0, max_sz = 0;
    for(int j = head[u]; j; j = E[j].next) {
        int v = E[j].v;
        if(v == fa || vis[v]) continue;
        son_sz = get_ctrd(v, u);
        sz += son_sz;
        max_sz = max(max_sz, son_sz);
    }
    max_sz = max(max_sz, tot_sz - sz);
    if(max_sz < ctrd_sz) {
        ctrd = u;
        ctrd_sz = max_sz;
    }
    return sz;
}

int get_sz(int u, int fa) {
    int sz = 1;
    for(int j = head[u]; j; j = E[j].next) {
        int v = E[j].v;
        if(vis[v] || v == fa) continue;
        sz += get_sz(v, u);
    }
    return sz;
}

void destroy(int u) {
    last_ans -= ans[u];
    for(auto v : dctree_sons[u]) {
        dctree_fa[v] = {0, 0};
        destroy(v);
    }
    dctree_sons[u].clear();
    tr[u].clear();
    adj_tr[u].clear();
    vis[u] = false;
    ans[u] = sz[u] = 0;
}

void build_ctrd_rbt(int u, int fa, int h, rank_tree_t &tree) {
    tree.insert(make_pair(w[u] - h, ++rbt_time));
    for(int j = head[u]; j; j = E[j].next) {
        int v = E[j].v, len = E[j].len;
        if(vis[v] || v == fa) continue;
        build_ctrd_rbt(v, u, h + len, tree);
    }
}

inline bool is_scapegoat(int u) {
    int mx = 0;
    for(auto v : dctree_sons[u]) mx = max(mx, sz[v]);
    return mx > sz[u] * .80;
}

inline void pushup_ans(int u, int h, int64_t &ans, rank_tree_t &tree, int fac = 1) {
    ans += fac * (tree.size() - tree.order_of_key({h - w[u], 0}));
}

void update_dfs(int u, int fa, int h, int64_t &ans, rank_tree_t &tree) {
    pushup_ans(u, h, ans, tree);
    for(int j = head[u]; j; j = E[j].next) {
        int v = E[j].v, len = E[j].len;
        if(vis[v] || v == fa) continue;
        update_dfs(v, u, h + len, ans, tree);
    }
}

void build(int u) {
    vis[u] = true;

    ans[u] = 0, sz[u] = 1;

    tr[u].insert(make_pair(w[u], ++rbt_time));
    for(int j = head[u]; j; j = E[j].next) {  // 统计答案
        int v = E[j].v, len = E[j].len;
        if(vis[v]) continue;

        update_dfs(v, u, len, ans[u], tr[u]);
        build_ctrd_rbt(v, u, len, tr[u]);
        build_ctrd_rbt(v, u, len,
                       adj_tr[u][v]);  // 放在原树的 u 的邻接点，再容斥
    }
    last_ans += ans[u];

    for(int j = head[u]; j; j = E[j].next) {
        int v = E[j].v, son_sz = 0;
        if(vis[v]) continue;

        ctrd_sz = n + 1;
        son_sz = get_sz(v, u);
        sz[u] += son_sz;

        tot_sz = son_sz;
        get_ctrd(v, -1);

        dctree_fa[ctrd] = (dctree_fa_t){u, v};
        dctree_sons[u].push_back(ctrd);

        build(ctrd);
    }
}

//---------dynamic tree div and conquer end-------------

//-----------------doubling lca start-----------------
int dist[MAXN + 10], dep[MAXN + 10], anc[MAXN + 10][22];

inline int query_lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 20; i >= 0; i--)
        if(dep[anc[u][i]] >= dep[v]) u = anc[u][i];
    if(u == v) return u;
    for(int i = 20; i >= 0; i--)
        if(anc[u][i] != anc[v][i]) {
            u = anc[u][i], v = anc[v][i];
        }
    u = anc[u][0], v = anc[v][0];
    return u;
}

inline int query_dist(int u, int v) {
    return dist[u] + dist[v] - 2 * dist[query_lca(u, v)];
}

//-----------------doubling lca end-------------------

void insert(int p, int cur, int cur_len, int r) {
    if(p) {
        // div and conquer
        add_pair(p, cur, cur_len);
        dctree_fa[cur] =
            (dctree_fa_t){p, cur};  // 记住一定要同时连接 fa 和 sons!
        dctree_sons[p].push_back(cur);
        vis[cur] = true; // !!!!!!!!!!!
        // doubling lca on original tree
        dep[cur] = dep[p] + 1;
        dist[cur] = dist[p] + cur_len;
        anc[cur][0] = p;
        for(int i = 1; i <= 20; i++) anc[cur][i] = anc[anc[cur][i - 1]][i - 1];
        for(int u = cur; u; u = dctree_fa[u].node) {
            ++sz[u];
        }
    } else dep[cur] = 1;  // important!!

    // rbt
    w[cur] = r;
    tr[cur].insert(make_pair(w[cur], ++rbt_time));

    assert(!ans[cur]);
    for(int u = p; u; u = dctree_fa[u].node) {
        int d = query_dist(u, cur);
        last_ans -= ans[u];
        pushup_ans(cur, d, ans[u], tr[u]);
    }
    for(int u = cur; u; u = dctree_fa[u].node) {
        int d = query_dist(dctree_fa[u].node, cur);
        pushup_ans(cur, d, ans[dctree_fa[u].node],
                    adj_tr[dctree_fa[u].node][dctree_fa[u].adj_node], -1);
        last_ans += ans[u];
    }
    // update
    for(int u = cur; dctree_fa[u].node; u = dctree_fa[u].node) {
        int d = query_dist(dctree_fa[u].node, cur);
        tr[dctree_fa[u].node].insert(make_pair(w[cur] - d, ++rbt_time));
        adj_tr[dctree_fa[u].node][dctree_fa[u].adj_node].insert(make_pair(w[cur] - d, ++rbt_time));
    }

    int scape = 0;
    for(int u = p; u; u = dctree_fa[u].node) {  // 首先找替罪羊
        if(is_scapegoat(u)) scape = u;
    }

    if(scape) {  // 重建 + 获取答案
        destroy(scape);

        tot_sz = get_sz(scape, -1);
        ctrd = 0;
        ctrd_sz = n + 1;
        get_ctrd(scape, -1);

        if(dctree_fa[scape].node) {
            dctree_fa[ctrd] = dctree_fa[scape];
            dctree_fa[scape] = (dctree_fa_t){0, 0};
            auto it = dctree_sons[dctree_fa[ctrd].node].begin();
            while(assert(it != dctree_sons[dctree_fa[ctrd].node].end()), *it != scape) ++it;
            dctree_sons[dctree_fa[ctrd].node].erase(it);
            dctree_sons[dctree_fa[ctrd].node].push_back(ctrd);
        }

        build(ctrd);
    }
}

inline int readint() {
    int f = 1, r = 0;
    char c = getchar();
    while(!isdigit(c)) {
        if(c == '-') f = -1;
        c = getchar();
    }
    while(isdigit(c)) {
        r = r * 10 + c - '0';
        c = getchar();
    }
    return f * r;
}

int main() {
    int a, c, r;
    readint();
    n = readint();
    for(int i = 1; i <= n; i++) {
        a = readint();
        a ^= (last_ans % int(1e9));
        c = readint();
        r = readint();

        insert(a, i, c, r);
        printf("%lld\n", last_ans);
    }
    return 0;
}