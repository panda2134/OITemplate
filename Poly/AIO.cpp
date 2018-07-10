#include <bits/stdc++.h>
using namespace std;

namespace polynomial {
    const int MAXN = 100000 << 2, MOD = 998244353, G = 3;
    int p_omega[MAXN + 10], p_inv[MAXN + 10];

    inline int pls(int a, int b) {
        int ret = (a + b);
        if(ret >= MOD) ret -= MOD;
        return ret;
    }

    inline int dec(int a, int b) {
        int ret = (a - b);
        if(ret < 0) ret += MOD;
        return ret;
    }

    inline int mul(int a, int b) { return (1ll * a) * b % MOD; }

    inline int fpow(int a, int x) {
        int ret = 1;
        while(x) {
            if(x & 1) ret = mul(ret, a);
            x >>= 1;
            a = mul(a, a);
        }
        return ret;
    }

    inline int mod_inv(int x) { return fpow(x, MOD - 2); }

    //-------------------NTT----------------------

    void init_omega() {
        for(int step = 1; step <= MAXN; step <<= 1) {
            p_omega[step] = fpow(G, (MOD - 1) / step);
            p_inv[step] = fpow(G, (MOD - 1) / step * (step - 1));
        }
    }

    struct _omega_init_t {
        _omega_init_t() { init_omega(); }
    } _omega_init;

    inline int get_rt(int step, bool idft) {
        return !idft ? p_omega[step] : p_inv[step];
    }

    inline void NTT(int len, int A[], bool idft = false) {
        static int rev[MAXN + 10];
        for(int i = 0; i < len; i++)
            rev[i] = (((rev[i >> 1] >> 1) | (len >> (i & 1))) & (len - 1));
        for(int i = 0; i < len; i++)
            if(rev[i] > i) swap(A[i], A[rev[i]]);

        for(int step = 1; step < len; step <<= 1) {
            int rt = get_rt(step << 1, idft);
            for(int i = 0; i < len; i += (step << 1)) {
                for(int j = 0, omega = 1; j < step;
                    j++, omega = mul(omega, rt)) {
                    int t = mul(A[i + j + step], omega);
                    A[i + j + step] = dec(A[i + j], t);
                    A[i + j] = pls(A[i + j], t);
                }
            }
        }

        if(idft) {
            int t = mod_inv(len);
            for(int i = 0; i < len; i++) A[i] = mul(A[i], t);
        }
    }

    inline void conv(int deg, int A0[], int B0[], int C[]) {
        static int A[MAXN + 10], B[MAXN + 10];
        int len;
        copy(A0, A0+deg+1, A), copy(B0, B0+deg+1, B);
        for(len = 1; len < deg * 2 + 1; len <<= 1);
        fill(A+deg+1, A+len, 0), fill(B+deg+1, B+len, 0); // !!
        NTT(len, A), NTT(len, B);
        for(int i = 0; i < len; i++) C[i] = mul(A[i], B[i]);
        NTT(len, C, true);
    }
    //-------------------Polynomial Add and Substract----------

    void poly_add(int deg, int A[], int B[], int C[]) {
        for(int i = 0; i <= deg; i++) C[i] = pls(A[i], B[i]);
    }

    void poly_sub(int deg, int A[], int B[], int C[]) {
        for(int i = 0; i <= deg; i++) C[i] = dec(A[i], B[i]);
    }

    //------------Polynomial Integral and Derivative-----------

    void poly_int(int deg, int A[], int B[]) {
        B[0] = 0;
        for(int i = 1; i <= deg + 1; i++)
            B[i] = mul(A[i - 1], mod_inv(i));
    }

    void poly_d(int deg, int A[], int B[]) {
        for(int i = 0; i <= deg - 1; i++)
            B[i] = mul(i + 1, A[i + 1]);
        B[deg] = 0;
    }

    //-------------------Polynomial inverse------------------

    void poly_inv(int deg, int A[], int B[]) { // mod $x^{\deg}$
        int tmp[MAXN + 10];
        if(deg == 1) {
            assert(A[0] != 0);
            B[0] = mod_inv(A[0]);
        } else {
            poly_inv((deg + 1) >> 1, A, B);
            int len;
            for(len = 1; len < 2 * deg; len <<= 1); // !!
            copy(A, A+deg, tmp); fill(tmp+deg, tmp+len, 0);
            NTT(len, tmp); NTT(len, B);
            for(int i = 0; i < len; i++)
                B[i] = mul(B[i], dec(2, mul(tmp[i], B[i])));
            NTT(len, B, true);
            fill(B+deg, B+len, 0); // !!
        }
    }

    //--------------------Polynomial division-----------------

    void poly_div(int n, int m, int A0[], int B0[], int Q[], int R[]) { // mod $x^{\deg}$
        int A[MAXN + 10], B[MAXN + 10], tmp[MAXN + 10];
        fill(A, A+MAXN, 0); fill(B, B+MAXN, 0); fill(tmp, tmp+MAXN, 0);
        copy(A0, A0+n+1, A), copy(B0, B0+m+1, B);
        reverse(A, A+n+1), reverse(B, B+m+1);
        poly_inv(n-m+1, B, tmp);
        conv(n-m, A, tmp, Q);
        fill(Q+n-m+1, Q+n+1, 0);
        reverse(Q, Q+n-m+1);
        copy(A0, A0+n+1, A), copy(B0, B0+m+1, B);
        conv(n, B, Q, tmp);
        poly_sub(n, A, tmp, R);
        fill(R+m, R+n+1, 0);
    }

    //--------------------Polynomial ln------------------------

    void poly_ln(int deg, int A0[], int B[]) { // mod $x^{\deg}$
        static int A[MAXN + 10], A1[MAXN + 10], tmp[MAXN + 10];
        fill(A, A + MAXN, 0); fill(A1, A1 + MAXN, 0); fill(tmp, tmp + MAXN, 0);
        copy(A0, A0+deg, A);
        poly_d(deg - 1, A, A1);
        poly_inv(deg, A, tmp);
        copy(tmp, tmp + deg, A);
        conv(deg-1, A, A1, tmp);
        poly_int(deg-1, tmp, B);
    }

    //--------------------Polynomial exp-----------------------

    void poly_exp(int deg, int A[], int B[]) { // mod $x^{\deg}$
        static int tmp[MAXN + 10];
        fill(tmp, tmp + MAXN, 0);
        if(deg == 1) {
            B[0] = 1;
        } else {
            int half = (deg + 1) >> 1;
            poly_exp(half, A, B);
            fill(B+half, B+deg, 0);

            poly_ln(deg, B, tmp);
            poly_sub(deg - 1, A, tmp, tmp);
            conv(deg - 1, tmp, B, tmp);
            poly_add(deg - 1, B, tmp, B);
        }
    }
}