#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e5+5;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

struct Node
{
    bool rev;
	Node *p, *s[2];
	void init(Node *emt) { s[0] = s[1] = p = emt, rev = false; }
	void sets(Node *x, int d) { (s[d] = x)->p = this; }
	bool pos() { return this == p->s[1]; }
	bool isroot() { return this != p->s[0] && this != p->s[1]; }
	void pushdown() { if(rev) s[0]->rev ^= 1, s[1]->rev ^= 1, swap(s[0], s[1]), rev ^= 1; }
} *emt = new Node(), s[maxn];

void rotate(Node *v)
{
	int d = v->pos(); Node *u = v->p, *f = u->p;
	u->pushdown(), v->pushdown();
	u->sets(v->s[!d], d);
	if(f != emt) f->sets(v, u->pos());
	else v->p = emt;
	v->sets(u, !d);
}

void splay(Node *v)
{
	for(Node *u; !v->isroot(); rotate(v))
		if(!(u = v->p)->isroot()) rotate(u->pos() == v->pos() ? u : v);
}

void access(Node *v)
{
	for(Node *u = emt; v != emt; u = v, v = v->p)
		splay(v), v->s[1] = u;
}

void rever(Node *u) { access(u), splay(u); u->rev ^= 1; }

void Link(Node *u, Node *v) { rever(u); u->p = v; splay(u); }

void Cut(Node *u, Node *v) { rever(u), access(v); splay(v); v->s[0] = u->p = emt; }

Node *getroot(Node *u) 
{
	access(u), splay(u);
	Node *v = u; v->pushdown();
	while(v->s[0] != emt) v = v->s[0], v->pushdown();
	return v;
}

int N, M;
char ch[10];
int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	emt->init(emt);
	for(int i = 1; i <= N; ++i) (s+i)->init(emt);
	for(int i = 1; i <= M; ++i)
	{
		scanf("%s", ch);
		Node *x = s+read(), *y = s+read();
		if(*ch == 'C') Link(x, y);
		if(*ch == 'D') Cut(x, y);
		if(*ch == 'Q') printf("%s\n", getroot(x) == getroot(y) ? "Yes" : "No");
	}
	return 0;
}
