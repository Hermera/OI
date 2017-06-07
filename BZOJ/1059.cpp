#include <cstdio>
#include <vector>
#include <cstring>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;

const int maxn = 405;
vector <int> G[maxn];
int match[maxn], N;
bool used[maxn];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}

void AddEdge(int x, int y){ G[x].push_back(y); G[y].push_back(x); }
bool dfs(int v)
{
	used[v] = true;
	for(int i = 0; i < G[v].size(); ++i)
	{
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w))
		{ match[v] = u, match[u] = v; return true; }
	}
	return false;
}

int BinMatching(int N)
{
	 int ans = 0;
	 mem(match, -1);
	 for(int i = 1; i <= N; ++i)
	 if(match[i] < 0)
	 {
	 	mem(used, 0);
	 	if(dfs(i)) ans++;
	 }
	 return ans;
}

int main()
{
//	freopen("data.in", "r", stdin);
//	freopen("my.out", "w", stdout);
	for(int T = read(); T; T--)
	{
		N = read();
		for(int i = 1; i <= 2*N; ++i) G[i].clear();
		for(int i = 1; i <= N; ++i)
		for(int j = 1; j <= N; ++j)
			if(read() == 1) AddEdge(i, N+j);
		printf("%s\n", BinMatching(2*N) >= N ? "Yes" : "No");
	}
	return 0;
}
