#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, maxl = 18;
int n, m, q, tim, cnt, head[maxn], L[maxn], R[maxn], deep[maxn], fa[maxn][maxl];
struct Data { int next, to; } data[maxn];
void add(int x, int y) {
	data[++cnt] = (Data) { head[x], y }; head[x] = cnt;
	data[++cnt] = (Data) { head[y], x }; head[y] = cnt;
}

void dfs(int x) {
	L[x] = ++tim;
	for(int i = 0; fa[x][i]; ++i) fa[x][i+1] = fa[ fa[x][i] ][i];
	for(int i = head[x]; i; i = data[i].next) 
		if(data[i].to != fa[x][0]) {
			Data &e = data[i];
			fa[e.to][0] = x, deep[e.to] = deep[x]+1;
			dfs(e.to);
		}
	R[x] = tim;
}

int jump(int x, int k) {
	for(int i = maxl-1; ~i; --i)
		if(k&(1<<i)) x = fa[x][i];
	return x;
}
int lca(int x, int y) {
	if(deep[x] < deep[y]) swap(x, y);
	x = jump(x, deep[x]-deep[y]);
	if(x == y) return x;
	for(int i = maxl-1; ~i; --i)
		if(fa[x][i] != fa[y][i])
			x = fa[x][i], y = fa[y][i];
	return fa[x][0];
}


struct BIT {
	int t[maxn];
	void modify(int l, int r, int v) {
		for(int i = l  ; i <= n; i += i&-i) t[i] += v;
		for(int i = r+1; i <= n; i += i&-i) t[i] -= v;
	}
	int query(int x) {
		int ret = 0;
		while(x) ret += t[x], x -= x&-x;
		return ret;
	}
} T;

int tot, sum[maxn], ans[maxn];
struct rec {
	int x1, x2, y1, y2, v;
	bool operator <(const rec &b) const { return v < b.v; }
} mat[maxn];

struct ele {
	int x, y1, y2, v, id;
	bool operator <(const ele &b) const { 
		return x != b.x ? x < b.x : id < b.id; 
	}
} eve[maxn];

struct point { int x, y, k, id; } ask[maxn], tmp1[maxn], tmp2[maxn];

void solve(int l, int r, int s, int t) {
	if(s >  t) return;
	if(l == r) {
		for(int i = s; i <= t; ++i) ans[ask[i].id] = mat[l].v;
		return;
	}
	
	int mid = (l+r)>>1, size = 0;
	for(int i = l; i <= mid; ++i) 
		eve[++size] = (ele){ mat[i].x1, mat[i].y1, mat[i].y2, 1, 0},
		eve[++size] = (ele){ mat[i].x2, mat[i].y1, mat[i].y2, -1, n+1};
	for(int i = s; i <= t; ++i) eve[++size] = (ele){ ask[i].x, ask[i].y, 0, 0, i};
	sort(eve+1, eve+1+size);
	for(int i = 1; i <= size; ++i) {
		ele &e = eve[i];
		if(e.id && e.id <= n) sum[e.id] = T.query(e.y1);
		else T.modify(e.y1, e.y2, e.v);
	}
	
	int a = 0, b = 0;
	for(int i = s; i <= t; ++i)
		if(sum[i] >= ask[i].k) tmp1[++a] = ask[i];
		else ask[i].k -= sum[i], tmp2[++b] = ask[i];
	for(int i = s; i <  s+a; ++i) ask[i] = tmp1[i-s+1];
	for(int i = s+a; i <= t; ++i) ask[i] = tmp2[i-s-a+1];
	solve(l, mid, s, s+a-1);
	solve(mid+1, r, s+a, t);
}

int main() {
	n = read(), m = read(), q = read();
	for(int i = 2, x, y; i <= n; ++i) add(read(), read());
	dfs(1);
	
	for(int i = 1, a, b, c, u; i <= m; ++i) {
		a = read(), b = read(), c = read(), u = lca(a, b);
		if(L[a] > L[b]) swap(a, b);
		if(a != u) mat[++tot] = (rec){ L[a], R[a], L[b], R[b], c };
		else {
			int w = jump(b, deep[b]-deep[a]-1);
			if(L[w] > 1) mat[++tot] = (rec){ 1, L[w]-1, L[b], R[b], c };
			if(R[w] < n) mat[++tot] = (rec){ L[b], R[b], R[w]+1, n, c };
		}
	}
	
	sort(mat+1, mat+1+tot);
	for(int i = 1, a, b, k; i <= q; ++i) {
		a = read(), b = read(), k = read();
		if(L[a] > L[b]) swap(a, b);
		ask[i] = (point) { L[a], L[b], k, i };
	}
	
	solve(1, tot, 1, q);
	for(int i = 1; i <= q; ++i) printf("%d\n", ans[i]);
	return 0;
}
