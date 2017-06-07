#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5+5;
typedef long long ll;
ll N;
ll dp[maxn];
 
ll solve(ll n)
{
    for(ll i = n; i >= 1; --i)
    {
        dp[i] = (N/i)*(N/i);
        for(ll j = (i<<1); j <= n; j += i) dp[i] -= dp[j];
    }
    return dp[1]; 
}
 
int main()
{
    scanf("%lld", &N);
    printf("%lld\n", solve(--N)+2);
    return 0;
}
