#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5;
int N, M, D, cnt, back;
int put[maxn], head[maxn], deg[maxn], fa[maxn], sum[maxn];
bool vis[maxn];
struct Data { int next, to; } data[maxn<<1];

void add(int x, int y) {
	data[++cnt] = (Data) { head[x], y }; head[x] = cnt;
}

int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }

queue <int> q;
int main() {
	N = read(), M = read(), D = read();
	for(int i = 1, u, v; i <= M; ++i) {
		u = read(), v = read();
		add(u, v), add(v, u);
		++deg[u], ++deg[v];
	}
	
	for(int i = 1; i <= N; ++i) 
		if(deg[i] < D) q.push(i), vis[i] = true;
	while(!q.empty()) {
		int v = q.front(); q.pop();
		for(int i = head[v]; i; i = data[i].next) {
			Data &e = data[i];
			if(!vis[e.to])
				if((--deg[e.to]) < D) 
					q.push(e.to), vis[e.to] = true;
		}
	}
	
	for(int i = 1; i <= N; ++i) fa[i] = i;
	for(int i = 1; i <= N; ++i) if(!vis[i])
		for(int j = head[i]; j; j = data[j].next) {
			Data &e = data[j];
			if(!vis[e.to]) fa[Find(e.to)] = Find(i);
		}
	
	int ans = 0;
	for(int i = 1; i <= N; ++i) if(!vis[i]) ++sum[Find(i)];
	for(int i = 1; i <= N; ++i) 
		if(!vis[i] && sum[i] > sum[ans]) ans = i;
		
	if(!sum[ans]) return printf("NIE\n"), 0;
		
	printf("%d\n", sum[ans]);
	for(int i = 1; i <= N; ++i) if(Find(i) == ans) put[++back] = i;
	for(int i = 1; i <= back; ++i)
		if(i != back) printf("%d ", put[i]);
		else printf("%d\n", put[i]);
	return 0;
}
