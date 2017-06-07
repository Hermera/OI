#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 2e7+5;
int n, m;
char s[maxn], t[maxn];

int idx(char c) {
	if(c == 'S') return 0;
	if(c == 'N') return 1;
	if(c == 'W') return 2;
	if(c == 'E') return 3;
}

struct SAM {
	struct Node {
		int len;
		Node *p, *s[4];
		Node(int len = 0): len(len), p(0) { memset(s, 0, sizeof(s)); }
	} gen[maxn], *root, *last; 
	int cnt;
	
	void init() { 
		cnt = 0;
		last = root = &gen[++cnt];
		*root = Node();
	}
	
	void extend(int w) {
		Node *fa = last, *lst = &gen[++cnt]; *lst = Node(fa->len+1);
		while(fa && !fa->s[w]) fa->s[w] = lst, fa = fa->p;
		if(!fa) lst->p = root;
		else {
			Node *now = fa->s[w];
			if(now->len == fa->len+1) lst->p = now;
			else {
				Node *np = &gen[++cnt]; *np = Node(fa->len+1);
				memcpy(np->s, now->s, sizeof(now->s));
				np->p = now->p, now->p = lst->p = np;
				while(fa && fa->s[w] == now) fa->s[w] = np, fa = fa->p;
			}
		}
		last = lst;
	}
	
	int query() {
		scanf("%s", t);
		Node *now = root;
		int ret = 0;
		for(int i = 0; t[i]; ++i)
			if(now->s[idx(t[i])]) ++ret, now = now->s[idx(t[i])];
			else break;
		return ret;
	}
} S;
	
int main() {
	freopen("4327.in", "r", stdin);

	S.init();
	scanf("%d%d%s", &n, &m, s);
	for(int i = 0; s[i]; ++i) S.extend(idx(s[i]));
	for(int i = 1; i <= m; ++i) printf("%d\n", S.query());
	return 0;
}
