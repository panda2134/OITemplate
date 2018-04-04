#include <bits/stdc++.h>
using namespace std;

const int MAXN = 3e5;

struct Node *null;
struct Node {
    int v, sumv; bool rev;
    Node *fa, *ch[2];
    Node(int v_) {
        v = sumv = v_; rev = false;
        fa = ch[0] = ch[1] = null;
    }
    bool splayrt() { return fa->ch[0] != this && fa->ch[1] != this; }
    int rel() { return splayrt() ? -1 : (fa->ch[0] == this ? 0 : 1); }
    void mark_rev() { rev ^= 1; }
    void maintain() {
        if(this == null) return;
        sumv = ch[0]->sumv ^ v ^ ch[1]->sumv;
    }
    void pushdown() {
        if(rev) {
            rev = false;
            ch[0]->mark_rev(); ch[1]->mark_rev();
            swap(ch[0], ch[1]);
        }
    }
} *nd[MAXN+10];

set<pair<Node*, Node*> > edges;

void init_null() {
    null = new Node(0);
    for(int i = 0; i <= MAXN; i++)
        nd[i] = null;
}

void rotate(Node* o) {
    Node *x, *y, *k; int d, d2;
    x = o->fa; y = x->fa;
    d = o->rel(); d2 = x->rel();
    k = o->ch[d^1];
    if(!x->splayrt()) y->ch[d2] = o;
    o->fa = y;
    o->ch[d^1] = x; x->fa = o;
    x->ch[d] = k; k->fa = x;
    x->maintain(); o->maintain();
}

void splay(Node* o) {
    static Node *x, *stk[MAXN+10]; int d, d2, p = 0;
    for(stk[p=1] = o; !stk[p]->splayrt(); p++)
        stk[p+1] = stk[p]->fa;
    for(; p; p--) stk[p]->pushdown();
    while(!o->splayrt()) {
        x = o->fa;
        d = o->rel(); d2 = x->rel();
        if(d2 != -1) {
            if(d == d2) rotate(x);
            else rotate(o);
        }
        rotate(o);
    }
}

void access(Node* o) {
    for(Node* t = null; o != null; t = o, o = o->fa) {
        splay(o); o->ch[1] = t; o->maintain();
    }
}

Node* get_root(Node* o) {
    access(o); splay(o);
    while(o->ch[0] != null) o = o->ch[0];
    splay(o); return o;
}

void make_root(Node* o) {
    access(o); splay(o); o->mark_rev();
}

void add_edge(Node* u, Node* v) {
    if(u > v) swap(u, v);
    edges.insert(make_pair(u, v));
}

bool has_edge(Node* u, Node* v) {
    if(u > v) swap(u, v); // 统一存储
    return edges.count(make_pair(u, v)) > 0;
}

void link(Node *u, Node *v) {
    if(get_root(u) == get_root(v)) return;
    make_root(u); splay(u); u->fa = v;
    add_edge(u, v);
}

void cut(Node *u, Node *v) {
    if(get_root(u) != get_root(v)) return;
    make_root(u); access(v); splay(u);
    u->pushdown();
    if(has_edge(u, v)) { // 不是u->ch[1] == v!!!
        u->ch[1] = null; v->fa = null; // v->fa !
    }
    u->maintain(); v->maintain();
}

int n, q;

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

int main() {
    int op, x, y;
    init_null();
    n = readint(); q = readint();
    for(int i = 1; i <= n; i++)
        nd[i] = new Node(readint());
    while(q--) {
        op = readint(); x = readint(); y = readint();
        switch(op) {
            case 0:
                assert(get_root(nd[x]) == get_root(nd[y]));
                make_root(nd[x]); access(nd[y]); splay(nd[x]);
                printf("%d\n", nd[x]->sumv);
                break;
            case 1:
                link(nd[x], nd[y]);
                break;
            case 2:
                cut(nd[x], nd[y]);
                break;
            case 3:
                splay(nd[x]); nd[x]->v = y; nd[x]->maintain();
                break;
        }
    }
    return 0;
}
