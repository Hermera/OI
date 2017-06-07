#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 2e6+5;
int N, Mod, cnt, prime[maxn], tot[maxn], down[maxn];
ll ans = 1;
bool vis[maxn];

ll QuickPow(ll x, int k)
{
	x %= Mod;
	ll ans = 1;
	for( ; k; k >>= 1, x *= x, x %= Mod)
		if(k&1) ans *= x, ans %= Mod;
	return ans;
}

void GetPrime()
{
	for(int i = 2; i <= (N<<1); ++i)
	{
		if(!vis[i]) prime[++cnt] = i, down[i] = i;
		for(int j = 1; j <= cnt && i*prime[j] <= (N<<1); ++j)
		{
			vis[i*prime[j]] = true;
			down[i*prime[j]] = prime[j];
			if(i%prime[j] == 0) break;
		}
	}
}

void add(int x, int v)
{ while(x != 1) tot[down[x]] += v, x /= down[x]; }

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);
	scanf("%d%d", &N, &Mod);
	GetPrime();
	
	for(int i = N+1; i <= 2*N; ++i) add(i, 1);
	for(int i = 1; i <= N; ++i) add(i, -1);
	add(N+1, -1);
	
	for(int i = 1; i <= cnt; ++i)
		if(tot[prime[i]]) ans *= QuickPow(prime[i], tot[prime[i]]), ans %= Mod;
	
	printf("%lld\n", ans);
}
