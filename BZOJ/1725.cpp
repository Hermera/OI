#include <cstdio>
using namespace std;
const int Mod = 100000000, maxn = 12;
int M, N, ans, model[maxn+3], dp[maxn+3][(1<<maxn)+5];
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

bool Judge(int x)
{
	for(int i = 0; i < M-1; ++i)
	if(x&(1<<i) && x&(1<<(i+1))) return false;
	return true;
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1; i <= N; ++i)
		for(int j = 0; j < M; ++j)
			model[i] |= read()*(1<<j);
	
	for(int j = 0; j < (1<<M); ++j) 
	if(Judge(j) && (j&model[1]) == j) dp[1][j] = 1;
	
	for(int i = 2; i <= N; ++i)
	for(int j = 0; j < (1<<M); ++j)
	if(Judge(j) && (j&model[i]) == j)
		for(int k = 0; k < (1<<M); ++k)
		if(Judge(k) && !(j&k) && (k&model[i-1]) == k)
			dp[i][j] += dp[i-1][k], dp[i][j] %= Mod;
	
	for(int i = 0; i < (1<<M); ++i)
	if(Judge(i)) ans += dp[N][i], ans %= Mod;
	
	printf("%d\n", ans);
}
