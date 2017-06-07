#include <cstdio>
#include <algorithm>
#include <queue>
#define bin(x) (1<<x)
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum*t;
}
const int maxn = 2e5+5, maxl = 18, inf = 1e9;
int N, M, root, dfn, cnt, sum, tot;
int Log[maxn], head[maxn], size[maxn], deep[maxn], son[maxn], fa[maxn], pos[maxn], c[maxn];
int mn[maxl][maxn];
bool vis[maxn];
char op[10];
struct Data { int next, to; } data[maxn];
struct Heap
{
	priority_queue <int> a, b;
	void push(int x) { a.push(x); }
	void erase(int x) { b.push(x); }
	void pop()
	{
		while(!b.empty() && a.top() == b.top()) a.pop(), b.pop();
		a.pop();
	}
	int top()
	{
		while(!b.empty() && a.top() == b.top()) a.pop(), b.pop();
		return a.empty() ? 0 : a.top();
	}
	int size() { return a.size()-b.size(); }
	int ctop()
	{
		if(size() < 2) return 0;
		int x = top(); pop();
		int y = top(); push(x);
		return y;
	}
} A, B[maxn], C[maxn];

void add(int x, int y) { data[++cnt] = (Data) { head[x], y }; head[x] = cnt; }

void dfs(int x, int fa)
{
	mn[0][pos[x] = ++dfn] = deep[x];
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(e.to == fa) continue;
		deep[e.to] = deep[x]+1;
		dfs(e.to, x);
		mn[0][++dfn] = deep[x];
	}
}

void getroot(int x, int fa)
{
	size[x] = 1, son[x] = 0;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(e.to == fa || vis[e.to]) continue;
		getroot(e.to, x);
		size[x] += size[e.to], son[x] = max(son[x], size[e.to]);
	}
	son[x] = max(son[x], sum-size[x]);
	if(son[x] < son[root]) root = x; 
}

void build(int x, int f)
{
	fa[x] = f, vis[x] = true;
	for(int i = head[x]; i; i = data[i].next)
	{
		Data &e = data[i];
		if(vis[e.to]) continue;
		sum = size[e.to], root = 0;
		getroot(e.to, x);
		build(root, x);
	}
}

int lca(int x, int y)
{
	x = pos[x], y = pos[y];
	if(y < x) swap(x, y);
	int t = Log[y-x+1];
	return min(mn[t][x], mn[t][y-bin(t)+1]);
}

int dis(int x, int y) { return deep[x]+deep[y]-(lca(x,y)<<1); }

void off(int u, int v)
{
	if(u == v)
	{
		B[u].push(0);
		if(B[u].size() == 2) A.push(B[u].top());
	}
	
	if(!fa[u]) return;
	int f = fa[u], D = dis(f, v), tmp = C[u].top();
	C[u].push(D);
	if(D > tmp)
	{
		int mx = B[f].top()+B[f].ctop(), size = B[f].size();
		if(tmp) B[f].erase(tmp);
		B[f].push(D);
		int now = B[f].top()+B[f].ctop();
		if(now > mx)
		{
			if(size >= 2) A.erase(mx);
			if(B[f].size() >= 2) A.push(now);
		}
	}
	off(f, v);
}

void on(int u, int v)
{
	if(u == v)
	{
		if(B[u].size() == 2) A.erase(B[u].top());
		B[u].erase(0);
	}
	
	if(!fa[u]) return;
	int f = fa[u], D = dis(f, v), tmp = C[u].top();
	C[u].erase(D);
	if(D == tmp)
	{
		int mx = B[f].top()+B[f].ctop(), size = B[f].size();
		B[f].erase(D);
		if(C[u].top()) B[f].push(C[u].top());
		int now = B[f].top()+B[f].ctop();
		if(now < mx)
		{
			if(size >= 2) A.erase(mx);
			if(B[f].size() >= 2) A.push(now);
		}
	}
	on(f, v);
}

void init()
{
	Log[0] = -1; 
	for(int i = 1; i < maxn; ++i) Log[i] = Log[i>>1]+1;
	
	N = read();
	for(int i = 1, u, v; i < N; ++i)
		u = read(), v = read(), add(u, v), add(v, u);
	
	dfs(1, 0);
	for(int i = 1; i <= Log[dfn]; ++i)
	for(int j = 1; j <= dfn; ++j)
	if(j+bin(i)-1 <= dfn) mn[i][j] = min(mn[i-1][j], mn[i-1][j+bin(i-1)]);
	
	son[0] = inf;
	sum = tot = N;
	getroot(1, 0);
	build(root, 0);
	
	for(int i = 1; i <= N; ++i) C[i].push(0), c[i] = 1;
	for(int i = 1; i <= N; ++i) off(i, i);
	M = read();
}

int main()
{
	freopen("data.in", "r", stdin);
	init();
	while(M--)
	{
		scanf("%s", op);
		if(*op == 'G') printf("%d\n", tot <= 1 ? tot-1 : A.top());
		else
		{
			int x = read();
			if(c[x]) on(x, x), --tot;
			else off(x, x), ++tot;
			c[x] ^= 1;
		}
	}
	return 0;
}
