#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 2e5+5;
const int INF = 1e9;

int n, m, idx, h[N], value[N];
struct node {
	node *ls, *rs;
	int val, pos, lsum, rsum;
	void sets(int v, int p) { 
		val = v, pos = p; 
		lsum = rsum = 1;
	}
	
	void update() {
		val = max(ls->val, rs->val);
		pos = ls->val < rs->val ? rs->pos : ls->pos;
	}
} gen[N << 2], *root;


#define mid (l+r>>1)
#define lc o->ls, l, mid
#define rc o->rs, mid+1, r
struct Segment {
	int dfsL(node *o, int l, int r, int v) {
		if(o->val < v) return 0;
		if(l == r) return 1;
		if(o->ls->val < v) return dfsL(rc, v);
		else return o->lsum - o->ls->lsum + dfsL(lc, v);
	} /* (l, r) = {9 6 7 2}, ask(5).
		the answer is 2.
		o->lsum - o->ls->lsum = 1. (right)
		o->rs->lsum = 2. (wrong)
		*/

	int dfsR(node *o, int l, int r, int v) {
		if(o->val < v) return 0;
		if(l == r) return 1;
		if(o->rs->val < v) return dfsR(lc, v);
		else return o->rsum - o->rs->rsum + dfsR(rc, v);
	}

	void pushup(node *o, int l, int r) {
		o->update();
		o->lsum = o->ls->lsum + dfsL(rc, o->ls->val);
		o->rsum = o->rs->rsum + dfsR(lc, o->rs->val);
	}
	
	void build(node *&o, int l, int r) {
		o = gen + (++idx);
		if(l == r) return;
		build(lc), build(rc);
	}

	void modify(node *o, int l, int r, int p, int v) {
		if(l == r) return o->sets(v, l);
		if(p <= mid) modify(lc, p, v);
		else modify(rc, p, v);
		pushup(o, l, r);
	}
	
	int askL(node *o, int l, int r, int L, int R, int &v) {
		if(R < l || r < L) return 0;
		int ret = 0;
		if(L <= l && r <= R) {
			ret = dfsL(o, l, r, v);
			v = max(v, o->val);
		} else {
			ret += askL(lc, L, R, v);
			ret += askL(rc, L, R, v);
		}
		return ret;
	}
	
	int askR(node *o, int l, int r, int L, int R, int &v) {
		if(R < l || r < L) return 0;
		int ret = 0;
		if(L <= l && r <= R) {
			ret = dfsR(o, l, r, v);
			v = max(v, o->val);
		} else {
			ret += askR(rc, L, R, v);
			ret += askR(lc, L, R, v);
		}
		return ret;
	}
	
	int query(node *o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return o->pos;
		if(R < l  || r < L ) return 0;
		int p1 = query(lc, L, R), p2 = query(rc, L, R);
		return value[p1] > value[p2] ? p1 : p2;
	}
} T;


int getdep(int x) {
	int ret = 0, val;
	ret += T.askR(root, 1, n, 1, x - 1, val = value[x]);
	ret += T.askL(root, 1, n, x + 1, n, val = value[x]);
	return ret;
}


struct ele {
	int type, x, y;
	void init() {
		type = read(), x = read();
		if(type != 1)  y = read();
	}
	
	void update() {
		x = lower_bound(h+1, h+1+n, x) - h;
		if(type == 2) {
			y = lower_bound(h+1, h+1+n, y) - h;
			if(x > y) swap(x, y);
		}
	}
} opt[N];

int main() {
	m = read();
	for(int i = 1; i <= m; ++i) opt[i].init();
	for(int i = 1; i <= m; ++i)
		if(opt[i].type == 0) h[++n] = opt[i].x;
	sort(h+1, h+1+n);
	for(int i = 1; i <= m; ++i) opt[i].update();
	
	T.build(root, 1, n);
	for(int i = 1; i <= m; ++i) {
		ele &e = opt[i];
		if(e.type == 0) T.modify(root, 1, n, e.x, e.y), value[e.x] = e.y;
		if(e.type == 1) T.modify(root, 1, n, e.x, 0),   value[e.x] = 0;
		if(e.type == 2) {
			int p = T.query(root, 1, n, e.x, e.y), ret = 0;
			ret += getdep(e.x);
			ret += getdep(e.y);
			ret -= getdep(p) * 2;
			printf("%d\n", ret);
		}
	}
	return 0;
}
