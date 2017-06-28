#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e5+5;
int N, C, num[maxn][35], dp[maxn][35];

void Input()
{
	N = read(), C = read();
	for(int i = 1; i <= C; ++i)
	{
		int E = read(), F = read(), L = read(), Hate = 0, Love = 0;
		for(int j = 0, x; j < F; ++j) x = read(), Hate |= 1<<(x-E+N)%N;
		for(int j = 0, x; j < L; ++j) x = read(), Love |= 1<<(x-E+N)%N;
		for(int i = 0; i < 32; ++i) if((Love&i) || (Hate&i) != Hate) ++num[E][i];
	}
}

int solve()
{
	int ans = 0;
	for(int S = 0; S < 16; ++S)
	{
		memset(dp, 0, sizeof(dp));
		for(int i = 1; i <= 4; ++i)
		for(int j = 0; j < 32; ++j)
			if((j>>i) == S) dp[i][j] = max(dp[i-1][(j<<1)&31], dp[i-1][(j<<1)&31|1])+num[i][j];
		for(int i = 5; i <= N-4; ++i)
		for(int j = 0; j < 32; ++j)
			dp[i][j] = max(dp[i-1][(j<<1)&31], dp[i-1][(j<<1)&31|1])+num[i][j];
		for(int i = N-3; i <= N; ++i)
		for(int j = 0; j < 32; ++j)
			if(j-((j>>(4-N+i))<<(4-N+i)) == S>>(N-i))
				dp[i][j] = max(dp[i-1][(j<<1)&31], dp[i-1][(j<<1)&31|1])+num[i][j];
			
		for(int j = 0; j < 32; ++j)
			ans = max(ans, dp[N][j]);
	}
}

int main()
{
	freopen("data.in", "r", stdin);
	Input();
	printf("%d\n", solve());
}
