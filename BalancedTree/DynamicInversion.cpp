#include <bits/stdc++.h>
using namespace std;

typedef long long int64;

const int MAXN = 1e5;

//---------------Treap--------------------
struct Node *null;
struct Node {
    Node *ch[2];
    int v, r, sz;
    void init(int v_) {
        v = v_; r = rand(); sz = 1;
        ch[0] = ch[1] = null;
    }
    Node() {
        init(0);
    }
    int cmp(int x) {
        return (x == v ? -1 : (x > v ? 1 : 0));
    }
    void maintain() {
        if(this != null)
            sz = ch[0]->sz + ch[1]->sz + 1;
    }
};

int n, m, w[MAXN+10], mp[MAXN+10], bitval[MAXN+10];
Node* bit[MAXN+10]; int64 ans;

const int alloc_size = 65536;
queue<Node*> pool;
void renew() {
    Node* pit = new Node[alloc_size];
    for(int i = 0; i < alloc_size; i++)
        pool.push(pit++);
}

Node* newnode(int v) {
    if(pool.empty()) renew();
    Node* ret = pool.front(); pool.pop();
    ret->init(v);
    return ret;
}

void delnode(Node* &o) {
    pool.push(o); o = null;
}

void rotate(Node* &o, int d) {
    Node* k = o->ch[d^1];
    o->ch[d^1] = k->ch[d];
    k->ch[d] = o;
    o->maintain(); k->maintain();
    o = k;
}

void insert(Node* &o, int val) {
    if(o == null)
        o = newnode(val);
    else {
        int d = o->cmp(val);
        if(d == -1) return;
        insert(o->ch[d], val);
        o->maintain();
        if((o->r) > (o->ch[d]->r))
            rotate(o, d^1);
    }
}

void erase(Node* &o, int val) {
    if(o == null) return;
    int d = o->cmp(val);
    if(d == -1) {
        if(o->ch[1] == null) {
            Node* lhs = o->ch[0];
            delnode(o); o = lhs;
        } else if(o->ch[0] == null) {
            Node* rhs = o->ch[1];
            delnode(o); o = rhs;
        } else {
            int d = (o->ch[0]->r) < (o->ch[1]->r) ? 1 : 0;
            rotate(o, d);
            erase(o->ch[d], val);
        }
    } else
        erase(o->ch[d], val);
    o->maintain();
}

int getrank(Node* o, int val) {
    if(o == null) return 0;
    int d = o->cmp(val);
    if(d == -1) return o->ch[0]->sz;// !!!
    return getrank(o->ch[d], val) + d * (o->ch[0]->sz + 1);
}

//----------------------------------------

void init_null() {
    null = new Node(); null->sz = 0;
    for(int i = 0; i <= MAXN; i++)
        bit[i] = null;
}

inline int lowbit(int x) { return x & (-x); }

int bit_sum(int p) {
    int ret = 0;
    while(p > 0) {
        ret += bitval[p];
        p -= lowbit(p);
    }
    return ret;
}

void bit_add(int p, int val) {
    while(p <= n) {
        bitval[p] += val;
        p += lowbit(p);
    }
}

void nd_bit_sum(int p, int &sz, Node* o[]) {
    while(p > 0) {
        o[sz++] = bit[p];
        p -= lowbit(p);
    }
}

void nd_bit_add(int p, int val) {
    while(p <= n) {
        insert(bit[p], val);
        p += lowbit(p);
    }
}

void nd_bit_del(int p, int val){
    while(p <= n) {
        erase(bit[p], val);
        p += lowbit(p);
    }
}

int query(int x, int y) {
    int ret = 0, sz = 0; Node* vec[50];
    nd_bit_sum(x, sz, vec);
    for(int i = 0; i < sz; i++) {
        Node* ptr = vec[i];
        ret += getrank(ptr, y);
    }
    return ret;
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

void init() {
    n = readint(); m = readint();
    for(int i = 1; i <= n; i++) {
        w[i] = readint(); mp[w[i]] = i;
        bit_add(w[i], 1); ans += bit_sum(n) - bit_sum(w[i]);
        nd_bit_add(i, w[i]);
    }
}

void work() {
    int i;
    while(m--) {
        i = mp[readint()];
        printf("%lld\n", ans);
        ans -= query(i-1, n+1) - query(i-1, w[i]+1);
        ans -= query(n, w[i]) - query(i, w[i]);
        nd_bit_del(i, w[i]);
    }
}

int main() {
    srand(66623333);
    init_null(); 
    init(); work();
}
