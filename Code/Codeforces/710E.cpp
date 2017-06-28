#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e7+5;
int N, X, Y;
ll dp[maxn];

int main() {
	scanf("%d%d%d", &N, &X, &Y);
	for(int i = 1; i <= N; ++i) dp[i] = 1e16;
	for(int i = 1; i <= N; ++i) {
		dp[i] = min(dp[i], dp[i-1]+X);
		if(i&1) dp[i] = min(dp[i], dp[(i+1)>>1]+Y+X);
		else dp[i] = min(dp[i], dp[i>>1]+Y);
	}
	printf("%lld\n", dp[N]);
	return 0;
}
