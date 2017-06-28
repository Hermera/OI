#include <cstdio>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3005;
int N, M;
bool d[maxn][maxn], move[maxn];

int main() {
	freopen("2530.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1, u, v; i <= M; ++i)
		u = read(), v = read(), d[u][v] = d[v][u] = true;
		
	for(int i = 1; i <= N; ++i) if(!move[i])
		for(int j = i+1; j <= N; ++j) if(!move[j] && !d[i][j]) {
			move[i] = move[j] = true;
			break;
		}
		
	for(int i = 1; i <= N; ++i) if(!move[i]) printf("%d ", i);
	return 0;
}
