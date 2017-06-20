#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}


const int N = 5e5+5;
const ll INF = 1e17;

int n, cnt, w[N], hd[N];
struct Data { int next, to; } g[N<<1];
void add(int x, int y) {
    g[++cnt] = (Data){ hd[x], y }; hd[x] = cnt;
    g[++cnt] = (Data){ hd[y], x }; hd[y] = cnt;
}


int ori[N], fin[N], rev[N], tim;
int son[N], siz[N], dep[N], top[N], fa[N];
void dfs(int x) {
    siz[x] = 1;
    ori[x] = ++tim, rev[ori[x]] = x;
    for(int v, i = hd[x]; i; i = g[i].next)
        if((v = g[i].to) != fa[x]) {
            fa[v] = x, dep[v] = dep[x]+1;
            dfs(v), siz[x] += siz[v];
            if(siz[v] > siz[son[x]]) son[x] = v;
        }
    fin[x] = tim;
}

int lca(int x, int y) {
    for(; top[x] != top[y]; x = fa[top[x]])
        if(dep[top[x]] < dep[top[y]]) swap(x, y);
    return dep[x] < dep[y] ? x : y;
}


ll val[N], dis[N], sum[N], hei[N];
int fir[N], sec[N], cen[N], vip[N], sta[N], tot;
void getcen(int x) {
    val[x] = w[x];
    for(int v, i = hd[x]; i; i = g[i].next)
        if((v = g[i].to) != fa[x]) {
            getcen(v);
            val[x] += val[v]; // the value of subtree
            dis[x] += dis[v] + val[v]; // \sum_{w[i]*dis(i,x)}, i in x subtree
            if(val[v] > val[fir[x]]) sec[x] = fir[x], fir[x] = v;
            else if(val[v] > val[sec[x]]) sec[x] = v;
        }

    if(val[fir[x]]*2 <= val[x]) cen[x] = x, sum[x] = dis[x];
    else {
        ll t = sum[fir[x]], v = cen[fir[x]];
        t += (dis[x]-dis[fir[x]]-val[fir[x]]);
        t += (val[x]-val[fir[x]]) * (dep[v]-dep[x]);
        for(; val[v]*2 < val[x]; v = fa[v]) // O(n)
            t += val[v] - (val[x]-val[v]);
        cen[x] = v;
        sum[x] = t;
    }
}


#define mid (l+r>>1)
int search(ll x) {
    int l = 2, r = tot, ret = 1;
    while(l <= r) {
        if((val[sta[mid]]-x)*2 >= val[1]-x) l = (ret = mid)+1;
        else r = mid-1;
    }
    return sta[ret];
}

void gethei(int x) {
    if(fa[x]) {
        vip[x] = search(val[x]); // removing x subtree, the gravity of tree is in vip[x]'s subtree
        hei[x] = hei[fa[x]]; // removing x subtree, \sum_{w[i]*dis(i,x)}
        hei[x] += dis[fa[x]]-dis[x]-val[x];
        hei[x] += val[1]-val[x];
    }
    sta[++tot] = x;
    for(int i = hd[x]; i; i = g[i].next)
        if(g[i].to != fa[x]) gethei(g[i].to);
    --tot;
}


ll t[N<<2];
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
struct Segment {
    void build(int o, int l, int r) {
        if(l == r) {
            t[o] = val[rev[l]]*2;
            return;
        }
        build(lc), build(rc);
        t[o] = max(t[o<<1], t[o<<1|1]);
    }

    int query(int o, int l, int r, int L, int R, ll p) {
        if(t[o] < p) return 0;
        if(l == r) return l;

        int ret = 0;
        if(R > mid) ret = query(rc, mid+1, R, p);
        if(ret) return ret;
        if(L <= mid) ret = query(lc, L, mid, p);
        return ret;
    }
} T;


#define contain(x, y) (ori[x] <= ori[y] && fin[y] <= fin[x])
int getroot(int o) {
    int x = vip[o], y, z;
    y = contain(fir[x], o) ? sec[x] : fir[x];
    if(y) z = T.query(1, 1, n, ori[y], fin[y], val[1]-val[o]);
    return z ? rev[z] : x;
} // removing o subtree, return the gravity of entire tree

ll solve(int x) {
    int o = getroot(x);
    int p = lca(o, x);
    ll ret = sum[x];
    ret += dis[o] + hei[o] - dis[x];
    ret -= val[x] * (dep[x]+dep[o]-2*dep[p]);
    return ret;
}

int main() {
    freopen("3068.in", "r", stdin);

    n = read();
    for(int i = 2; i <= n; ++i) add(read(), read());
    for(int i = 1; i <= n; ++i) w[i] = read();

    dfs(1);
    for(int i = 1; i <= n; ++i) if(son[fa[i]] != i)
        for(int j = i; j; j = son[j]) top[j] = i;

    getcen(1);
    gethei(1);
    T.build(1, 1, n);

    ll ans = INF;
    for(int i = 2; i <= n; ++i)
        ans = min(ans, solve(i));
    printf("%lld\n", ans);
    return 0;
}
