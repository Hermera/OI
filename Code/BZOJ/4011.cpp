#include <cstdio>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5, mod = 1e9+7;
int n, m, x, y, cnt, d[maxn], p[maxn], q[maxn], head[maxn];
ll inv[maxn], f[maxn], ans;
struct Data { int next, to; } data[maxn];
void add(int x, int y) {
	data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
}

void topsort() {
	int h = 1, t = 0;
	for(int i = 1; i <= n; ++i) if(!p[i]) q[++t] = i;
	while(h <= t) {
		int v = q[h++];
		(f[v] *= inv[d[v]])%= mod;
		for(int i = head[v]; i; i = data[i].next) {
			Data &e = data[i];
			(f[e.to] += f[v])%= mod;
			if(!(--p[e.to])) q[++t] = e.to;
		}
	}
}

int main() {
	inv[1] = 1;
	n = read(), m = read(), x = read(), y = read();
	for(int i = 2; i <= m+1; ++i)
		inv[i] = (mod-mod/i)*inv[mod%i]%mod;
	for(int i = 1, u, v; i <= m; ++i) 
		u = read(), v = read(), add(u, v),
		++d[v], ++p[v];
	++d[y];
	
	ans = 1;
	for(int i = 2; i <= n; ++i) 
		(ans *= d[i])%= mod;
	if(y == 1) return printf("%lld\n", ans), 0;
	
	f[y] = ans;
	topsort();
	(ans -= f[x])%= mod;
	printf("%lld\n", (ans+mod)%mod);
	return 0;
}	
