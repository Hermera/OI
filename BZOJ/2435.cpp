#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e6+5;
typedef long long ll;
struct Data { int next, to, w; } data[maxn<<1];
int N, cnt, head[maxn], size[maxn], deg[maxn], fa[maxn];
bool check[maxn], inq[maxn];

void add(int x, int y, int w)
{ data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; data[cnt].w = w;}

void GetSize()
{
	queue <int> q;
	q.push(1); check[1] = true;
	while(!q.empty())
	{
		int v = q.front(); q.pop();
		for(int i = head[v]; i; i = data[i].next)
		if(!check[data[i].to])
			check[data[i].to] = true, fa[data[i].to] = v, q.push(data[i].to);
	}
	for(int i = 2; i <= N; ++i)
		if(deg[i] == 1) q.push(i);
	while(!q.empty())
	{
		int v = q.front(); q.pop();
		size[v] += 1, size[fa[v]] += size[v], --deg[fa[v]];
		if(deg[fa[v]] == 1) q.push(fa[v]);
	}
}

ll Calc()
{
	ll ans = 0;
	queue <int> q; q.push(1);
	memset(check, 0, sizeof(check));
	check[1] = true;
	while(!q.empty())
	{
		int v = q.front(); q.pop();
		for(int i = head[v]; i; i = data[i].next)
		if(!check[data[i].to])
		{
			Data &e = data[i];
			ans += (long long)e.w*abs(N-size[e.to]*2);
			q.push(e.to); check[e.to] = true;
		}
	}
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1, u, v, w; i < N; ++i)
		u = read(), v = read(), w = read(), add(u, v, w), add(v, u, w), ++deg[v], ++deg[u];
	GetSize();
	printf("%lld\n", Calc());
}
