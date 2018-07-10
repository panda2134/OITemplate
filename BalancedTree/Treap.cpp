#include <bits/stdc++.h>
using namespace std;

struct Node *null, *rt;
struct Node {
    int v, r, sz, cnt;
    Node *ch[2];
    Node(int v_) {
        v = v_; r = rand(); sz = cnt = 1;
        ch[0] = ch[1] = null;
    }
    int cmp(int val) {
        return val == v ? -1 : (val > v ? 1 : 0);
    }
    void maintain() {
        if(this == null) return;
        sz = ch[0]->sz + ch[1]->sz + cnt;
    }
};

void init_null() {
    null = new Node(0); null->sz = null->cnt = 0;
    rt = null;
}

void rotate(Node* &o, int d) {
    Node* k = o->ch[d^1];
    o->ch[d^1] = k->ch[d];
    k->ch[d] = o;
    o->maintain(); k->maintain();
    o = k;
}

void insert(Node* &o, int val) {
    if(o == null) {
        o = new Node(val);
        return;
    } else {
        int d = o->cmp(val);
        if(d == -1) {
            ++o->cnt; o->maintain();
        } else {
            insert(o->ch[d], val);
            o->maintain();
            if(o->ch[d]->r < o->r) rotate(o, d^1);
        }
    }
}

void erase(Node* &o, int val) {
    int d = o->cmp(val);
    if(d == -1) {
        if(o->cnt == 1) {
            if(o->ch[1] == null) {
                Node* lhs = o->ch[0];
                delete o;
                o = lhs;
            } else if(o->ch[0] == null) {
                Node* rhs = o->ch[1];
                delete o;
                o = rhs;
            } else {
                int d2 = (o->ch[0]->r) > (o->ch[1]->r);
                rotate(o, d2^1);
                erase(o->ch[d2^1], val);
            }
        } else
            --o->cnt;
    } else
        erase(o->ch[d], val);
    o->maintain();
}

Node* kth(Node* o, int k) {
    int d = (k >= o->ch[0]->sz + 1 && k <= o->ch[0]->sz + o->cnt) ? -1 :
            (k <= o->ch[0]->sz ? 0 : 1);
    if(d == -1) return o;
    if(d == 1) k -= (o->sz - o->ch[1]->sz);
    return kth(o->ch[d], k);
}

int get_rank(Node* o, int val) {
    if(o == null) return 1;
    int d = o->cmp(val);
    if(d == -1) return o->ch[0]->sz + 1;
    return get_rank(o->ch[d], val) + d * (o->sz - o->ch[1]->sz);
}

Node* find(Node* o, int val) {
    if(o == null) return o;
    int d = o->cmp(val);
    if(d == -1) return o;
    else return find(o->ch[d], val);
}

Node* pre(int val) {
    int rk = get_rank(rt, val);
    return rk != 1 ? kth(rt, rk-1) : null;
}

Node* succ(int val) {
    int rk = get_rank(rt, val);  //     \/!!!!!!!!!
    return rk != (rt->sz) ? kth(rt, rk+find(rt, val)->cnt) : null;
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

int main() {
    srand(66623333);
    int q, op, x;
    init_null();
    q = readint();
    while(q--) {
        op = readint();
        switch(op) {
            case 1:
                x = readint(); insert(rt, x);
                break;
            case 2:
                x = readint(); erase(rt, x);
                break;
            case 3:
                x = readint(); insert(rt, x);
                printf("%d\n", get_rank(rt, x));
                erase(rt, x);
                break;
            case 4:
                x = readint();
                printf("%d\n", kth(rt, x)->v);
                break;
            case 5:
                x = readint(); insert(rt, x);
                assert(pre(x) != null);
                printf("%d\n", pre(x)->v);
                erase(rt, x);
                break;
            case 6:
                x = readint(); insert(rt, x);
                assert(succ(x) != null);
                printf("%d\n", succ(x)->v);
                erase(rt, x);
                break;
        }
    }
    return 0;
}
