#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#include <cmath>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
const int maxn = 5005, sqr = 32, inf = 1e9;
int A, B, S, T, flow, cost;
int dis[maxn], iter[maxn];
bool vis[maxn];
struct Edge { int to, rev, cap, cost; };
vector <Edge> G[maxn];

int gcd(int x, int y) { return !y ? x : gcd(y, x%y); }
void AddEdge(int x, int y, int cap, int cost)
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
			{ cost += d*e.cost, e.cap -= d, G[e.to][e.rev].cap += d; return d; }
		}
	}
	return 0;
}


int ZKW(int s, int t)
{
	while(SPFA())
		for(int f; (f = dfs(s, t, inf)) > 0; ) flow += f;
	return flow;
}

bool check(int y, int x)
{
	int tmp = x*x-y*y, z = (int)sqrt(tmp);
	if(z*z != tmp) return false;
	return gcd(y, z) == 1;
}

int main()
{
	scanf("%d%d", &A, &B);
	S = 0, T = 2*B+1;
	for(int i = A; i <= B; ++i)
	for(int j = i+1; j <= B; ++j)
	if(check(i, j)) 
		AddEdge(i, j+B, 1, -i-j), AddEdge(j, i+B, 1, -i-j);
	
	for(int i = A; i <= B; ++i) AddEdge(S, i, 1, 0), AddEdge(i+B, T, 1, 0);
	ZKW(S, T);
	printf("%d %d\n", flow>>1, (-cost)>>1);
	
	return 0;
}
