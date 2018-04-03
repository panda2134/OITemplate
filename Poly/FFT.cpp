#include <bits/stdc++.h>

const int MAXN = 4e6;
const double PI = 3.14159265358979323846264338;

struct cpx {
    double real, imag;
    cpx() { real = imag = .0; }
    cpx(double x) { real = x, imag = .0; }
    cpx(double x, double y) { real = x, imag = y; }
    friend cpx operator+(const cpx &lhs, const cpx &rhs) {
        return cpx(lhs.real + rhs.real, lhs.imag + rhs.imag);
    }
    friend cpx operator-(const cpx &lhs, const cpx &rhs) {
        return cpx(lhs.real - rhs.real, lhs.imag - rhs.imag);
    }
    friend cpx operator*(const cpx &lhs, const cpx &rhs) {
        return cpx(lhs.real * rhs.real - lhs.imag * rhs.imag,
            lhs.imag * rhs.real + lhs.real * rhs.imag);
    }
    cpx operator*=(const cpx &rhs) { return (*this) = (*this) * rhs; }
    cpx conj() const { return cpx(real, -imag); }
    friend cpx operator/(const cpx &lhs, double rhs) {
        return cpx(lhs.real / rhs, lhs.imag / rhs);
    }
    friend cpx operator/(const cpx &lhs, const cpx &rhs) {
        cpx ret = lhs * rhs.conj();
        ret.real /= (rhs.real * rhs.real + rhs.imag * rhs.imag);
        ret.imag /= (rhs.real * rhs.real + rhs.imag * rhs.imag);
        return ret;
    }
    cpx operator/=(const cpx &rhs) { return (*this) = (*this) / rhs; }
};

int n, m, R[MAXN+10]; double A[MAXN+10], B[MAXN+10], C[MAXN+10];

inline cpx get_rt(int step, bool inv) { // rotation factor
    return inv ? cpx(std::cos(2*PI / step), -std::sin(2*PI / step)) :
                 cpx(std::cos(2*PI / step), std::sin(2*PI / step));
}

void fft(cpx A[], int len, bool inv) {
    for(int i = 0; i < len; i++)
        if(R[i] > i) std::swap(A[i], A[R[i]]);
    for(int step = 1; step < len; step <<= 1) {
        for(int i = 0; i < len; i += (step<<1)) {
            cpx omega = 1, rt = get_rt(step<<1, inv);
            for(int j = 0; j < step; j++, omega *= rt) {
                cpx t = omega * A[i+j+step];
                A[i+j+step] = A[i+j] - t;
                A[i+j] = A[i+j] + t;
            }
        }
    }
    if(inv)
        for(int i = 0; i < len; i++) A[i] /= len;
}

void conv(double dA[], double dB[], int deg1, int deg2, double dC[]) { // deg: 输入多项式的度数
    int len;
    static cpx A[MAXN+10], B[MAXN+10], C[MAXN+10];
    for(len = 1; len < deg1+deg2+1; len <<= 1); // 考虑乘完后的长度
    for(int i = 0; i < len; i++) {
        A[i] = dA[i], B[i] = dB[i];
    }
    
    R[0] = 0;
    for(int i = 1; i < len; i++)
        R[i] = ((R[i>>1]>>1) | (len >> (i&1))) & (len-1);
    
    fft(A, len, false); fft(B, len, false);
    for(int i = 0; i < len; i++) C[i] = A[i] * B[i];
    fft(C, len, true);
    for(int i = 0; i < len; i++) dC[i] = C[i].real;
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c)) { r=r*10+c-'0'; c=getchar(); }
    return f*r;
}

int main() {
    n = readint(); m = readint();
    for(int i = 0; i <= n; i++) A[i] = readint();
    for(int i = 0; i <= m; i++) B[i] = readint();
    conv(A, B, n, m, C);
    for(int i = 0; i <= n+m; i++) std::printf("%d ", int(round(C[i])));
    return 0;
}
