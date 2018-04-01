#include <bits/stdc++.h>
using namespace std;

const int MAXLEN = 1e6, SIGMA = 100;

inline int idx(char c) {
    if(!c) return 0;
    else if(isdigit(c)) return c - '0' + 1;
    else if(isupper(c)) return c - 'A' + 1 + 10;
    else if(islower(c)) return c - 'a' + 1 + 10 + 26;
    else throw "Invalid Character";
}

struct SuffixArray {
    int sa[MAXLEN+10], rk[MAXLEN+10], buf[3][MAXLEN+10], height[MAXLEN+10], c[MAXLEN+10];
    void build_sa(char *s, int len) {
        int m = SIGMA + 10, n = len + 1, *x = buf[0], *y = buf[1];
        for(int i = 0; i < m; i++) c[i] = 0;
        for(int i = 0; i < n; i++) ++c[x[i] = idx(s[i])];
        for(int i = 1; i < m; i++) c[i] += c[i-1];
        for(int i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1) {
            int p = 0;
            for(int i = n-k; i < n; i++) y[p++] = i;
            for(int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
            for(int i = 0; i < m; i++) c[i] = 0;
            for(int i = 0; i < n; i++) ++c[x[y[i]]];
            for(int i = 1; i < m; i++) c[i] += c[i-1];
            for(int i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            swap(x, y);
            p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; i++)
                x[sa[i]] = (y[sa[i]] == y[sa[i-1]] && y[sa[i] + k] == y[sa[i-1] + k] ? p-1 : p++);
            if(p >= n) break;
            m = p;
        }
        memcpy(rk, x, sizeof(rk));
        int k = 0;
        for(int i = 0; i < n; i++) {
            if(!rk[i]) continue;
            if(k) k--;
            int j = sa[rk[i]-1];
            while(s[i+k] == s[j+k]) k++;
            height[rk[i]] = k;
        }
    }
} SA;
inline void readstr(char* str) {
    char c=getchar(); int p=0;
    while(!isalnum(c) && !ispunct(c)) c=getchar();
    while(isalnum(c) || ispunct(c)) {
        str[p++] = c;
        c = getchar();
    }
    str[p++] = '\0';
}

int len;
char str[MAXLEN+10];

int main() {
    readstr(str); len = strlen(str);
    SA.build_sa(str, len);
    for(int i = 1; i <= len; i++)
        printf("%d ", SA.sa[i]+1);
    return 0;
}