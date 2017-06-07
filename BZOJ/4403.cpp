#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 1e6+10, Mod = 1e6+3;
ll T, N, L, R, fac[maxn];

ll QuickPow(ll x, ll k) {
	ll ans = 1; x %= Mod;
	for( ; k; k >>= 1, (x *= x)%= Mod)
		if(k&1) (ans *= x)%= Mod;
	return ans;
}

ll C(ll n, ll m) {
	if(n < m) return 0;
	return fac[n]*QuickPow(fac[m]*fac[n-m], Mod-2)%Mod;
}

ll Lucas(ll n, ll m) {
	if(n < m) return 0;
	if(!m || m == n) return 1;
	return Lucas(n/Mod, m/Mod)*C(n%Mod, m%Mod)%Mod;
}

int main() {
	scanf("%lld", &T);
	fac[0] = 1;
	for(int i = 1; i <= Mod; ++i) fac[i] = fac[i-1]*i%Mod;
	
	while(T--) {
		scanf("%lld%lld%lld", &N, &L, &R);
		printf("%lld\n", ((Lucas(R-L+N+1, N)-1)%Mod + Mod)%Mod);
	}
	return 0;
}
