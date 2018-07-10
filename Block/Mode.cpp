#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e5, SQN = 316;
int N, Q, BlkSize, MxBlk, A[MAXN+10], Blk[MAXN+10], L[MAXN+10], R[MAXN+10];
int Num[MAXN+10], Mode[SQN+10][SQN+10], PreCnt[SQN+10][MAXN+10];

inline void InitBlk() {
    static int Md, Bkt[MAXN+10];
    BlkSize = ceil(sqrt(N)) + 0.5;
    for(int i=0; i * BlkSize + 1 <= N; i++) {
        MxBlk = i;
        L[i] = i * BlkSize + 1, R[i] = min(N, (i+1) * BlkSize);
        for(int j = L[i]; j <= R[i]; j++) Blk[j] = i;
    }
    for(int i = 1; i <= N; i++) 
        PreCnt[Blk[i]][A[i]]++;
    for(int i = 1; i <= MxBlk; i++)
        for(int j = 1; j <= N; j++)
            PreCnt[i][j] += PreCnt[i-1][j];
    for(int i = 0; i <= MxBlk; i++) {
        for(int j = i; j <= MxBlk; j++) {
            if(i < j) Md = Mode[i][j-1];
            else Md = 0;
            for(int k = L[j]; k <= R[j]; k++) {
                Bkt[A[k]]++;									// !!!
                int lhs = Bkt[A[k]] + (i < j ? PreCnt[j-1][A[k]] - (i>=1 ? PreCnt[i-1][A[k]] : 0) : 0);
                int rhs = Bkt[Md] + (i < j ? PreCnt[j-1][Md] - (i>=1 ? PreCnt[i-1][Md] : 0) : 0);
                if(lhs > rhs || (lhs == rhs && A[k] < Md)) 
                    Md = A[k];
            }
            Mode[i][j] = Md;
            for(int k = L[j]; k <= R[j]; k++) Bkt[A[k]]--;
        }
    }
}

int Query(int qL, int qR) {
    static int Md, Bkt[MAXN+10];
    if(Blk[qL] == Blk[qR]) {
        Md = 0;
        for(int i = qL; i <= qR; i++) {
            Bkt[A[i]]++;
            if(Bkt[A[i]] > Bkt[Md] || (Bkt[A[i]] == Bkt[Md] && A[i] < Md)) 
                Md = A[i];
        }
        for(int i = qL; i <= qR; i++) Bkt[A[i]]--;
        return Md;
    } else {
        if(Blk[qL] + 1 <= Blk[qR] - 1)
            Md = Mode[Blk[qL]+1][Blk[qR]-1];
        else Md = 0;
        for(int i = qL; Blk[i] == Blk[qL]; i++) {
            ++Bkt[A[i]];
            int lhs = Bkt[A[i]] + (Blk[qL]+1 <= Blk[qR]-1 ? 
                PreCnt[Blk[qR]-1][A[i]] - PreCnt[Blk[qL]][A[i]] : 0);
            int rhs = Bkt[Md] + (Blk[qL]+1 <= Blk[qR]-1 ? 
                PreCnt[Blk[qR]-1][Md] - PreCnt[Blk[qL]][Md] : 0);
            if(lhs > rhs || (lhs == rhs && A[i] < Md)) 
                Md = A[i];
        }
        for(int i = qR; Blk[i] == Blk[qR]; i--) {
            ++Bkt[A[i]];
            int lhs = Bkt[A[i]] + (Blk[qL]+1 <= Blk[qR]-1 ? 
                PreCnt[Blk[qR]-1][A[i]] - PreCnt[Blk[qL]][A[i]] : 0);
            int rhs = Bkt[Md] + (Blk[qL]+1 <= Blk[qR]-1 ? 
                PreCnt[Blk[qR]-1][Md] - PreCnt[Blk[qL]][Md] : 0);
            if(lhs > rhs || (lhs == rhs && A[i] < Md)) 
                Md = A[i];
        }
        for(int i = qL; Blk[i] == Blk[qL]; i++) --Bkt[A[i]];
        for(int i = qR; Blk[i] == Blk[qR]; i--) --Bkt[A[i]];
        return Md;
    }
}

template<typename T>
inline void readint(T& x) {
    T f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    x = f*r;
}

void Init() {
    readint(N); readint(Q);
    for(int i=1; i<=N; i++) {
        readint(A[i]);
        Num[++Num[0]] = A[i];
    }
    sort(Num+1, Num+Num[0]+1);
    Num[0] = unique(Num+1, Num+Num[0]+1) - Num - 1;
    for(int i=1; i<=N; i++)
        A[i] = lower_bound(Num+1, Num+Num[0]+1, A[i]) - Num;
    InitBlk();
}

void Work() {
    int l, r, LastAns = 0;
    for(int i=1; i<=Q; i++) {
        readint(l); readint(r);
        l = (l + LastAns - 1) % N + 1;
        r = (r + LastAns - 1) % N + 1;
        if(l > r) swap(l, r);
        printf("%d\n", LastAns = Num[Query(l, r)]);
    }
}

int main() {
    Init(); Work();
    return 0;
}