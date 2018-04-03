#include <bits/stdc++.h>
#define fst first
#define snd second
using namespace std;

typedef pair<int, int> pii;
const int MAXN = 1e5;

extern struct Node *null;
struct Node {
    pii val; int dist;
    Node *ch[2];
    Node() {
        ch[0] = ch[1] = null;
        dist = -1; //!!!
    };
    Node(pii v_) {
        ch[0] = ch[1] = null;
        dist = -1; val = v_;
    }
} Tnull, *null=&Tnull, *rt[MAXN+10];
int n, q, fa[MAXN+10], del[MAXN+10];

int get_fa(int x) { return x == fa[x] ? x : fa[x] = get_fa(fa[x]); }
void union_set(int x, int y) { fa[get_fa(y)] = get_fa(x); } // 顺序

Node* merge(Node* lhs, Node* rhs) {
    if(lhs == null) return rhs;
    else if(rhs == null) return lhs;
    else {
        if(lhs->val > rhs->val) swap(lhs, rhs);
        lhs->ch[1] = merge(lhs->ch[1], rhs);
        if(lhs->ch[0]->dist < lhs->ch[1]->dist)
            swap(lhs->ch[0], lhs->ch[1]);
        lhs->dist = lhs->ch[1]->dist + 1; // 距离应该是左右儿子的最小dist + 1 （定义）
        return lhs;
    }
}

void pop(Node* &o) {
    Node *lhs = o->ch[0], *rhs = o->ch[1];
    delete o;
    o = merge(lhs, rhs);
}

void push(Node* &o, pii val) {
    o = merge(o, new Node(val));
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

int main() {
    int op, x, y;
    n = readint(); q = readint();
    for(int i = 1; i <= n; i++) {
        fa[i] = i;
        rt[i] = new Node(make_pair(readint(), i));
    }
    while(q--) {
        op = readint();
        switch(op) {
            case 1:
                x = readint(); y = readint();
                if(del[x] || del[y] || get_fa(x) == get_fa(y))
                    continue;
                rt[get_fa(x)] = merge(rt[get_fa(x)], rt[get_fa(y)]);
                union_set(x, y);
                break;
            case 2:
                x = readint();
                if(del[x]) puts("-1");
                else {
                    pii u = rt[get_fa(x)]->val;
                    printf("%d\n", u.fst);
                    del[u.snd] = true;
                    pop(rt[get_fa(x)]);
                }
                break;
        }
    }
    return 0;
}
