#include <map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e5+5;
int n, m;
int a[maxn], b[maxn];
ll fir, len;

ll pow(ll x, int k) {
	ll ret = 1;
	for(; k; k >>= 1, (x *= x) %= m)
		if(k & 1) (ret *= x) %= m;
	return ret;
}

void solve(int *a, int n) {
	int step = a[1] - a[0], cnt = 0;
	
	map <int, int> app;
	for(int i = 0; i < n; ++i) app[a[i]] = 1;
	for(int i = 0; i < n; ++i) if(app.count((a[i]+step)%m)) ++cnt;
	
	int k = n-cnt, d = 1LL * step * pow(k, m-2) % m;
	fir = -1, len = (m - d) % m;
	for(int i = 0; i < n; ++i) 
		if(!app.count((a[i]+d)%m)) 
			if(~fir) {
				fir = -1;
				break;
			} else fir = a[i];

}

int main() {
	scanf("%d%d", &m, &n);
	for(int i = 0; i < n; ++i) scanf("%d", a + i);
	if(n == 1 || m == n) printf("%d 1\n", a[0]);
	else {
		sort(a, a+n);
		if(2*n < m) solve(a, n);
		else {
			map <int, int> app;
			for(int i = 0; i < n; ++i) app[a[i]] = 1; n = 0;
			for(int i = 0; i < m; ++i) 
				if(!app.count(i)) b[n++] = i;
			solve(b, n);
			if(~fir) (fir += 1LL * len * n) %= m;
		}
		if(~fir) printf("%lld %lld\n", fir, len);
		else printf("-1\n");
	}
	return 0;
}
