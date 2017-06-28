#include <cstdio>
using namespace std;

const int maxn = 3e5+5;
long double dp[maxn], x[maxn], p;
int N;
char ch;

int main()
{
	scanf("%d", &N); getchar();
	for(int i = 1; i <= N; ++i)
	{
		ch = getchar();
		if(ch == 'o') p = 1;
		if(ch == 'x') p = 0;
		if(ch == '?') p = 0.5;
		x[i] = (x[i-1]+1)*p;
		dp[i] = dp[i-1] + (2*x[i-1]+1)*p;
	}
	printf("%.4Lf\n", dp[N]);
	return 0;
}
