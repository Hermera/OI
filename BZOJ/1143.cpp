#include <cstdio>
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
const int maxn = 205;
struct Data { int next, to; } data[maxn*maxn];
int N, M, cnt, head[maxn], part[maxn];
bool check[maxn], map[maxn][maxn];

void add(int x, int y) { data[++cnt] = (Data){ head[x], y }; head[x] = cnt; }

/*bool dfs(int x)
{
	check[x] = true;
	for(int i = 1; i <= N; ++i)
	if(map[x][i])
		if(!part[i] || !check[part[i]] && dfs(part[i]))
		{ part[x] = i, part[i] = x; return true; }
	return false;
}*/

bool dfs(int x)
{
	for(int i=1;i<=N;i++)
	{
		if(map[x][i]&&!check[i])
		{
			check[i]=1;
			if( !part[i] || dfs(part[i]) )
			{
				part[i]=x;
				return true;
			}
		}
	}
	return false;
}

int BinCompare()
{
	int ret = 0;
	for(int i = 1; i <= N; ++i)
		mset(check, 0), ret += dfs(i);
	return ret;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), map[u][v] = true;
	
	for(int k = 1; k <= N; ++k)
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= N; ++j)
		map[i][j] |= map[i][k]&map[k][j];
	
	printf("%d\n", N-BinCompare());
	return 0;
}
