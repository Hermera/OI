#include <cstdio>
#include <cstring>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}
const int maxn = 2005;

int N, M, cnt, dis[maxn], head[maxn];
bool vis[maxn];
struct Data { int next, to, w; } data[maxn];

void add(int x, int y, int w) { data[++cnt] = (Data) { head[x], y, w }; head[x] = cnt; }

void dfs(int x) {
	vis[x] = 1;
	for(int i = head[x]; i; i = data[i].next)
		if(!vis[data[i].to]) dfs(data[i].to);
}

void Bellman_Ford() {
	memset(dis, 63, sizeof(dis));
	memset(vis, 0, sizeof(vis));
	dis[1] = 0;

	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= N; ++j)
	for(int k = head[j]; k; k = data[k].next) {
		Data &e = data[k];
		if(dis[e.to] > dis[j]+e.w) dis[e.to] = dis[j]+e.w;
	}
	
	for(int i = 1; i <= N; ++i)
	for(int j = head[i]; j; j = data[j].next) {
		Data &e = data[j];
		if(dis[e.to] > dis[i]+e.w) 
			dfs(i);
	}
}

int main() {
	for(int T = read(), kase = 0; T; --T) {
		memset(head, 0, sizeof(head));
		cnt = 0;
		N = read(), M = read();
		for(int i = 1, u, v, w; i <= M; ++i)	
			u = read()+1, v = read()+1, w = read(), add(u, v, w);
		
		Bellman_Ford();
		printf("Case #%d: %s\n", ++kase, vis[1] ? "possible" : "not possible");
	}
	return 0;
}
