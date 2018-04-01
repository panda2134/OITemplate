#include <bits/stdc++.h>
#define Mid(x, y) (((x) + (y)) >> 1)
using namespace std;

const int MAXN = 1000, BKT = MAXN * MAXN * 16, INF = 0x3f3f3f3f;

int n, q, w[MAXN+10][MAXN+10];

inline char readch() {
	char c=getchar();
	while(!isalnum(c) && !ispunct(c))
		c=getchar();
	return c;
}

inline int readint() {
	int f=1, r=0; char c=getchar();
	while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
	while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
	return f*r;
}

void init() {
	n = readint();
	for(int i = 1; i <= n; i++)
		for(int j = 1; j <= n; j++)
			w[i][j] = readint();
}

void work() {
	int op, X1, Y1, X2, Y2, val;
	int maxv, minv;
	q = readint();
	while(q--) {
		op = readch();
		switch(op) {
			case 'q':
				X1 = readint(); Y1 = readint();
				X2 = readint(); Y2 = readint();
				maxv = -INF, minv = INF;
				for(int i = X1; i <= X2; i++)
					for(int j = Y1; j <= Y2; j++) {
						maxv = max(maxv, w[i][j]);
						minv = min(minv, w[i][j]);
					}
				printf("%d %d\n", maxv, minv);
			break;
			case 'c':
				X1 = readint(); Y1 = readint();
				val = readint();
				w[X1][Y1] = val;
			break;
		}
	}
}

int main() {
	init(); work();
	return 0;
}