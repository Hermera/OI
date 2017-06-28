#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 105;
const int maxm = 1005;
const int mod = 31011;

struct Edge {
	int x, y, w;
	bool operator <(const Edge &b) const {
		return w < b.w;
	}
} e[maxm];

int fa[maxn], pa[maxn], ok[maxm];
vector <Edge> g[maxn];
int getfa(int x) { return fa[x] == x ? x : fa[x] = getfa(fa[x]); }

namespace matrix_tree {
	int a[maxn][maxn];
	int id[maxn], n;

	int determinant(int a[][maxn]) {
		int ret = 1;
		for(int i = 1; i <= n; ++i) {
			for(int j = i+1; j <= n; ++j) 
				while(a[j][i]) {
					int t = a[i][i] / a[j][i];
					for(int k = i; k <= n; ++k)
						(a[i][k] -= a[j][k]*t) %= mod;
					for(int k = i; k <= n; ++k)
						swap(a[i][k], a[j][k]);
					ret = -ret;
				}
			(ret *= a[i][i]) %= mod;
		}
		return ret;
	}

	int getid(int x) {
		x = pa[x];
		if(id[x]) return id[x];
		return id[x] = ++n;
	}
	
	int count(vector <Edge> &g) {
		n = 0;
		memset(id, 0, sizeof(id));
		memset(a , 0, sizeof(a ));
		for(int i = 0; i < g.size(); ++i) {
			int x = getid(g[i].x), y = getid(g[i].y);
			++a[x][x], ++a[y][y];
			--a[x][y], --a[y][x];
		}
		return --n, determinant(a);
	}
}

int n, m;
bool connect() {
	for(int i = 1; i <= n; ++i)
		if(getfa(i) != getfa(1)) return 0;
	return 1;
}

int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= m; ++i)
		scanf("%d%d%d", &e[i].x, &e[i].y, &e[i].w);
	
	int ans = 1, h = 1;
	sort(e + 1, e + 1 + m);
	for(int i = 1; i <= n; ++i) fa[i] = i;
	for(int t = 1; t <= m; ++t) 
		if(e[t+1].w != e[h].w) {
			for(int j = 1; j <= n; ++j) g[j].clear(), pa[j] = getfa(j);
			for(int j = h; j <= t; ++j) ok[j] = (getfa(e[j].x) != getfa(e[j].y));
			for(int j = h; j <= t; ++j) fa[getfa(e[j].x)] = getfa(e[j].y);
			for(int j = h; j <= t; ++j) if(ok[j]) g[getfa(e[j].x)].push_back(e[j]);
			for(int j = 1; j <= n; ++j) if(!g[j].empty()) 
				(ans *= matrix_tree::count(g[j])) %= mod;
			h = t+1;
		}

	printf("%d\n", connect() ? ans : 0);
	return 0;
}
