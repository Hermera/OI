#include <cstdio>
#include <algorithm>
#define bin(x) (1LL<<x)
using namespace std;
typedef long long ll;
inline ll read() {
	char ch = getchar(); ll x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e4+5;
int N, M, tot, zero;
ll a[maxn];

void Gauss() {
	tot = zero = 0;
	for(ll i = bin(60); i; i >>= 1) {
		int j = tot+1;
		while(!(i&a[j]) && j <= N) ++j;
		if(j > N) continue;
		++tot;
		
		swap(a[tot], a[j]);
		for(int k = 1; k <= N; ++k)
			if(k != tot && (a[k]&i)) a[k] ^= a[tot];
	}
	zero = (tot != N);
}	

ll query(ll x) {
	ll ans = 0;
	x -= zero;
	if(!x) return 0;
	if(x>>tot) return -1;
	for(int i = 1; i <= tot; ++i)
		if(x&bin(tot-i)) ans ^= a[i];
	return ans;
}		

int main() {
	freopen("data.in", "r", stdin);
	for(int T = read(), kase = 0; T; --T) {
		printf("Case #%d:\n", ++kase);
		
		N = read();
		for(int i = 1; i <= N; ++i) a[i] = read();
		Gauss();
		
		M = read();
		while(M--) printf("%lld\n", query(read()));
	}
	return 0;
}
