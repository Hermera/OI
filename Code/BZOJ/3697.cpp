#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
const int maxn = 2e5+5;
int n, t, cnt, sum, now, root;
int c3[maxn<<1], siz[maxn], st[maxn], h[maxn], f[maxn], val[maxn];
int *app = c3+maxn;
bool has[maxn], vis[maxn];
long long ans;
 
 
struct Data { int next, to, w; } g[maxn];
void add(int x, int y, int w) {
    g[++cnt] = (Data){ h[x], y, w }; h[x] = cnt;
}
 
void getroot(int x, int fa) {
    siz[x] = 1, f[x] = 0;
    for(int i = h[x]; i; i = g[i].next) {
        Data &e = g[i];
        if(!vis[e.to] && e.to != fa) {
            getroot(e.to, x);
            f[x] = max(f[x], siz[e.to]);
            siz[x] += siz[e.to];
        }
    }
    f[x] = max(f[x], sum-siz[x]);
    if(f[x] < f[root]) root = x;
}
 
void dfs(int x, int fa, int d) {
    val[x] = d;
    has[x] = app[d];
    ++app[d], st[++t] = x;
    for(int i = h[x]; i; i = g[i].next) {
        Data &e = g[i];
        if(e.to != fa && !vis[e.to]) 
            dfs(e.to, x, d+e.w);
    }
    --app[d];
}
 
struct ele {
    int tim, sum;
    void update() { if(tim != now) tim = now, sum = 0; }
} c1[maxn<<1], c2[maxn<<1];
ele *ok = c1+maxn;
ele *no = c2+maxn;
 
void work(int x) {
    ++now;
    for(int i = h[x]; i; i = g[i].next) if(!vis[g[i].to]) {
        Data &e = g[i];
        t = 0, dfs(e.to, x, e.w);
        for(int i = 1, w; i <= t; ++i) {
            w = val[st[i]];
            ok[-w].update();
            no[-w].update();
            if(has[st[i]] || !w) ans += ok[-w].sum+no[-w].sum;
            else ans += ok[-w].sum;
        }
         
        for(int i = 1, w; i <= t; ++i) {
            w = val[st[i]];
            ok[w].update();
            no[w].update();
            if(has[st[i]]) ++ok[w].sum;
            else ++no[w].sum;
        }
    }
    ok[0].update();
    ans += ok[0].sum;
}
 
void solve(int x) {
    vis[x] = 1, work(x);
    for(int i = h[x]; i; i = g[i].next) {
        Data &e = g[i];
        if(!vis[e.to]) {
            root = 0, sum = siz[e.to];
            getroot(e.to, x);
            solve(root);
        }
    }
}
 
int main() {
    n = read();
    for(int i = 1, a, b, t; i < n; ++i)
        a = read(), b = read(), t = read(),
        add(a, b, t ? 1 : -1), add(b, a, t ? 1 : -1);
     
    sum = f[0] = n;
    getroot(1, 0);
    solve(root);
     
    printf("%lld\n", ans);
    return 0;
}
