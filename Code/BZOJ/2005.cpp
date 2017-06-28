#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5+5;
typedef long long ll;
ll N, M;
ll dp[maxn];

ll solve(ll n)
{
	ll ans = 0;
	for(ll i = n; i >= 1; --i)
	{
		dp[i] = (N/i)*(M/i);
		for(ll j = (i<<1); j <= n; j += i) dp[i] -= dp[j];
		ans += dp[i]*((i<<1)-1);
	}
	return ans;	
}

int main()
{
	scanf("%lld%lld", &N, &M);
	printf("%lld\n", solve(max(N, M)));
	return 0;
}
