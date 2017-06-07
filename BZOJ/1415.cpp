#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1005;
int N, M, cc, kk, cnt;
int head[maxn], deg[maxn], dis[maxn][maxn], go[maxn][maxn];
double f[maxn][maxn];
struct Data { int next, to; } data[maxn<<1];

bool bfs(int x, int *dis) {
	queue <int> q;
	q.push(x), dis[x] = 0;
	while(!q.empty()) {
		int v = q.front(), tmp = go[x][v]; q.pop();
		for(int i = head[v]; i; i = data[i].next) {
			Data &e = data[i];
			if(dis[e.to] < 0 || (dis[v]+1 == dis[e.to] && tmp < go[x][e.to])) {
				dis[e.to] = dis[v]+1;
				if(!tmp) go[x][e.to] = e.to;
				else go[x][e.to] = tmp;
				q.push(e.to);
			}
		}
	}
}

double dp(int x, int y) {
	if(f[x][y]) return f[x][y];
	if(x == y) return 0;
	if(go[x][y] == y || go[go[x][y]][y] == y) return 1;
	double ret = dp(go[go[x][y]][y], y);
	for(int i = head[y]; i; i = data[i].next) {
		Data &e = data[i];
		ret += dp(go[go[x][y]][y], e.to);
	}
	return f[x][y] = ret/(deg[y]+1)+1;
}

void add(int x, int y) { data[++cnt] = (Data){ head[x], y }; head[x] = cnt; }

int main() {
	freopen("1415.in", "r", stdin);

	N = read(), M = read(), cc = read(), kk = read();
	for(int i = 1, x, y; i <= M; ++i)
		x = read(), y = read(), ++deg[x], ++deg[y], add(x, y), add(y, x);
	
	memset(dis, -1, sizeof(dis));
	for(int i = 1; i <= N; ++i)	bfs(i, dis[i]);
	printf("%.3lf\n", dp(cc, kk));
	return 0;
}
