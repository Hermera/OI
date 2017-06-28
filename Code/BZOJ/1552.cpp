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

const int maxn = 2e5+5;
const ll INF = 1e16;
struct node {
	ll val, mn; int siz; bool rev;
	node *p, *s[2];
	
	node() {}
	node(node *p, ll);
	void rever();
	void sets(node *x, int d) { (s[d] = x)->p = this; }
	bool pos() { return this == p->s[1]; }
	void pushdown() { if(rev) s[0]->rever(), s[1]->rever(), rev = 0; }
	void update() {
		siz = s[0]->siz + s[1]->siz + 1;
		mn = min(min(s[0]->mn, s[1]->mn), val);
	}
} *emt = new node(emt, INF), *root = emt;
int n;
ll a[maxn];

node::node(node *fa, ll v) {
	val = mn = v, siz = rev = 0;
	p = fa, s[0] = s[1] = emt;
}

void node::rever() {
	if(this == emt) return;
	swap(s[0], s[1]), rev ^= 1;
}

#define mid (l+r>>1)
#define half (x->s[0]->siz+1)
struct splaytree {
	node gen[maxn], *st[maxn], *fir;
	int cnt, top;
	void init() { emt->p = emt, cnt = 0; }
	
	void rotate(node *x) {
		node *y = x->p, *z = y->p;
		int d = x->pos();
		y->sets(x->s[!d], d);
		if(z == emt) x->p = y->p;
		else z->sets(x, y->pos());
		x->sets(y, !d), y->update();
	}
	
	void splay(node *x, node *g = emt) {
		top = 0, st[++top] = x;
		for(node *i = x; i->p != g; i = i->p) st[++top] = i->p;
		for(int i = top; i; --i) st[i]->pushdown();
		for(node *y; (y = x->p) != g; rotate(x))
			if(y->p != g) rotate(x->pos() == y->pos() ? y : x);
		x->update();
		if(g == emt) root = x;
	}
	
	void build(int l, int r, node *&x = root, node *fa = emt) {
		if(l > r) return;
		x = &gen[++cnt], *x = node(fa, 1LL*a[mid]*(n+1)+mid);
		if(mid == 0) fir = x;
		build(l, mid-1, x->s[0], x);
		build(mid+1, r, x->s[1], x);
		x->update();
	} 
	
	node *find_kth(int k, node *x = root) {
		x->pushdown();
		if(half == k) return x;
		if(half > k) return find_kth(k, x->s[0]);
		return find_kth(k-half, x->s[1]);
	}
	
	node *find_min(node *x = root) {
		x->pushdown();
		if(x->val == x->mn) return x;
		if(x->s[0]->mn == x->mn) return find_min(x->s[0]);
		return find_min(x->s[1]);
	}
	
	node *range(int l, int r) {
		node *x = find_kth(l-1), *y = find_kth(r+1);
		splay(y), splay(x, root);
		return x->s[1];
	}
	
	void rever(int l, int r) {
		node *x = range(l, r);
		x->rever();
	}
	
	node *get_min(int l, int r) {
		node *x = range(l, r);
		return find_min(x);
	}
	
	void work(int k) {
		node *x = get_min(k+1, n+1);
		splay(x), printf("%d", x->s[0]->siz);
		printf("%c", k == n ? '\n' : ' ');
		rever(k+1, x->s[0]->siz+1);
	}
	
	void print(node *x = root) {
		if(x == emt) return;
		x->pushdown();
		print(x->s[0]);
		printf("%lld ", x->val);
		print(x->s[1]);
	}
	
} s;

int main() {
	freopen("sort.in", "r", stdin);
	freopen("sort.out", "w", stdout);

	n = read(), a[0] = a[n+1] = INF;
	for(int i = 1; i <= n; ++i) a[i] = read();
	s.init(), s.build(0, n+1);
	
	for(int i = 1; i <= n; ++i) s.work(i);//, s.print(), printf("\n");
	return 0;
}
