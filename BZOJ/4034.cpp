#include <cstdio>
#include <algorithm>
#define mid ((left+right)>>1)
#define lc node<<1, left, mid, L, R
#define rc node<<1|1, mid+1, right, L, R
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum*t;
}
const int maxn = 100005;
int N, M, tim, cnt;
int head[maxn], fa[maxn], size[maxn], son[maxn], deep[maxn], top[maxn], id[maxn], w[maxn], val[maxn], l[maxn], r[maxn];
struct Data { int next, to; } data[maxn<<1];
ll tree[maxn<<2], lazy[maxn<<2];
void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }

void MakeSize(int x, int f)
{
	size[x] = 1; deep[x] = deep[f]+1; fa[x] = f;
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != f)
	{
		Data &e = data[i];
		MakeSize(e.to, x);
		size[x] += size[e.to];
		if(size[e.to] > size[son[x]]) son[x] = e.to;
	}
}
void MakeLink(int x, int tp)
{
	id[x] = ++tim; top[x] = tp;
	l[x] = tim;
	if(son[x]) MakeLink(son[x], tp);
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa[x] && data[i].to != son[x])
		MakeLink(data[i].to, data[i].to);
	r[x] = tim;
}

void pushdown(int node, int left, int right)
{
	if(!lazy[node]) return;
	lazy[node<<1] += lazy[node]; lazy[node<<1|1] += lazy[node];
	tree[node<<1] += (ll)(mid-left+1)*lazy[node];
	tree[node<<1|1] += (ll)(right-mid)*lazy[node];
	lazy[node] = 0;
}
void pushup(int node) { tree[node] = tree[node<<1]+tree[node<<1|1]; }

void Build(int node, int left, int right)
{
	if(left == right) { tree[node] = val[left]; return; }
	Build(node<<1, left, mid); Build(node<<1|1, mid+1, right);
	pushup(node);
}

ll Query(int node, int left, int right, int L, int R)
{
	if(L <= left && right <= R) return tree[node];
	if(R < left || right < L) return 0;
	pushdown(node, left, right);
	ll ret1 = Query(lc), ret2 =  Query(rc);
	pushup(node);
	return ret1+ret2;
}

void Modify(int node, int left, int right, int L, int R, int v)
{
	if(L <= left && right <= R) { tree[node] += (ll)(right-left+1)*v; lazy[node] += v; return;}
	if(R < left || right < L) return;
	pushdown(node, left, right);
	Modify(lc, v); Modify(rc, v);
	pushup(node);
}

ll Ask(int u, int v)
{
	ll ans = 0;
	while(top[u] != top[v])
	{
		if(deep[top[u]] < deep[top[v]]) swap(u, v);
		ans += Query(1, 1, N, id[top[u]], id[u]);
		u = fa[top[u]];
	}
	if(deep[u] > deep[v]) swap(u, v);
	ans += Query(1, 1, N, id[u], id[v]);
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1; i <= N; ++i) w[i] = read();
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), add(u, v), add(v, u);
	MakeSize(1, 0); MakeLink(1, 1);
	for(int i = 1; i <= N; ++i) val[id[i]] = w[i]; 
	Build(1, 1, N);
	for(int i = 1; i <= M; ++i)
	{
		int op = read(), x = read();
		if(op == 1) Modify(1, 1, N, id[x], id[x], read());
		if(op == 2) Modify(1, 1, N, l[x], r[x], read());
		if(op == 3) printf("%lld\n", Ask(1, x));
	}
	return 0;
}
