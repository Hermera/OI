#include <cstdio>
#include <cstring>
#include <algorithm>
#include <queue>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
typedef long long ll;
const int maxn = 1005;
const int inf = 1e9;
int N, S, T, level[maxn], iter[maxn];
ll C, sum[maxn];
struct Edge { ll to, cap, rev; };
vector <Edge> G[maxn];
void add(int x, int y, ll c)
{
	G[x].push_back((Edge){y, c, G[y].size()});
	G[y].push_back((Edge){x, 0, G[x].size()-1});
}

bool bfs(int s)
{
	queue <int> q;
	mem(level, -1), mem(iter, 0);
	level[s] = 0; q.push(s);
	while(!q.empty())
	{
		int v = q.front(); q.pop();
		for(int i = 0; i < G[v].size(); ++i)
		{
			Edge &e = G[v][i];
			if(e.cap > 0 && level[e.to] < 0)
				level[e.to] = level[v]+1, q.push(e.to);
		}
	}
	return level[T] != -1;
}

ll dfs(int v, int t, ll f)
{	
	if(v == t || f == 0) return f;
	for(int &i = iter[v]; i < G[v].size(); ++i)
	{
		Edge &e = G[v][i];
		if(e.cap > 0 && level[e.to] > level[v])
		{
			int d = dfs(e.to, t, min(f, e.cap));
			if(d > 0) { e.cap -= d, G[e.to][e.rev].cap += d; return d; }
		}
	}
	return 0;
}

ll MaxFlow(int s, int t)
{
	ll flow = 0;
	while(bfs(s))
		for(ll f; (f = dfs(s, t, inf)) > 0; ) flow += f;
	return flow;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(); S = 0; T = N+1;
	for(int i = 1, val; i <= N; ++i) val = read(), add(i, T, val); 
	for(int i = 1; i <= N; ++i)
	for(int j = 1, val; j <= N; ++j)
		val = read(), sum[i] += val, add(i, j, (ll)val<<1), C += val;
	for(int i = 1; i <= N; ++i) add(S, i, sum[i]);
	printf("%lld\n", C-MaxFlow(S, T));
}
