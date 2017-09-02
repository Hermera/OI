#include <map>
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

int getphi(int x) {
	int ret = x;
	for(int i = 2; i*i <= x; ++i)
		if(!(x % i)) {
			(ret /= i) *= i-1;
			while(!(x % i)) x /= i;
		}
	if(x > 1) (ret /= x) *= x-1;
	return ret;
}

const int N = 5e4+5;

map <int, int> phi;
int n, m, p, c, lim, a[N];

void prepare() {
	phi[1] = lim = 1;
	for(int x = p; x != 1; ) 
		x = phi[x] = getphi(x), ++lim;
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

ll calc(ll x, ll k, ll p) {
	if(!k) return x < p ? x : x % p + p;
	return getans(c, calc(x, k-1, phi[p]), p);
}


struct node {
	int sum, tot;
} t[N << 2];

#define ls o<<1
#define rs o<<1|1
#define mid (l+r>>1)
#define lc ls, l, mid
#define rc rs, mid+1, r
struct segment {
	void pushup(int o) {
		t[o].sum = (t[ls].sum + t[rs].sum) % p;
		t[o].tot = min(t[ls].tot, t[rs].tot);
	}

	void build(int o, int l, int r) {
		if(l == r) t[o].sum = a[l];
		else build(lc), build(rc), pushup(o);
	}
	
	void update(int o, int l, int r, int L, int R) {
		if(R < l || r < L || t[o].tot > lim) return;
		if(l == r) {
			t[o].sum = calc(a[l], ++t[o].tot, p) % p;
			return;
		}
		
		update(lc, L, R);
		update(rc, L, R);
		pushup(o);
	}
	
	int query(int o, int l, int r, int L, int R) {
		if(R < l || r < L) return 0;
		if(L <= l && r <= R) return t[o].sum;
		return (query(lc, L, R) + query(rc, L, R)) % p;
	}
} T;


int main() {
	n = read(), m = read();
	p = read(), c = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	
	prepare();
	T.build(1, 1, n);
	for(int i = 1; i <= m; ++i) {
		int op = read(), l = read(), r = read();
		if(!op) T.update(1, 1, n, l, r);
		else printf("%d\n", T.query(1, 1, n, l, r));
	}
	return 0;
}
