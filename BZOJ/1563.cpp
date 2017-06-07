#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
typedef long double ld;

const int maxn = 1e5+5;
const ld lim = 1e18;
int t, n, l, oc, cas;
int sum[maxn], g[maxn], q[maxn];

char s[maxn];
int get() { scanf("%s", s); return strlen(s); }

ld f[maxn];
ld mypow(ld x, int k) {
	ld ret = 1;
	while(k--) ret *= x;
	return abs(ret);
}
ld F(int x, int y) { return f[x] + mypow(sum[y]-sum[x]+(y-x-1)-l, oc); }

int getpos(int x) {
	int l = 1, r = t, o = 1;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(g[q[mid]] <= x) o = mid, l = mid+1;
		else r = mid-1;
	}
	return o;
}

int getg(int x, int y) {
	int l = g[x]+1, r = n, o = n+1;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(F(x, mid) > F(y, mid)) o = mid, r = mid-1;
		else l = mid+1;
	}
	return o;
}

int main() {
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d%d%d", &n, &l, &oc);
		for(int i = 1; i <= n; ++i) sum[i] = sum[i-1]+get();
		
		g[0] = 1, q[t = 1] = 0;
		for(int i = 1, p; i <= n; ++i) {
			f[i] = F(p = q[getpos(i)], i);
			while(g[q[t]] > i && F(q[t], g[q[t]]) > F(i, g[q[t]])) --t;
			p = getg(q[t], i);
			if(p <= n) q[++t] = i, g[i] = p;
		}
		if(f[n] > lim) printf("Too hard to arrange\n");
		else printf("%lld\n", (ll)(f[n]+0.5));
		printf("--------------------\n");
	}
	return 0;
}
