 
#include <cstdio>
using namespace std;
inline int read() { 
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
const int N = 50005;
const int K = 160;
const int mod = 10007;
 
void inc(int &x, int y) {
    x += y;
    if(x < 0) x += mod;
    if(x >= mod) x -= mod;
}
 
 
int n, k, cnt, h[N];
struct Data { int next, to; } g[N << 1];
void add(int x, int y) {
    g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
    g[++cnt] = (Data) { h[y], x }; h[y] = cnt;
}
 
 
int f[N][K], q[N][K], ans[N], p[K];
int fac[N], stl[K][K];
 
void dfs1(int x, int fa) {
    f[x][0] = 1;
    for(int v, i = h[x]; i; i = g[i].next) 
        if((v = g[i].to) != fa) {
            dfs1(v, x);
            inc(f[x][0], f[v][0]);
            for(int j = 1; j <= k; ++j)
                inc(f[x][j], (f[v][j] + f[v][j-1]) % mod);
        }
}
 
void dfs2(int x, int fa) {
    for(int i = 0; i <= k; ++i) {
        int ret = f[x][i] + p[i];
        (ret *= stl[k][i]) %= mod;
        (ret *= fac[i]) %= mod;
        inc(ans[x], ret);
    }
     
    q[x][0] = p[0];
    for(int i = 1; i <= k; ++i) q[x][i] = p[i];
    for(int v, i = h[x]; i; i = g[i].next) 
        if((v = g[i].to) != fa) {
            p[0] = (q[x][0] + f[x][0] - f[v][0]) % mod;
            for(int j = 1; j <= k; ++j)
                p[j] = (q[x][j] + f[x][j] - (f[v][j]+f[v][j-1])) % mod;
            for(int j = k; j >= 1; --j) p[j] = p[j] + p[j-1];
            dfs2(v, x);
        }
}
 
int L, W, A, B, C;
int main() {
    n = read(), k = read();
    L = read(), W = read();
    A = read(), B = read(), C = read();
     
    for(int u, i = 1; i < n; ++i) {
        W = (W*A + B) % C;
        u = i - W % (i < L ? i : L);
        add(u, i + 1);
    }
     
    fac[0] = stl[0][0] = 1;
    for(int i = 1; i <= k; ++i)
        fac[i] = fac[i-1] * i % mod;
    for(int i = 1; i <= k; ++i)
    for(int j = 1; j <= k; ++j)
        inc(stl[i][j], (stl[i-1][j-1]+stl[i-1][j]*j) % mod);
     
    dfs1(1, 0);
    dfs2(1, 0);
    for(int i = 1; i <= n; ++i)
        printf("%d\n", ans[i]);
    return 0;
}