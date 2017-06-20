#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0, t = 1;
    while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x * t;
}


const int R = 105;
const int N = 2e4+5;
const int M = 1e5+5;
const int INF = 1e9;

int n, m, c, sum, idx;
int num[R][R], val[R];

struct Edge {
    int next, to, cap;
} g[M];

int le[N], hd[N], it[N], S, T, cnt = 1;
void add(int x, int y, int w) {
    g[++cnt] = (Edge) { hd[x], y, w }; hd[x] = cnt;
    g[++cnt] = (Edge) { hd[y], x, 0 }; hd[y] = cnt;
}

int q[N];
bool bfs() {
    int fi = 1, ed = 0;
    for(int i = 1; i <= idx; ++i)
        it[i] = hd[i], le[i] = -1;
    le[S] = 0, q[++ed] = S;
    while(fi <= ed) {
        int v = q[fi++];
        for(int i = hd[v]; i; i = g[i].next) {
            Edge &e = g[i];
            if(le[e.to] < 0 && e.cap)
                le[e.to] = le[v]+1, q[++ed] = e.to;
        }
    }
    return ~le[T];
}

int dfs(int x, int f) {
    if(x == T) return f;
    for(int &i = it[x]; i; i = g[i].next) {
        Edge &e = g[i];
        if(e.cap && le[e.to] > le[x]) {
            int d = dfs(e.to, min(f, e.cap));
            if(d) {
                e.cap -= d, g[i^1].cap += d;
                return d;
            }
        }
    }
    return 0;
}

int maxflow() {
    int flow = 0;
    while(bfs())
        for(int f; f = dfs(S, INF);) flow += f;
    return flow;
}


int main() {
    freopen("4873.in", "r", stdin);

    n = read(), m = read(), c = idx = 1000;
    for(int i = 1; i <= n; ++i) val[i] = read();

    S = ++idx;
    T = ++idx;
    for(int i = 1; i <= c; ++i) add(i, T, m * i * i);

    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j)
            num[i][j] = ++idx;
    for(int i = 1; i <= n; ++i)
        for(int j = i; j <= n; ++j) {
            int w = read();
            if(i == j) {
                w -= val[i];
                add(num[i][j], val[i], INF);
            }

            if(w > 0) add(S, num[i][j], w), sum += w;
            if(w < 0) add(num[i][j], T, -w);
            if(i != j) {
                add(num[i][j], num[i+1][j], INF);
                add(num[i][j], num[i][j-1], INF);
            }
        }

    int ans = sum - maxflow();
    printf("%d\n", ans);
    return 0;
}
