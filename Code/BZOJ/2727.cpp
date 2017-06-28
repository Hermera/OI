#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e6+5;
const int maxp = 2e4+5;
const int mod = 1e9+9;

ll c1[maxn], c2[maxn], c3[maxn], c4[maxn];
int n, m, k, t;
bool a[maxn];

inline void inc(int &x, int y) { x += y; if(x >= mod) x -= mod; }
inline void dec(int &x, int y) { x -= y; if(x < 0) x += mod; }
inline ll sum(ll x, ll y) { return ((x+y) * (y-x+1) >> 1) % mod; }

struct BIT {
	int w[maxp], v[maxp];
	void modify(int x, int k) {
		if(!x) return;
		for(; x <= m; x += x&-x) {
			if(v[x] != t) w[x] = 0, v[x] = t;
			inc(w[x], k);
		}
	}
	
	int query(int l, int r) {
		int ret = 0;
		if(r < l || !l || !r) return ret;
		for(--l; l; l -= l&-l) if(v[l] == t) dec(ret, w[l]);
		for(   ; r; r -= r&-r) if(v[r] == t) inc(ret, w[r]);
		return ret;
	}
} t1, t2, t3;

#define id(i, j) ((i)*(m+1) + (j))
#define le(i, j) (c1[id(i, j)])
#define ri(i, j) (c2[id(i, j)])
#define up(i, j) (c3[id(i, j)])
#define dw(i, j) (c4[id(i, j)])

int main() {
	n = read(), m = read(), k = read();
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
		a[id(i, j)] = 1;
	for(int x, y; k--; )
		x = read(), y = read(), a[id(x, y)] = 0;
	
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
		if(!a[id(i, j)]) le(i, j) = up(i, j) = 0;
		else le(i, j) = le(i, j-1)+1,
			 up(i, j) = up(i-1, j)+1;
	for(int i = n; i >= 1; --i)
	for(int j = m; j >= 1; --j)
		if(!a[id(i, j)]) ri(i, j) = dw(i, j) = 0;
		else ri(i, j) = ri(i, j+1)+1,
			 dw(i, j) = dw(i+1, j)+1;

	ll ans = 0, len = 0;
	for(int j = 1; j <= m; ++j, ++t) 
		for(int i = 1; i <= n; ++i) {
			if(!a[id(i, j)]) { ++t; continue; }
			len = min(le(i, j), ri(i, j))-1;
			if(len > 1) {
				(ans += (dw(i, j)-1) * sum(1, len-1) % mod * t1.query(len+1, m))%= mod;
				(ans += (dw(i, j)-1) * len % mod * t2.query(1, len)) %= mod;
				(ans -= (dw(i, j)-1) * t3.query(1, len)) %= mod;
			}
			
			if(i > 1) {
				len = min(le(i-1, j), ri(i-1, j))-1;
				if(len > 0) {
					t1.modify(len, up(i-1, j)-1);
					t2.modify(len, len * (up(i-1, j)-1) % mod);
					t3.modify(len, sum(1, len) * (up(i-1, j)-1) % mod);
				}
			}
		}
	printf("%lld\n", (ans + mod) % mod);
	return 0;
}
