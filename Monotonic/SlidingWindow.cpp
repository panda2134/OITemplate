#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;

int n, k, Hd, Tl, A[MAXN+10], Q[MAXN+10];

void SlideMin() {
	Hd = 1, Tl = 0;
	for(int i = 1; i <= k; i++) {
		while(Hd <= Tl && A[Q[Tl]] >= A[i]) Tl--;
		Q[++Tl] = i;
	}
	printf("%d ", A[Q[Hd]]);
	for(int i = k+1; i <= n; i++) {
		while(Hd <= Tl && Q[Hd] < i-k+1) Hd++;
		while(Hd <= Tl && A[Q[Tl]] >= A[i]) Tl--;
		Q[++Tl] = i;
		printf("%d ", A[Q[Hd]]);
	}
}

void SlideMax() {
	Hd = 1, Tl = 0;
	for(int i = 1; i <= k; i++) {
		while(Hd <= Tl && A[Q[Tl]] <= A[i]) Tl--;
		Q[++Tl] = i;
	}
	printf("%d ", A[Q[Hd]]);
	for(int i = k+1; i <= n; i++) {
		while(Hd <= Tl && Q[Hd] < i-k+1) Hd++;
		while(Hd <= Tl && A[Q[Tl]] <= A[i]) Tl--;
		Q[++Tl] = i;
		printf("%d ", A[Q[Hd]]);
	}
}

inline int readint() {
	int f=1, r=0; char c=getchar();
	while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
	while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
	return f*r;
}

int main() {
	n = readint(); k = readint();
	for(int i = 1; i <= n; i++) A[i] = readint();
	SlideMin();
	putchar(10);
	SlideMax();
	return 0;
}
