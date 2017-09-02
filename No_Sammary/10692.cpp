#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
    int x = 0, ch = getchar();
    while((ch < '0' || ch > '9') && ch != '#') ch = getchar();
    if(ch == '#') exit(0);
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}

const int N = 1e4+5;

int n, m, cas, a[N], phi[N];
void prepare() {
	phi[1] = 1, n = 1e4;
	for(int i = 2; i <= n; ++i) if(!phi[i])
		for(int j = i; j <= n; j += i) {
			if(!phi[j]) phi[j] = j;
			(phi[j] /= i) *= (i-1);
		}
}

ll getans(ll x, ll k, ll p) {
	ll ret = 1;
	for(int i = 1; i <= k; ++i) {
		if((ret *= x) > p) break;
		if(i == k) return ret;
	}
	
	ret = 1;
	for(; k; k >>= 1, (x *= x) %= p)
		if(k & 1) (ret *= x) %= p;
	return ret + p;
}


ll solve(int k, ll p) {
	if(k == n) return a[k] < p ? a[k] : a[k] % p + p;
	return getans(a[k], solve(k+1, phi[p]), p);
}


int main() {
	freopen("10692.in", "r", stdin);
	prepare();

	while(m = read(), n = read()) {
		for(int i = 1; i <= n; ++i) a[i] = read();
		printf("Case #%d: %lld\n", ++cas, solve(1, m) % m);
	}
	return 0;
}
