/*
 * [JSOI2008]最大数
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2e5;
int q, mod, n, last, a[MAXN+10], s[MAXN+10];

int main() {
    char op; int x;
    cin.sync_with_stdio(false);
    cin.tie(NULL);
    cin >> q >> mod;
    while(q--) {
        cin >> op >> x;
        switch(op) {
            case 'Q':
                if(x == 0)
                    cout << (last = 0) << endl;
                else
                    cout << (last = a[*lower_bound(s + 1, s + s[0] + 1, n-x+1)]) << endl;
                break;
            case 'A':
                x = (x + last) % mod;
                while(s[0] && a[s[s[0]]] < x) --s[0];
                s[++s[0]] = ++n; a[n] = x;
                break;
        }
    }
} 
