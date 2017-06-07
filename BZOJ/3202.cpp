#include <cstdio>
#include <assert.h>
#include <algorithm>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;
const ll sqmod = 1LL*mod*mod;
const int maxv = 1e7+5;

int tot, cnt, cas;
ll n, m;

int p[maxv], mu[maxv];
bool vis[maxv];
void getmobius() {
	mu[1] = 1;
	for(int i = 2; i < maxv; ++i) {
		if(!vis[i]) p[++cnt] = i, mu[i] = -1;
		for(int j = 1; j <= cnt && i*p[j] < maxv; ++j) {
			vis[i*p[j]] = 1;
			if(i % p[j] == 0) break;
			mu[i*p[j]] = -mu[i];
		}
	}
	for(int i = 1; i < maxv; ++i) mu[i] += mu[i-1];
}

inline void inc(ll &x, ll y) {
	x += y;
	if(x < -sqmod) x += sqmod;
	if(x >= sqmod) x -= sqmod;
}

ll mul(ll x, ll y) {
	if(abs(x) < mod && abs(y) < mod) return x * y;
	ll ret = 0;
	for(; y; y >>= 1, inc(x, x))
		if(y & 1) inc(ret, x);
	return ret;
		
}

ll getcolor(int x) {
	ll ret = 0;
	for(int l = 1, r; l <= x; l = r+1) 
		r = x/(x/l), inc(ret, mul(mul(mu[r]-mu[l-1], x/l+3), mul(x/l, x/l)));
	inc(ret, sqmod);
	return mul(833333345000000041LL, ret + 2);
}


const int maxl = 105;
ll g[maxl];
void divide(ll x) {
	tot = 0;
	for(int i = 1; i <= cnt && p[i] <= x; ++i) 
		if(x % p[i] == 0) {
			g[++tot] = p[i];
			while(x % p[i] == 0) x /= p[i];
		}
	if(x != 1) g[++tot] = x;
	
}


ll pow(ll x, ll k) {
	ll ret = 1;
	for(; k; k >>= 1, x = mul(x, x))
		if(k & 1) ret = mul(ret, x);
	return ret;
}

ll f(ll x) {
	if(x == 1) return 0;
	if(x == 2) return mul(m, m-1);
	ll ret = pow(m-1, x);
	inc(ret, (x&1) ? 1-m : m-1);
	return ret;
}

ll phi(ll x){
	ll ret = x;
	for(int i = 1; i <= tot; ++i)
	if(x % g[i] == 0) {
		ret = ret / g[i] * (g[i] - 1);
		while(x % g[i] == 0) x /= g[i];
	}
	return ret;
}

ll inv(ll x) {
	ll ret = 1, k = mod - 2;
	for(; k; k >>= 1, (x *= x) %= mod)
		if(k & 1) (ret *= x) %= mod;
	return ret;
}

int main() {
	getmobius();
	scanf("%d", &cas);
	while(cas--) {
		scanf("%lld%lld", &n, &m);
		m = getcolor(m), divide(n);

		ll ans = 0;
		for(ll i = 1; i*i <= n; ++i) 
			if(n % i == 0) {
				inc(ans, mul(f(i), phi(n/i)));
				if(i*i != n) 
					inc(ans, mul(f(n/i), phi(i)));
			}
		
		if(n % mod == 0) ans /= mod, (ans *= inv(n/mod)) %= mod;
		else ans %= mod, (ans *= inv(n%mod)) %= mod;
		printf("%lld\n", (ans + mod) % mod);
	}
	return 0;
}
