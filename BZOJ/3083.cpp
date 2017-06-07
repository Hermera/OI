#include <cstdio>
#include <algorithm>
#define mid ((l+r)>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
using namespace std;
typedef long long ll;
inline ll read()
{
	char ch = getchar(); ll sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5;
const ll inf = 1LL<<31;
int N, M, cnt, root, tim;
int head[maxn], deep[maxn], val[maxn];
int L[maxn], R[maxn], size[maxn], top[maxn], fa[maxn][20], son[maxn];
ll tree[maxn<<2], lazy[maxn<<2];
struct Data { int next, to; } data[maxn<<1];

void add(int x, int y) { data[++cnt] = (Data){ head[x], y }; head[x] = cnt; }

void MakeSize(int x)
{
	size[x] = 1;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(e.to == fa[x][0]) continue;
		fa[e.to][0] = x, deep[e.to] = deep[x]+1;
		MakeSize(e.to);
		size[x] += size[e.to];
		if(size[e.to] > size[son[x]]) son[x] = e.to;
	}
}

void MakeLink(int x, int tp)
{
	L[x] = ++tim; top[x] = tp;
	if(son[x]) MakeLink(son[x], tp);
	for(int i = head[x]; i; i = data[i].next)
		if(data[i].to != fa[x][0] && data[i].to != son[x]) 
			MakeLink(data[i].to, data[i].to);
	R[x] = tim;
}

void Pushup(int x) { tree[x] = min(tree[x<<1], tree[x<<1|1]); }
void Pushdown(int x)
{
	if(!lazy[x]) return;
	lazy[x<<1] = tree[x<<1] = lazy[x<<1|1] = tree[x<<1|1] = lazy[x];
	lazy[x] = 0;
}

void Build(int o, int l, int r)
{
	if(l == r) { tree[o] = val[l]; return; }
	Build(lc), Build(rc);
	Pushup(o);
}

void Modify(int o, int l, int r, int L, int R, ll v)
{
	if(L <= l && r <= R) { tree[o] = lazy[o] = v; return; }
	if(R < L || R < l || r < L) return;
	Pushdown(o);
	Modify(lc, L, R, v), Modify(rc, L, R, v);
	Pushup(o);
}

ll Query(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return tree[o];
	if(R < L || R < l || r < L) return inf;
	Pushdown(o);
	return min(Query(lc, L, R), Query(rc, L, R));
	Pushup(o);
}

void Update(int u, int v, int val)
{
	while(top[u] != top[v])
	{
		if(deep[top[u]] < deep[top[v]]) swap(u, v);
		Modify(1, 1, N, L[top[u]], L[u], val);
		u = fa[top[u]][0];
	}
	if(deep[u] < deep[v]) swap(u, v);
	Modify(1, 1, N, L[v], L[u], val);
}

int LCA(int u, int v)
{
	while(top[u] != top[v])
	{
		if(deep[top[u]] < deep[top[v]]) swap(u, v);
		u = fa[top[u]][0];
	}
	if(deep[u] < deep[v]) swap(u, v);
	return v;
}

ll Ask(int x, int d)
{
	for(int i = 0; i < 20; ++i)
	if(d&(1<<i)) x = fa[x][i];
	return min(Query(1, 1, N, 1, L[x]-1), Query(1, 1, N, R[x]+1, N));
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), add(u, v), add(v, u);
	MakeSize(1);
	MakeLink(1, 1);
	for(int i = 1; i <= N; ++i) val[L[i]] = read();
	Build(1, 1, N);
	root = read();
	
	for(int i = 1; i < 20; ++i)
	for(int j = 1; j <= N; ++j)
		fa[j][i] = fa[fa[j][i-1]][i-1];
	
	while(M--)
	{
		int op = read(), p1, p2;
		if(op == 1) root = read();
		if(op == 2) p1 = read(), p2 = read(), Update(p1, p2, read());
		if(op == 3)
		{
			int p = read(), lca = LCA(root, p);
			if(p == root) printf("%lld\n", Query(1, 1, N, 1, N));
			else if(lca == p) 
				printf("%lld\n", Ask(root, deep[root]-deep[p]));
			else printf("%lld\n", Query(1, 1, N, L[p], R[p]));
		}
	}
	return 0;
}
