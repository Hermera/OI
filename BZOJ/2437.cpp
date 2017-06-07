#include <cstdio>
#include <cstring>
#define mset(x) memset(x, 0, sizeof(x))
using namespace std;

const int maxt = 2005;
int cnt, h[maxt], mat[maxt];
bool vis[maxt], del[maxt], win[maxt];
struct Data { int next, to; } g[maxt<<2];
void add(int x, int y) {
	g[++cnt] = (Data){ h[x], y }; h[x] = cnt; 
}

bool dfs(int x) {
	if(del[x]) return 0;
	for(int i = h[x]; i; i = g[i].next) {
		Data &e = g[i];
		if(!vis[e.to] && !del[e.to]) {
			vis[e.to] = 1;
			if(!mat[e.to] || dfs(mat[e.to])) {
				mat[x] = e.to, mat[e.to] = x;
				return 1;
			}
		}
	}
	return 0;
}


const int maxn = 55;
const int fx[] = { 1, -1, 0, 0 };
const int fy[] = { 0, 0, 1, -1 };
int n, m, t, k, r, c, map[maxn][maxn], id[maxn][maxn];
char s[maxn];

int col(int x, int y) { return (x+y)&1; }
int idx(char ch) {
	if(ch == 'X') return 1;
	if(ch == 'O') return 0;
	return 2;
}


int main() {
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) {
		scanf("%s", s+1);
		for(int j = 1; j <= m; ++j) {
			map[i][j] = idx(s[j]);
			if(map[i][j] == 2) r = i, c = j;
		}
	}
	
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
		if((col(i, j) == col(r, c)) == (bool)map[i][j])
			id[i][j] = ++t;
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j) if(id[i][j]) 
		for(int d = 0; d < 4; ++d) if(id[i+fx[d]][j+fy[d]])
			add(id[i][j], id[i+fx[d]][j+fy[d]]);
	for(int i = 1; i <= t; ++i) 
		if(!mat[i]) mset(vis), dfs(i);	
	
	
	scanf("%d", &k), k <<= 1;
	for(int i = 1; i <= k; ++i) {
		int o1 = id[r][c], o2 = mat[o1];
		del[o1] = 1;
		if(mat[o1]) {
			mat[o1] = mat[o2] = 0;
			mset(vis), win[i] = !dfs(o2);
		} else win[i] = 0;
		scanf("%d%d", &r, &c);
	}
	
	int ans = 0;
	for(int i = 1; i <= k; i += 2)
		if(win[i] && win[i+1]) ++ans;
	printf("%d\n", ans);
	for(int i = 1; i <= k; i += 2) 
		if(win[i] && win[i+1]) printf("%d\n", (i>>1)+1);
	return 0;
}	
