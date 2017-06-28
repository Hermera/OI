#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 1e5+5;
int n, m;
struct node {
	int val, mx, tag, siz; 
	bool rev;
	node *p, *s[2];
	
	node() {}
	node(node*, int);
	void pushdown();
	void update();
	void rever();
	void add(int v);	
	void sets(node *x, int d) { (s[d] = x)->p = this; }
	bool pos() { return this == p->s[1]; }
} *emt = new node(), *root = emt;

node::node(node* fa, int v = 0) {
	p = fa, val = mx = v, tag = siz = 0;
	s[0] = s[1] = emt;
}

void node::rever() {
	if(this == emt) return;
	swap(s[0], s[1]), rev ^= 1;
}

void node::add(int v = 0) {
	if(this == emt) return;
	tag += v, val += v, mx += v;
}

void node::update() {
	mx = val;
	if(s[0] != emt) mx = max(mx, s[0]->mx);
	if(s[1] != emt) mx = max(mx, s[1]->mx);
	siz = s[0]->siz + s[1]->siz + 1;
}

void node::pushdown() {
	if(rev) s[0]->rever(), s[1]->rever(), rev = 0;
	if(tag) s[0]->add(tag), s[1]->add(tag), tag = 0;
}

#define mid (l+r>>1)
#define half (x->s[0]->siz+1)
struct splaytree {
	node *st[maxn], gen[maxn];
	int cnt, top;
	void init() { cnt = 0, emt->p = emt; }
	
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
		x = &gen[++cnt], *x = node(fa, 0);
		build(l, mid-1, x->s[0], x);
		build(mid+1, r, x->s[1], x);
		x->update();
	}
	
	node *find_kth(int k, node *x = root) {
		x->pushdown();
		if(k == half) return x;
		if(k < half) return find_kth(k, x->s[0]);
		return find_kth(k-half, x->s[1]);
	}
	
	void print(node *x = root) {
		if(x == emt) return;
		x->pushdown();
		print(x->s[0]);
		printf("%d ", x->val);
		print(x->s[1]);
	}
} s;


int main() {
	n = read(), m = read();
	s.init(), s.build(0, n+1);
	for(int k, l, r; m--;) {
		k = read(), l = read()+1, r = read()+1;
		node *x = s.find_kth(l-1), *y = s.find_kth(r+1), *o;
		s.splay(y), s.splay(x, root), o = x->s[1];
		
		if(k == 1) o->add(read());
		if(k == 2) o->rever();
		if(k == 3) printf("%d\n", o->mx);
	}
	return 0;
}

