#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e4, MAXC = 1e6;
int N, Q, Q1, Q2, L, R, T, BlkSize, NowAns, M[MAXC+10], A[MAXN+10], B[MAXN+10], Ans[MAXN+10];

struct Query {
    int L, R, T, id;
    Query() {}
    Query(int l, int r, int t, int id_): L(l), R(r), T(t), id(id_) {}
    bool operator<(const Query& rhs) const {
        if(L/BlkSize == rhs.L/BlkSize) {
            if(R/BlkSize == rhs.R/BlkSize) 
                return T < rhs.T;
            else return R/BlkSize < rhs.R/BlkSize;
        } else return L/BlkSize < rhs.L/BlkSize;
    }
} q[MAXN+10];

struct Modify {
    int p, val, orig, id;
    Modify() {}
    Modify(int p_, int val_, int orig_, int id_): p(p_), val(val_), orig(orig_), id(id_) {}
} mod[MAXN+10];

template<typename T>
inline void readint(T& x) {
    T f=1, r=0; char c=getchar();
    while(!isdigit(c)){ if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)){ r=r*10+c-'0'; c=getchar(); }
    x = f*r;
}

inline char readc() { 
    char c=getchar(); 
    while(!isalnum(c) && !ispunct(c)) 
        c=getchar(); 
    return c; 
}

void Init() {
    static int u, v; char op;
    readint(N); readint(Q);
    BlkSize = ceil(pow(N, 0.67));
    for(int i=1; i<=N; i++) {
        readint(A[i]); B[i] = A[i];
    }
    for(int i=1; i<=Q; i++) {
        op = readc(); readint(u); readint(v);
        switch(op) {
            case 'Q':
                q[++Q1] = Query(u, v, Q2, i);
                break;
            case 'R':
                mod[++Q2] = Modify(u, v, B[u], i); 
                B[u] = v;
                break;
        }
    }
    sort(q+1, q+Q1+1);
}

inline void add(int Clr) {
    if(M[Clr]++ == 0) NowAns++;
}

inline void sub(int Clr) {
    if(--M[Clr] == 0) NowAns--;
}

inline void goforth(int t) {
    //先把修改点纳入当前区间！ 
    while(L > mod[t].p) add(A[--L]);
    while(R < mod[t].p) add(A[++R]);
    A[mod[t].p] = mod[t].val;
    sub(mod[t].orig); add(mod[t].val);
}

inline void goback(int t) {
    while(L > mod[t].p) add(A[--L]);
    while(R < mod[t].p) add(A[++R]);
    A[mod[t].p] = mod[t].orig; //改回去！
    sub(mod[t].val); add(mod[t].orig);
}

void Work() {
    L=1, R=0, T=0;
    for(int i=1; i<=Q1; i++) {
        while(T < q[i].T) goforth(++T);
        while(T > q[i].T) goback(T--); //先调整时间后调整区间
        while(R < q[i].R) add(A[++R]);
        while(L > q[i].L) add(A[--L]);
        while(R > q[i].R) sub(A[R--]);
        while(L < q[i].L) sub(A[L++]);
        Ans[q[i].id] = NowAns;
    }
    for(int i=1; i<=Q; i++) 
        if(Ans[i]) {
            printf("%d\n", Ans[i]);
        }
}

int main() {
    Init(); Work();
    return 0;
}