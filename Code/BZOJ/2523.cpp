#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 90005;
int ans[maxn][4];
int N, M, cnt;

inline int P(int x1, int x2) 
{ return x2-x1 >= 0 ? x2-x1 : x2-x1+3; }

int solve(int x, int y, int t1, int t2, int t3)
{
	if(x == y) return t3;
	if(y > x) return solve(x, y-x, t1, t3, t2)+P(t2, t3);
	if(x > y) return solve(y, x-y, t2, t3, t1)+P(t1, t3);
}

int main()
{
	freopen("data.in", "r", stdin);
	while(scanf("%d%d", &N, &M) != EOF)
	{
		if(N < 0 || M < 0) break;
		cnt = 0;
		int t = N%3, a, b;
		if(t == 0) a = 1, b = 2, t = 3;
		if(t == 1) a = 2, b = 3;
		if(t == 2) a = 1, b = 3;
		for(int i = 1; i < M; ++i)
		if(solve(i, M-i, a, b, t) == N)
			ans[++cnt][a] = i, ans[cnt][b] = M-i, ans[cnt][t] = M;
		printf("%d\n", cnt);
		for(int i = 1; i <= cnt; ++i)
		printf("%d %d %d\n", ans[i][1], ans[i][2], ans[i][3]);
	}
	return 0;
}
