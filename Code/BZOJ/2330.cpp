#include <cstdio>
#include <queue>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5;
const int INF = 1e9;
struct Data { int next, to, w; } g[maxn<<1];
int n, k, s, cnt, h[maxn], dis[maxn], vis[maxn], inq[maxn];
long long ans;

void add(int x, int y, int w) {
	g[++cnt] = (Data){ h[x], y, w }; h[x] = cnt;
}

queue <int> q;
bool SPFA() {
	q.push(s);
	while(!q.empty()) {
		int v = q.front(); q.pop(), inq[v] = 0;
		for(int i = h[v]; i; i = g[i].next) {
			Data &e = g[i];
			if(dis[v]+e.w > dis[e.to]) {
				dis[e.to] = dis[v]+e.w;
				if((++vis[e.to]) >= n) return 0;
				if(!inq[e.to]) q.push(e.to), inq[e.to] = 1;
			}
		}
	}
	return 1;
}

int main() {
	n = read(), k = read();
	for(int x, a, b; k--; ) {
		x = read(), a = read(), b = read();
		if(a == b) 
			if(x&1) continue;
			else return printf("-1\n"), 0;
			
		if(x == 1) add(a, b, 0), add(b, a, 0);
		if(x == 2) add(a, b, 1);
		if(x == 3) add(b, a, 0);
		if(x == 4) add(b, a, 1);
		if(x == 5) add(a, b, 0);
	}
	
	for(int i = n; i; --i) add(s, i, 1);
	if(!SPFA()) return printf("-1\n"), 0;
	for(int i = 1; i <= n; ++i) ans += dis[i];
	printf("%lld\n", ans);
	return 0;
}
