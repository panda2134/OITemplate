#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5;

struct Node *null, *rt;
struct Node {
    int v, sz; bool flip;
    Node* ch[2];
    Node(int v_) { v = v_, sz = 1; flip = false; ch[0] = ch[1] = null; }
    int cmp(int k) {
        return k == ch[0]->sz + 1 ? -1 : (k > ch[0]->sz + 1 ? 1 : 0);
    }
    void rev() {
        if(this == null) return;
        flip ^= 1;
    }
    void maintain() {
        if(this == null) return;
        sz = ch[0]->sz + ch[1]->sz + 1;
    }
    void pushdown() {
        if(flip) {
            flip = false;
            ch[0]->rev(); ch[1]->rev();
            swap(ch[0], ch[1]);
        }
    }
};
int n, m;

void init_null() {
    null = new Node(0); null->sz = 0;
    rt = null;
}

void rotate(Node* &o, int d) {
    Node* k = o->ch[d^1];
    o->pushdown(); k->pushdown();
    o->ch[d^1] = k->ch[d];
    k->ch[d] = o;
    o->maintain(); k->maintain();
    o = k;
}

void splay(Node* &o, int k) {
    o->pushdown();
    int d = o->cmp(k);
    if(d == 1) k -= (o->ch[0]->sz + 1);
    if(d != -1) {
        Node* p = o->ch[d];
        p->pushdown();
        int d2 = p->cmp(k);
        if(d2 == 1) k -= (p->ch[0]->sz + 1);
        if(d2 != -1) {
            splay(p->ch[d2], k);
            if(d == d2) rotate(o, d^1);
            else rotate(o->ch[d], d);
        }
        rotate(o, d^1);
    }
}

Node* merge(Node* lhs, Node* rhs) {
    splay(lhs, lhs->sz);
    lhs->pushdown();
    lhs->ch[1] = rhs;
    lhs->maintain();
    return lhs; 
}

void split(Node* o, int k, Node* &lhs, Node* &rhs) {
    splay(o, k);
    o->pushdown(); 
    lhs = o, rhs = o->ch[1];
    o->ch[1] = null; o->maintain(); // 赋值后再断开和右儿子的连接，并维护sz！
}

void traverse(Node* o) {
    if(o == null) return;
    o->pushdown();
    traverse(o->ch[0]);
    if(o->v > 0) printf("%d ", o->v);
    traverse(o->ch[1]);
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

int main() {
    int l, r; Node *a, *b, *c;
    init_null();
    
    n = readint(); m = readint();
    
    rt = new Node(0); // dummy
    for(int i = 1; i <= n; i++) rt = merge(rt, new Node(i));
    rt = merge(rt, new Node(0)); // dummy
    
    while(m--) {
        l = readint() + 1, r = readint() + 1;
        split(rt, l-1, a, b); split(b, r-l+1, b, c);
        b->rev();
        rt = merge(a, merge(b, c));
    }
    
    traverse(rt);
    return 0;
}
