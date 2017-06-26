#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
const int maxn = 1e5+5;
 
int n, q, cnt, h[maxn], fa[maxn], dep[maxn];
struct Data { int next, to, tim; } g[maxn<<1];
void add(int x, int y, int w) {
    g[++cnt] = (Data){ h[x], y, w }; h[x] = cnt;
    g[++cnt] = (Data){ h[y], x, w }; h[y] = cnt;
}
 
void dfs(int x) {
    for(int v, i = h[x]; i; i = g[i].next)
        if((v = g[i].to) != fa[x]) 
            fa[v] = x, dep[v] = dep[x]+1, dfs(v);
}
 
 
struct Node {
    int ls, rs, tot;
} t[maxn * 40];
int idx;
 
#define mid (l+r>>1)
#define lc t[o].ls, l, mid
#define rc t[o].rs, mid+1, r
struct Segment {
    int root, ret, L, R;
     
    void pushup(int o) { t[o].tot = t[t[o].ls].tot + t[t[o].rs].tot; }
    void insert(int &o, int l, int r, int p, int v) {
        if(!o) o = ++idx;
        if(l == r) {
            t[o].tot += v;
            return;
        }
        if(p <= mid) insert(lc, p, v);
        else insert(rc, p, v);
        pushup(o);
    }
     
    int query(int o, int l, int r) {
        if(!o || R < l || r < L) return 0;
        if(L <= l && r <= R) return t[o].tot;
        return query(lc) + query(rc);
    }
     
    void remove(int &o, int l, int r) {
        if(R < l || r < L) return;
        if(L <= l && r <= R) {
            ret += t[o].tot, o = 0;
            return;
        }
        remove(lc);
        if(mid < R) remove(rc);
        pushup(o);
        if(!t[o].tot) o = 0;
    }
     
    int merge(int o1, int o2, int l, int r) {
        if(!o1 || !o2) return o1 | o2;
        if(l == r) return t[o1].tot += t[o2].tot, o1;
        t[o1].ls = merge(t[o1].ls, t[o2].ls, l, mid);
        t[o1].rs = merge(t[o1].rs, t[o2].rs, mid+1, r);
        return pushup(o1), o1;
    }
     
    int query(int x) { return L = 1, R = x, query(root, 1, q); }
    void merge(Segment &x) { root = merge(root, x.root, 1, q); }
    void insert(int x, int p) { insert(root, 1, q, x, p); }
    int remove(int x) {
        ret = 0, L = 1, R = x;
        return remove(root, 1, q), ret;
    }
} s[maxn];
 
 
 
ll ans[maxn];
vector <int> ask[maxn];
void solve(int x) {
    s[x].insert(1, 1);
    for(int v, p, i = h[x]; i; i = g[i].next)
        if((v = g[i].to) != fa[x]) {
            solve(v);
            p = s[v].remove(g[i].tim - 1);
            s[x].insert(g[i].tim, p);
            s[x].merge(s[v]);
        }
         
    for(int v, p, i = 0; i < ask[x].size(); ++i) {
        v = ask[x][i], p = s[x].query(v);
        if(ans[v]) ans[v] = 1LL * (p-ans[v]) * ans[v];
        else ans[v] = p;
    }
}
 
char str[5];
struct opt {
    int type, x, y;
    void init() {
        scanf("%s", str);
        x = read(), y = read();
        type = (*str == 'A');
    }
} op[maxn];
 
int pa[maxn], top[maxn];
int getpa(int x) { return x == pa[x] ? x : pa[x] = getpa(pa[x]); }
void merge(int x, int y) {
    x = getpa(x), y = getpa(y), pa[y] = x;
    top[x] = dep[top[x]] < dep[top[y]] ? top[x] : top[y];
}
 
int main() {
    n = read(), q = read();
    for(int i = 1; i <= q; ++i) op[i].init();
    for(int i = 1; i <= q; ++i)
        if(op[i].type) add(op[i].x, op[i].y, i);
         
    for(int i = 1; i <= n; ++i) if(!dep[i]) dfs(i);
    for(int i = 1; i <= n; ++i) pa[i] = top[i] = i;
    for(int i = 1; i <= q; ++i) {
        opt &e = op[i];
        if(e.type) merge(e.x, e.y);
        else {
            if(dep[e.x] > dep[e.y]) swap(e.x, e.y);
            ask[top[getpa(e.x)]].push_back(i);
            ask[e.y].push_back(i);
        }
    }
     
    for(int i = 1; i <= n; ++i) if(!dep[i]) solve(i);
    for(int i = 1; i <= q; ++i)
        if(ans[i]) printf("%lld\n", ans[i]);
    return 0;
}