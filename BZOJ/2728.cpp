#include <cstdio>
#include <algorithm>
#define bin(x) (1LL<<(x))
using namespace std;
typedef long long ll;
 
const int maxn = 1005;
int n, k, t, v[maxn];
ll a[maxn], b[maxn], L, R;
 
void gauss() {
	ll state = bin(k) - 1;
	for(int i = k-1; ~i; --i) if(!v[i]) {
		ll now = state;
		for(int j = 1; j <= n; ++j)
			if(a[j] & bin(i)) now &= a[j];
			else now &= ~a[j] & state;
		b[++t] = now;
		for(int j = 0; j <= i; ++j)
			if(now & bin(j)) v[j] = 1;
	}
	
}
 
ll dp(ll x) {
	ll now = 0, ret = 0;
	if(x == -1) return -1;
	for(int i = 1; i <= t; ++i) 
		if((now|b[i]) <= x)
			now |= b[i], ret |= bin(t-i);
	return ret;
}
 
int main() {
	scanf("%d%d%lld%lld", &n, &k, &L, &R);
	for(int i = 1; i <= n; ++i) scanf("%lld", a+i);
	
	gauss();
	printf("%lld\n", dp(R) - dp(L-1));
	return 0;
}
