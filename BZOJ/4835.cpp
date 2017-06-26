#include <cstdio>
using namespace std;
typedef long long ll;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int N = 1e5+5;
const int L = 20;
const int mod = 1e9+7;
 
 
#define mid (l+r>>1)
#define lc t[o].ls, l, mid
#define rc t[o].rs, mid+1, r
struct node {
    int ls, rs, tot;
} t[N * L];
int idx, rt[N];
 
void insert(int &o, int l, int r, int p) {
    t[++idx] = t[o], o = idx, ++t[o].tot;
    if(l == r) return;
    if(p <= mid) insert(lc, p);
    else insert(rc, p);
}
 
int query(int o, int l, int r, int L, int R) {
    if(L <= l && r <= R) return t[o].tot;
    if(R < l || r < L) return 0;
    return query(lc, L, R) + query(rc, L, R);
}
 
 
 
int h[N], vis[N];
int n, m, cas, cnt, root;
struct Data {
    int next, to;
} g[N];
 
void add(int x, int y) {
    g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
}
 
 
int siz[N], ori[N], fin[N], seq[N], tim; 
void dfs(int x) {
    ori[x] = ++tim;
    seq[ori[x]] = x;
    siz[x] = 1;
    for(int i = h[x]; i; i = g[i].next)
        dfs(g[i].to), siz[x] += siz[g[i].to];
    fin[x] = tim;
}
 
ll dp[N];
void calc(int x) {
    dp[x] = 1;
    for(int i = h[x], v; i; i = g[i].next) {
        calc(v = g[i].to);
        ll ret = dp[v];
        if(siz[v]*2 == siz[x]) 
            (ret *= query(rt[fin[v]], 1, n, x, n) - 
                    query(rt[ori[v]-1], 1, n, x, n)) %= mod;
        else (ret *= siz[v]) %= mod;
        (dp[x] *= ret) %= mod;
    }
}
 
 
int main() {
    cas = read();
    while(cas--) {
        n = read(), m = read();
         
        cnt = idx = tim = 0;
        for(int i = 1; i <= n; ++i) vis[i] = h[i] = 0;
        for(int i = 2; i <= n; ++i) {
            int x = read(), y = read();
            add(x, y), vis[y] = 1;
        }
         
        for(int i = 1; i <= n; ++i)
            if(!vis[i]) root = i;
             
        dfs(root);
        for(int i = 1; i <= n; ++i)
            insert(rt[i] = rt[i-1], 1, n, seq[i]);
         
        calc(root);
        (dp[root] += mod) %= mod;
        printf("%lld\n", dp[root]);
    }
    return 0;
}
﻿