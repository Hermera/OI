#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 4e6+5, size = 26;
char s[maxn], t[maxn];

struct Node {
	int len, vis, right;
	Node *p, *s[size];
	Node(int len = 0) : p(0), len(len) { memset(s, 0, sizeof(s)); }
} *root, *last, *top[maxn], gen[maxn];
int N, M, cnt, c[maxn];

void extend(int w) {
	Node *fa = last, *p = &gen[++cnt]; *p = Node(fa->len+1);
	while(fa && !fa->s[w]) fa->s[w] = p, fa = fa->p;
	if(!fa) p->p = root;
	else {
		Node *now = fa->s[w];
		if(fa->len+1 == now->len) p->p = now;
		else {
			Node *newpo = &gen[++cnt]; *newpo = Node(fa->len+1);
			memcpy(newpo->s, now->s, sizeof(now->s));
			newpo->p = now->p;
			p->p = now->p = newpo;
			while(fa && fa->s[w] == now) fa->s[w] = newpo, fa = fa->p;
		}
	}
	last = p;
}

int solve(int R) {
	scanf("%s", t);
	int ans = 0, len = 0, K = strlen(t);
	Node *now = root;
	for(int i = K; i < (K<<1); ++i) t[i] = t[i-K];
	for(int i = 0; i < (K<<1); ++i) {
		int w = t[i]-'a';
		while(now && !now->s[w]) {
			now = now->p;
			if(now) len = now->len;
			else len = 0;
		}
		if(now) now = now->s[w], ++len;
		else now = root, len = 0;
		
		if(len >= K) {
			while(now->p->len >= K) now = now->p, len = now->len;
			if(now->vis != R) now->vis = R, ans += now->right;
		}
	}
	return ans;
}

int main() {
	last = root = &gen[++cnt]; *root = Node();
	scanf("%s%d", s, &M);
	int N = strlen(s);
	for(int i = 0; s[i]; ++i) extend(s[i]-'a');
	    
    Node *now = root;
    for(int i = 0; s[i]; ++i) now = now->s[s[i]-'a'], ++now->right;
    for(int i = 1; i <= cnt; ++i) ++c[gen[i].len];
    for(int i = 1; i <= N; ++i) c[i] += c[i-1];
    for(int i = 1; i <= cnt; ++i) top[--c[gen[i].len]] = &gen[i];
    for(int i = cnt-1; i; --i) top[i]->p->right += top[i]->right;
	
	for(int i = 1; i <= M; ++i) printf("%d\n", solve(i));
	return 0;
}
