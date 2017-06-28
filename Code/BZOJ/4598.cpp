#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
int get() {
    char ch = getchar();
    while(ch < 'A' || ch > 'Z') ch = getchar();
    return ch - 'A' + 1;
}
 
 
const int maxn = 1e6+5;
const int bin = 29;
inline bool cmax(int &x, int y) { x = (x < y ? y : x); }
 
int n, m, cnt, w[maxn], s[maxn], h[maxn];
struct Data { int next, to; } g[maxn<<1];
void add(int x, int y) {
    g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
    g[++cnt] = (Data) { h[y], x }; h[y] = cnt;
}
 
 
bool vis[maxn];
int root, all, len;
int siz[maxn], low[maxn], pre[maxn], suf[maxn];
void getroot(int x, int fa) {
    siz[x] = 1, low[x] = 0;
    for(int v, i = h[x]; i; i = g[i].next)
        if(g[i].to != fa && !vis[g[i].to]) {
            getroot(v = g[i].to, x);
            siz[x] += siz[v];
            cmax(low[x], siz[v]);
        }
    cmax(low[x], all - siz[x]);
    if(low[x] < low[root]) root = x;
}
 
 
ll ans, pow[maxn], zs[maxn], fs[maxn];
void dfs(int x, int fa, int dep, ll has, int *a, ll *b) {
    cmax(len, dep);
    has += pow[dep-1] * w[x];
    if(has == b[dep]) ++a[dep % m];
    for(int i = h[x]; i; i = g[i].next)
        if(g[i].to != fa && !vis[g[i].to]) dfs(g[i].to, x, dep+1, has, a, b);
}
 
ll calc() {
    ll ret = 1LL * suf[0] * pre[0];
    int lim = min(len, m-1);
    for(int i = 1; i <= lim; ++i)
        ret += 1LL * pre[i] * suf[m-i];
    for(int i = 0; i <= len; ++i) pre[i] = suf[i] = 0;
    return ret;
}
 
 
void work(int x) {
    len = 0, dfs(x, 0, 1, 0, suf, fs);
    for(int i = h[x]; i; i = g[i].next)
        if(!vis[g[i].to]) dfs(g[i].to, x, 1, 0, pre, zs);
    ans += suf[0];
    ans += calc();
     
    for(int i = h[x]; i; i = g[i].next) 
        if(!vis[g[i].to]) {
            len = 0;
            dfs(g[i].to, x, 1, 0, pre, zs);
            dfs(g[i].to, x, 2, w[x], suf, fs);
            ans -= calc();
        }
}
 
 
void solve(int x) {
    work(x);
    vis[x] = 1;
    for(int v, i = h[x]; i; i = g[i].next)
        if(!vis[v = g[i].to]) {
            if((all = siz[v]) < m) continue;
            getroot(v, root = 0);
            solve(root);
        }
}
 
 
int main() {
    for(int cas = read(); cas--;) {
        n = read(), m = read(), ans = cnt = 0;
        for(int i = 1; i <= n; ++i) h[i] = vis[i] = 0;
        for(int i = 1; i <= n; ++i) w[i] = get();
        for(int i = 2; i <= n; ++i) add(read(), read());
        for(int i = 1; i <= m; ++i) s[i] = get();
         
        pow[0] = 1;
        for(int i = 1; i <= n; ++i) pow[i] = pow[i-1] * bin;
        for(int i = 1; i <= n; ++i) 
            if(i%m) zs[i] = zs[i-1] * bin + s[i%m];
            else zs[i] = zs[i-1] * bin + s[m];
        reverse(s+1, s+1+m);
        for(int i = 1; i <= n; ++i) 
            if(i%m) fs[i] = fs[i-1] * bin + s[i%m];
            else fs[i] = fs[i-1] * bin + s[m];
         
        low[0] = all = n;
        getroot(1, root = 0);
        solve(root);
         
        printf("%llu\n", ans);
    }
    return 0;
}
﻿