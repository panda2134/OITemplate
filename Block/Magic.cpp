#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6, INF = 0x3f3f3f3f;
int N, Q, BlkSize, A[MAXN+10], B[MAXN+10], Blk[MAXN+10], 
	L[MAXN+10], R[MAXN+10], Addv[MAXN+10];

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

inline void InitBlk() {
	BlkSize = ceil(sqrt(N));
	for(int i=0; i*BlkSize + 1 <= N; i++) { //注意在分块时考虑末尾块的情况！ 
		L[i] = i*BlkSize + 1, R[i] = min((i+1)*BlkSize, N);
		for(int j=L[i]; j<=R[i]; j++) {
			Blk[j] = i; B[j] = A[j];
		}
		sort(B+L[i], B+R[i]+1);
	}
}

inline void Maintain(int o) {
	for(int i=L[o]; i<=R[o]; i++)
		B[i] = A[i];
	sort(B+L[o], B+R[o]+1);
}

inline void Add(int qL, int qR, int v) {
	if(Blk[qL] == Blk[qR]) {
		for(int i=qL; i<=qR; i++)
			A[i] += v;
		Maintain(Blk[qL]);
	} else {
		for(int i=qL; Blk[i] == Blk[qL]; i++) 
			A[i] += v;
		for(int i=qR; Blk[i] == Blk[qR]; i--)
			A[i] += v;
		Maintain(Blk[qL]); Maintain(Blk[qR]);
		for(int i=Blk[qL]+1; i<=Blk[qR]-1; i++)
			Addv[i] += v;
	}
}

inline int Query(int qL, int qR, int v) { //>=v
	int ret = 0, p;
	if(Blk[qL] == Blk[qR]) {
		for(int i=qL; i<=qR; i++)
			if(A[i] + Addv[Blk[i]] >= v) ret++;
		return ret;
	} else {
		for(int i=qL; Blk[i] == Blk[qL]; i++)
			if(A[i] + Addv[Blk[i]] >= v) ret++;
		for(int i=qR; Blk[i] == Blk[qR]; i--)
			if(A[i] + Addv[Blk[i]] >= v) ret++;
		for(int i=Blk[qL]+1; i<=Blk[qR]-1; i++) {
			p = lower_bound(B+L[i], B+R[i]+1, v-Addv[i]) - (B+L[i]);
			ret += R[i] - L[i] + 1 - p;
		}
		return ret;
	}
}

void Init() {
	readint(N); readint(Q);
	for(int i=1; i<=N; i++) readint(A[i]);
	InitBlk();
}

void Work() {
	int l, r, v; char op;
	while(Q--) {
		op = readc(); readint(l); readint(r); readint(v);
		switch(op) {
		case 'M':
			Add(l, r, v);
			break;
		case 'A':
			printf("%d\n", Query(l, r, v));
			break;
		}
	}
}

int main() {
	Init(); Work();
	return 0;
}