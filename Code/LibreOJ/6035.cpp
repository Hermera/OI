#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 2e6+5;
const ll INF = 1e16;

int clo, n, m;
int a[N], b[N];
ll s[N], t[N];


ll getsum(int n, int *a, ll x) {
	ll ret = 0;
	for(int i = 1; i <= n; ++i)
		ret += x / a[i];
	return ret;
}

void work(int n, int *a, ll *p) {
	ll l = 1, r = INF, ans = INF;
	while(l <= r) {
		ll mid = (l+r)>>1;
		if(getsum(n, a, mid) >= clo) 
			ans = mid, r = mid-1;
		else l = mid+1;
	}
	
	int t = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = a[i]; j <= ans; j += a[i])
			p[++t] = j;
	sort(p+1, p+1+t);
}


int main() {
	clo = read(), n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= m; ++i) b[i] = read();
	
	work(n, a, s);
	work(m, b, t);
	
	ll ans = 0;
	for(int i = 1; i <= clo; ++i)
		ans = max(ans, s[i] + t[clo-i+1]);
	printf("%lld\n", ans);
	return 0;
}