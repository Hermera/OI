#include <cstdio>
#include <algorithm>
#include <cstring> 
#include <queue>
#define mset(x, a) memset(x, a, sizeof(x))
#define color(x, y) ((x+y)&1)
#define p(x, y) ((x-1)*M+y)
using namespace std;
typedef long long ll;
inline ll read()
{
	ll sum = 0; char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}
const ll maxn = 2005, fx[4] = { 0, 0, 1, -1 }, fy[4] = { 1, -1, 0, 0 };
const ll inf = 1e16;
ll N, M, S, T, MaxNum;
struct Edge { ll to, rev; ll cap; };
vector <Edge> G[maxn];
ll level[maxn], iter[maxn], a[45][45], s[5], c[5];

void add(ll from, ll to, ll cap)
{
	G[from].push_back((Edge){to, G[to].size(), cap});
	G[to].push_back((Edge){from, G[from].size()-1, 0});
}

bool bfs(ll s, ll t)
{
	mset(iter, 0), mset(level, -1);
	queue <ll> q;
	level[s] = 0; q.push(s);
	while(!q.empty())
	{
		ll v = q.front(); q.pop();
		for(ll i = 0; i < G[v].size(); i++)
		{
			Edge &e = G[v][i];
			if(e.cap && level[e.to] < 0)
				level[e.to] = level[v] + 1, q.push(e.to);
		}
	}
	return level[t] != -1;
}

ll dfs(ll v, ll t, ll f)
{
	if(v == t || f == 0) return f;
	for(ll &i = iter[v]; i < G[v].size(); i++)
	{
		Edge &e = G[v][i];
		if(e.cap && level[e.to] > level[v])
		{
			ll d = dfs(e.to, t, min(e.cap, f));
			if(d > 0) { e.cap -= d, G[e.to][e.rev].cap += d; return d; }
		}
	}
	return 0;
}

ll MaxFlow(ll s, ll t)
{
	ll flow = 0;
	while(bfs(s, t))
		for(ll f; (f = dfs(s, t, inf)) > 0; ) flow += f;
	return flow;
}

bool Judge(ll x)
{
	for(ll i = 0; i <= T; ++i) G[i].clear();
	ll tot = 0;
	for(ll i = 1; i <= N; ++i)
	for(ll j = 1; j <= M; ++j)
	if(color(i, j))
	{
		add(S, p(i, j), x-a[i][j]), tot += x-a[i][j];
		for(ll d = 0; d < 4; ++d)
		{
			ll nx = i+fx[d], ny = j+fy[d];
			if(nx && ny && nx <= N && ny <= M) add(p(i, j), p(nx, ny), inf);
		}
	}
	else add(p(i, j), T, x-a[i][j]);
	return MaxFlow(S, T) == tot;
}

void init()
{
	mset(c, 0); mset(s, 0);
	N = read(), M = read(), MaxNum = 0, S = 0, T = p(N, M)+1;
	for(ll i = 1; i <= N; ++i)
	for(ll j = 1; j <= M; ++j)
		MaxNum = max(MaxNum, a[i][j] = read()), ++c[color(i, j)], s[color(i, j)] += a[i][j];
}

int main()
{
	freopen("data.in", "r", stdin);
	for(ll T = read(); T; --T)
	{
		init();
		if(c[0] != c[1])
		{
			ll x = (s[0]-s[1])/(c[0]-c[1]);
			if(x >= MaxNum && Judge(x)) printf("%lld\n", x*c[1]-s[1]);
			else printf("-1\n");
		}
		else
		{
			ll left = MaxNum, right = inf, ans;
			while(left <= right)
			{
				ll mid = (left+right)>>1;
				if(Judge(mid)) ans = mid, right = mid-1;
				else left = mid+1;
			}
			printf("%lld\n", ans*c[1]-s[1]);
		}
	}
	return 0;
}
