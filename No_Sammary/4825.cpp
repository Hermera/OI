#include <set>
#include <cstdio>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 1e5+5;
const int INF = 2e9;

struct node {
	node *p, *s[2];
	node *anc, *son[2];
	int val, key, tag;
	node() {
		p = s[0] = s[1] = this;
		anc = son[0] = son[1] = this;
	}
	
	void sets(node *x, int d) { (s[d] = x)->p = this; }
	bool pos() { return p->s[1] == this; }
	void add(int v) { val += v, tag += v; }
	void pushdown() {
		if(tag) {
			s[0]->add(tag);
			s[1]->add(tag);
			tag = 0;
		}
	}
} gen[N];
node *st[N];
node *emt = new node(), *root = emt;

int idx, top, ans;
node *newnode(node *o, int v) {
	node *p = gen + (++idx);
	return *p = *emt, p->p = o, p->key = v, p;
}


void rotate(node *x) {
	node *y = x->p, *z = y->p;
	int d = x->pos();
	y->sets(x->s[!d], d);
	if(z == emt) x->p = emt;
	else z->sets(x, y->pos());
	x->sets(y, !d);
}

void splay(node *x, node *g = emt) {
	st[top = 1] = x;
	for(node *i = x; i->p != g; i = i->p) st[++top] = i->p;
	for(int i = top; i; --i) st[i]->pushdown();
	for(node *y; (y = x->p) != g; rotate(x))
		if(y->p != g) rotate(x->pos() == y->pos() ? y : x);
	if(g == emt) root = x;
}


node *next(node *o, int d) {
	splay(o), o = o->s[d];
	for(; o->s[!d] != emt;) o = o->s[!d];
	return splay(o), o;
}

node *insert(node *&o, node *p, int v) {
	if(o == emt) return o = newnode(p, v);
	if(v < o->key) insert(o->s[0], o, v);
	else insert(o->s[1], o, v);
}

void remove(node *o) {
	node *l = next(o, 0);
	node *r = next(o, 1);
	splay(l), splay(r, l);
	r->s[0] = emt;
}



void sets(node *u, node *v, int d) {
	v->anc = u;
	u->son[d] = v;
	v->val = u->val + 1;
}

void insert(int v) {
	node *o = insert(root, emt, v);
	node *l = next(o, 0);
	node *r = next(o, 1);
	if(l->val < r->val) sets(r, o, 1);
	else sets(l, o, 0);
	ans = o->val;
}

void to_top(node *x, int on) {
	ans = x->val;
	node *p = x->anc;
	if(p == emt) return;
	
	splay(p), p->val += 1;
	int d = (p->s[1] != emt);
	p->s[d]->add(1);

	x->son[d]->anc = p;
	p->son[!d] = x->son[d];
	if(on) p->anc = emt, remove(x), p->add(-1);
	else p->anc = x, x->anc = emt;
}

int n;
node *lb, *rb;
int main() {
	freopen("4825.in", "r", stdin);

	n = read();
	lb = insert(root, emt, -INF);
	rb = insert(root, emt,  INF);
	for(int i = 1; i <= n; ++i) {
		int c = read();
		if(c == 1) insert(read());
		if(c == 2) to_top(next(lb, 1), 0);
		if(c == 3) to_top(next(rb, 0), 0);
		if(c == 4) to_top(next(lb, 1), 1);
		if(c == 5) to_top(next(rb, 0), 1);
		printf("%d\n", ans);
	}
	return 0;
}
