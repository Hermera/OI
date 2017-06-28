#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 505;
const int maxm = 5e5+5;
int n, m, t, c, tim;
int h[maxm], ans[maxm];

struct opt {
	int x1, x2, y1, y2, val, id;
	bool type;
} q[maxm], p[maxm];

void init() {
	n = read(), m = read();
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j)
		h[++c] = q[++t].val = read(),
		q[t].x1 = i, q[t].y1 = j, q[t].type = 1;
	sort(h+1, h+1+c);
	c = unique(h+1, h+1+c)-h-1;
	for(int i = 1; i <= t; ++i) 
		q[i].val = lower_bound(h+1, h+1+c, q[i].val)-h;
	for(int i = 1; i <= m; ++i) {
		++t;
		q[t].x1 = read(), q[t].y1 = read();
		q[t].x2 = read(), q[t].y2 = read();
		q[t].val = read(), q[t].id = i;
	}
}


struct BIT {
	int w[maxn][maxn], v[maxn][maxn];
	void add(int x, int y) {
		for(int i = x; i <= n; i += i&-i)
		for(int j = y; j <= n; j += j&-j) {
			if(v[i][j] != tim) v[i][j] = tim, w[i][j] = 0;
			++w[i][j];
		}	
	}
	
	int query(int x, int y) {
		int ret = 0;
		for(int i = x; i; i -= i&-i)
		for(int j = y; j; j -= j&-j)
			if(v[i][j] == tim) ret += w[i][j];
		return ret;
	}
	
	int query(opt e) {
		return query(e.x2, e.y2) + query(e.x1-1, e.y1-1)
		- query(e.x1-1, e.y2) - query(e.x2, e.y1-1);
	}
} T;

void solve(int l, int r, int t1, int t2) {
	if(t1 > t2) return;
	if(l == r) {
		for(int i = t1; i <= t2; ++i)
			if(!q[i].type) ans[q[i].id] = h[l];
		return;
	}
	
	++tim;
	int mid = (l+r)>>1, k1 = t1, k2 = t2;
	for(int i = t1; i <= t2; ++i) {
		opt &e = q[i];
		if(e.type) {
			if(e.val > mid) p[k2--] = e;
			else T.add(e.x1, e.y1), p[k1++] = e;
		} else {
			int ret = T.query(e);
			if(ret >= e.val) p[k1++] = e;
			else e.val -= ret, p[k2--] = e;
		}
	}
	for(int i = t1; i <= t2; ++i) q[i] = p[i];
	reverse(q+k1, q+t2+1);
	
	solve(l, mid, t1, k1-1);
	solve(mid+1, r, k1, t2);
}


int main() {
	init();
	solve(1, c, 1, t);
	for(int i = 1; i <= m; ++i)
		printf("%d\n", ans[i]);
	return 0;
}
