#include <cstdio>
#include <vector>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

const int maxn = 5005;
vector <int> G[maxn];
int N, ans;
bool check[maxn];

bool dfs(int x)
{
	if(x == N) return true;
	check[x] = true;
	for(int i = 0; i < G[x].size(); ++i)
	if(!check[G[x][i]] && dfs(G[x][i])) return true;
	return false;
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read();
	for(int i = 1; i < N; ++i)
	for(int k = read(), j = 1; j <= k; ++j)
		G[i].push_back(read());
		
	for(int i = 0; i < G[1].size(); ++i) ans += dfs(G[1][i]);
	printf("%d\n", ans);
	
	return 0;
}
