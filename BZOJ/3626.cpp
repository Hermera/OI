#include <cstdio>
#include <vector>
#include <algorithm>
#define mid ((l+r)>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

const int maxn = 50005, Mod = 201314;
int N, Q, cnt, tim;
int deep[maxn], head[maxn], fa[maxn], son[maxn], size[maxn], top[maxn], id[maxn], lazy[maxn<<2];
vector <int> G[maxn];
ll tree[maxn<<2];
struct Data { int next, to; } data[maxn];
struct Op
{
	int l, r, z; bool flag; ll ret;
	void init(int id)
	{
		l = read()+1, r = read()+1, z = read()+1;
		G[l-1].push_back(id), G[r].push_back(id);
	}
} op[maxn];

void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }

void MakeSize(int x)
{
	size[x] = 1;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(e.to != fa[x])
		{
			fa[e.to] = x, deep[e.to] = deep[x]+1;
			MakeSize(e.to);
			size[x] += size[e.to];
			if(size[e.to] > size[son[x]]) son[x] = e.to;
		}
	}
}

void MakeLink(int x, int tp)
{
	top[x] = tp, id[x] = ++tim;
	if(son[x]) MakeLink(son[x], tp);
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(e.to != fa[x] && e.to != son[x]) MakeLink(e.to, e.to);
	}
}

void pushup(int x) { tree[x] = tree[x<<1]+tree[x<<1|1]; }
void pushdown(int x, int l, int r)
{
	if(!lazy[x]) return;
	lazy[x<<1] += lazy[x], lazy[x<<1|1] += lazy[x];
	tree[x<<1] += (mid-l+1)*lazy[x];
	tree[x<<1|1] += (r-mid)*lazy[x];
	lazy[x] = 0;
}

void Update(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) { tree[o] += r-l+1, ++lazy[o]; return; }
	if(r < L || R < l) return;
	pushdown(o, l, r);
	Update(lc, L, R), Update(rc, L, R);
	pushup(o);
}

ll Query(int o, int l, int r, int L, int R)
{
	if(L <= l && r <= R) return tree[o];
	if(r < L || R < l) return 0;
	pushdown(o, l, r);
	ll ans = Query(lc, L, R)+Query(rc, L, R);
	pushup(o);
	return ans;
}

void Modify(int u, int v)
{
	while(top[u] != top[v])
	{
		if(deep[top[u]] < deep[top[v]]) swap(u, v);
		Update(1, 1, N, id[top[u]], id[u]);
		u = fa[top[u]];
	}
	if(deep[u] < deep[v]) swap(u, v);
	Update(1, 1, N, id[v], id[u]);
}

ll Ask(int u, int v)
{
	ll ans = 0;
	while(top[u] != top[v])
	{
		if(deep[top[u]] < deep[top[v]]) swap(u, v);
		ans += Query(1, 1, N, id[top[u]], id[u]);
		ans %= Mod;
		u = fa[top[u]];
	}
	if(deep[u] < deep[v]) swap(u, v);
	ans += Query(1, 1, N, id[v], id[u]);
	return ans%Mod;
}

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);

	N = read(), Q = read();
	for(int i = 2; i <= N; ++i) add(read()+1, i);
	for(int i = 1; i <= Q; ++i) op[i].init(i);
	MakeSize(1);
	MakeLink(1, 1);
	
	for(int i = 0; i <= N; ++i)
	{
		if(i) Modify(1, i);
		for(int j = 0; j < G[i].size(); ++j)
		{
			Op &e = op[G[i][j]];
			if(!e.flag) e.ret = Ask(1, e.z), e.flag = true;
			else e.ret = Ask(1, e.z)-e.ret;
		}
	}
	
	for(int i = 1; i <= Q; ++i) printf("%lld\n", (op[i].ret+Mod)%Mod);
	return 0;
}
