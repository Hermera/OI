#include <cstdio>
#include <queue>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, maxm = 1e6+5, maxl = 20;
int N, dfn[maxn];
vector <int> eat[maxn];

struct Data { int next, to; };
struct Graph {
	int head[maxn], deg[maxn], cnt, tot;
	Data data[maxm];
	void add(int x, int y) {
		data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
		++deg[y];
	}
	
	void Topsort() {
		queue <int> q;
		for(int i = 1; i <= N; ++i) if(!deg[i]) dfn[++tot] = i, q.push(i);
		while(!q.empty()) {
			int v = q.front(); q.pop();
			for(int i = head[v]; i; i = data[i].next) {
				Data &e = data[i];
				if(!(--deg[e.to])) dfn[++tot] = e.to, q.push(e.to);
			}
		}
	}
} G;

struct Tree {
	int head[maxn], deep[maxn], size[maxn], fa[maxn][maxl], cnt, tot;
	Data data[maxn<<1];
	void add(int x, int y) {
		data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
		fa[y][0] = x, deep[y] = deep[x]+1;		
		for(int j = 1; j < maxl; ++j)
			fa[y][j] = fa[fa[y][j-1]][j-1];
	}
	
	int LCA(int x, int y) {
		if(deep[x] < deep[y]) swap(x, y);
		int d = deep[x]-deep[y];
		for(int i = 0; i < maxl; ++i)
			if(d&(1<<i)) x = fa[x][i];
		if(x == y) return x;
		for(int i = maxl-1; ~i; --i)
			if(fa[x][i] != fa[y][i])
				x = fa[x][i], y = fa[y][i];
		return fa[x][0];
	}
	
	void dfs(int x) {
		size[x] = 1;
		for(int i = head[x]; i; i = data[i].next) {
			Data &e = data[i];
			dfs(e.to);
			size[x] += size[e.to];
		}
	}
} T;

int main() {
	freopen("catas.in", "r", stdin);
	freopen("catas.out", "w", stdout);

	N = read();
	for(int i = 1, a; i <= N; ++i) {
		while(a = read()) {
			eat[i].push_back(a);
			G.add(a, i);
		}
	}
	
	G.Topsort();
	for(int i = 1; i <= N; ++i) {
		int x = dfn[i], tar = 0;
		if(eat[x].size()) {
			tar = eat[x][0];
			for(int j = 1; j < eat[x].size(); ++j)
				tar = T.LCA(tar, eat[x][j]);
		}		
		T.add(tar, x);
	}
	
	T.dfs(0);
	for(int i = 1; i <= N; ++i) printf("%d\n", T.size[i]-1);
	return 0;
}	
	
