#include <cstdio>
#include <cstring>
#include <cmath>
using namespace std;
int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 2e4+5;
const double eps = 1e-8;
int N, M, cnt, head[maxn];
struct Data { int next, to; double w; } data[maxn];
bool vis[maxn];
double val[maxn];

void add(int x, int y, double w) {
	data[++cnt] = (Data){ head[x], y, w }; head[x] = cnt;
}

bool equa(double x, double y) { return fabs(x-y) < eps; }
bool dfs(int x, double v) {
	vis[x] = true;
	val[x] = v;
	for(int i = head[x]; i; i = data[i].next) {
		Data &e = data[i];
		if(!vis[e.to] && !dfs(e.to, v*e.w)) return false;
		else if(!equa(val[e.to], v*e.w)) return false;
	}
	return true;
}

bool Judge() {	
	for(int i = 1; i <= N; ++i)
		if(!vis[i])
			if(!dfs(i, 1.0)) return false;
	return true;
}

int main() {
	freopen("4602.in", "r", stdin);

	for(int T = read(), k = 0; T; --T) {
		scanf("%d%d", &N, &M);
		memset(head, 0, sizeof(head));
		memset(vis, 0, sizeof(vis));
		memset(val, 0, sizeof(val));
		cnt = 0;
		
		for(int i = 1, u, v, x, y; i <= M; ++i) {
			u = read(), v = read(), x = read(), y = read();
			add(u, v, 1.0*y/x), add(v, u, 1.0*x/y);
		}
		
		printf("Case #%d: %s\n", ++k, Judge() ? "Yes" : "No");
	}
	return 0;
}

