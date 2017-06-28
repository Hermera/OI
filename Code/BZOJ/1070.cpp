#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
const int maxn = 605, inf = 1e9;
int N, M, S, T, ans, t[maxn][maxn], dis[maxn], iter[maxn];
bool vis[maxn];
struct Edge { int to, rev, cap, cost; };
vector <Edge> G[maxn];

void add(int x, int y, int cap, int cost)
{
	G[x].push_back((Edge){ y, G[y].size(), cap, cost });
	G[y].push_back((Edge){ x, G[x].size()-1, 0, -cost });
}

bool SPFA()
{
	queue <int> q;
	mset(vis, 0), mset(dis, 63), mset(iter, 0);
	q.push(T); dis[T] = 0; vis[T] = true;
	while(!q.empty())
	{
		int v = q.front(); q.pop(); vis[v] = false;
		for(int i = 0; i < G[v].size(); ++i)
		{
			Edge &e = G[v][i];
			if(G[e.to][e.rev].cap && dis[e.to] > dis[v]-e.cost)
			{
				dis[e.to] = dis[v]-e.cost;
				if(!vis[e.to]) vis[e.to] = true, q.push(e.to);
			}
		}
	}
	mset(vis, 0);
	return dis[S] < inf;
}

int dfs(int v, int t, int f)
{
	vis[v] = true;
	if(v == t || !f) return f;
	for(int &i = iter[v]; i < G[v].size(); ++i)
	{
		Edge &e = G[v][i];
		if(e.cap && !vis[e.to] && dis[v]-e.cost == dis[e.to])
		{
			int d = dfs(e.to, t, min(e.cap, f));
			if(d > 0)
			{ ans += d*e.cost, e.cap -= d, G[e.to][e.rev].cap += d; return d; }
		}
	}
	return 0;
}


int ZKW(int s, int t)
{
	int flow = 0;
	while(SPFA())
		for(int f; (f = dfs(s, t, inf)) > 0; ) flow += f;
	return flow;
}
                
void init()
{
	scanf("%d%d", &N, &M);
	S = 0, T = N*M+M+1;
	for(int i = 1; i <= M; ++i)
	for(int j = 1; j <= N; ++j)
		scanf("%d", &t[i][j]);
		
	for(int i = 1; i <= N*M; ++i) add(S, i, 1, 0);
	for(int i = N*M+1; i <= N*M+M; ++i) add(i, T, 1, 0);
	
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= M; ++j)
	for(int k = 1; k <= M; ++k)
		add((i-1)*M+j, N*M+k, 1, t[k][i]*j);
}

int main()
{
	freopen("data.in", "r", stdin);
	init();
	ZKW(S, T);
	printf("%.2lf\n", ans*1.0/M);
	return 0;
}
