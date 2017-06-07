#include <cstdio>
#include <cstring>
#include <functional>
#include <queue>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;

const int maxn = 2e5+5;
const long long inf = 1e15;
struct Data { int next, to, w, t, op; } data[maxn<<1], sh[maxn<<1];
struct Load { int u, v; long long w; } load[maxn<<1];
struct Node { int x; long long d; };
struct cmp
{
	bool operator ()(const Node &a, const Node &b) const
		{ return a.d > b.d; } 
};
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}
int N, M, S, T, cnt, tot, id;
int head[maxn], fir[maxn], dfn[maxn], low[maxn];
long long dis[2][maxn], Min;
bool check[maxn], scc[maxn], used[maxn];

void add(int x, int y, int w, int op)
{ data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; data[cnt].w = w; data[cnt].op = op; }
void insert(int x, int y, int t)
{ sh[++tot].next = fir[x]; fir[x] = tot; sh[tot].to = y; sh[tot].t = t; }
void Input()
{
	N = read(), M = read(), S = read(), T = read();
	for(int i = 1, u, v, w; i <= M; ++i)
		u = read(), v = read(), w = read(), load[i] = (Load){u, v, w}, add(u, v, w, 0), add(v, u, w, 1);
	mem(dis, 63);
}

void dijkstra(long long *dis, int on, int s)
{
	mem(check, 0);
	priority_queue<Node, vector<Node>, cmp>q;
	dis[s] = 0; q.push((Node){s, 0});
	while(!q.empty())
	{
		Node v = q.top(); q.pop();
		if(check[v.x]) continue;
		check[v.x] = true;
		for(int i = head[v.x]; i; i = data[i].next)
		if(data[i].op == on)
		{
			Data &e = data[i];
			if(dis[v.x]+e.w < dis[e.to]) dis[e.to] = dis[v.x]+e.w, q.push((Node){e.to, dis[e.to]});
		}
	}
}

void BuildGraph()
{
	Min = dis[0][T];
	for(int i = 1; i <= M; ++i)
	{
		Load &e = load[i];
		if(dis[0][e.u]+e.w+dis[1][e.v] == Min) insert(e.u, e.v, i), insert(e.v, e.u, i);
	}
}

void Tarjan(int x, int fa)
{
	if(used[x]) return;
	used[x] = true; low[x] = dfn[x] = ++id;
	int sum = 0;
	for(int i = fir[x]; i; i = sh[i].next)
	{
		Data &e = sh[i];
		if(e.to == fa)
		{
			if(sum) low[x] = min(low[x], low[fa]);
			++sum;
		}
		else Tarjan(e.to, x), low[x] = min(low[e.to], low[x]);
		if(dfn[x] < low[e.to]) scc[e.t] = true;
	}
}

void Output()
{
	for(int i = 1; i <= M; ++i)
	{
		Load &e = load[i];
		long long D = dis[0][e.u]+dis[1][e.v]+e.w;
		if(dis[0][e.u] > inf || dis[1][e.v] > inf) { printf("NO\n"); continue; }
		if(scc[i]) { printf("YES\n"); continue; }
		else if(D >= Min)
		{
			long long temp = D-Min+1;
			if(e.w > temp) printf("CAN %I64d\n", temp);
			else printf("NO\n");
		}
		else printf("NO\n");
	}
}

int main()
{
//	freopen("data.in", "r", stdin);
//	freopen("my.out", "w", stdout);
	Input();
	dijkstra(dis[0], 0, S);
	dijkstra(dis[1], 1, T);
	BuildGraph();
	Tarjan(S, 0);
	Output();
	return 0;
}
