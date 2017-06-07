#include <cstdio>
#include <algorithm>
#define ins(x, a, b) ((a) <= (x) && (x) <= (b))
#define out(x, a, b) ((x) < (a) || (b) < (x))
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(out(ch, '0', '9')) ch = getchar();
	while(ins(ch, '0', '9')) x = x*10+ch-'0', ch = getchar();
	return x;
}

char get() {
	char ch = getchar();
	while(out(ch, 32, 126)) ch = getchar();
	return ch;
}


const int maxn = 2*1024*1024+5;
struct node {
	int siz, val;
	node *p, *s[2];
	
	node() {}
	node(node*, int);
	void sets(node *x, int d) { (s[d] = x)->p = this; }
	void update() { siz = s[0]->siz + s[1]->siz + 1; }
	int pos() { return this == p->s[1]; }
} *emt = new node(), *root = emt, gen[maxn];
int m, t, cnt;
char str[maxn], op[20];

node::node(node* fa, int v) {
	p = fa, val = v, siz = 0;
	s[0] = s[1] = emt;
}

#define mid (l+r>>1)
#define half (x->s[0]->siz + 1)
struct splaytree {
	void init() { emt->p = emt, push(0), push(0), push(0), push(0); }
	void rotate(node *x) {
		node *y = x->p, *z = y->p;
		int d = x->pos();
		y->sets(x->s[!d], d);
		if(z == emt) x->p = y->p;
		else z->sets(x, y->pos());
		x->sets(y, !d), y->update();
	}
	
	void splay(node *x, node *g = emt) {
		for(node *y; (y = x->p) != g; rotate(x))
			if(y->p != g) rotate(x->pos() == y->pos() ? y : x);
		x->update();
		if(g == emt) root = x;
	}
	
	void push(int v, node *&x = root, node *fa = emt) {
		if(x == emt) x = &gen[++cnt], *x = node(fa, v);
		else push(v, x->s[0], x);
		x->update();
	}
	
	void build(int l, int r, node *&x, node *fa) {
		if(l > r) return;
		x = &gen[++cnt], *x = node(fa, str[mid]);
		build(l, mid-1, x->s[0], x);
		build(mid+1, r, x->s[1], x);
		x->update();
	}
	
	node* find_kth(int k, node *x = root) {
		if(k == half) return x;
		if(k < half) return find_kth(k, x->s[0]);
		return find_kth(k-half, x->s[1]);
	}
	
	node *range(int l, int r) {
		node *x = find_kth(l-1), *y = find_kth(r+1);
		splay(y), splay(x, root);
		return x->s[1];
	}
	
	void print(node *x) {
		if(x == emt) return;
		print(x->s[0]);
		if(x->val) printf("%c", x->val);
		print(x->s[1]);
	}
	
	void insert(int k) {
		for(int i = 1; i <= k; ++i) str[i] = get();
		node *x = range(t, t);
		build(1, k, x->s[1], x);
		splay(x->s[1]);
	}
	
	void remove(int k) {
		node *x = range(t+1, t+k);
		x->p->s[x->pos()] = emt;
		splay(x->p);
	}
	
	void output(int k) {
		node *x = range(t+1, t+k);
		print(x);
		printf("\n");
	}
} s;

int main() {
	m = read(), t = 2, s.init();
	while(m--) {
		scanf("%s", op);
		if(*op == 'P') --t;
		if(*op == 'N') ++t;
		if(*op == 'M') t = read()+2;
		if(*op == 'I') s.insert(read());
		if(*op == 'D') s.remove(read());
		if(*op == 'G') s.output(read());
	}
	return 0;
}
