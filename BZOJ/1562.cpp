#include <cstdio>
#include <vector>
#include <algorithm>
#include <cstring>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;

const int maxn = 20005;
vector <int> G[maxn];
int match[maxn], s[maxn], N;
bool used[maxn];
inline int read()
{
	int sum = 0; char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

void AddEdge(int x, int y) { G[x].push_back(y); G[y].push_back(x); }

bool dfs(int v)
{
	used[v] = true;
	for(int i = 0; i < G[v].size(); ++i)
	{
		int u = G[v][i], w = match[u];
		if(w < 0 || !used[w] && dfs(w))
		{ match[u] = v; match[v] = u; return true; }
	}
	return false;
}

bool BinMatching()
{
	mem(match, -1);
	int ans = 0;
	for(int i = N-1; i >= 0; --i)
	if(match[i] < 0)
	{
		mem(used, 0);
		if(dfs(i)) ++ans;
	}
	return ans == N;
}

int main()
{
//	freopen("data.in", "r", stdin);
	N = read();
	for(int i = 0; i < N; ++i)
	{
		int d = read();
		for(int j = 1; j <= 5; ++j) s[j] = 0;
		if(i+d < N) s[1] = N+i+d;
		if(i-d >= 0) s[2] = N+i-d;
		if(N+i-d < N) s[3] = N+N+i-d;
		if(d-N+i >= 0) s[4] = d+i;
		sort(s+1, s+5);
		for(int j = 1; j < 5; ++j) if(s[j]) AddEdge(i, s[j]);
	}
	if(!BinMatching()) printf("No Answer");
	else
	for(int i = 0; i < N; ++i) 
	{
		printf("%d", match[i]-N);
		if(i != N-1) printf(" ");
	}
	printf("\n");
	return 0;
}
