#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 3e5+5, sqr = 550, inf = 1e9;
int N, K, mst[maxn], fa[maxn];
struct Data { char s[2]; int x, ans; } data[maxn];

int Find(int x) { return fa[x] == x  ? x : fa[x] = Find(fa[x]); }

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);

	for(int i = 1; i <= maxn-5; ++i) fa[i] = i+1;
	fa[maxn-4] = maxn-4;
	N = read();
	for(int i = N; i; --i) 
	{
		scanf("%s", data[i].s), data[i].x = read(), data[i].ans = inf;
		if(*data[i].s == 'A')  fa[data[i].x] = data[i].x;
	}
	
	memset(mst, 63, sizeof(mst));
	for(int i = N; i; --i)
	if(*data[i].s == 'A')
		for(int j = 1; j < sqr; ++j)
			mst[j] = min(mst[j], data[i].x%j);
	else if(data[i].x < sqr) data[i].ans = mst[data[i].x];

	for(int i = 1; i <= N; ++i)
	{
	if(*data[i].s == 'A') fa[data[i].x] = data[i].x+1;
	else if(data[i].x >= sqr)
		for(int j = 0; j <= maxn-5; j += data[i].x)
		if(Find(max(1, j)) <= maxn-5) data[i].ans = min(data[i].ans, Find(max(1, j))-j);
	}
	
	for(int i = N; i; --i)
	if(*data[i].s == 'B') printf("%d\n", data[i].ans);
	
	return 0;
}
