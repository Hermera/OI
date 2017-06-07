#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

const int maxn = 55;
int n, m, t, mx, cnt, f[maxn], son[maxn], head[maxn], size[maxn];
string h[maxn], q[maxn], v[maxn];
struct Data { int next, to; } data[maxn<<1];
void add(int x, int y) {
	data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
}

void findroot(int x, int fa) {
	size[x] = 1, f[x] = 0;
	for(int i = head[x]; i; i = data[i].next) 
	if(data[i].to != fa) {
		Data &e = data[i];
		findroot(e.to, x);
		size[x] += size[e.to];
		if(size[e.to] > f[x]) f[x] = size[e.to];
	}
	if(n-size[x] > f[x]) f[x] = n-size[x];
	if(f[x] < mx) mx = f[x];
}

void dfs(int x, int fa) {
	h[x] = "(";
	for(int i = head[x]; i; i = data[i].next) 
		if(data[i].to != fa) dfs(data[i].to, x);
	t = 0;
	for(int i = head[x]; i; i = data[i].next) 
		if(data[i].to != fa) q[t++] = h[data[i].to];
	sort(q, q+t);
	for(int i = 0; i < t; ++i) h[x] += q[i];
	h[x] += ")";
}

string solve() {
	string t = "";
	scanf("%d", &n), cnt = 0, mx = n;
	for(int i = 1; i <= n; ++i) head[i] = 0;
	for(int i = 1, x; i <= n; ++i) {
		scanf("%d", &x);
		if(x) add(i, x), add(x, i);
	}
	
	findroot(1, 0);
	for(int i = 1; i <= n; ++i) if(f[i] == mx) {
		dfs(i, 0);
		if(h[i] > t) t = h[i];
	}
	return t;
}

int main() {	
	scanf("%d", &m);
	for(int i = 1; i <= m; ++i) v[i] = solve();
	for(int i = 1, j, k; i <= m; ++i) {
		for(j = k = i; j; --j) if(v[j] == v[i]) k = j;
		printf("%d\n", k);
	}
	return 0;
}
