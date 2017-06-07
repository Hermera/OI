#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#define mset(x, a) memset(x, a, sizeof(x))
#define mid ((left+right)>>1)
#define lc node<<1, left, mid
#define rc node<<1|1, mid+1, right
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5, Log = 18;
const ll inf = 1e15;
int N, M, tim, cnt;
int head[maxn], id[maxn], deep[maxn], top[maxn], son[maxn], size[maxn], from[maxn], fa[maxn][Log];
struct Data { int next, to; } data[maxn<<1];
struct Edge { int to, w; };
struct Node
{ 
	int id; ll dis; 
	bool operator <(const Node &b) const
	{ return dis > b.dis; }
};
ll dis[maxn], tree[maxn<<2];
vector <Edge> G[maxn];
bool check[maxn];

void add(int x, int y)
{ data[++cnt] = (Data){ head[x], y }; head[x] = cnt; }

void Dijkstra(int s)
{
	priority_queue <Node, vector<Node> > q;
	mset(dis, 63), dis[s] = 0, q.push((Node){ s, dis[s] });
	while(!q.empty())
	{
		Node v = q.top(); q.pop();
		if(check[v.id]) continue;
		check[v.id] = true;
		for(int i = 0; i < G[v.id].size(); ++i)
		{
			Edge &e = G[v.id][i];
			if(!check[e.to] && dis[e.to] > dis[v.id]+e.w)
				dis[e.to] = dis[v.id]+e.w, from[e.to] = v.id, q.push((Node){ e.to, dis[e.to] });
		}
	}
	for(int i = 1; i <= N; ++i) add(from[i], i);
}

void MakeSize(int x, int f)
{
	size[x] = 1; fa[x][0] = f;
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != f)
	{
		Data &e = data[i];
		deep[e.to] = deep[x]+1;
		MakeSize(e.to, x);
		size[x] += size[e.to];
		if(size[e.to] > size[son[x]]) son[x] = e.to;
	}
}

void MakeLink(int x, int tp)
{
	top[x] = tp; id[x] = ++tim;
	if(son[x]) MakeLink(son[x], tp);
	for(int i = head[x]; i; i = data[i].next)
	if(data[i].to != fa[x][0] && data[i].to != son[x])
		MakeLink(data[i].to, data[i].to);
}

int LCA(int x, int y)
{
	if(deep[y] > deep[x]) swap(x, y);
	int d = deep[x]-deep[y];
	for(int i = 0; i < Log; ++i)
	if(d&(1<<i)) x = fa[x][i];
	if(x == y) return x;
	for(int i = Log-1; i >= 0; --i)
	if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
	return fa[x][0];	
}

void Update(int node, int left, int right, int L, int R, ll v)
{
	if(L <= left && right <= R) { tree[node] = min(tree[node], v); return; }
	if(right < L || R < left) return;
	Update(lc, L, R, v);
	Update(rc, L, R, v);
}

ll Query(int node, int left, int right, int pos)
{
	if(left == right) return tree[node];
	if(pos <= mid) return min(tree[node], Query(lc, pos));
	else return min(tree[node], Query(rc, pos));
}

void Modify(int u, int v, ll w)
{
	while(top[u] != top[v])
	{
		if(deep[top[u]] < deep[top[v]]) swap(u, v);
		Update(1, 1, N, id[top[u]], id[u], w);
		u = fa[top[u]][0]; 
	}
	if(deep[u] > deep[v]) swap(u, v);
	if(u != v) Update(1, 1, N, id[u]+1, id[v], w);
}

int main()
{
//	freopen("travel.in", "r", stdin);
//	freopen("travel.out", "w", stdout);
	N = read(), M = read();
	for(int i = 1, u, v, w; i <= M; ++i)
		u = read(), v = read(), w = read(), G[u].push_back((Edge){v, w}), G[v].push_back((Edge){u, w});
	
	Dijkstra(1);
	
	MakeSize(1, 0), MakeLink(1, 1);
	mset(tree, 63);
	
	for(int i = 1; i < Log; ++i)
	for(int j = 1; j <= N; ++j)
		fa[j][i] = fa[fa[j][i-1]][i-1];
	
	for(int i = 1; i <= N; ++i)
	for(int j = 0; j < G[i].size(); ++j)
	{
		Edge &e = G[i][j];
		if(e.to == fa[i][0]) continue;
		int f = LCA(i, e.to);
		Modify(f, i, dis[i]+dis[e.to]+e.w);
	}
	
	for(int i = 2; i <= N; ++i)
	{
		ll ans = Query(1, 1, N, id[i]);
		printf("%lld\n", ans < inf ? ans-dis[i] : -1);
	}
	return 0;
}
