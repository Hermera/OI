<<<<<<< a2824b917e289d5fe1d2fa5151a17a549f4561fb
#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}

const int maxn = 3e5+5;
const int INF = 1e9;

namespace tree {
    int h[maxn], n, cnt;
    int f[maxn][2], w[maxn][2];
    bool fre[maxn];

    struct Data { int next, to; } g[maxn];
    void add(int x, int y) {
        g[++cnt] = (Data){ h[x], y }; h[x] = cnt;
        g[++cnt] = (Data){ h[y], x }; h[y] = cnt;
    }

    void dfs(int x, int fa) {
        if(!fre[x]) {
            f[x][0] = 0, f[x][1] = 1;
            for(int v, i = h[x]; i; i = g[i].next)
                if((v = g[i].to) != fa) {
                    dfs(v, x);
                    if(fre[v]) continue;
                    f[x][0] += max(f[v][0], f[v][1]);
                    f[x][1] += f[v][1];
                }
        } else {
            int t = 0;
            for(int i = h[x]; i; i = g[i].next)
                if(g[i].to != fa) dfs(g[i].to, x);

            for(int i = h[x]; i; i = g[i].next)
                w[++t][0] = f[g[i].to][0],
                w[t][1]   = f[g[i].to][1];
            for(int i = t-1; i; --i)
                w[i][0] += max(w[i+1][0], w[i+1][1]),
                w[i][1] += w[i+1][0];
            f[fa][0] = w[1][0];

            t = 0;
            for(int i = h[x]; i; i = g[i].next)
                w[++t][0] = f[g[i].to][0],
                w[t][1]   = f[g[i].to][1];
            w[t][1] = -INF;
            for(int i = t-1; i; --i)
                w[i][0] += max(w[i+1][0], w[i+1][1]),
                w[i][1] += w[i+1][0];
            f[fa][1] = w[1][1];
        }
    }
};


namespace cactus {
    int h[maxn], dfn[maxn], fa[maxn];
    int n, m, tim, cnt = 1;
    bool cir[maxn];
    struct Data { int next, to; } g[maxn];
    void add(int x, int y) {
        g[++cnt] = (Data){ h[x], y }; h[x] = cnt;
        g[++cnt] = (Data){ h[y], x }; h[y] = cnt;
    }

    void dfs(int x, int fr) {
        dfn[x] = ++tim;
        for(int v, i = h[x]; i; i = g[i].next)
            if(i ^ fr ^ 1) {
                v = g[i].to;
                if(!dfn[v]) {
                    fa[v] = x, cir[v] = 0, dfs(v, i);
                    if(!cir[v]) tree::add(x, v);
                } else {
                    if(dfn[v] > dfn[x]) continue;
                    tree::fre[++tree::n] = 1;
                    for(int j = x;; j = fa[j]) {
                        tree::add(tree::n, j), cir[j] = 1;
                        if(j == v) break;
                    }
                }
           }
    }
};


int main() {
    cactus::n = tree::n = read();
    cactus::m = read();
    for(int x, y, i = 1; i <= cactus::m; ++i) cactus::add(read(), read());
    cactus::dfs(1, 0);
    tree::dfs(1, 0);
    printf("%d\n", max(tree::f[1][0], tree::f[1][1]));
    return 0;
}
=======
#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}

const int maxn = 3e5+5;
const int INF = 1e9;

namespace tree {
    int h[maxn], n, cnt;
    int f[maxn][2], w[maxn][2];
    bool fre[maxn];

    struct Data { int next, to; } g[maxn];
    void add(int x, int y) {
        g[++cnt] = (Data){ h[x], y }; h[x] = cnt;
        g[++cnt] = (Data){ h[y], x }; h[y] = cnt;
    }

    void dfs(int x, int fa) {
        if(!fre[x]) {
            f[x][0] = 0, f[x][1] = 1;
            for(int v, i = h[x]; i; i = g[i].next)
                if((v = g[i].to) != fa) {
                    dfs(v, x);
                    if(fre[v]) continue;
                    f[x][0] += max(f[v][0], f[v][1]);
                    f[x][1] += f[v][1];
                }
        } else {
            int t = 0;
            for(int i = h[x]; i; i = g[i].next)
                if(g[i].to != fa) dfs(g[i].to, x);

            for(int i = h[x]; i; i = g[i].next)
                w[++t][0] = f[g[i].to][0],
                w[t][1]   = f[g[i].to][1];
            for(int i = t-1; i; --i)
                w[i][0] += max(w[i+1][0], w[i+1][1]),
                w[i][1] += w[i+1][0];
            f[fa][0] = w[1][0];

            t = 0;
            for(int i = h[x]; i; i = g[i].next)
                w[++t][0] = f[g[i].to][0],
                w[t][1]   = f[g[i].to][1];
            w[t][1] = -INF;
            for(int i = t-1; i; --i)
                w[i][0] += max(w[i+1][0], w[i+1][1]),
                w[i][1] += w[i+1][0];
            f[fa][1] = w[1][1];
        }
    }
};


namespace cactus {
    int h[maxn], dfn[maxn], fa[maxn];
    int n, m, tim, cnt = 1;
    bool cir[maxn];
    struct Data { int next, to; } g[maxn];
    void add(int x, int y) {
        g[++cnt] = (Data){ h[x], y }; h[x] = cnt;
        g[++cnt] = (Data){ h[y], x }; h[y] = cnt;
    }

    void dfs(int x, int fr) {
        dfn[x] = ++tim;
        for(int v, i = h[x]; i; i = g[i].next)
            if(i ^ fr ^ 1) {
                v = g[i].to;
                if(!dfn[v]) {
                    fa[v] = x, cir[v] = 0, dfs(v, i);
                    if(!cir[v]) tree::add(x, v);
                } else {
                    if(dfn[v] > dfn[x]) continue;
                    tree::fre[++tree::n] = 1;
                    for(int j = x;; j = fa[j]) {
                        tree::add(tree::n, j), cir[j] = 1;
                        if(j == v) break;
                    }
                }
           }
    }
};


int main() {
    cactus::n = tree::n = read();
    cactus::m = read();
    for(int x, y, i = 1; i <= cactus::m; ++i) cactus::add(read(), read());
    cactus::dfs(1, 0);
    tree::dfs(1, 0);
    printf("%d\n", max(tree::f[1][0], tree::f[1][1]));
    return 0;
}
>>>>>>> merge
