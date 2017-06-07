#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e5+5;
int N, cnt, size[maxn], head[maxn], down[maxn], ans[maxn];
struct Data { int next, to; } data[maxn<<1];

void add(int x, int y) {
	data[++cnt] = (Data){ head[x], y }; head[x] = cnt; 
}

void dfs(int x, int fa) {
	size[x] = 1;
	for(int i = head[x]; i; i = data[i].next) 
	if(data[i].to != fa) {
		Data &e = data[i];
		dfs(e.to, x);
		size[x] += size[e.to];
		down[x] = max(down[x], down[e.to]);
	}
	if(size[x] <= N/2) down[x] = size[x];
}
		
void dfs(int x, int fa, int mx) {
	int fir = 0, sec = 0;
	if(N-size[x]-mx <= N/2) ans[x] = 1;
	for(int i = head[x]; i; i = data[i].next) 
	if(data[i].to != fa) {
		Data &e = data[i];
		if(down[e.to] > fir) sec = fir, fir = down[e.to];
		else if(down[e.to] > sec) sec = down[e.to];
		if(size[e.to]-down[e.to] > N/2) ans[x] = 0;
	}
	
	for(int i = head[x]; i; i = data[i].next) 
	if(data[i].to != fa) {
		Data &e = data[i];
		if(N-size[e.to] <= N/2) dfs(e.to, x, N-size[e.to]);
		else {
			if(down[e.to] == fir) dfs(e.to, x, max(mx, sec));
			else dfs(e.to, x, max(fir, mx));
		}
	}
}

int main() {
	freopen("708C.in", "r", stdin);

	N = read();
	for(int i = 1, u, v; i < N; ++i) 
		u = read(), v = read(), add(u, v), add(v, u);
	dfs(1, 0);
	dfs(1, 0, 0);
	
	for(int i = 1; i <= N; ++i) printf("%d ", ans[i]);
	return 0;
}
