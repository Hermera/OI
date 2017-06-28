#include <cstdio>
#include <cmath>
#include <map>
using namespace std;
typedef long long ll;

int cas, p, a, b, x, t;

ll pow(ll x, int k, int p) {
	ll ret = 1;
	for( ; k; k >>= 1, (x *= x)%= p)
		if(k&1) (ret *= x)%= p;
	return ret;
}
ll inv(ll x) { return pow(x, p-2, p); }
ll gcd(ll x, ll y) { return !y ? x : gcd(y, x%y); }

int BSGS(int a, int b, int p) {
	a %= p, b %= p;
	int ret = 0, sqt = sqrt(p);
	ll tmp = 1;
	if(b == 1) return ret;
	for(int g = gcd(a, p); g != 1; g = gcd(a, p)) {
		if(b%g) return -1;
		p /= g, b /= g, (tmp *= a/g)%= p, ++ret;
		if(b == tmp) return ret;
	}
	
	map <int, int> h;
	ll bas = b, now = tmp;
	for(int i = 0; i < sqt; ++i) h[bas] = i, (bas *= a)%= p;
	
	int oo = 0;
	bas = pow(a, sqt, p);
	for(int i = 1; i <= sqt+1; ++i) {
		(now *= bas)%= p;
		if(h.count(now)) 
			return i*sqt - h[now] + ret;
	}
	return -1;
}


int main() {
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d%d%d%d%d", &p, &a, &b, &x, &t);
		if(x == t) printf("1\n");
		else if(!a) printf("%d\n", b == t ? 2 : -1);
		else if(a == 1) {
			ll g = gcd(b, p);
			if((t-x+p)%g) printf("-1\n");
			else {
				int ans = 1LL*(t-x+b+p)*inv(b)%p;
				if(!ans) ans += p;
				printf("%d\n", ans);
			}
		}
		else {	
			ll c = 1LL * b * inv(a-1) % p;
			int ans = BSGS(a, (t+c)*inv(x+c)%p, p);
			printf("%d\n", ~ans ? ans+1 : ans);
		}
	}
	return 0;
}
