#include <bits/stdc++.h>
#define CLEAR(x) memset((x), 0, sizeof(x))
using namespace std;

const int SIGMA = 26, MAX_TEMP_LEN = 70, MAXN = 150, 
MAX_LEN = 1e6, MAX_NODE = MAXN * MAX_TEMP_LEN;

int N, sz, ch[MAX_NODE + 10][SIGMA + 2], f[MAX_NODE + 10], last[MAX_NODE+10],
    val[MAX_NODE + 10], found_cnt[MAX_NODE+10];
char str[MAX_LEN+10], tpl[MAXN+10][MAX_TEMP_LEN+10];
unordered_map<string, int> ms;

inline int idx(char c) { return c - 'a' + 1; }

void insert(char *str) {
    int u = 0, len = strlen(str);
    for(int i = 0; i < len; i++) {
    	int c = idx(str[i]);
    	if(!ch[u][c]) ch[u][c] = ++sz;
    	u = ch[u][c];
    }
    ms[string(str)] = u;
    ++val[u];
}

void get_fail() {
    queue<int> Q;
    f[0] = 0;
    for(int c = 1; c <= SIGMA; c++) if(ch[0][c]) {
    	int v = ch[0][c];
    	f[v] = last[v] = 0;
    	Q.push(v);
    }
    while(!Q.empty()) {
        int u = Q.front(); Q.pop();
        for(int c = 1; c <= SIGMA; c++) {
            int v = ch[u][c];
            if(!v) {
                ch[u][c] = ch[f[u]][c];
                continue;
            }
            
            Q.push(v);
            
            int u2 = f[u];
            while(u2 && !ch[u2][c]) u2 = f[u2];
            f[v] = ch[u2][c];
            last[v] = val[f[v]] ? f[v] : last[f[v]];
        }
    }
}

void found(int u) {
    for(; u; u = last[u])
        found_cnt[u] += val[u];
}

void search(char *str) {
    int u = 0, len = strlen(str);
    for(int i = 0; i < len; i++) {
        int c = idx(str[i]);
        u = ch[u][c];
        if(val[u]) found(u);
        else if(last[u]) found(last[u]);
    }
}

inline void readstr(char *str) {
    char c=getchar(); int p=0;
    while(!isalnum(c) && !ispunct(c)) c = getchar();
    while(isalnum(c) || ispunct(c)) {
        str[p++] = c;
        c = getchar();
    }
    str[p++] = '\0';
}

int main() {
    while(true) {
        int ans = 0;
        sz = 0; CLEAR(ch); CLEAR(f); CLEAR(found_cnt); 
        CLEAR(last); CLEAR(tpl); CLEAR(val); CLEAR(str);
        
        scanf("%d", &N); if(N == 0) break;
        for(int i = 1; i <= N; i++) {
            readstr(tpl[i]); insert(tpl[i]);
        }
        get_fail();
        
        readstr(str); search(str);
        
        for(int i = 0; i <= sz; i++)
            ans = max(ans, found_cnt[i]);
        printf("%d\n", ans);
        for(int i = 1; i <= N; i++)
            if(found_cnt[ms[string(tpl[i])]] == ans)
                printf("%s\n", tpl[i]);
    }
    return 0;
}
