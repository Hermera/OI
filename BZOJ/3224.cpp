#include <cstdio>
#include <algorithm>
#include <cstring>
#define half (u->s[0]->size+1)
#define mcpy(x, y) memcpy(x, y, sizeof(x))
using namespace std;
const int inf = 1e9;
inline int read()
{
	char ch = getchar(); int sum = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum*t;
}

struct Node
{
	int size, key;
	Node *p, *s[2];
	Node(Node *emt = 0, Node *p = 0, int key = 0) :p(p), key(key) 
		{ s[0] = s[1] = emt, size = 0; }
	void sets(Node *x, int d) { (s[d] = x)->p = this; }
	void update() { size = s[0]->size+s[1]->size+1; }
	bool pos() { return this == p->s[1]; }
} *emt = new Node(), *root = emt, *ms = new Node(0, 0, -inf), *mb = new Node(0, 0, inf);

Node *Min(Node *u, Node *v) { return u->key < v->key ? u : v; }
Node *Max(Node *u, Node *v) { return u->key > v->key ? u : v; }

void rotate(Node *v)
{
	int d = v->pos(); Node *u = v->p, *f = u->p;
	u->sets(v->s[!d], d);
	if(f != emt) f->sets(v, u->pos());
	else v->p = emt;
	v->sets(u, !d), u->update();
}

void splay(Node *v, Node *g = emt)
{
	for(Node *u; (u = v->p) != g; rotate(v))
		if(u->p != g) rotate(u->pos() == v->pos() ? u : v);
	v->update();
	if(g == emt) root = v;
}

void insert(int w, Node *&u = root, Node *f = emt)
{
	if(u == emt) { u = new Node(emt, f, w), u->update(), splay(u); return; }
	if(w < u->key) insert(w, u->s[0], u);
	else insert(w, u->s[1], u);
}

Node *find_value(int w, Node *u = root)
{
	if(u->key == w || u == emt) return u;
	if(u->key < w) return find_value(w, u->s[1]);
	return find_value(w, u->s[0]);
}

Node *find_kth(int k, Node *u = root)
{
	if(k == half) return u;
	if(k < half) return find_kth(k, u->s[0]);
	return find_kth(k-half, u->s[1]);
}

Node *next(Node *u, int d)
{
	u = u->s[d];
	while(u->s[!d] != emt && u != emt) u = u->s[!d];
	return u;
}

Node *prev(int w, Node *u = root)
{
	if(u == emt) return ms;
	if(u->key < w) return Max(u, prev(w, u->s[1]));
	else return prev(w, u->s[0]);
}

Node *sub(int w, Node *u = root)
{
	if(u == emt) return mb;
	if(u->key > w) return Min(u, sub(w, u->s[0]));
	else return sub(w, u->s[1]);
}

int ranking(int w, Node *u = root)
{
	if(u->key == w) return half;
	if(u->key < w) return half+ranking(w, u->s[1]);
	return ranking(w, u->s[0]);
}

void remove(Node *u)
{
	if(u == emt) return;
	splay(u);
	Node *pre = next(u, 0);
	if(pre == emt) root = u->s[1], root->p = emt;
	else 
	{
		splay(pre, root);
		pre->s[1] = root->s[1], pre->s[1]->p = pre, pre->p = emt;
		pre->update(), root = pre;
	}
}

void print(Node *u = root)
{
	if(u == emt) return;
	print(u->s[0]);
	printf("*%d ", u->key);
	print(u->s[1]);
}

int main()
{
	freopen("3224.in", "r", stdin);
	freopen("3224.out", "w", stdout);

	int N = read();
	for(int i = 1; i <= N; ++i)
	{
		int op = read(), x = read();
		if(op == 1) insert(x);
		if(op == 2) remove(find_value(x));
		if(op == 3) printf("%d\n", ranking(x));
		if(op == 4) printf("%d\n", find_kth(x)->key);
		if(op == 5) printf("%d\n", prev(x)->key);
		if(op == 6) printf("%d\n", sub(x)->key);
//		printf("%d: ", i);
//		print();
//		printf("\n");
	}
	return 0;
}
