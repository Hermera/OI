#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 1e5 + 5;

struct node {
	node *ls, *rs;
	int siz, val, tag, key;
	
	node() {
		ls = rs = this;
		siz = val = tag = 0;
	}
	void pushdown();

	int value() { 
		return ls->siz + 1; 
	}
	void add(int x) {
		tag += x, val += x;
	}
	void update() {
		siz = ls->siz + rs->siz + 1;
	}
} gen[N];

node *emt = new node();
node *root = emt;

void node::pushdown() {
	if (tag) {
		if (ls != emt) ls->add(tag);
		if (rs != emt) rs->add(tag);
		tag = 0;
	}
}


int idx;
node *newnode(int v) {
	node *p = gen + (++idx);
	p->ls = p->rs = emt;
	p->key = rand();
	return p->val = v, p;
}


typedef pair<node*, node*> pii;
#define fir first
#define sec second

node *merge(node *x, node *y) {
	if (x == emt) return y;
	if (y == emt) return x;
	if (x->val > y->val) swap(x, y);

	x->pushdown();
	y->pushdown();
	if (x->key < y->key) {
		x->rs = merge(x->rs, y);
		return x->update(), x;
	} else {
		y->ls = merge(y->ls, x);
		return y->update(), y;
	}
}

pii split(node *o, int k) {
	if (o == emt) return pii(o, o);

	o->pushdown();
	if (o->ls->siz >= k) {
		pii x = split(o->ls, k);
		o->ls = x.sec, o->update();
		return x.sec = o, x;
	} else {
		pii x = split(o->rs, k - o->value());
		o->rs = x.fir, o->update();
		return x.fir = o, x;
	}
}

int get_kth(node *o, int v) {
	if (o == emt) return 0;
	o->pushdown();
	if (v <	o->val) return get_kth(o->ls, v);
	return o->value() + get_kth(o->rs, v);
}

void insert(node *&x, node *y) {
	int k = get_kth(x, y->val);
	pii o = split(x, k);
	x = merge(o.fir, y);
	x = merge(x, o.sec);
}

node *find_kth(node *o, int k) {
	if (k == o->value()) return o;
	o->pushdown();
	if (k <= o->ls->siz) return find_kth(o->ls, k);
	return find_kth(o->rs, k - o->value());
}


int top;
node *st[N];
void print(node *x) {
	if(x == emt) return;
	st[++top] = x;
	x->pushdown();
	print(x->ls);
	print(x->rs);
	x->ls = x->rs = emt;
	x->update();
}


int n, m, a[N];
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) a[i] = read();
	for (int i = 1; i <= n; ++i) {
		node *p = newnode(a[i]);
		p->update(), insert(root, p);
	}

	for (int i = 1; i <= m; ++i) {
		int op = read(), k = read();
		if (op == 1) {
			int ans = find_kth(root, k)->val;
			printf("%d\n", ans);
		} else {
			int k1 = get_kth(root, k);
			int k2 = get_kth(root, k * 2);
			pii o1 = split(root, k1);
			pii o2 = split(o1.sec, k2 - k1);

			root = o1.fir;
			if(o2.fir != emt) {
				o2.fir->add(-k), print(o2.fir);
				for(int i = 1; i <= top; ++i) 
					insert(root, st[i]);
				top = 0;
			}

			if (o2.sec != emt) o2.sec->add(-k);
			root = merge(root, o2.sec);
		}
	}
	return 0;
}