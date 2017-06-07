#include <cstdio>
#include <cmath>
using namespace std;
const int maxn = 1e5+5;
typedef long long ll;
int N, T, primes, prime[maxn], mu[maxn];
bool vis[maxn];

void GetMobius()  
{   
    mu[1] = 1;
    for(int i = 2; i < maxn; ++i)  
    {  
        if(!vis[i]) prime[++primes] = i, mu[i] = -1;  
        for(int j = 1; j <= primes && i*prime[j] < maxn; ++j)  
        {  
            vis[i*prime[j]] = true;  
            if(i%prime[j]) mu[i*prime[j]] = -mu[i];  
            else { mu[i*prime[j]] = 0 ; break;}  
        }
    }
}

ll judge(ll n)
{
	ll ans = 0;
	int t = sqrt(n);
	for(ll i = 1; i <= t; ++i)
		ans += mu[i]*n/(i*i);
	return ans;
}

ll solve()
{
	ll left = N, right = (N<<1), ans;
	while(left <= right)
	{
		ll mid = (left+right)>>1, tot = judge(mid); 
		if(tot >= N) ans = mid, right = mid-1;
		else left = mid+1;
	}
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);
	GetMobius();
	scanf("%d", &T);
	while(T--) scanf("%d", &N), printf("%lld\n", solve());
	return 0;
}
