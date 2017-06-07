#include <cstdio>
using namespace std;

const int maxn = 15;
const int n = 10;
int dp[maxn][maxn], base[maxn];

int Abs(int x) { return x > 0 ? x : -x; }
int MakeTable()
{
	base[1] = 1;
	for(int i = 2; i <= n; ++i) base[i] = base[i-1]*10;
	for(int i = 0; i < n; ++i) dp[1][i] = 1;
	for(int i = 2; i <= n; ++i)
	for(int j = 0; j < n; ++j)
		for(int k = 0; k < n; ++k) 
		if(Abs(j-k) >= 2) dp[i][j] += dp[i-1][k];
}

int solve(int x)
{
	if(!x) return 0;
	int w = 10, tmp = 0;
	while(base[w] > x) --w;
	for(int i = 1; i < w; ++i)
	for(int j = 1; j < n; ++j) tmp += dp[i][j];
	int cur = x/base[w], pre = cur;
	for(int i = 1; i < cur; ++i) tmp += dp[w][i];
	x %= base[w];
	for(int i = w-1; i; --i)
	{
		cur = x/base[i];
		if(i != 1)
		{
			for(int j = 0; j < cur; ++j)
			if(Abs(pre-j) >= 2) tmp += dp[i][j];
		}
		else
		{
			for(int j = 0; j <= cur; ++j)
			if(Abs(pre-j) >= 2) tmp += dp[i][j];
		}
		if(Abs(cur-pre) < 2) break;
		pre = cur; x %= base[i];
	}
	return tmp;
}


int main()
{
	int A, B;
	MakeTable();
	scanf("%d%d", &A, &B);
	printf("%d\n", solve(B)-solve(A-1));
	return 0;
}
