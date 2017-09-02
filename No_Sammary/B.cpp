#include <cstdio>
using namespace std;
typedef long long ll;

ll n, m, p;

ll mul(ll x, ll y) {
	ll ret = 0;
	for(; y; y >>= 1, (x += x)%= p)
		if(y & 1) (ret += x) %= p;
	return ret;
}

ll pow(ll x, ll y) {
	ll ret = 1;
	for(; y; y >>= 1, x = mul(x, x))
		if(y & 1) ret = mul(ret, x);
	return ret;
}

int main() {
	scanf("%lld%lld%lld", &n, &m, &p);
	
	ll ans = mul(pow(n, m-1), pow(m, n-1));
	printf("%lld\n", ans);
	return 0;
}
