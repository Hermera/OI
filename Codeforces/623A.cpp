#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1005;

int N, M, root, cnt, head[maxn], deg[maxn], c[maxn];
bool s[maxn][maxn];
struct Data { int next, to; } data[maxn*maxn];

void add(int x, int y) { data[++cnt] = (Data){ head[x], y }; head[x] = cnt; }

bool color(int x) {
	for(int i = head[x]; i; i = data[i].next) {
		Data &e = data[i];
		if(~c[e.to] && c[e.to] == c[x]) return false;
		if(c[e.to] < 0) {
			c[e.to] = !c[x]; 
			if(!color(e.to)) return false;
		}
	}
	return true;
}

bool Judge() {
	for(int i = 1; i <= N; ++i)
	for(int j = i+1; j <= N; ++j) {
		if(c[i] == c[j] && !s[i][j]) return false;
		if(~c[i] && ~c[j] && c[i] != c[j] && s[i][j]) return false;
	}
	return true;
}

int main() {
	scanf("%d%d", &N, &M);
	for(int i = 1, u, v; i <= M; ++i)
		scanf("%d%d", &u, &v), s[u][v] = s[v][u] = true;
	
	for(int i = 1; i <= N; ++i)
	for(int j = i+1; j <= N; ++j)
	if(!s[i][j]) add(i, j), add(j, i), ++deg[i], ++deg[j];
	
	for(int i = 1; i <= N; ++i) if(deg[i]) { root = i; break; }
	
	memset(c, -1, sizeof(c));
	c[root] = 0;
	if(color(root) && Judge()) {
		printf("Yes\n");
		for(int i = 1; i <= N; ++i)
		if(deg[i]) printf("%c", c[i] ? 'c' : 'a');
		else printf("b");
		printf("\n");
	}
	else printf("No\n");
	
	return 0;
}
