#include <cstdio>
using namespace std;
const int maxn = 505;
char s[maxn][maxn];
int N, M, K, X, Y;
bool vis[maxn][maxn];

void dfs(int x, int y) {
	if(!x || !y || x > N || y > M || s[x][y] == '#' || vis[x][y]) return;
	vis[x][y] = true;
	dfs(x-1, y), dfs(x+1, y);
	dfs(x, y-1), dfs(x, y+1);
	if(K) s[x][y] = 'X', --K;
}

int main() {
	scanf("%d%d%d", &N, &M, &K);
	for(int i = 1; i <= N; ++i) scanf("%s", s[i]+1);
	
	for(X = 1; X <= N; ++X) {
		for(Y = 1; Y <= M; ++Y)
		if(s[X][Y] == '.') break;
		if(s[X][Y] == '.') break;
	}
	
	dfs(X, Y);
	for(int i = 1; i <= N; ++i) printf("%s\n", s[i]+1);
	return 0;
}
