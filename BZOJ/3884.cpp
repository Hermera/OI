#include <cstdio>
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 1e7+5;
int tot, phi[maxn], prime[maxn];
bool vis[maxn];

void getphi()
{
	phi[1] = 1;
	for(int i = 2; i < maxn; ++i)
	{
		if(!vis[i]) prime[++tot] = i, phi[i] = i-1;
		for(int j = 1; j <= tot; ++j)
		{
			int now = i*prime[j];
			if(now >= maxn) break;
			vis[now] = true;
			if(i%prime[j] == 0) { phi[now] = phi[i]*prime[j]; break; }
			else phi[now] = phi[i]*(prime[j]-1);
		}
	}
}

ll QuickPow(ll x, ll k, ll mod)
{
	ll ans = 1;
	for( ; k; k >>= 1, x = x*x, x %= mod)
	if(k&1) ans = ans*x, ans %= mod;
	return ans%mod;
}

ll solve(int p)
{
	if(p == 1) return 0;
	int temp = 0;
	while(~p&1) p >>= 1, ++temp;
	ll k = solve(phi[p]);
	(k += phi[p] - temp%phi[p]) %= phi[p];
	return QuickPow(2, k, p)<<temp;
}

int main()
{
	getphi();
	for(int T = read(); T; --T)
		printf("%lld\n", solve(read()));
	return 0;
}
