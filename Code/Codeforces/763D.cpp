#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int p = 19;
const int maxn = 2e5+5;
inline bool cmax(int &a, int b) { return a < b ? a = b, 1 : 0; }

int n, root, node, beau;
int siz[maxn], dep[maxn], mx[maxn];
ll w[maxn], c[maxn], pow[maxn];

int h[maxn], cnt;
struct Data { int next, to; } g[maxn<<1];
void add(int x, int y) {
	g[++cnt] = (Data){ h[x], y }; h[x] = cnt;
	g[++cnt] = (Data){ h[y], x }; h[y] = cnt;
}

void getroot(int x, int fa) {
	siz[x] = 1;
	for(int v, i = h[x]; i; i = g[i].next) 
		if((v = g[i].to) != fa) {
			getroot(v, x);
			siz[x] += siz[v];
			cmax(mx[x], siz[v]);
		}
	cmax(mx[x], n - siz[x]);
	if(mx[x] < mx[root]) root = x;
}

bool cmp(int x, int y) { return w[x] < w[y]; }
void gethash(int x, int fa) {
	vector <int> son;
	siz[x] = w[x] = 1;
	for(int v, i = h[x]; i; i = g[i].next) 
		if((v = g[i].to) != fa) {
			dep[v] = dep[x]+1, gethash(v, x);
			siz[x] += siz[v], son.push_back(v);
		}
	sort(son.begin(), son.end(), cmp);
	for(int i = 0; i < son.size(); ++i)
		(w[x] *= pow[siz[son[i]] << 1]) += w[son[i]];
	w[x] *= p;
}

int sum[maxn], tot;
void insert(int x) { if(!(sum[x]++)) ++tot; }
void remove(int x) { if(!(--sum[x])) --tot; }

void dfs(int x, int fa) {
	remove(w[x]);
	if(cmax(beau, tot + dep[x])) node = x;
	for(int i = h[x]; i; i = g[i].next)
		if(g[i].to != fa) dfs(g[i].to, x);
	insert(w[x]);
}

int main() {
	n = read();
	for(int i = 2; i <= n; ++i) add(read(), read());
	mx[0] = n, getroot(1, 0);
	
	pow[0] = 1;
	dep[root] = 1;
	for(int i = 1; i < maxn; ++i) pow[i] = pow[i-1] * p;
	gethash(root, 0);
	
	for(int i = 1; i <= n; ++i) c[i] = w[i];
	sort(c + 1, c + 1 + n);
	for(int i = 1; i <= n; ++i) w[i] = lower_bound(c+1, c+1+n, w[i]) - c;
	for(int i = 1; i <= n; ++i)
		if(i != root) insert(w[i]);
	dfs(root, 0);
	
	printf("%d\n", node);
	return 0;
}
