#include <cstdio>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 1e6+5;
int N, cnt, lack, back, q[maxn], head[maxn], son[maxn];
struct Data { int next, to; } data[maxn];
bool need[maxn], leaf[maxn], co[maxn];

void add(int x, int y) {
	data[++cnt] = (Data){ head[x], y }; head[x] = cnt;
}

void dfs(int x, int fa) {
	need[x] |= !co[x];
	leaf[x] = true;
	for(int i = head[x]; i; i = data[i].next) 
	if(data[i].to != fa) {
		Data &e = data[i];
		dfs(e.to, x);
		need[x] |= need[e.to];
		leaf[x] = false;
		son[x] = e.to;
	}
}

void modify(int x) {
	co[x] ^= 1;
	if(!co[x]) ++lack;
	else --lack;
}

void solve(int x, int fa) {
	q[++back] = x;
	modify(x);
	if(leaf[x]) return;

	for(int i = head[x]; i; i = data[i].next) 
	if(data[i].to != fa && need[data[i].to]) {
		solve(data[i].to, x);
		if(!lack) return;
		q[++back] = x;
		modify(x);
	}
		
	if(!co[x]) 
		if(x != 1) {
			modify(fa), modify(x);
			q[++back] = fa, q[++back] = x;
		}
		else q[++back] = son[x], q[++back] = x, q[++back] = son[x];
}

int main() {
	freopen("717E.in", "r", stdin);

	N = read();
	for(int i = 1; i <= N; ++i) 
		if(read() > 0) co[i] = true;
		else co[i] = false, ++lack;	
	for(int i = 1, u, v; i < N; ++i) 
		u = read(), v = read(), add(u, v), add(v, u);
	
	if(!lack) return printf("1\n"), 0;
	
	dfs(1, 0);
	modify(1);
	solve(1, 0);
	for(int i = 1; i <= back; ++i) printf("%d ", q[i]);
	printf("\n");
	return 0;
}
