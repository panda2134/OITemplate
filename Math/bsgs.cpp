#include <bits/stdc++.h>
#include <bits/extc++.h>
#define fst first
#define snd second
using namespace std;
typedef long long i64;

i64 mod;
i64 pls(i64 a, i64 b) { return (a + b) > mod ? (a + b - mod) : (a + b); }
i64 sub(i64 a, i64 b) { return (a - b) < 0 ? (a - b + mod) : (a - b); }
i64 mul(i64 a, i64 b) { return (a * b) % mod; }
i64 fpow(i64 a, i64 x) {
    i64 ret = 1;
    while (x) {
        if (x & 1) ret = mul(ret, a);
        x >>= 1;
        a = mul(a, a);
    }
    return ret;
}
i64 inv(i64 a) { return fpow(a, mod - 2); }

unordered_map<i64, i64> x;
i64 log_mod(i64 a, i64 b) {
    // BSGS: solve $\log_a b \pmod{p}$
    x.clear();
    i64 e = 1, v = 1, w = 1, m = ceil(sqrt(mod));
    x[1] = 0;
    for (i64 i = 1; i < m; i++) {
        e = mul(e, a);
        if (!x.count(e)) x[e] = i;
    }
    v = inv(fpow(a, m));
    for (i64 i = 0; i < m; i++) {
        if (x.count(mul(b, w))) return i * m + x[mul(b, w)];
        w = mul(w, v);
    }
    return -1;
}

int main() {
    i64 a, b;
    while (scanf("%lld%lld%lld", &mod, &a, &b) != EOF) {
        i64 ans = log_mod(a, b);
        if (~ans) printf("%lld\n", ans);
        else puts("no solution");
    }
    return 0;
}