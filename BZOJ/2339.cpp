#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 1e6+5;
const int mod = 1e8+7;

int n, m;
ll p[maxn], f[maxn];

ll pow(ll x, int k) {
	ll ret = 1;
	for( ; k; k >>= 1, (x *= x) %= mod)
		if(k&1) (ret *= x) %= mod;
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	
	ll state = pow(2, n) - 1;
	for(int i = p[0] = 1; i <= m; ++i)
		p[i] = p[i-1] * (state-i+1) % mod;
	for(int i = 3; i <= m; ++i)
		f[i] = (p[i-1] - f[i-1] - f[i-2] * (i-1) % mod * (state-i+2)) % mod;
	state = 1;
	for(int i = 1; i <= m; ++i) (state *= i) %= mod;
	
	ll ans = f[m] * pow(state, mod-2) % mod;
	printf("%lld\n", (ans + mod) % mod);
	return 0;
}
