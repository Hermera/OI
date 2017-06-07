#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e6+5;
int n, m, c, top, len, cnt;
int a[maxn], b[maxn], f[maxn], ans[maxn], st[maxn], head[maxn], h[maxn];
struct Data { int next, to; } data[maxn];
void add(int x, int y) {
	data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
}

void upd(int &x, int y) { if(y > x) x = y; }
void dfs(int x) {
	st[++top] = x;
	if(x <= c) for(ans[x] = len; st[top-ans[x]] < x+c; ++ans[x]);
	for(int i = head[x]; i; i = data[i].next) dfs(data[i].to);
	--top;
}			

int main() {
	n = read(), read();
	for(int i = 1; i <= n; ++i)
		h[++c] = a[i] = read(), h[++c] = b[i] = read();
	sort(h+1, h+1+c);
	c = unique(h+1, h+1+c)-h-1;
	for(int i = 1; i <= n; ++i)
		a[i] = lower_bound(h+1, h+1+c, a[i])-h,
		b[i] = lower_bound(h+1, h+1+c, b[i])-h;
	
	m = c<<1;
	for(int i = 1; i <= n; ++i) 
		if(a[i] < b[i]) 
			upd(f[a[i]], b[i]),
			upd(f[a[i]+c], b[i]+c);
		else 
			upd(f[1], b[i]),
			upd(f[a[i]], b[i]+c),
			upd(f[a[i]+c], m);
	for(int i = 1; i <= m; ++i) upd(f[i], f[i-1]);
	for(int i = 1; i <  m; ++i) add(f[i], i);
	for(int i = 1; i <= c; i = f[i]) ++len; --len;
	
	dfs(m);
	for(int i = 1; i <= n; ++i) printf("%d ", ans[a[i]]);
	return 0;
}
