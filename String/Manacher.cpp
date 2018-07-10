#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1.1e7 * 2;

char str[MAXN + 10];

int manacher(char *buf) {
    static char s[MAXN + 10];
    static int r[MAXN + 10];
    int n = strlen(buf);

    int p = 0; s[p++] = '#';
    for(int i = 0; i < n; i++) {
        s[p++] = buf[i], s[p++] = '#';
    }

    n = strlen(s) - 1;
    int pos = 0, mx = 0, ans = 0;
    for(int i = 1; i <= n; i++) {
        if(i > mx) r[i] = 1;
        else r[i] = min(r[2*pos-i], mx-i);
        while(i-r[i] >= 0 && i+r[i] <= n && s[i-r[i]] == s[i+r[i]]) ++r[i];
        if(i+r[i]-1 > mx) {
            mx = i+r[i]-1; pos = i;
        }
        ans = max(ans, r[i]-1);
    }
    return ans;
}

int main() {
    scanf("%s", str);
    cout << manacher(str);
    return 0;
}