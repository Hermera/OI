#include <cstdio>
using namespace std;
typedef long long ll;

const int mod = 1e9+7;
ll quickpow(ll x, ll k) {
	ll ret = 1;
	for( ; k; k >>= 1, (x *= x)%= mod)
		if(k&1) (ret *= x)%= mod;
	return ret;
}

int n, k;
int main() {
	scanf("%d%d", &n, &k);
	printf("%lld\n", quickpow(2, 1ll*n*k));
	return 0;
}
