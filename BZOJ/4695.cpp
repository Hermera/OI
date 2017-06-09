#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
template<typename T> inline T cmax(T a, T b) { return a > b ? a : b; }
template<typename T> inline T cmin(T a, T b) { return a < b ? a : b; }

int read() {
    char ch = getchar(); int x = 0, t = 1;
    while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x*t;
}

const int maxn = 5e5+5;
const int INF = 1e9;
int n, m, L, R, a[maxn];

#define ls o<<1
#define rs o<<1|1
#define mid (l+r>>1)
#define lc ls, l, mid
#define rc rs, mid+1, r
struct Segment {
    struct node {
        ll sum, tag;
        int min, max, se1, se2, tmn, tmx, num1, num2;

        void init(int w) {
            min = max = sum = w;
            tag = 0, num1 = num2 = 1;
            se1 = -INF, se2 = INF;
        }

        void add(int w, int l, int r) {
            max += w, min += w, tmn += w, tmx += w;
            sum += 1LL*w*(r-l+1), tag += w;
            if(se1 != -INF) se1 += w;
            if(se2 !=  INF) se2 += w;
        }

        void updmax(int w, int l, int r) {
            sum += 1LL*num2*(w - min);
            min = cmax(min, w), max = cmax(max, w);
            tmx = cmax(tmx, w), tmn = cmax(tmx, tmn); //!
            if(max != w) se1 = cmax(se1, w);
            else se1 = -INF, se2 = INF, num1 = num2 = r-l+1;
        }

        void updmin(int w, int l, int r) {
            sum -= 1LL*num1*(max - w);
            min = cmin(min, w), max = cmin(max, w);
            tmn = cmin(tmn, w), tmx = cmin(tmn, tmx);
            if(min != w) se2 = cmin(se2, w);
            else se1 = -INF, se2 = INF, num1 = num2 = r-l+1;
        }
    } t[maxn<<2];

    /* the basic */
    bool updmax(int o, int l, int r, int w) {
        if(w <= t[o].min) return 1;
        if(w <  t[o].se2) return t[o].updmax(w, l, r), 1;
        return 0;
    }

    bool updmin(int o, int l, int r, int w) {
        if(w >= t[o].max) return 1;
        if(w >  t[o].se1) return t[o].updmin(w, l, r), 1;
        return 0;
    }

    void pushup(int o) {
        t[o].num1 = t[o].num2 = 0, t[o].sum = t[ls].sum + t[rs].sum;
        if(t[ls].max >= t[rs].max) t[o].max = t[ls].max, t[o].num1 += t[ls].num1;
        if(t[rs].max >= t[ls].max) t[o].max = t[rs].max, t[o].num1 += t[rs].num1;
        if(t[ls].min <= t[rs].min) t[o].min = t[ls].min, t[o].num2 += t[ls].num2;
        if(t[rs].min <= t[ls].min) t[o].min = t[rs].min, t[o].num2 += t[rs].num2;

        /* !!! */
        int se = -INF;
        if(t[ls].max < t[rs].max) se = cmax(se, t[ls].max);
        else se = cmax(se, t[ls].se1);
        if(t[rs].max < t[ls].max) se = cmax(se, t[rs].max);
        else se = cmax(se, t[rs].se1);
        t[o].se1 = se;

        se = INF;
        if(t[ls].min > t[rs].min) se = cmin(se, t[ls].min);
        else se = cmin(se, t[ls].se2);
        if(t[rs].min > t[ls].min) se = cmin(se, t[rs].min);
        else se = cmin(se, t[rs].se2);
        t[o].se2 = se;
    }

    void pushdown(int o, int l, int r) {
        if(t[o].tag) t[ls].add(t[o].tag, l, mid), t[rs].add(t[o].tag, mid+1, r), t[o].tag = 0;
        if(t[o].tmx != -INF) updmax(lc, t[o].tmx), updmax(rc, t[o].tmx), t[o].tmx = -INF;
        if(t[o].tmn !=  INF) updmin(lc, t[o].tmn), updmin(rc, t[o].tmn), t[o].tmn = INF;
    }

    void build(int o, int l, int r) {
        t[o].tmx = -INF, t[o].tmn = INF;
        if(l == r) t[o].init(a[l]);
        else build(lc), build(rc), pushup(o);
    }


    /* the part of modify */
    void add(int o, int l, int r, int w) {
        if(L <= l && r <= R) return t[o].add(w, l, r);
        if(R < l || r < L) return;
        pushdown(o, l, r);
        add(lc, w), add(rc, w);
        pushup(o);
    }

    void max(int o, int l, int r, int w) {
        if(R < l || r < L) return;
        if(L <= l && r <= R) if(updmax(o, l, r, w)) return;
        pushdown(o, l, r);
        max(lc, w), max(rc, w);
        pushup(o);
    }

    void min(int o, int l, int r, int w) {
        if(R < l || r < L) return;
        if(L <= l && r <= R) if(updmin(o, l, r, w)) return;
        pushdown(o, l, r);
        min(lc, w), min(rc, w);
        pushup(o);
    }


    /* the part of query */
    ll sigma(int o, int l, int r) {
        if(L <= l && r <= R) return t[o].sum;
        if(R < l || r < L) return 0;
        pushdown(o, l, r);
        return sigma(lc) + sigma(rc);
    }

    ll maxiz(int o, int l, int r) {
        if(L <= l && r <= R) return t[o].max;
        if(R < l || r < L) return -INF;
        pushdown(o, l, r);
        return cmax(maxiz(lc), maxiz(rc));
    }

    ll miniz(int o, int l, int r) {
        if(L <= l && r <= R) return t[o].min;
        if(R < l || r < L) return INF;
        pushdown(o, l, r);
        return cmin(miniz(lc), miniz(rc));
    }
} T;


int main() {
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read();
    T.build(1, 1, n);

    m = read();
    for(int op; m--;) {
        op = read(), L = read(), R = read();
        if(op == 1) T.add(1, 1, n, read());
        if(op == 2) T.max(1, 1, n, read());
        if(op == 3) T.min(1, 1, n, read());
        if(op == 4) printf("%lld\n", T.sigma(1, 1, n));
        if(op == 5) printf("%lld\n", T.maxiz(1, 1, n));
        if(op == 6) printf("%lld\n", T.miniz(1, 1, n));
    }
    return 0;
}
