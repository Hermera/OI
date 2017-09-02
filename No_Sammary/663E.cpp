#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int maxn = 25;
const int maxm = 1e5+5;
const int maxl = (1<<20) + 5;

char s[maxn][maxm];
ll F[maxl], G[maxl], H[maxl];
int n, m, l, siz[maxl];


void fwt(ll *a) {
	for(int h = 2; h <= l; h <<= 1)
		for(int i = 0; i < l; i += h)
			for(int j = i; j < i+h/2; ++j) {
				ll u = a[j], v = a[j+h/2];
				a[j] = u + v;
				a[j+h/2] = u - v;
			}
}

void ufwt(ll *a) {
	for(int h = 2; h <= l; h <<= 1)
		for(int i = 0; i < l; i += h)
			for(int j = i; j < i+h/2; ++j) {
				ll u = a[j], v = a[j+h/2];
				a[j] = (u + v) / 2;
				a[j+h/2] = (u - v) / 2;
			}
}

int rev(int x) {
	int ret = 0;
	for(int i = 0; i < n; ++i)
		if(~x & (1<<i)) ret |= (1<<i);
	return ret;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		scanf("%s", s[i]);
	
	l = 1 << n;	
	for(int i = 0; i < m; ++i) {
		int state = 0;
		for(int j = 0; j < n; ++j)
			if(s[j][i] == '1') state |= (1<<j);
		++F[state];
	}
	
	for(int i = 0; i < l; ++i) siz[i] = siz[i>>1] + (i&1);
	for(int i = 0; i < l; ++i) G[i] = min(siz[i], siz[rev(i)]);
	
	/*for(int i = 0; i < l; ++i)
		for(int j = 0; j < l; ++j)
			H[i] += F[j] * G[i^j];*/
	
	fwt(F), fwt(G);
	for(int i = 0; i < l; ++i)
		H[i] = F[i] * G[i];
	ufwt(H);
	
	
	ll ans = 1e16;
	for(int i = 0; i < l; ++i)
		ans = min(ans, H[i]);
	printf("%lld\n", ans);
	return 0;
}
