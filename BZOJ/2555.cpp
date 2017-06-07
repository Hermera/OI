#include <cstdio>
#include <cstring>
#include <string>
using namespace std;

const int maxn = 3e6+5, size = 26;
string chars;
int mask, cnt;
char s[maxn], op[10];

string gets(int mask)
{
	scanf("%s", s);
	chars = s;
	int len = chars.size();
	for(int i = 0; i < len; ++i)
	{
		mask = (mask*131+i)%chars.length();
		char t = chars[i];
		chars[i] = chars[mask], chars[mask] = t;
	}
	return chars;
}

struct Node;
void add(Node *x, int val);
struct Node
{
	int len, right, tag;
	Node *s[2], *p, *fa, *go[size];
	Node(int len = 0): len(len) 
	{ s[0] = s[1] = p = fa = 0; tag = right = 0; memset(go, 0, sizeof(go)); }
	void sets(Node *x, int d) { s[d] = x; if(x) x->fa = this; }
	bool isroot() { return (!fa || this != fa->s[0] && this != fa->s[1]); }
	bool pos() { return this == fa->s[1]; }
	void pushdown() { if(tag) add(s[0], tag), add(s[1], tag), tag = 0; }
} *root, *last, *st[maxn], gen[maxn];

void add(Node *x, int val) { if(x) x->right += val, x->tag += val; }

void rotate(Node *x)
{
	Node *y = x->fa, *z = y->fa;
	y->pushdown(), x->pushdown();
	int d = x->pos();
	y->sets(x->s[!d], d);
	if(y->isroot()) x->fa = y->fa;
	else z->sets(x, y->pos());
	x->sets(y, !d);
}

void splay(Node *x)
{
	int top = 0; st[++top] = x;
	for(Node *i = x; !i->isroot(); i = i->fa) st[++top] = i->fa;
	for(int i = top; i; --i) st[i]->pushdown();
	for(Node *y; !x->isroot(); rotate(x))
		if(!(y = x->fa)->isroot()) 
			rotate(x->pos() == y->pos() ? y : x);
}

void access(Node *x)
{
	for(Node *y = 0; x; y = x, x = x->fa)
		splay(x), x->s[1] = y;
}

void link(Node *x, Node *f) { x->fa = f, access(f), splay(f), add(f, x->right); }

void cut(Node *x) 
{ access(x); splay(x); add(x->s[0], -x->right); x->s[0]->fa = 0, x->s[0] = 0; }

void extend(int w)
{
	Node *fa = last, *p = &gen[++cnt]; *p = Node(fa->len+1);
	p->right = 1;
	while(fa && !fa->go[w]) fa->go[w] = p, fa = fa->p;
	if(!fa) p->p = root, link(p, root);
	else
	{
		Node *now = fa->go[w];
		if(now->len == fa->len+1) p->p = now, link(p, now);
		else
		{
			Node *newpo = &gen[++cnt]; *newpo = Node(fa->len+1);
			memcpy(newpo->go, now->go, sizeof(newpo->go));
			newpo->p = now->p, link(newpo, now->p);
			cut(now);
			now->p = p->p = newpo, link(now, newpo), link(p, newpo);
			while(fa && fa->go[w] == now) fa->go[w] = newpo, fa = fa->p;
		}
	}
	last = p;
}

void insert(string a)
{
	int len = a.size();
	for(int i = 0; i < len; ++i) extend(a[i]-'A');
}

int query(string a)
{
	int len = a.size();
	Node *now = root;
	for(int i = 0; i < len; ++i)
		if(!(now = now->go[a[i]-'A'])) return 0;
	splay(now);
	mask ^= now->right;
	return now->right;
	
}

int main()
{
	freopen("data.in", "r", stdin);

	int T;
	scanf("%d%s", &T, s);
	chars = s;
	root = last = &gen[++cnt];
	*root = Node(); 
	insert(chars);
	while(T--)
	{
		scanf("%s", op);
		if(*op == 'A') insert(gets(mask));
		else printf("%d\n", query(gets(mask)));
	}
	return 0;
}
