#include <cstdio>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e6+5;
int n, cnt, head[maxn], mx[maxn], deep[maxn];
ll ans, tmp[maxn], *fyt = tmp+1, *f[maxn], *g[maxn];
struct Data { int next, to; } data[maxn];
void add(int x, int y) {
	data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
	data[++cnt] = (Data){ head[y], x }; head[y] = cnt;
}

void dfs(int x, int fa) {
	mx[x] = x;
	for(int i = head[x], v; i; i = data[i].next) 
		if((v = data[i].to) != fa) {
			deep[v] = deep[x]+1;
			dfs(v, x);
			if(deep[mx[v]] > deep[mx[x]]) mx[x] = mx[v];
		}
	for(int i = head[x], v; i; i = data[i].next) 
		if((v = data[i].to) != fa) {
			if(mx[v] != mx[x] || x == 1) 
				v = mx[v],
				fyt += deep[v]-deep[x]+1, f[v] = fyt,
				g[v] = ++fyt, fyt += (deep[v]-deep[x])*2+1;
		}
}

void dp(int x, int fa) {
	for(int i = head[x], v; i; i = data[i].next) 
		if((v = data[i].to) != fa) {
			dp(v, x);
			if(mx[v] == mx[x])
				f[x] = f[v]-1, g[x] = g[v]+1;
		}
	
	f[x][0] = 1;
	ans += g[x][0];
	for(int i = head[x], v; i; i = data[i].next) 
		if((v = data[i].to) != fa) 	
			if(mx[v] != mx[x]) {
				for(int j = 0; j <= deep[mx[v]]-deep[x]; ++j)
					ans += f[x][j-1]*g[v][j] + g[x][j+1]*f[v][j];
				for(int j = 0; j <= deep[mx[v]]-deep[x]; ++j)
					g[x][j-1] += g[v][j],
					g[x][j+1] += f[x][j+1]*f[v][j],
					f[x][j+1] += f[v][j];
			}
}
				
				
int main() {
	n = read();
	for(int i = 2; i <= n; ++i) 	
		add(read(), read());
		
	deep[1] = 1;
	dfs(1, 0), dp(1, 0);
	printf("%lld\n", ans);
	return 0;
}
