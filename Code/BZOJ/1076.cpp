#include <cstdio>
#include <algorithm>
using namespace std;

const int maxk = 105, maxn = 15;
int K, N, w[maxn+5], pre[maxn+5];
double dp[maxk][(1<<maxn)+5];

int main()
{
	scanf("%d%d", &K, &N);
	for(int i = 0, x; i < N; ++i)
	{
		scanf("%d", w+i);
		while(scanf("%d", &x) && x) pre[i] |= 1<<(x-1);
	}
	for(int k = K; k; --k)
	for(int s = 0; s < (1<<N); ++s)
	for(int x = 0; x < N; ++x)
		if((s&pre[x]) == pre[x])
			dp[k][s] += max(dp[k+1][s|(1<<x)]+w[x], dp[k+1][s])/N;
		else dp[k][s] += dp[k+1][s]/N;
		
	printf("%.6lf\n", dp[1][0]);
	return 0;
}
