#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned int ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5;
const int mod = 51061;
struct node {
	ll add, mul, val, sum, siz; bool rev;
	node *p, *s[2];
	
	node();
	void rever();
	void calc(int, int);
	void sets(node *x, int d) { (s[d] = x)->p = this; }
	bool pos() { return this == p->s[1]; }
	bool isroot() { return this != p->s[0] && this != p->s[1]; }
	void update() { 
		sum = (s[0]->sum + s[1]->sum + val)%mod; 
		siz = (s[0]->siz + s[1]->siz + 1)%mod;
	}
	void pushdown() {
		if(rev) s[0]->rever(), s[1]->rever(), rev = 0;
		if(add || mul != 1) 
			s[0]->calc(mul, add),
			s[1]->calc(mul, add),
			add = 0, mul = 1;
	}
} *emt = new node(), *st[maxn], s[maxn];
int n, q, top;

node::node() {
	add = rev = val = sum = siz = 0, mul = 1;
	p = s[0] = s[1] = emt;
}

void node::rever() {
	if(this == emt) return;
	swap(s[0], s[1]), rev ^= 1;
}

void node::calc(int m, int a) {
	if(this == emt) return;
	val = (val*m+a)%mod;
	sum = (sum*m+siz*a)%mod;
	add = (add*m+a)%mod;
	mul = (mul*m)%mod;
}


struct link_cut_tree {
	void init() { 
		emt->p = emt->s[0] = emt->s[1] = emt;
		for(int i = 1; i <= n; ++i) s[i] = node(), s[i].sum = s[i].val = 1; 
	}
	void rotate(node *x) {
		node *y = x->p, *z = y->p;
		int d = x->pos();
		y->sets(x->s[!d], d);
		if(y->isroot()) x->p = y->p;
		else z->sets(x, y->pos());
		x->sets(y, !d), y->update();
	}
	
	void splay(node *x) {
		top = 0, st[++top] = x;
		for(node *i = x; !i->isroot(); i = i->p) st[++top] = i->p;
		for(int i = top; i; --i) st[i]->pushdown();
		for(node *y; !x->isroot(); rotate(x))
			if(!(y = x->p)->isroot()) rotate(x->pos() == y->pos() ? y : x);
		x->update();
	}
	
	void access(node *x) {
		for(node *y = emt; x != emt; y = x, x = x->p)
			splay(x), x->s[1] = y, x->update();
	}
	
	void rever(node *x) { access(x), splay(x); x->rever(); }
	void split(node *x, node *y) { rever(y), access(x), splay(x); }
	void link(node *x, node *y) { rever(x), x->p = y, splay(x); }
	void cut(node *x, node *y) { split(x, y), x->s[0] = y->p = emt, splay(x); }
} LCT;


char op[4];
int main() {
	n = read(), q = read(), LCT.init();
	for(int i = 1; i < n; ++i) LCT.link(s+read(), s+read());
	for(node *u, *v; q--; ) {
		scanf("%s", op), u = s+read(), v = s+read();
		if(*op == '+') LCT.split(u, v), u->calc(1, read()), LCT.splay(u);
		if(*op == '*') LCT.split(u, v), u->calc(read(), 0), LCT.splay(u);
		if(*op == '-') LCT.cut(u, v), LCT.link(s+read(), s+read());
		if(*op == '/') LCT.split(u, v), printf("%d\n", u->sum);
	}
	return 0;
}
