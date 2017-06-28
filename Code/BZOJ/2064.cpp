#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 10;
int A, B, a[maxn+5], b[maxn+5], dp[(1<<maxn)+5][(1<<maxn)+5];
int SA[(1<<maxn)+5], SB[(1<<maxn)+5];

void Getsum(int cnt, int *x, int *sum)
{
	for(int i = 0; i < (1<<cnt); ++i)
		for(int j = 0; j < cnt; ++j)
			if(i&(1<<j)) sum[i] += x[j];
}

int main()
{
	freopen("data.in", "r", stdin);

	scanf("%d", &A);
	for(int i = 0; i < A; ++i) scanf("%d", a+i);
	scanf("%d", &B);
	for(int i = 0; i < B; ++i) scanf("%d", b+i);
	
	Getsum(A, a, SA);
	Getsum(B, b, SB);
	
	for(int i = 1; i < (1<<A); ++i)
	for(int j = 1; j < (1<<B); ++j)
	{
		for(int k = 0; k < A; ++k)
		if(i&(1<<k)) dp[i][j] = max(dp[i][j], dp[i^(1<<k)][j]);
		
		for(int k = 0; k < B; ++k)
		if(j&(1<<k)) dp[i][j] = max(dp[i][j], dp[i][j^(1<<k)]);
		
		if(SA[i] == SB[j]) ++dp[i][j];
	}
	
	printf("%d\n", A+B-2*dp[(1<<A)-1][(1<<B)-1]);
	return 0;
}
