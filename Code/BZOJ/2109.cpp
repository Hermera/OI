#include <cstdio>
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
const int maxn = 2005;
int N, M, k[maxn], now[maxn], in[maxn];
vector <int> G[maxn];
struct cmp { bool operator ()(int a, int b) { return k[a] < k[b]; }};

int TopSearch(int x)
{
	memcpy(now, in, sizeof(in));
	priority_queue <int, vector<int>, cmp> q;
	int tot = 0;
	for(int i = 1; i <= N; ++i) if(!now[i] && i != x) q.push(i);
	while(!q.empty())
	{
		int v = q.top(); q.pop();
		if(k[v] > tot) continue;
		++tot;
		for(int i = 0; i < G[v].size(); ++i)
		{
			--now[G[v][i]];
			if(!now[G[v][i]] && G[v][i] != x) q.push(G[v][i]);
		}
	}
	return N-tot;
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1; i <= N; ++i) k[i] = N-read();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), G[v].push_back(u), ++in[u];
	
	for(int i = 1; i <= N; ++i) printf("%d ", TopSearch(i));
	
	return 0;
}
