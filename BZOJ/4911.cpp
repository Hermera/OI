// Cannot AC at BZOJ

#include <cstdio>
#include <cstring>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
const int N = 30001;
const int M = 128;
const int mod = 10007;
int n, m, q, inv;
void upd(int &x, int y) {
    x += y;
    if(x >= mod) x -= mod;
}
int quickpow(int x, int k) {
    int ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod)
        if(k & 1) (ret *= x) %= mod;
    return ret;
}
void FWT(int *s, int on) {
    for(int h = 2; h <= m; h <<= 1)
        for(int i = 0; i < m; i += h)
            for(int j = i; j < i + h/2; ++j) {
                int u = s[j], v = s[j + h/2];
                s[j] = (u + v) % mod;
                s[j+h/2] = (u - v + mod) % mod;
            }
    if(!on)
        for(int i = 0; i < m; ++i)
            (s[i] *= inv) %= mod;
}
struct value {
    int s[M];
    value(int x = -1) {
        memset(s, 0, sizeof(s));
        if(~x) s[x] = 1, FWT(s, 1);
    }
    int &operator [](int x) {
        return s[x];
    }
} ans, now;
value operator +(value a, int k) {
    value b = a;
    for(int i = 0; i < m; ++i)
        b[i] += k;
    return b;
}
value operator +(value a, value b) {
    value c = a;
    for(int i = 0; i < m; ++i)
        upd(c[i], b[i]);
    return c;
}
value operator -(value a, value b) {
    value c = a;
    for(int i = 0; i < m; ++i)
        upd(c[i], mod - b[i]);
    return c;
}
value operator *(value a, value b) {
    value c(-1);
    for(int i = 0; i < m; ++i)
        upd(c[i], a[i] * b[i] % mod);
    return c;
}
struct node {
    int ls, rs;
    value pre, suf, sum, mul;
    void init(value x) {
        pre = suf = sum = mul = x;
    }
} t[N << 2];
value p[N];
int len, idx, tot;
int lit[N], chn[N], num[N], pos[N];
#define mid (l + r >> 1)
#define lc t[o].ls, l, mid
#define rc t[o].rs, mid+1, r
struct segment {   
    int root, len;
    node ask() {
        return t[root];
    }   
    void pushup(int o) {
        int ls = t[o].ls;
        int rs = t[o].rs;
        t[o].pre = t[ls].pre + t[ls].mul * t[rs].pre;
        t[o].suf = t[rs].suf + t[rs].mul * t[ls].suf;
        t[o].sum = t[ls].sum + t[rs].sum + t[ls].suf * t[rs].pre;
        t[o].mul = t[ls].mul * t[rs].mul;
    }
    void build(int &o, int l, int r) {
        o = ++idx;
        if(l == r) return t[o].init(p[l]);
        build(lc), build(rc);
        pushup(o);
    }
    void update(int o, int l, int r, int p) {       
        if(l == r) return t[o].init(now);
        if(p <= mid) update(lc, p);
        else update(rc, p);
        pushup(o);
    }
    void update(int p, value v, int on) {
        now = v;
        if(on) ans = ans - ask().sum;
        update(root, 1, len, p);
        if(on) ans = ans + ask().sum;
    }
    void init(int x) {
        if(!x) {
            root = ++idx;
            t[idx].init(value(0));
        } else build(root, 1, len = x);
    }
} T[N << 1];
int hd[N], cnt;
struct Data {
    int next, to;
} gr[N << 1];
void add(int x, int y) {
    gr[++cnt] = (Data) { hd[x], y }; hd[x] = cnt;
    gr[++cnt] = (Data) { hd[y], x }; hd[y] = cnt;
}
value a[N], f[N], h[N];
int siz[N], fa[N], son[N], top[N];
void dfs(int x) {
    siz[x] = 1;
    f[x] = h[x] = a[x];
    for(int v, i = hd[x]; i; i = gr[i].next)
        if((v = gr[i].to) != fa[x]) {
            fa[v] = x, dfs(v), siz[x] += siz[v];
            if(siz[v] > siz[son[x]]) son[x] = v;
        }
    len = 0;   
    for(int v, i = hd[x]; i; i = gr[i].next)
        if((v = gr[i].to) != fa[x]) {
            if(v != son[x]) {
                num[v] = ++len;
                p[len] = (f[v] + 1);
            }
            f[x] = f[x] * (f[v] + 1);
        }
    lit[x] = ++tot;
    T[tot].init(len);
    h[x] = h[x] * T[tot].ask().mul;
}
void dfs(int x, int tp) {
    top[x] = tp;
    pos[x] = ++len;
    p[len] = h[x];
    if(son[x]) dfs(son[x], tp);
    else {
        chn[tp] = ++tot;
        T[tot].init(len);
    }
    for(int i = hd[x], v; i; i = gr[i].next)
        if((v = gr[i].to) != son[x] && v != fa[x])
            len = 0, dfs(v, v);
}
void modify(int x, int v) {
    a[x] = value(v);
    for(; top[x] != 1; x = fa[top[x]]) {
        int t = top[x];
        T[chn[t]].update(pos[x], T[lit[x]].ask().mul * a[x], 1);
        T[lit[fa[t]]].update(num[t], T[chn[t]].ask().pre + 1, 0);
    }
    T[chn[top[x]]].update(pos[x], T[lit[x]].ask().mul * a[x], 1);
}
int query(int x) {
    now = ans;
    FWT(now.s, 0);
    return now[x];
}
char op[10];
int main() {
    freopen("cut.in", "r", stdin);
    freopen("cut.out", "w", stdout);
    n = read(), m = read();
    inv = quickpow(m, mod - 2);
    for(int i = 1; i <= n; ++i) a[i] = value(read());
    for(int i = 2; i <= n; ++i) add(read(), read());
    dfs(1);
    len = 0;
    dfs(1, 1);
    for(int i = 1; i <= n; ++i)
        if(chn[i]) ans = ans + T[chn[i]].ask().sum;
    q = read();
    for(int x, y, k = 1; q--; ++k) {
        scanf("%s", op);
        if(*op == 'C') {
            x = read(), y = read();
            modify(x, y);
        } else {
            printf("%d\n", query(read()));
        }
    }
    return 0;
}