#include <cstdio>
#include <queue>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e6+5;
int N, M, K, back, cnt, head[maxn], ans[maxn];
bool mark[maxn], fir[maxn];
struct Data { int next, to; } data[maxn];

void add(int x, int y) { data[++cnt] = (Data) { head[x], y }; head[x] = cnt; }

queue <int> q;
void bfs(int x) {
	mark[x] = true;
	for(int i = head[x]; i; i = data[i].next) {
		Data &e = data[i];
		mark[e.to] = true;
		if(!fir[e.to]) fir[e.to] = true, q.push(e.to);
	}
	
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = head[v]; i; i = data[i].next) mark[data[i].to] = true;
	}
}

int main() {
	N = read(), M = read(), K = read();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), add(u, v), add(v, u);
		
	for(int i = 1; i <= N; ++i)
		if(!mark[i]) ans[++back] = i, bfs(i);
	
	printf("%d\n", back);
	for(int i = 1; i <= back; ++i)
		if(i == back) printf("%d", ans[i]);
		else printf("%d ", ans[i]);
	
	return 0;
}
