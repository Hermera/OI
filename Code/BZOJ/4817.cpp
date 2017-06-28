#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int N = 1e5+5;
 
#define mid (l+r>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
int dep[N], rev[N];
struct Segment {
    int t[N << 2], p[N << 2];
    void pushup(int o) {
        t[o] = max(t[o<<1], t[o<<1|1]) + p[o];
    }
     
    void build(int o, int l, int r) {
        if(l == r) t[o] = dep[rev[l]];
        else build(lc), build(rc), pushup(o);
    }
     
    void modify(int o, int l, int r, int L, int R, int v) {
        if(R < l || r < L) return;
        if(L <= l && r <= R) {
            p[o] += v;
            t[o] += v;
            return;
        }
        modify(lc, L, R, v);
        modify(rc, L, R, v);
        pushup(o);
    }
     
    int query(int o, int l, int r, int L, int R) {
        if(R < l || r < L) return 0;
        if(L <= l && r <= R) return t[o];
        return max(query(lc, L, R), query(rc, L, R)) + p[o];
    }
} T;
 
 
 
struct node {
    node *p, *s[2];
    int id;
     
    node() { p = s[0] = s[1] = this; }
    void sets(node *x, int d) { (s[d] = x)->p = this; }
    bool pos() { return p->s[1] == this; }
    bool isroot() { return p->s[0] != this && p->s[1] != this; }
    void update() {}
} gen[N], *num[N], *emt = new node();
 
int n, m, idx, L[N], R[N];
node *newnode(int v) {
    node *p = gen + (++idx);
    return *p = *emt, p->id = v, p;
}
 
 
void rotate(node *x) {
    node *y = x->p, *z = y->p;
    int d = x->pos();
    y->sets(x->s[!d], d);
    if(y->isroot()) x->p = z;
    else z->sets(x, y->pos());
    x->sets(y, !d), y->update();
}
 
void splay(node *x) {
    for(node *y; !x->isroot(); rotate(x))
        if(!(y = x->p)->isroot()) rotate(x->pos() == y->pos() ? y : x);
    x->update();
}
 
 
node *pre(node *x) {
    for(; x->s[0] != emt; x = x->s[0]);
    return x;
}
 
void access(node *x) {
    for(node *y = emt; x != emt; y = x, x = x->p) {
        splay(x);
        if(x->s[1] != emt) {
            node *z = pre(x->s[1]);
            x->s[1] = emt, splay(z);
            T.modify(1, 1, n, L[z->id], R[z->id], 1);
        }
        if(y != emt) {
            node *z = pre(y);
            splay(z), x->s[1] = z;
            T.modify(1, 1, n, L[z->id], R[z->id], -1);
        }
        x->update();     
    }
}
 
 
 
int h[N], cnt, tim;
struct Data {
    int next, to;
} g[N << 1];
 
void add(int x, int y) {
    g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
    g[++cnt] = (Data) { h[y], x }; h[y] = cnt;
}
 
 
int fa[N], siz[N], son[N], top[N];
void dfs(int x) {
    siz[x] = 1;
    L[x] = ++tim;
    rev[L[x]] = x;
    num[x] = newnode(x);
    dep[x] = dep[fa[x]]+1;
    if(fa[x]) num[x]->p = num[fa[x]];
    for(int v, i = h[x]; i; i = g[i].next)
        if((v = g[i].to) != fa[x]) {
            fa[v] = x, dfs(v), siz[x] += siz[v];
            if(siz[v] > siz[son[x]]) son[x] = v;
        }
    R[x] = tim;
}
 
 
int lca(int x, int y) {
    for(; top[x] != top[y]; x = fa[top[x]])
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
    return dep[x] < dep[y] ? x : y;
}
 
int query(int x, int y) {
    int ret = 1, p = lca(x, y);
    ret += T.query(1, 1, n, L[x], L[x]);
    ret += T.query(1, 1, n, L[y], L[y]);
    ret -= T.query(1, 1, n, L[p], L[p]) * 2;
    return ret;
}
 
 
int main() {
    n = read(), m = read();
    for(int i = 2; i <= n; ++i)
        add(read(), read());
    dfs(1);
    for(int i = 1; i <= n; ++i)
        if(son[fa[i]] != i) 
            for(int j = i; j; j = son[j]) top[j] = i;
     
    T.build(1, 1, n);
    for(int i = 1; i <= m; ++i) {
        int t = read(), x = read();
        if(t == 1) access(num[x]);
        if(t == 2) printf("%d\n", query(x, read()));
        if(t == 3) printf("%d\n", T.query(1, 1, n, L[x], R[x]));
    }
    return 0;
}

