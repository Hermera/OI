#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 1e7+5;
int n, m, c, t;
int mu[maxn], sum[maxn], f[maxn], p[maxn];
bool vis[maxn];

void get_mobius() {
	mu[1] = 1;
	for(int i = 2, j, v; i < maxn; ++i) {
		if(!vis[i]) p[++c] = i, mu[i] = -1;
		for(j = 1; j <= c; ++j) {
			if((v = p[j]*i) >= maxn) break;
			vis[v] = 1;
			
			if(i%p[j] == 0) { mu[v] = 0; break; }
			mu[v] = -mu[i];
		}
	}
	for(int i = 1, j, k; i <= c; ++i)
		for(j = p[i], k = 0; j < maxn; j += p[i])
			f[j] += mu[++k];
	for(int i = 1; i < maxn; ++i) sum[i] = sum[i-1]+f[i];
}

int main() {
	get_mobius();
	scanf("%d", &t);
	while(t--) {
		ll ans = 0;
		scanf("%d%d", &n, &m);
		if(n > m) swap(n, m);
		for(int l = 2, r; l <= n; l = r+1) {
			r = min(n/(n/l), m/(m/l));
			ans += 1LL*(sum[r]-sum[l-1])*(n/l)*(m/l);
		}
		printf("%lld\n", ans);
	}
	return 0;
}
