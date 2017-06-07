#include <cstdio>
using namespace std;
typedef long long ll;

const int mod = 1e6+3;
ll N, K, P;

ll pow(ll x, ll k) {
	ll ret = 1;
	x %= mod;
	for( ; k; k >>= 1, (x *= x)%= mod)
		if(k&1) (ret *= x)%= mod;
	return ret;
}

int main() {
	scanf("%lld%lld", &N, &K);
	if(N <= 62 && (1LL<<N) < K) return printf("1 1\n"), 0;
		
	ll tot = 0;
	for(ll j = 2; j < K; j <<= 1) tot += (K-1)/j; tot += N;
	
	P = N%(mod-1), tot %= (mod-1);
	ll mother = pow(2, (P*(K%(mod-1))%(mod-1)-tot)%(mod-1)+mod-1);
	
	ll son = 1;
	for(int i = 1; i <= K && i <= mod; ++i) (son *= (pow(2, N)-i+1))%= mod;
	(son *= pow(pow(2, tot), mod-2))%= mod;
	
	printf("%lld %lld\n", ((mother-son)%mod+mod)%mod, mother);
	return 0;
}
