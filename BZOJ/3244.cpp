#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 200005;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
int N, dfs[maxn], bfs[maxn], change[maxn], Rank[maxn], rem[maxn], ans = 2;


int main()
{
	N = read();
	for(int i = 1; i <= N; ++i) dfs[i] = read();
	for(int i = 1; i <= N; ++i) bfs[i] = read();
	for(int i = 1; i <= N; ++i) change[bfs[i]] = i;
	for(int i = 1; i <= N; ++i) dfs[i] = change[dfs[i]];
	for(int i = 1; i <= N; ++i) Rank[dfs[i]] = i, rem[i] = max(rem[i-1], dfs[i]);
	
	for(int i = 1; i < N; ++i)
		if(i == 1 || Rank[i] > Rank[i+1]) ans += 2;
		else if(Rank[i]+1 == Rank[i+1] && i == Rank[i] && rem[i] == i) ++ans;
	
	for(int i = N; i && Rank[i] == Rank[i-1]+1; --i)
		if(i != Rank[i]) ++ans;
		
	printf("%.3lf\n%.3lf\n%.3lf\n", (double)ans/2.0-0.001, (double)ans/2.0, (double)ans/2.0+0.001);
	return 0;
}
