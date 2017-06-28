#include <cstdio>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
int n, m, q, a[maxn], b[maxn];

#define mid (l+r>>1)
#define lc o<<1, l, mid
#define rc o<<1|1, mid+1, r
struct Segment {
	int t[maxn<<2], p[maxn<<2];
	void pushup(int o) { t[o] = t[o<<1]+t[o<<1|1]; }
	void pushdown(int o, int l, int r) {
		if(~p[o]) {
			t[o<<1] = p[o]*(mid-l+1);
			t[o<<1|1] = p[o]*(r-mid);
			p[o<<1] = p[o<<1|1] = p[o];
			p[o] = -1;
		}
	}
	
	void build(int o, int l, int r) {
		p[o] = -1;
		if(l == r) t[o] = b[l];
		else build(lc), build(rc), pushup(o);
	}
	
	void modify(int o, int l, int r, int L, int R, int v) {
		if(L <= l && r <= R) {
			t[o] = v*(r-l+1);
			p[o] = v;
			return;
		}
		if(R < l || r < L) return;
		pushdown(o, l, r);
		modify(lc, L, R, v), modify(rc, L, R, v);
		pushup(o);
	}
	
	int query(int o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[o];
		if(R < l || r < L) return 0;
		pushdown(o, l, r);
		return query(lc, L, R)+query(rc, L, R);
	}
} T;

struct ele {
	int op, l, r;
	void init() { op = read(), l = read(), r = read(); }
} opt[maxn];

bool judge(int x) {
	for(int i = 1; i <= n; ++i) b[i] = a[i] > x;
	T.build(1, 1, n);
	for(int i = 1, zro, one; i <= m; ++i) {
		ele &e = opt[i];
		one = T.query(1, 1, n, e.l, e.r);
		zro = e.r-e.l+1 - one;
		if(!e.op) 
			T.modify(1, 1, n, e.l, e.l+zro-1, 0),
			T.modify(1, 1, n, e.r-one+1, e.r, 1);
		else 
			T.modify(1, 1, n, e.l, e.l+one-1, 1),
			T.modify(1, 1, n, e.r-zro+1, e.r, 0);
	}
	return !T.query(1, 1, n, q, q);
}

int main() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= m; ++i) opt[i].init();
	q = read();
	
	int l = 1, r = n, ans;
	while(l <= r) 
		if(judge(mid)) ans = mid, r = mid-1;
		else l = mid+1;
	
	printf("%d\n", ans);
	return 0;
}
