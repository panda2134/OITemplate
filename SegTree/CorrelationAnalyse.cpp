/*
    [SDOI2017] 相关分析
    Coded by panda_2134
*/
#include <bits/stdc++.h>
#define LC(o) ((o)*2)
#define RC(o) ((o)*2+1)
#define Mid(x, y) (((x) + (y)) / 2)
using namespace std;

const double eps = 1e-6, NONE = -1e6;
const int MAXN = 1e5;

int dcmp(double x) {
    return fabs(x) < eps ? 0 : (x > 0 ? 1 : -1);
}

struct Info {
    double x, y, xy, x2;
    Info() { x = y = xy = x2 = .0; }
    Info(double a, double b, double c, double d):
        x(a), y(b), xy(c), x2(d) {}
    Info operator+(const Info &rhs) const {
        return Info(x + rhs.x, y + rhs.y, xy + rhs.xy, x2 + rhs.x2);
    }
    Info operator+=(const Info &rhs) { return *this = *this + rhs; }
};

struct Node {
    double x, y, xy, x2, add_s, add_t, set_s, set_t;
    Node() {
        x = y = xy = x2 = .0;
        add_s = add_t = .0;
        set_s = set_t = NONE;
    }
    void clear() { x = y = xy = x2 = .0; }
} nd[(MAXN+10)<<2];

int n, q;
double X[MAXN+10], Y[MAXN+10];

void Maintain(int o, double L, double R) {
    if(dcmp(nd[o].set_s - NONE) == 0) {
        // no set (if set\_s exists, then set\_t exists, and vice versa)
        assert(dcmp(nd[o].set_t - NONE) == 0);
        nd[o].clear();
        if(L != R) {
            nd[o].x = nd[LC(o)].x + nd[RC(o)].x;
            nd[o].y = nd[LC(o)].y + nd[RC(o)].y;
            nd[o].xy = nd[LC(o)].xy + nd[RC(o)].xy;
            nd[o].x2 = nd[LC(o)].x2 + nd[RC(o)].x2;
        }
    } else {
        nd[o].x2 = (R-L+1) * nd[o].set_s * nd[o].set_s 
            + R * (R+1) * (2*R+1) / 6 - L * (L-1) * (2*L-1) / 6
            + nd[o].set_s * (L+R) * (R-L+1);
        nd[o].xy = (R-L+1) * nd[o].set_s * nd[o].set_t 
            + (nd[o].set_s + nd[o].set_t) * (L+R) * (R-L+1) / 2
            + R * (R+1) * (2*R+1) / 6 - L * (L-1) * (2*L-1) / 6;
        nd[o].x = (R-L+1) * nd[o].set_s + (L+R) * (R-L+1) / 2;
        nd[o].y = (R-L+1) * nd[o].set_t + (L+R) * (R-L+1) / 2;
    }
    nd[o].x2 += 2 * nd[o].add_s * nd[o].x + (R-L+1) * nd[o].add_s * nd[o].add_s;
    nd[o].xy += nd[o].add_t * nd[o].x 
             + nd[o].add_s * nd[o].y + (R-L+1) * nd[o].add_s * nd[o].add_t;
    nd[o].x += (R-L+1) * nd[o].add_s;
    nd[o].y += (R-L+1) * nd[o].add_t; // update last
}

void Pushdown(int o) {
    if(dcmp(nd[o].set_s - NONE) != 0) { // mark exist
        assert(dcmp(nd[o].set_t - NONE) != 0);
        nd[LC(o)].set_s = nd[RC(o)].set_s = nd[o].set_s;
        nd[LC(o)].set_t = nd[RC(o)].set_t = nd[o].set_t;
        nd[LC(o)].add_s = nd[RC(o)].add_s = .0;
        nd[LC(o)].add_t = nd[RC(o)].add_t = .0;
        nd[o].set_s = NONE;
        nd[o].set_t = NONE;
    }
    if(dcmp(nd[o].add_s) != 0) {
        nd[LC(o)].add_s += nd[o].add_s; //add标记要累加！！！！！！！！！！！
        nd[RC(o)].add_s += nd[o].add_s;
        nd[o].add_s = .0;
    }
    if(dcmp(nd[o].add_t) != 0) {
        nd[LC(o)].add_t += nd[o].add_t;
        nd[RC(o)].add_t += nd[o].add_t;
        nd[o].add_t = .0;
    }
}

Info Query(int o, int L, int R, int qL, int qR) {
    Maintain(o, L, R);
    if(qL <= L && R <= qR)
        return Info(nd[o].x, nd[o].y, nd[o].xy, nd[o].x2);
    else {
        Info ret;
        Pushdown(o);
        if(qL <= Mid(L, R)) ret += Query(LC(o), L, Mid(L, R), qL, qR);
        else Maintain(LC(o), L, Mid(L, R));
        if(qR >= Mid(L, R)+1) ret += Query(RC(o), Mid(L, R)+1, R, qL, qR);
        else Maintain(RC(o), Mid(L, R)+1, R);
        return ret;
    }
}

void BuildTree(int o, int L, int R) {
    if(L == R) {
        nd[o].add_s = X[L];
        nd[o].add_t = Y[L];
    } else {
        BuildTree(LC(o), L, Mid(L, R));
        BuildTree(RC(o), Mid(L, R)+1, R);
    }
    Maintain(o, L, R);
}

void Add(int o, int L, int R, int qL, int qR, double S, double T) {
    if(qL <= L && R <= qR) {
        nd[o].add_s += S;
        nd[o].add_t += T;
    } else {
        Pushdown(o);
        if(qL <= Mid(L, R)) Add(LC(o), L, Mid(L, R), qL, qR, S, T);
        else Maintain(LC(o), L, Mid(L, R));
        if(qR >= Mid(L, R)+1) Add(RC(o), Mid(L, R)+1, R, qL, qR, S, T);
        else Maintain(RC(o), Mid(L, R)+1, R);
    }
    Maintain(o, L, R);
}

void Set(int o, int L, int R, int qL, int qR, double S, double T) {
    if(qL <= L && R <= qR) {
        nd[o].add_s = nd[o].add_t = .0; // override 'add' mark
        nd[o].set_s = S;
        nd[o].set_t = T;
    } else {
        Pushdown(o);
        if(qL <= Mid(L, R)) Set(LC(o), L, Mid(L, R), qL, qR, S, T);
        else Maintain(LC(o), L, Mid(L, R));
        if(qR >= Mid(L, R)+1) Set(RC(o), Mid(L, R)+1, R, qL, qR, S, T);
        else Maintain(RC(o), Mid(L, R)+1, R);
    }
    Maintain(o, L, R);
}

void init() {
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; i++)
        scanf("%lf", &X[i]);
    for(int i = 1; i <= n; i++)
        scanf("%lf", &Y[i]);
    BuildTree(1, 1, n);
}

void work() {
    int op, L, R; double S, T;
    Info res;
    while(q--) {
        scanf("%d", &op);
        switch(op) {
            case 1:
                scanf("%d%d", &L, &R);
                res = Query(1, 1, n, L, R);
                printf("%.12lf\n", 
                    (res.xy - res.x * res.y / (R-L+1)) / (res.x2 - res.x * res.x / (R-L+1)));
                break;
            case 2:
                scanf("%d%d%lf%lf", &L, &R, &S, &T);
                Add(1, 1, n, L, R, S, T);
                break;
            case 3:
                scanf("%d%d%lf%lf", &L, &R, &S, &T);
                Set(1, 1, n, L, R, S, T);
                break;
        }
    }
}

int main() {
    init(); work();
    return 0;
}
