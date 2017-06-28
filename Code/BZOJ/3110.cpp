#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 1e5+5;
const int NAN = 1e9;

int n, m, c,ans[maxn];
struct opt {
	int op, l, r, v, id;
	void init(int i) {
		op = read(), l = read(), r = read();
		v = read(), id = i;
	}
} a[maxn], b[maxn];


#define mid (l+r>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
struct Segment {
	ll t[maxn<<2], p[maxn<<2];
	void add(int o, int l, int r, int L, int R, int v) {
		if(R < l || r < L) return;
		if(L <= l && r <= R) {
			t[o] += 1LL*v*(r-l+1);
			p[o] += v;
			return;
		}
		add(lc, L, R, v);
		add(rc, L, R, v);
		t[o] = t[o<<1] + t[o<<1|1] + p[o]*(r-l+1);
	}
	
	ll query(int o, int l, int r, int L, int R) {
		if(L == l && r == R) return t[o];
		
		ll ret = 0;
		if(R <= mid) ret = query(lc, L, R);
		else if(L > mid) ret = query(rc, L, R);
		else ret = query(lc, L, mid) + query(rc, mid+1, R);
		return ret + p[o]*(R-L+1);
	}
} T;

void solve(int l, int r, int s, int t) {
	if(l == r) {
		for(int i = s; i <= t; ++i) 
			if(a[i].op == 2) ans[a[i].id] = l;
			else ans[a[i].id] = NAN;
		return;
	}
	
	int k1 = s, k2 = t;
	for(int i = s; i <= t; ++i) {
		opt &e = a[i];
		if(e.op == 1) {
			if(e.v <= mid) b[k1++] = e;
			else T.add(1, 1, n, e.l, e.r, 1), b[k2--] = e;
		} else {
			ll ret = T.query(1, 1, n, e.l, e.r);
			if(ret >= e.v) b[k2--] = e;
			else e.v -= ret, b[k1++] = e;
		}
	}
	
	for(int i = s; i <= t; ++i) a[i] = b[i];
	reverse(a+k1, a+t+1);
	for(int i = s; i <= t; ++i) 
		if(a[i].op == 1 && a[i].v > mid)
			T.add(1, 1, n, a[i].l, a[i].r, -1);
	
	solve(l, mid, s, k1-1);
	solve(mid+1, r, k1, t);
}


int main() {
	n = read(), m = read();
	for(int i = 1; i <= m; ++i) a[i].init(i);
	solve(-n, n, 1, m);	
	for(int i = 1; i <= m; ++i)
		if(ans[i] != NAN) printf("%d\n", ans[i]);
	return 0;
}
