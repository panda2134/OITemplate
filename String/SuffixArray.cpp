#include <bits/stdc++.h>
using namespace std;

const int MAXN = 8e6, SIGMA = 128; // ascii 0 - 127

struct SuffixArray {
    
    int sa[MAXN + 10], buf[3][MAXN + 10], c[SIGMA + 10], rk[MAXN + 10], height[MAXN + 10];
    
    void build_sa(char *str) {
        int n = strlen(str) + 1, m = SIGMA, p = 0;
        int *x = buf[0], *y = buf[1];
        
        for(int i = 0; i < m; i++) c[i] = 0;
        for(int i = 0; i < n; i++) ++c[x[i] = str[i]];
        for(int i = 1; i < m; i++) c[i] += c[i-1];
        for(int i = n-1; i >= 0; i--) sa[--c[x[i]]] = i;
        for(int k = 1; k <= n; k <<= 1) {
            p = 0;
            
            for(int i = n-k; i < n; i++) y[p++] = i;
            for(int i = 0; i < n; i++) if(sa[i] >= k) y[p++] = sa[i] - k;
            
            for(int i = 0; i < m; i++) c[i] = 0;
            for(int i = 0; i < n; i++) ++c[x[y[i]]];
            for(int i = 1; i < m; i++) c[i] += c[i-1];
            for(int i = n-1; i >= 0; i--) sa[--c[x[y[i]]]] = y[i];
            
            swap(x, y);
            p = 1, x[sa[0]] = 0;
            for(int i = 1; i < n; i++)
                x[sa[i]] = (y[sa[i]] == y[sa[i-1]] and y[sa[i]+k] == y[sa[i-1]+k]) ? p-1 : p++;
            
            if(p == n) break;
            else m = p;
        }
        
        memcpy(rk, x, sizeof(rk)); // sizeof(rk)! 不要取指针大小！
        int k = 0;
        for(int i = 0; i < n; i++) {
            if(k) k--;
            if(!rk[i]) continue;
            int j = sa[rk[i]-1];
            while(str[i+k] == str[j+k]) k++;
            height[rk[i]] = k;
        }
    }
} sa;

int len;
char buf[MAXN + 10];

int main() {
    scanf("%s", buf); len = strlen(buf);
    sa.build_sa(buf);
    for(int i = 1; i <= len; i++)
        printf("%d ", sa.sa[i] + 1);
    return 0;
}