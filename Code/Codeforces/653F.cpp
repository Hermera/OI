#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5, maxl = 20;
int N, top, st[maxn], fa[maxn][maxl];
char s[maxn];

struct Node {
	int len, pos;
	Node *p, *s[2];
	Node(int len = 0, int pos = 0): len(len), p(0), pos(pos) 
		{ memset(s, 0, sizeof(s)); }
	int calc() {
		int ret = 0, x = pos, l = len;
		for(int i = maxl-1; ~i; --i) 
			if(fa[x][i] && x-fa[x][i]+1 <= l) 
				ret += 1<<i, l -= x-fa[x][i]+1, x = fa[x][i]-1;
		return ret;
	}
};

struct SAM {
	int cnt;
	Node *root, *last, gen[maxn];
	void init() {
		cnt = 0;
		root = last = &gen[cnt++];
		*root = Node();
	}
	
	void extend(int w, int pos) {
		Node *fa = last, *lst = &gen[cnt++]; *lst = Node(fa->len+1, pos);
		while(fa && !fa->s[w]) fa->s[w] = lst, fa = fa->p;
		if(!fa) lst->p = root;
		else {
			Node *now = fa->s[w];
			if(fa->len+1 == now->len) lst->p = now;
			else {
				Node *np = &gen[cnt++]; *np = *now;
				np->len = fa->len+1;
				lst->p = now->p = np;
				while(fa && fa->s[w] == now) fa->s[w] = np, fa = fa->p;
			}
		}
		last = lst;
	}
	
	ll solve() {
		ll ans = 0;
		for(Node *now = gen+1; now != gen+cnt; ++now)
			ans += now->calc() - now->p->calc();
		return ans;
	}
} G;

int main() {
	freopen("653F.in", "r", stdin);

	G.init();
	scanf("%d%s", &N, s+1);
	for(int i = 1; i <= N; ++i) G.extend(s[i] == ')', i);
	for(int i = 1; i <= N; ++i) 
		if(s[i] == '(') st[++top] = i;
		else if(top) {
			fa[i][0] = st[top--];
			for(int k = 1; k < maxl && fa[i][k-1]; ++k)
				fa[i][k] = fa[ fa[i][k-1]-1 ][k-1];
		}
	
	printf("%lld\n", G.solve());
	return 0;
}
