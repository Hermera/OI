#include <cstdio>
#include <algorithm>
#define Int register int
using namespace std;
typedef long long ll;
const int mod = 1e9+7, maxn = 5e6+5;
int T, cnt, p[maxn], mu[maxn], fac[maxn];
ll N, M, K, ans, d[maxn], f[maxn], sum[maxn];
bool vis[maxn];

ll quickpow(ll x, ll k) {
	ll a = 1;
	for(; k; k >>= 1, (x *= x)%= mod)
		if(k&1) (a *= x)%= mod;
	return a;
}

void prework() {
	mu[1] = 1, f[1] = 1;
	for(Int i = 2; i < maxn; ++i) {
		if(!vis[i]) 
			p[++cnt] = i, mu[i] = -1,
			fac[i] = i, d[i] = quickpow(i, K), f[i] = d[i]-1;
		for(Int j = 1; j <= cnt && p[j]*i < maxn; ++j) {
			vis[p[j]*i] = 1;
			if(i%p[j] == 0) {
				mu[p[j]*i] = 0, fac[p[j]*i] = fac[i]*p[j];
				if(fac[i] != i) f[p[j]*i] = f[i/fac[i]]*f[fac[i]*p[j]]%mod;
				else f[p[j]*i] = f[i]*d[p[j]]%mod;
				break;
			}
			mu[p[j]*i] = -mu[i];
			f[p[j]*i] = f[i]*f[p[j]]%mod;
			fac[p[j]*i] = p[j];
		}
	}
	for(Int i = 1; i < maxn; ++i) sum[i] = (sum[i-1]+f[i])%mod;
}	

int main() {
	scanf("%d%lld", &T, &K);
	prework();
	while(T--) {
		ans = 0;
		scanf("%lld%lld", &N, &M);
		if(N > M) swap(N, M);
		for(Int l = 1, r; l <= N; l = r+1){
			r = min(N/(N/l), M/(M/l));
			(ans += 1LL*(N/l)*(M/l)%mod *((sum[r]-sum[l-1])%mod)+mod)%= mod;
		}
		printf("%lld\n", (ans+mod)%mod);
	}
	return 0;
}
			
