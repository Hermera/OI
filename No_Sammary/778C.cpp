#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3e5+5;
int n, d, top, ans, pos;
int siz[maxn], son[maxn], dep[maxn], ret[maxn];

char ch[4];
int g[maxn][26];
void add(int x, int y) {
	scanf("%s", ch);
	g[y][*ch-'a'] = x;
}

#define fir first
#define sec second
typedef pair<int, int> pi;
pi q[maxn];

int calc;
bool cmax(int &x, int y) { return x < y ? x = y, 1 : 0; }
void merge(int x, int y) {
	++calc;
	for(int i = 0; i < 26; ++i) if(g[y][i]) 
		if(g[x][i]) merge(g[x][i], g[y][i]);
		else g[x][i] = g[y][i], q[++top] = pi(x, i);
}

void dfs(int x) {
	siz[x] = 1, cmax(d, dep[x]);
	for(int v, i = 0; i < 26; ++i)
		if((v = g[x][i])) {
			dep[v] = dep[x]+1;
			dfs(v), siz[x] += siz[v];
			if(siz[v] > siz[son[x]]) son[x] = v;
		}
		
	calc = bool(son[x]);
	for(int v, i = 0; i < 26; ++i)
		if((v = g[x][i])) 
			if(v != son[x]) merge(son[x], v);
	ret[dep[x]] += calc;
	for(; top; --top) g[q[top].fir][q[top].sec] = 0;
}


int main() {
	freopen("778C.in", "r", stdin);

	n = read(), dep[1] = 1;
	for(int i = 2; i <= n; ++i) add(read(), read());
	
	dfs(1);
	for(int i = 1; i <= d; ++i)
		if(cmax(ans, ret[i])) pos = i;
	printf("%d\n%d\n", n - ans, pos);
	return 0;
}
