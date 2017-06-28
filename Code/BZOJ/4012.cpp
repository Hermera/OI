#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 150005;
int n, m, mod, idx, cnt, tim;
int head[maxn], size[maxn], son[maxn], fa[maxn], top[maxn], id[maxn], root[maxn];
ll ans, dis[maxn], sum[maxn], w[maxn], v[maxn];

#define mid (l+r>>1)
#define lc t[o].l, l, mid
#define rc t[o].r, mid+1, r
struct Persistent_Segment {
	struct Node { int l, r, tot; ll sum; } t[maxn*50];
	void modify(int &o, int l, int r, int L, int R) {
		t[++idx] = t[o], o = idx;
		if(L == l && r == R) {
			++t[o].tot;
			return;
		}
		
		t[o].sum += v[R]-v[L-1];
		if(R <= mid) modify(lc, L, R);
		else if(mid < L) modify(rc, L, R);
		else modify(lc, L, mid), modify(rc, mid+1, R);
	}
	
	ll query(int o, int l, int r, int L, int R) {
		ll ret = (v[R]-v[L-1])*t[o].tot;
		if(L == l && r == R) return ret+t[o].sum;
		if(R <= mid) ret += query(lc, L, R);
		else if(mid < L) ret += query(rc, L, R);
		else return ret += query(lc, L, mid)+query(rc, mid+1, R);
		return ret;
	}
} T;

struct Data { int next, to, w; } G[maxn<<1];
void add(int x, int y, int w) {
	G[++cnt] = (Data){ head[x], y, w }, head[x] = cnt;
}

void dfs(int x) {
	size[x] = 1;
	for(int i = head[x]; i; i = G[i].next) 
		if(G[i].to != fa[x]) {
			Data &e = G[i];
			fa[e.to] = x, w[e.to] = e.w, dis[e.to] = dis[x]+e.w;
			dfs(e.to), size[x] += size[e.to];
			if(size[e.to] > size[son[x]]) son[x] = e.to;
		}
}

void dfs(int x, int tp) {
	id[x] = ++tim, top[x] = tp, v[tim] = w[x];
	if(son[x]) dfs(son[x], tp);
	for(int i = head[x]; i; i = G[i].next)
		if(G[i].to != fa[x] && G[i].to != son[x])
			dfs(G[i].to, G[i].to);
}

void modify(int &rt, int x) {
	for( ; top[x] != 1; x = fa[top[x]])
		T.modify(rt, 1, n, id[top[x]], id[x]);
	T.modify(rt, 1, n, 1, id[x]);
}

ll query(int rt, int x) {
	ll ret = 0;
	for( ; top[x] != 1; x = fa[top[x]])
		ret += T.query(rt, 1, n, id[top[x]], id[x]);
	return ret + T.query(rt, 1, n, 1, id[x]);
}

struct ele {
	int age, id;
	bool operator <(const ele &b) const {
		return age < b.age; 
	}
} a[maxn];

int load() { return (ans+read())%mod; }
int main() {
	n = read(), m = read(), mod = read();
	for(int i = 1; i <= n; ++i) a[i].age = read(), a[i].id = i;
	for(int i = 2, x, y, w; i <= n; ++i)
		x = read(), y = read(), w = read(),
		add(x, y, w), add(y, x, w);
		
	dfs(1);
	dfs(1, 1);
	sort(a+1, a+1+n);
	for(int i = 1; i <= n; ++i) v[i] += v[i-1];
	for(int i = 1; i <= n; ++i) sum[i] = sum[i-1]+dis[a[i].id];
	for(int i = 1; i <= n; ++i) modify(root[i] = root[i-1], a[i].id);
	for(int i = 1, x, l, r; i <= m; ++i) {
		x = read(), l = load(), r = load();
		if(l > r) swap(l, r);
		l = lower_bound(a+1, a+1+n, (ele){ l, 0 })-a;
		r = upper_bound(a+1, a+1+n, (ele){ r, 0 })-a-1;
		
		ans = 0;
		ans += 1ll*(r-l+1)*dis[x];
		ans += sum[r]-sum[l-1];
		ans -= 2ll*(query(root[r], x)-query(root[l-1], x));
		printf("%lld\n", ans);
	}
	return 0;
}
