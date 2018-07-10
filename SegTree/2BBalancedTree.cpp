#include <bits/stdc++.h>
#define Mid(x, y) (((x)+(y)) >> 1)
using namespace std;

const int MAXN = 5e4, NOT_FOUND = 2147483647;

struct Query {
    int type, a, b, c;
} qry[MAXN+10];

int n, q, cnt, lc[MAXN*300], rc[MAXN*300], sumv[MAXN*300];
int rt[MAXN+10], w[MAXN+10], nums[(MAXN+10)<<1]; 
// nums要开成所有数字的种类的大小！或者直接开输入的4倍！第二次错了！

void maintain(int o, int L, int R) {
    if(L != R)
        sumv[o] = sumv[lc[o]] + sumv[rc[o]];
}

void st_add(int &o, int L, int R, int p, int val) {
    if(!o) o = ++cnt;
    if(L == R) sumv[o] += val;
    else {
        if(p <= Mid(L, R))
            st_add(lc[o], L, Mid(L, R), p, val);
        else
            st_add(rc[o], Mid(L, R)+1, R, p, val);
        maintain(o, L, R);
    }
}

int st_kth(vector<int> &o, vector<int> &his, int L, int R, int k) {
    if(L == R)
        return L;
    else {
        int lc_sum = 0;
        for(int &x : o)   lc_sum += sumv[lc[x]];
        for(int &x : his) lc_sum -= sumv[lc[x]];
        if(k <= lc_sum) {
            for(int &x : o)   x = lc[x];
            for(int &x : his) x = lc[x];
            return st_kth(o, his, L, Mid(L, R), k);
        } else {
            k -= lc_sum;
            for(int &x : o)   x = rc[x];
            for(int &x : his) x = rc[x];
            return st_kth(o, his, Mid(L, R)+1, R, k);
        }
    }
}

int st_sum(vector<int> &o, vector<int> &his, int L, int R, int qL, int qR) {
    int ret = 0;
    if(qL <= L && R <= qR) {
        for(int &x : o)   ret += sumv[x];
        for(int &x : his) ret -= sumv[x];
    } else {
        vector<int> o2 = o, his2 = his;
        if(qL <= Mid(L, R)) {
            for(int &x : o)   x = lc[x];
            for(int &x : his) x = lc[x];
            ret += st_sum(o, his, L, Mid(L, R), qL, qR);
        }
        o = o2, his = his2;
        if(qR >= Mid(L, R)+1) {
            for(int &x : o)   x = rc[x];
            for(int &x : his) x = rc[x];
            ret += st_sum(o, his, Mid(L, R)+1, R, qL, qR);
        }
    }
    return ret;
}

inline int lowbit(int x) { return x & (-x); }

inline void bit_sum(int p, vector<int> &o) {
    while(p > 0) {
        o.push_back(rt[p]);
        p -= lowbit(p);
    }
}

inline void bit_add(int p, int w, int val) {
    while(p <= n) {
        st_add(rt[p], 1, nums[0], w, val);
        p += lowbit(p);
    }
}

inline int kth(int L, int R, int k) {
    vector<int> o, his;
    bit_sum(R, o); bit_sum(L-1, his);
    return st_kth(o, his, 1, nums[0], k);
}

inline int getrank(int L, int R, int val) {
    vector<int> o, his;
    bit_sum(R, o); bit_sum(L-1, his);
    if(val != 1)
        return st_sum(o, his, 1, nums[0], 1, val - 1) + 1;
    else
        return 1;
}

inline int count(int L, int R, int val) {
    vector<int> o, his;
    bit_sum(R, o); bit_sum(L-1, his);
    return st_sum(o, his, 1, nums[0], val, val);
}

inline void modify(int p, int val) {
    bit_add(p, w[p], -1);
    w[p] = val;
    bit_add(p, w[p], 1);
}

inline int pre(int L, int R, int val) {
    int rk = getrank(L, R, val);
    if(rk == 1) return -NOT_FOUND;
    return kth(L, R, rk-1);
}

inline int suf(int L, int R, int val) {
    int rk = getrank(L, R, val), cnt = count(L, R, val);
    if(rk + cnt - 1 == R - L + 1) return NOT_FOUND;
    return kth(L, R, rk + cnt);
}

inline int readint() {
    int f=1, r=0; char c=getchar();
    while(!isdigit(c)) { if(c=='-')f=-1; c=getchar(); }
    while(isdigit(c))  { r=r*10+c-'0';   c=getchar(); }
    return f*r;
}

int main() {
    int ans;
    n = readint(); q = readint();
    for(int i = 1; i <= n; i++) {
        w[i] = readint();
        nums[++nums[0]] = w[i];
    }
    for(int i = 1; i <= q; i++) {
        qry[i].type = readint();
        switch(qry[i].type) {
            case 1: case 2: case 4: case 5:
                qry[i].a = readint(); qry[i].b = readint(); qry[i].c = readint();
                if(qry[i].type != 2) nums[++nums[0]] = qry[i].c;
                break;
            case 3:
                qry[i].a = readint(); qry[i].b = readint();
                nums[++nums[0]] = qry[i].b;
                break;
        }
    }
    
    sort(nums + 1, nums + nums[0] + 1);
    nums[0] = unique(nums + 1, nums + nums[0] + 1) - &nums[1];
    
    for(int i = 1; i <= n; i++) {
        w[i] = lower_bound(nums + 1, nums + nums[0] + 1, w[i]) - nums;
        bit_add(i, w[i], 1);
    }
    
    for(int i = 1; i <= q; i++) {
        switch(qry[i].type) {
            case 1: case 4: case 5:
                qry[i].c = lower_bound(nums + 1, nums + nums[0] + 1, qry[i].c) - nums;
                break;
            case 3:
                qry[i].b = lower_bound(nums + 1, nums + nums[0] + 1, qry[i].b) - nums;
                break;
        }
    }
    for(int i = 1; i <= q; i++) {
        switch(qry[i].type) {
            case 1:
                printf("%d\n", getrank(qry[i].a, qry[i].b, qry[i].c));
                break;
            case 2:
                printf("%d\n", nums[kth(qry[i].a, qry[i].b, qry[i].c)]);
                break;
            case 3:
                modify(qry[i].a, qry[i].b);
                break;
            case 4:
                ans = pre(qry[i].a, qry[i].b, qry[i].c);
                if(ans != -NOT_FOUND) ans = nums[ans];
                printf("%d\n", ans);
                break;
            case 5:
                ans = suf(qry[i].a, qry[i].b, qry[i].c);
                if(ans != NOT_FOUND) ans = nums[ans];
                printf("%d\n", ans);
                break;
        }
    }
    return 0;
}