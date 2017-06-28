#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 4e6+5, size = 10;
int N, C, cnt, tot, c[maxn], deg[maxn], head[maxn];
ll ans;
struct Data { int next, to; } data[maxn];

struct Node
{
	int len;
	Node *p, *go[size];
	Node(int len = 0) : len(len) { p = 0; memset(go, 0, sizeof(go)); }
	int calc() { return len - p->len; }
} *root, gen[maxn];

void add(int x, int y) { data[++cnt] = (Data){head[x], y}; head[x] = cnt; }

Node *extend(Node *last, int w)
{
	Node *fa = last, *p = &gen[++tot]; *p = Node(fa->len+1);
	while(fa && !fa->go[w]) fa->go[w] = p, fa = fa->p;
	if(!fa) p->p = root;
	else
	{
		Node *now = fa->go[w];
		if(now->len == fa->len+1) p->p = now;
		else
		{
			Node *newpo = &gen[++tot]; *newpo = Node(fa->len+1);
			memcpy(newpo->go, now->go, sizeof(now->go));
			ans -= now->calc();
			newpo->p = now->p, now->p = p->p = newpo;
			ans += now->calc(), ans += newpo->calc();
			while(fa && fa->go[w] == now) fa->go[w] = newpo, fa = fa->p;
		}
	}
	ans += p->calc();
	return p;
}

void dfs(Node *par, int x, int fa)
{
	Node *p = extend(par, c[x]);
	for(int i = head[x]; i; i = data[i].next)
		if(data[i].to != fa) dfs(p, data[i].to, x);
}

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), C = read();
	for(int i = 1; i <= N; ++i) c[i] = read();
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), add(u, v), add(v, u), ++deg[u], ++deg[v];
	
	root = &gen[++tot]; *root = Node();
	for(int i = 1; i <= N; ++i)
	if(deg[i] == 1) dfs(root, i, 0);
	
	printf("%lld\n", ans);
	return 0;
}
