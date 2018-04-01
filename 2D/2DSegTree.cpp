#include <bits/stdc++.h>
#define Mid(x, y) (((x) + (y)) >> 1)
using namespace std;

const int MAXN = 1000, BKT = MAXN * MAXN;

struct Info {
	int maxv, minv;
	Info() { maxv = INT_MIN; minv = INT_MAX; }
	Info(int mx, int mi) { maxv = mx, minv = mi; }
	friend Info operator+(const Info &lhs, const Info &rhs) {
		return Info(max(lhs.maxv, rhs.maxv), min(lhs.minv, rhs.minv));
	}
	Info operator+=(const Info &rhs) { return *this = *this + rhs; }
};

int n, q, nd_cnt, rt, rt2d[BKT], lc[BKT], rc[BKT]; Info v[BKT];

inline void maintain(int o, int L, int R) {
	if(L != R)
		v[o] = v[lc[o]] + v[rc[o]];
}

void insert2d(int &o, int L, int R, int p, int val) {
	if(!o) o = ++nd_cnt;
	if(L == R) {
		v[o].maxv = max(v[o].maxv, val);
		v[o].minv = min(v[o].minv, val);
	} else {
		if(p <= Mid(L, R))
			insert2d(lc[o], L, Mid(L, R), p, val);
		else
			insert2d(rc[o], Mid(L, R)+1, R, p, val);
	}
	maintain(o, L, R);
}

Info query2d(int o, int L, int R, int qL, int qR) {
	if(!o) return Info();
	if(qL <= L && R <= qR)
		return v[o];
	else {
		Info ret;
		if(qL <= Mid(L, R))
			ret += query2d(lc[o], L, Mid(L, R), qL, qR);
		if(qR >= Mid(L, R)+1)
			ret += query2d(rc[o], Mid(L, R)+1, R, qL, qR);
		return ret;
	}
}

void insert1d(int &o, int L, int R, int x, int y, int val) {
	if(!o) o = ++nd_cnt;
	insert2d(rt2d[o], 1, n, y, val);
	if(L == R)
		return;
	else {
		if(x <= Mid(L, R))
			insert1d(lc[o], L, Mid(L, R), x, y, val);
		else
			insert1d(rc[o], Mid(L, R)+1, R, x, y, val);
	}
}

Info query1d(int &o, int L, int R, int qLX, int qRX, int qLY, int qRY) {
	if(!o) return Info();
	if(qLX <= L && R <= qRX)
		return query2d(rt2d[o], 1, n, qLY, qRY);
	else {
		Info ret;
		if(qLX <= Mid(L, R))
			ret += query1d(lc[o], L, Mid(L, R), qLX, qRX, qLY, qRY);
		if(qRX >= Mid(L, R)+1)
			ret += query1d(rc[o], Mid(L, R)+1, R, qLX, qRX, qLY, qRY);
		return ret;
	}
}

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
			insert1d(rt, 1, n, i, j, readint());
}

void work() {
	int op, X1, Y1, X2, Y2, val;
	Info res;
	q = readint();
	while(q--) {
		op = readch();
		switch(op) {
			case 'q':
				X1 = readint(); Y1 = readint();
				X2 = readint(); Y2 = readint();
				res = query1d(rt, 1, n, X1, X2, Y1, Y2);
				printf("%d %d\n", res.maxv, res.minv);
			break;
			case 'c':
				X1 = readint(); Y1 = readint();
				val = readint();
				insert1d(rt, 1, n, X1, Y1, val);
			break;
		}
	}
}

int main() {
	init(); work();
	return 0;
}