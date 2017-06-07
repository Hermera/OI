#include <cstdio>
#include <cstring>
#include <assert.h>
#include <algorithm>
using namespace std;
typedef unsigned int ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 6e5+5;
const int maxs = 15000005;
const int INF = 1e9;
const int bin = 29;

int n, m, tim, cnt;
char op[5], str[maxn];
ll pow[maxn];

#define ln o<<1
#define rn o<<1|1
#define mid (l+r>>1)
#define lc ln, l, mid
#define rc rn, mid+1, r
struct segment_min {
	int t[maxn<<2], g[maxn<<2];
	void clear() { memset(t, 63, sizeof(t)); }
	void pushup(int o) { t[o] = min(t[ln], t[rn]); }
	void pushdown(int o) {
		if(g[o]) {
			t[ln] += g[o], t[rn] += g[o];
			g[ln] += g[o], g[rn] += g[o];
			g[o] = 0;
		}
	}
	
	void update(int o, int l, int r, int p, int v) {
		if(l == r) {
			t[o] = v, g[o] = 0;
			return;
		}
		pushdown(o);
		if(p <= mid) update(lc, p, v);
		else update(rc, p, v);
		pushup(o);
	}
	
	void modify(int o, int l, int r, int L, int R, int v) {
		if(R < l || r < L) return;
		if(L <= l && r <= R) {
			t[o] += v ,g[o] += v;
			return;
		}
		pushdown(o);
		modify(lc, L, R, v);
		modify(rc, L, R, v);
		pushup(o);
	}
	
	int query(int o, int l, int r, int L, int R) {
		if(L <= l && r <= R) return t[o];
		if(R < l || r < L) return INF;
		pushdown(o);
		return min(query(lc, L, R), query(rc, L, R));
	}
} h;


struct node {
	node *ls, *rs;
	node() { ls = rs = this; }
	int siz, tim, val; ll has;
	void update() {
		siz = ls->siz + rs->siz + 1;
		has = pow[rs->siz+1]*ls->has + pow[rs->siz]*val + rs->has;
	}
} *emt = new node(), gen[maxs];

#define fir first
#define sec second
typedef pair<node*, node*> pi;
struct treap {
	node *root;
	treap() { root = emt; }
	node *newnode(int t = 0, int v = 0) {
		node *o = gen + (++cnt);
		*o = *emt, o->tim = t, o->val = v;
		return o->update(), o;
	}  
	
	node *merge(node *x, node *y) {
		if(x == emt) return y;
		if(y == emt) return x;
		if(x->tim < y->tim) swap(x, y);
		
		node *o = newnode();
		int d = rand()%(x->siz + y->siz) < x->siz;
		if(d) *o = *x, o->rs = merge(o->rs, y);
		else  *o = *y, o->ls = merge(o->ls, x);
		return o->update(), o;
	}

	void insert(treap x) { root = merge(root, x.root); }
	void insert(int t, int v) {
		node *o = newnode(t, v);
		root = merge(root, o);
	}
	
	ll gethash(int k, node *o) {
		if(!k || o == emt) return 0;
		if(o->ls->siz >= k) return gethash(k, o->ls);
		else {
			ll sum = gethash(k - o->ls->siz - 1, o->rs);
			sum += o->ls->has * pow[k-o->ls->siz];
			sum += o->val * pow[k-o->ls->siz - 1];
			return sum;
		}
	}
};

struct segment_treap {
	treap t[maxn<<2];
	void pushdown(int o) {
		if(t[o].root != emt) {
			t[ln].insert(t[o]);
			t[rn].insert(t[o]);
			t[o].root = emt;
		}
	}

	treap get(int o, int l, int r, int p) {
		if(l == r) return t[o];
		pushdown(o);
		if(p <= mid) return get(lc, p);
		else return get(rc, p);
	}
	
	void insert(int o, int l, int r, int L, int R, treap p) {
		if(L <= l && r <= R) {
			t[o].insert(p);
			return;
		}
		if(R < l || r < L) return;
		pushdown(o);
		insert(lc, L, R, p);
		insert(rc, L, R, p);
	}
} t;


int getLCP(int x, int y) {
	treap tx = t.get(1, 1, n, x);
	treap ty = t.get(1, 1, n, y);
	int l = 0, r = min(tx.root->siz, ty.root->siz), ans = 0;
	while(l <= r) 
		if(tx.gethash(mid, tx.root) == ty.gethash(mid, ty.root)) ans = mid, l = mid+1;
		else r = mid-1;
	return ans;
}


void insert(int l, int r) {
	scanf("%s", str);
	int len = strlen(str); 
	tim += len;
	
	treap now; 
	for(int i = 0; str[i]; ++i) now.insert(tim--, str[i]-'a'+1);
	t.insert(1, 1, n, l, r, now);
	if(l > 1) h.update(1, 1, n, l, getLCP(l-1, l));
	if(r < n) h.update(1, 1, n, r+1, getLCP(r, r+1));
	if(l < r) h.modify(1, 1, n, l+1, r, len);
	tim += len;
}

int query(int l, int r) { 
	if(l == r) return t.get(1, 1, n, l).root->siz;
	return h.query(1, 1, n, l+1, r); 
}

int main() {
	n = read(), m = read();

	h.clear();
	pow[0] = 1;
	for(int i = 1; i < maxn; ++i) pow[i] = pow[i-1] * bin;
	for(int i = 1; i <= n; ++i) insert(i, i);
	
	for(int l, r; m--; ) {
		scanf("%s", op), l = read(), r = read();
		if(*op == 'I') insert(l, r);
		else printf("%d\n", query(l, r));
	}
	return 0;
}
