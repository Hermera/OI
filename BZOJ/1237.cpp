#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = 5e6+5;
const int LIM = 5e6;
const int mod = 1e9+7;
const int inv2 = (mod+1) >> 1;

int pri[N], cnt;
ll phi[N], etf[N], n;

void getprime() {
	n = LIM;
	phi[1] = 1;
	for(int i = 2; i <= LIM; ++i) {
		if(!phi[i]) phi[i] = i-1, pri[++cnt] = i;
		for(int j = 1; j <= cnt && i * pri[j] <= LIM; ++j) {
			int now = i * pri[j];
			if(i % pri[j]) phi[now] = phi[i] * (pri[j]-1);
			else {
				phi[now] = phi[i] * pri[j];
				break;
			}
		}
	}
	
	for(int i = 2; i <= LIM; ++i) 
		(phi[i] += phi[i-1]) %= mod;
}

ll getfac(ll l, ll r) {
	l %= mod;
	r %= mod;
	return (l+r) * (r-l+1) % mod * inv2 % mod;
}

ll getetf(ll x) {
	if(x <= LIM) return phi[x];
	if(etf[n/x]) return etf[n/x];
	
	int t = n/x;
	etf[t] = getfac(1, x);
	for(ll l = 2, r; l <= x; l = r+1) 
		r = x/(x/l), (etf[t] -= getetf(x/l) * (r-l+1)) %= mod;
	return etf[t];
} 


ll solve(ll n) {
	ll ret = 0;
	for(ll l = 1, r; l <= n; l = r+1) {
		r = n / (n / l);
		(ret += getfac(l, r) * getetf(n/l)) %= mod;
	}
	return (ret + mod) % mod;
}


int main() {
	getprime();
	scanf("%lld", &n);
	
	ll ans = 0;
	(ans += solve(n) * 2) % mod;
	(ans -= getfac(1, n)) %= mod;
	(ans += mod) %= mod;
	
	printf("%lld\n", ans);
	return 0;
}
