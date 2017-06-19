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
const int L = 18;


struct node {
	int val, tag, add;
	node *ls, *rs;

	void sets(int w) {
		val = max(val, w);
	}

	void update() {
		val = 0;
		if(ls) val = max(val, ls->val);
		if(rs) val = max(val, rs->val);
	}

	void update(int w) {
		val += w;
		tag += w;
	}

	void pushdown() {
		if(tag) {
			if(ls) ls->update(tag);
			if(rs) rs->update(tag);
			tag = 0;
		}
	}
} gen[N * L];

int idx;
node *newnode() {
	node *p = gen + (++idx);
	return p;
}


int n;
int p[N], v[N], h[N];


#define mid (l + r >> 1)
#define lc o->ls, l, mid
#define rc o->rs, mid+1, r
struct segment {
	node *root;
	int query(node *o, int l, int r, int L, int R) {
		if(!o || R < l || r < L) return 0;
		if(L <= l && r <= R) return o->val;
		o->pushdown();
		return max(query(lc, L, R), query(rc, L, R));
	} 

	void update(node *&o, int l, int r, int p, int w) {
		if(!o) o = newnode();
		if(l == r) return o->sets(w);

		o->pushdown();
		if(p <= mid) update(lc, p, w);
		else update(rc, p, w);
		o->update();
	}

	int query(int l, int r) {
		return query(root, 1, n, l, r);
	}

	void update(int p, int w) {
		update(root, 1, n, p, w);
	}
} T[N];

node *merge(node *o1, node *o2, int l, int r, int w1, int w2) {
	if(!o1 && !o2) return 0;
	if(!o1) return o2->update(w1), o2;
	if(!o2) return o1->update(w2), o1;
	if(l == r) {
		int w3 = max(o1->val, w1);
		int w4 = max(o2->val, w2);
		o1->update(w4), o2->update(w3);
		return o1->val > o2->val ? o1 : o2;
	}

	o1->pushdown();
	o2->pushdown();

	int w3 = max(w1, o1->ls ? o1->ls->val : 0);
	int w4 = max(w2, o2->ls ? o2->ls->val : 0);
	o1->ls = merge(o1->ls, o2->ls, l, mid, w1, w2);
	o1->rs = merge(o1->rs, o2->rs, mid+1, r, w3, w4);
	return o1->update(), o1;
}



int main() {
	n = read();
	for(int i = 1; i <= n; ++i)
		v[i] = h[i] = read(), p[i] = read();
	sort(h + 1, h + 1 + n);
	for(int i = 1; i <= n; ++i)
		v[i] = lower_bound(h + 1, h + 1 + n, v[i]) - h;

	for(int o = n; o >= 1; --o) {
		int w = T[o].query(1, v[o] - 1);
		T[o].update(v[o], w + 1);
		w = T[o].query(1, n);
		if(p[o]) T[p[o]].root = merge(T[p[o]].root, T[o].root, 1, n, 0, 0);
	}

	int ans = T[1].query(1, n);
	printf("%d\n", ans);
	return 0;
}