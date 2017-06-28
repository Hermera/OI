#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x * t;
}


const int N = 1e5+5;
const int INF = 2e9;
int n, q, a[N];

struct node {
	node *ls, *rs;
	ll mn, mx, sum, tag;
	int siz;
	
	void sets(int v) {
		mn = mx = sum = v;
	}
	
	void add(ll v) {
		mn += v, mx += v, tag += v;
		sum += v * siz;
	}
	
	void update() {
		mn = min(ls->mn, rs->mn);
		mx = max(ls->mx, rs->mx);
		sum = ls->sum + rs->sum;
	}
	
	void pushdown() {
		if(tag) {
			ls->add(tag);
			rs->add(tag);
			tag = 0;
		}
	}
} gen[N << 2], *root;
int idx;


#define mid (l+r>>1)
#define lc o->ls, l, mid
#define rc o->rs, mid+1, r
struct Segment {
	void build(node *&o, int l, int r) {
		o = gen + (++idx);
		o->siz = r - l + 1;
		if(l == r) return o->sets(a[l]);
		build(lc), build(rc);
		o->update();
	}
	
	void add(node *o, int l, int r, int L, int R, int v) {
		if(R < l  || r < L ) return;
		if(L <= l && r <= R) return o->add(v);
		o->pushdown();
		add(lc, L, R, v);
		add(rc, L, R, v);
		o->update();
	}
	
	void div(node *o, int l, int r, int L, int R, int v) {
		if(R < l  || r < L ) return;
		if(L <= l && r <= R) {
			ll p1 = o->mn - floor(1.0*o->mn / v);
			ll p2 = o->mx - floor(1.0*o->mx / v);
			if(p1 == p2) return o->add(-p1);
		}
		
		o->pushdown();
		div(lc, L, R, v);
		div(rc, L, R, v);
		o->update();
	}
	
	ll ask(node *o, int l, int r, int L, int R) {
		if(R < l  || r < L ) return INF;
		if(L <= l && r <= R) return o->mn;
		o->pushdown();
		return min(ask(lc, L, R), ask(rc, L, R));
	}
	
	ll sum(node *o, int l, int r, int L, int R) {
		if(R < l  || r < L ) return 0;
		if(L <= l && r <= R) return o->sum;
		o->pushdown();
		return sum(lc, L, R) + sum(rc, L, R);
	}
} T;


int main() {
	n = read(), q = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	
	T.build(root, 1, n);
	for(int i = 1; i <= q; ++i) {
		int t = read(), l = read()+1, r = read()+1;
		if(t == 1) T.add(root, 1, n, l, r, read());
		if(t == 2) T.div(root, 1, n, l, r, read());
		if(t == 3) printf("%lld\n", T.ask(root, 1, n, l, r));
		if(t == 4) printf("%lld\n", T.sum(root, 1, n, l, r));
	}
	return 0;
}