#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e4+5;

int N, M, cnt, dis[maxn], tot[maxn], on[maxn], head[maxn];
bool vis[maxn];
struct Edge { int x, y; } e[maxn];
struct Data { int next, to, w, k; } data[maxn];
queue <int> q;

void add(int x, int y, int w = 0, int k = 0) 
{ data[++cnt] = (Data) { head[x], y, w, k }; head[x] = cnt; }

void dfs(int x, int k) {
	vis[x] = true, ++on[x];
	for(int i = head[x]; i; i = data[i].next)
		if(!vis[data[i].to] && data[i].k == k) dfs(data[i].to, k);
}

bool SPFA(int s) {
	memset(dis, 63, sizeof(dis)), dis[s] = 0;
	memset(vis, 0, sizeof(vis));
	q.push(s);
	while(!q.empty()) {
		int v = q.front(); q.pop();
		vis[v] = false;
		for(int i = head[v]; i; i = data[i].next) {
			Data &e = data[i];
			if(dis[e.to] > dis[v]+e.w) {
				if((++tot[e.to]) > N) return false;
				dis[e.to] = dis[v]+e.w;
				if(!vis[e.to]) vis[e.to] = true, q.push(e.to);
			}
		}
	}
	return true;
}

int main() {
	N = read(), M = read();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), add(u, v, 0, 1), add(v, u, 0, 0), e[i] = (Edge){ u, v };
	
	dfs(1, 1);
	memset(vis, 0, sizeof(vis));
	dfs(N, 0);
	
	memset(head, 0, sizeof(head)), cnt = 0;
	if(on[1] < 2 || on[N] < 2) return printf("No\n"), 0;
	for(int i = 1, u, v; i <= M; ++i) {
		u = e[i].x, v = e[i].y;
		if(on[u] == 2 && on[v] == 2) 
			add(u, v, 2), add(v, u, -1);
	}
	
	if(!SPFA(1)) printf("No\n");
	else {
		printf("Yes\n");
		for(int i = 1, u, v; i <= M; ++i) {
			u = e[i].x, v = e[i].y;
			if(on[u] == 2 && on[v] == 2)
				printf("%d\n", dis[v]-dis[u]);
			else printf("1\n");
		}
	}
	return 0;
}
