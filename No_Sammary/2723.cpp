#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int maxn = 5005;
inline bool cmin(int &x, int y) { return x > y ? x = y, 1 : 0; }

int n, m, c, cnt, h[maxn];
struct Data { int next, to; } g[maxn<<1];
void add(int x, int y) {
	g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
}


int tim, tot, top;
int dfn[maxn], low[maxn], scc[maxn], stack[maxn];
void tarjan(int x) {
	dfn[x] = low[x] = ++tim;
	stack[++top] = x;
	for(int i = h[x]; i; i = g[i].next) {
		int v = g[i].to;
		if(!dfn[v]) tarjan(v), cmin(low[x], low[v]);
		else if(!scc[v]) cmin(low[x], low[v]);
	}
	if(low[x] == dfn[x]) {
		++tot;
		while(top) {
			int v = stack[top--];
			scc[v] = tot;
			if(v == x) break;
		}
	}
}

#define fir first
#define sec second
typedef pair<int, int> pi;
pi keys[maxn], door[maxn];

bool judge(int l) {
	cnt = top = tim = tot = 0;
	for(int i = 1; i <= c*2; ++i) h[i] = dfn[i] = scc[i] = 0;
	for(int i = 1; i <= n; ++i) 
		add(keys[i].fir, keys[i].sec + c),
		add(keys[i].sec, keys[i].fir + c);
	for(int i = 1; i <= l; ++i)
		add(door[i].fir + c, door[i].sec),
		add(door[i].sec + c, door[i].fir);
	
	for(int i = 1; i <= c*2; ++i)
		if(!dfn[i]) tarjan(i);
	for(int i = 1; i <= c; ++i)
		if(scc[i] == scc[i+c]) return 0;
	return 1;
}

int main() {
	while(scanf("%d%d", &n, &m) != EOF) {
		if(!n && !m) break;
		
		c = n << 1;
		for(int i = 1; i <= n; ++i) keys[i] = pi(read()+1, read()+1);
		for(int i = 1; i <= m; ++i) door[i] = pi(read()+1, read()+1);
		
		int l = 0, r = m, ans = 0;
		while(l <= r) {
			int mid = (l+r)>>1;
			if(judge(mid)) l = mid+1, ans = mid;
			else r = mid-1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
