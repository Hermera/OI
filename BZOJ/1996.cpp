#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 1005;
const int mod = 19650827;
int n, a[maxn];
ll dp[maxn][maxn][2];

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", a+i);
	for(int l = n; l; --l) {
		dp[l][l][0] = dp[l][l][1] = 1;
		for(int r = l+1; r <= n; ++r) {
			if(a[l] < a[l+1]) dp[l][r][0] += dp[l+1][r][0];
			if(a[r] > a[r-1]) dp[l][r][1] += dp[l][r-1][1];
			if(l+1 != r && a[l] < a[r]) dp[l][r][0] += dp[l+1][r][1];
			if(l+1 != r && a[r] > a[l]) dp[l][r][1] += dp[l][r-1][0];
			dp[l][r][0] %= mod;
			dp[l][r][1] %= mod;
		}
	}
	printf("%lld\n", (dp[1][n][0] + dp[1][n][1])%mod);
	return 0;
}
