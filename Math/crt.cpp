#include <bits/stdc++.h>
using namespace std;

typedef long long int64;
const int MAXN = 1e5;
int n; int64 a[MAXN+10], m[MAXN+10];

void exgcd(int64 a, int64 b, int64 &d, int64 &x, int64 &y) {
	if(b == 0) { d = a, x = 1, y = 0; }
	else {
		exgcd(b, a % b, d, y, x); y -= x * (a / b);
	}
}

int64 china(int n, int64 a[], int64 m[]) {
	int64 M = 1, ret = 0, Mi, Minv, d, y;
	for(int i = 1; i <= n; i++)
		M *= m[i];
	for(int i = 1; i <= n; i++) {
		Mi = M / m[i];
		exgcd(Mi, m[i], d, Minv, y);
		assert(d == 1);
		ret = (ret + Mi * Minv % M * a[i] % M) % M;
	}
	ret = (ret + M) % M;
	return ret;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; i++)
		scanf("%lld%lld", &a[i], &m[i]);
	printf("%lld\n", china(n, a, m));
	return 0;
}