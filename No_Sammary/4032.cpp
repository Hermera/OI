#include <cstdio>
#include <cstring>
using namespace std;
#define mset(x, a) memset(x, a, sizeof(x))
#define mcpy(x, y) memcpy(x, y, sizeof(x))


const int maxn = 4050;
const int maxs = 26;

struct node {
	int len;
	node *p, *s[maxs];
	node(int x = 0): len(x), p(0) { mset(s, 0); }
};

struct SuffixAutomation {
	int cnt;
	node gen[maxn], *root, *last;
	node *newnode(int v = 0) {
		node *p = gen + (++cnt);
		return *p = node(v), p;
	}
	
	SuffixAutomation() {
		last = root = newnode();
	}
	
	void extend(int w) {
		node *fa = last, *p = newnode(fa->len+1);
		for(; fa && !fa->s[w]; fa = fa->p) fa->s[w] = p;
		if(!fa) p->p = root;
		else {
			node *now = fa->s[w];
			if(now->len == fa->len+1) p->p = now;
			else {
				node *newpo = newnode(fa->len+1);
				mcpy(newpo->s, now->s);
				newpo->p = now->p, now->p = p->p = newpo;
				for(; fa && fa->s[w] == now; fa = fa->p) fa->s[w] = newpo;
			}
		}
		last = p;
	}
} Astr, Bstr;


struct SequenceAutomation {
	int cnt;
	node gen[maxn], *last[maxs+1], *root;
	node *newnode() { 
		return gen + (++cnt); 
	}
	
	SequenceAutomation() {
		root = last[maxs] = newnode();
	}
	
	void extend(int w) {
		node *p = newnode();
		for(int i = 0; i <= maxs; ++i)
			for(node *o = last[i]; o && !o->s[w]; o = o->p)
				o->s[w] = p;
		p->p = last[w];
		last[w] = p;
	}
} Aseq, Bseq;


struct State {
	node *a, *b;
	int len;
	
	State() {}
	State(node *x, node *y, int l): a(x), b(y), len(l) {}
} q[maxn * maxn];
int vis[maxn][maxn], h, t;

int bfs(node *s1, node *s2) {
	mset(vis, 0);
	h = 1, t = 0, vis[0][0] = 1;
	q[++t] = State(s1, s2, 0);
	while(h <= t) {
		State now = q[h++];
		for(int i = 0; i < maxs; ++i) {
			if(!now.a->s[i]) continue;
			if(!now.b->s[i]) return now.len + 1;
			
			int nx = now.a->s[i] - s1;
			int ny = now.b->s[i] - s2;
			if(!vis[nx][ny]) {
				vis[nx][ny] = 1;
				q[++t] = State(now.a->s[i], now.b->s[i], now.len+1);
			}
		}
	}
	return -1;
}

char str[maxn];
int main() {
	scanf("%s", str);
	for(int i = 0; str[i]; ++i)
		Astr.extend(str[i]-'a'),
		Aseq.extend(str[i]-'a');
	scanf("%s", str);
	for(int i = 0; str[i]; ++i)
		Bstr.extend(str[i]-'a'),
		Bseq.extend(str[i]-'a');
		
	printf("%d\n", bfs(Astr.root, Bstr.root));
	printf("%d\n", bfs(Astr.root, Bseq.root));
	printf("%d\n", bfs(Aseq.root, Bstr.root));
	printf("%d\n", bfs(Aseq.root, Bseq.root));
	return 0;		
}
