#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1e6;
char s1[MAXN + 10], s2[MAXN + 10];
int n, m, fail[MAXN + 10];

int main() {
    scanf("%s%s", s1, s2);
    n = strlen(s1), m = strlen(s2);
    
    fail[0] = -1;
    
    for(int i = 1; i < m; i++) {
        int j = fail[i-1];
        while(j != -1 && s2[j+1] != s2[i]) j = fail[j];
        if(s2[j+1] == s2[i]) fail[i] = j + 1;
        else fail[i] = -1;
    }
    
    for(int i = 0, j = -1; i < n; i++) {
        while(j != -1 && s2[j+1] != s1[i]) j = fail[j];
        if(s2[j+1] == s1[i]) j++;
        if(j == m-1) {
            printf("%d\n", i-m+2);
            j = fail[j];
        }
    }
    
    for(int i = 0; i < m; i++) printf("%d ", fail[i]+1);
    return 0;
}