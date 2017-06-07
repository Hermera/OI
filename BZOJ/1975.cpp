#include <cstdio>
#include <cstring>
#include <algorithm>
#include <functional>
#include <queue>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
const int maxn = 5005, maxm = 200005, inf = 1e9;
int N, M, cnt, fcnt;
double E, dis[maxn], head[maxn], fhead[maxn];
bool vis[maxn];
struct Data { int next, to; double w; } data[maxm], fdata[maxm];
struct Node { double g; int node; };
struct cmp
{
	bool operator ()(const Node &a, const Node &b) const
		{ return a.g+dis[a.node] > b.g+dis[b.node]; }
};

void add(int x, int y, double w) { data[++cnt] = (Data){head[x], y, w}; head[x] = cnt; }
void fadd(int x, int y, double w) { fdata[++fcnt] = (Data){fhead[x], y, w}; fhead[x] = fcnt; }

void SPFA()
{
	queue <int> q;
	for(int i = 1; i <= N; ++i) dis[i] = inf;
	q.push(N); dis[N] = 0; vis[N] = true;
	while(!q.empty())
	{
		int v = q.front(); q.pop(); vis[v] = false;
		for(int i = fhead[v]; i; i = fdata[i].next)
		{
			Data &e = fdata[i];
			if(dis[e.to] > dis[v]+e.w)
			{
				dis[e.to] = dis[v]+e.w;
				if(!vis[e.to]) vis[e.to] = true, q.push(e.to);
			}
		}
	}
}

int AstarDijkstra()
{
	priority_queue <Node, vector<Node>, cmp>q;
	q.push((Node){0, 1});
	int cnt = 0;
	while(!q.empty())
	{
		Node v = q.top(); q.pop();
		if(v.node == N)
			if(E >= v.g) ++cnt, E -= v.g;
			else return cnt;
		for(int i = head[v.node]; i; i = data[i].next)
		{
			Data &e = data[i];
			q.push((Node){v.g+e.w, e.to});
		}
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	scanf("%d%d%lf", &N, &M, &E);
	for(int i = 1; i <= M; ++i)
	{
		int s, t; double e;
		scanf("%d%d%lf", &s, &t, &e), add(s, t, e), fadd(t, s, e);
	}
	SPFA();
	printf("%d\n", AstarDijkstra());
	return 0;
}
