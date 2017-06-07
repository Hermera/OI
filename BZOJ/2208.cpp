#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2005;
int N, ans, cnt, head[maxn];
struct Data { int next, to; } data[maxn*maxn];
char s[maxn];
bool check[maxn];

void add(int x, int y) { data[++cnt].next = head[x]; head[x] = cnt; data[cnt].to = y; }

void dfs(int x)
{
	check[x] = true;
	for(int i = head[x]; i; i = data[i].next)
		if(!check[data[i].to]) dfs(data[i].to);
}

int main()
{
	freopen("data.in", "r", stdin);
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i)
	{
		scanf("%s", s+1);
		for(int j = 1; j <= N; ++j)
			if(s[j] == '1') add(i, j);
	}
	for(int i = 1; i <= N; ++i)
	{
		memset(check, 0, sizeof(check));
		dfs(i);
		for(int j = 1; j <= N; ++j) ans += check[j];
	}
	printf("%d\n", ans);
	return 0;
}
