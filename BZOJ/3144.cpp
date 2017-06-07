#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
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
const int fx[4] = {0, 0, -1, 1};
const int fy[4] = {-1, 1, 0, 0};
const int maxn = 45*45*45;
const int inf = 1e9;
int P, Q, R, D, S, T, val[45][45][45], level[maxn], iter[maxn];

struct Edge { ll to, cap, rev; };
vector <Edge> G[maxn];
void add(int x, int y, ll c)
{
	G[x].push_back((Edge){y, c, G[y].size()});
	G[y].push_back((Edge){x, 0, G[x].size()-1});
}

int p(int x, int y, int h) { return h == 0 ? 0 : (h-1)*P*Q+(x-1)*Q+y; }

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

void Input()
{
	P = read(), Q = read(), R = read(), D = read();
	S = 0, T = R*P*Q+1;
	for(int i = 1; i <= R; ++i)
	for(int j = 1; j <= P; ++j)
	for(int k = 1; k <= Q; ++k)
		val[j][k][i] = read();
}

void Build()
{
	for(int x = 1; x <= P; ++x)
	for(int y = 1; y <= Q; ++y)
	{
		for(int h = 1; h <= R; ++h)
		{
			add(p(x, y, h-1), p(x, y, h), val[x][y][h]);
			if(h > D)
			for(int dis = 0; dis < 4; ++dis)
			{
				int nx = x+fx[dis], ny = y+fy[dis];
				if(nx < 1 || ny < 1 || nx > P || ny > Q) continue;
				add(p(x, y, h), p(nx, ny, h-D), inf);
			}
		}
		add(p(x, y, R), T, inf);
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	Input();
	Build();
	printf("%lld\n", MaxFlow(S, T));
	return 0;
}
