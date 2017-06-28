#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
 
const int N = 1005;
const int INF = 1e9;
 
 
int s, t, cnt = 1, idx, hd[N], it[N], le[N];
struct Data {
    int next, to, cap;
} g[N * N];
 
void add(int x, int y, int w) {
    g[++cnt] = (Data){ hd[x], y, w }; hd[x] = cnt;
    g[++cnt] = (Data){ hd[y], x, 0 }; hd[y] = cnt;
}
 
int q[N];
bool bfs() {
    int h = 1, k = 0;
    for(int i = s; i <= t; ++i)
        le[i] = -1, it[i] = hd[i];
    le[s] = 0, q[++k] = s;
    while(h <= k) {
        int v = q[h++];
        for(int i = hd[v]; i; i = g[i].next) {
            Data &e = g[i];
            if(le[e.to] < 0 && e.cap)
                le[e.to] = le[v]+1, q[++k] = e.to;
        }
    }
    return ~le[t];
}
 
int dfs(int v, int f) {
    if(v == t) return f;
    for(int &i = it[v]; i; i = g[i].next) {
        Data &e = g[i];
        if(le[e.to] > le[v] && e.cap) {
            int d = dfs(e.to, min(e.cap, f));
            if(d) {
                e.cap -= d;
                g[i^1].cap += d;
                return d;
            }
        }
    }
    return 0;
}
 
int maxflow() {
    int flow = 0;
    while(bfs())
        for(int f; f = dfs(s, INF); flow += f);
    return flow;
}
 
int n, sum;
int B[N][N], C[N], D[N];
 
int main() {
    n = read();
    for(int i = 1; i <= n; ++i)
    for(int j = 1; j <= n; ++j)
        B[i][j] = read() << 1, sum += B[i][j];
    for(int i = 1; i <= n; ++i) C[i] = read() << 1;
    for(int i = 1; i <= n; ++i)
        for(int j = i+1; j <= n; ++j)
            B[i][j] += B[j][i];
             
    s = 0, t = 2*n + 1;
    for(int i = 1; i <= n; ++i) add(s, i, C[i]);
    for(int i = 1; i <= n; ++i) D[i] += B[i][i];
    for(int i = 1; i <= n; ++i) add(i, i+n, INF);
     
    for(int i = 1; i <= n; ++i)
        for(int j = i+1; j <= n; ++j) {
            add(i, j+n, B[i][j] / 2);
            add(j, i+n, B[i][j] / 2);
            D[i] += B[i][j] / 2;
            D[j] += B[i][j] / 2;        
        }
     
    for(int i = 1; i <= n; ++i) add(i+n, t, D[i]);
     
    printf("%d\n", (sum - maxflow()) >> 1);
    return 0;
}