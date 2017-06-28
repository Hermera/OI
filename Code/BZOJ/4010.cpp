#include <cstdio>
#include <queue>
#include <algorithm>
#include <cstring>
#define mset(x, a) memset(x, a, sizeof(x))
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

const int maxn = 1e5+5;
vector <int> G[maxn];
int p[maxn], in[maxn], cnt, N, M;
bool check[maxn], inq[maxn];

void init()
{
	N = read(), M = read(); cnt = 0;
	mset(check, 0); mset(inq, 0); mset(in, 0);
	for(int i = 1; i <= N; ++i) G[i].clear();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), G[v].push_back(u), ++in[u];
	for(int i = 1; i <= N; ++i) sort(G[i].begin(), G[i].end());
}

void print(int x)
{
	if(check[x]) return;
	for(int i = 0; i < G[x].size(); ++i) print(G[x][i]);
	p[++cnt] = x;
	check[x] = true;
}

bool Circle()
{
	queue <int> q;
	for(int i = 1; i <= N; ++i) if(!in[i]) q.push(i);
	while(!q.empty())
	{
		int v = q.front(); q.pop();
		inq[v] = true;
		for(int i = 0; i < G[v].size(); ++i)
		{
			--in[G[v][i]];
			if(!in[G[v][i]]) q.push(G[v][i]);
		}
	}
	for(int i = 1; i <= N; ++i) if(!inq[i]) return true;
	return false;
}

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);

	for(int T = read(); T; --T)
	{
		init();
		if(Circle()) { printf("Impossible!\n"); continue; }
		for(int i = 1; i <= N; ++i) print(i);
		for(int i = 1; i <= N; ++i)
		if(i == N) printf("%d\n", p[i]);
		else printf("%d ", p[i]);
	}
	return 0;
}
