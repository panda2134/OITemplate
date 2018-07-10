#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5e4, MAXQ = 2e5, MAXC = 1e6;
int N, Q, BlkSize, L, R, NowAns, A[MAXN+10], M[MAXC+10], Ans[MAXQ+10];

struct Query {
    int L, R, id;
    Query() {}
    Query(int l, int r, int i): L(l),R(r),id(i) {}
    inline bool operator<(const Query& rhs) const {
        return L/BlkSize == rhs.L/BlkSize ? 
            R < rhs.R : L/BlkSize < rhs.L/BlkSize;
    }
} q[MAXQ+10];

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

inline void readstr(char *str) {
    char c=getchar(); int p=0;
    while(!isalnum(c) && !ispunct(c)) c=getchar();
    while(isalnum(c) || ispunct(c)) {
        str[p++]=c;
        c=getchar();
    }
    str[p]='\0';
}

void Init() {
    int u, v;
    readint(N); BlkSize = ceil(sqrt(N));
    for(int i=1; i<=N; i++) 
        readint(A[i]);
    readint(Q);
    for(int i=1; i<=Q; i++) {
        readint(u); readint(v);
        q[i] = Query(u, v, i);
    }
    sort(q+1, q+Q+1);
}

inline void Add(int Clr) {
    if(M[Clr]++ == 0) NowAns++;
}

inline void Sub(int Clr) {
    if(--M[Clr] == 0) NowAns--;
}

void Work() {
    L=1, R=0; NowAns=0;
    for(int i=1; i<=Q; i++) {
        while(R < q[i].R) Add(A[++R]);
        while(L > q[i].L) Add(A[--L]);
        while(R > q[i].R) Sub(A[R--]);
        while(L < q[i].L) Sub(A[L++]);
        Ans[q[i].id] = NowAns;
    }
    for(int i=1; i<=Q; i++)
        printf("%d\n", Ans[i]);
}

int main() {
    Init(); Work();
    return 0;
}