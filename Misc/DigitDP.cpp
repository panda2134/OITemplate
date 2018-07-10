#include <bits/stdc++.h>
using namespace std;

struct state_t {
    int64_t cnt[10];

    state_t() { memset(cnt, 0, sizeof(cnt)); }

    state_t operator+(const state_t &rhs) const {
        state_t ret;
        for(int i = 0; i < 10; i++) {
            ret[i] += cnt[i];
            ret[i] += rhs.cnt[i];
        }
        return ret;
    }

    state_t operator-(const state_t &rhs) const {
        state_t ret;
        for(int i = 0; i < 10; i++) {
            ret[i] += cnt[i];
            ret[i] -= rhs.cnt[i];
        }
        return ret;
    }

    state_t operator+=(const state_t &rhs) { return (*this) = (*this) + rhs; }
    state_t operator-=(const state_t &rhs) { return (*this) = (*this) - rhs; }

    int64_t& operator[](const int idx) {
        assert(idx >= 0 && idx <= 9);
        return cnt[idx];
    }
};

const int64_t pow_base10[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000,
                        10000000000ll, 100000000000ll, 1000000000000ll, 10000000000000ll };

const int MAX_LEN = 15;

bool vis[MAX_LEN + 10];
state_t f[MAX_LEN + 10];

state_t dp(int len) {
    if(vis[len] || len == 0) return f[len];
    else {
        vis[len] = true;
        for(int i = 0; i < 10; i++) {
            state_t cur = dp(len-1);
            cur[i] += pow_base10[len-1];
            f[len] += cur;
        }
        return f[len];
    }
}

int64_t to_int64(string s) {
    int len = s.length();
    int64_t ret = 0ll;
    for(int i = 0; i < len; i++)
        ret += (s[len-i-1]-'0') * pow_base10[i];
    return ret;
}

state_t dfs(string s, bool first = false) {
    state_t ret;
    int nxt, len = s.length();
    if(len == 0) return state_t();

    if(s != "0") {
        for(nxt = 1; nxt < len && !(s[nxt]-'0'); ++nxt);

        if(first) {
            ret[0]++; // for "0"
            for(int i = 1; i < len; i++)
                for(int high = 1; high < 10; high++) {
                    state_t cur = dp(i-1);
                    cur[high] += pow_base10[i-1];
                    ret += cur;
                }
        }

        int lbound = first ? 1 : 0;
        for(int high = lbound; high < (s[0]-'0'); high++) {
            state_t cur = dp(len-1);
            cur[high] += pow_base10[len-1];
            ret += cur;
        }

        int64_t left = 1ll + (nxt < len ? to_int64(s.substr(nxt)) : 0);
        ret[s[0]-'0'] += left;
        ret[0] += (nxt - 1) * left;

        if(nxt < len) ret += dfs(s.substr(nxt));
    } else {
        assert(first);
        ret[0]++;
    }
    return ret;
}

int64_t a, b;
state_t ans;

int main() {
    cin >> a >> b;
    ans = dfs(to_string(b), true) - dfs(to_string(a-1), true);
    for(int i = 0; i < 10; i++) cout << ans[i] << ' ';
    return 0;
}