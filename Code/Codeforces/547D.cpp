#include <cstdio>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e5+10;
int N, cnt, head[maxn], deg[maxn], c[maxn];
struct Data { int next, to, id; } data[maxn<<1];

void add(int x, int y, int i) {
	data[++cnt] = (Data){ head[x], y, i }; head[x] = cnt;
}

void dfs(int x, int k) {
	for(int &i = head[x]; i; i = data[i].next) {
		Data &e = data[i];
		if(~c[e.id]) continue;
		c[e.id] = k;
		dfs(e.to, k^1);
		return;
	}
}

int main() {
	N = read();
	for(int i = 1, x, y; i <= N; ++i) { 
		x = read(), y = read()+maxn/2;
		add(x, y, i), add(y, x, i);
		++deg[x], ++deg[y];
	}
	for(int i = 0; i < maxn; ++i) c[i] = -1;
	for(int i = 0; i < maxn; ++i)
		if(deg[i]&1) dfs(i, 1);
	for(int i = 0; i < maxn; ++i)
		if(deg[i]) dfs(i, 1);
	
	for(int i = 1; i <= N; ++i) printf("%c", c[i] ? 'r' : 'b');
	printf("\n");
	return 0;
}
	
		
