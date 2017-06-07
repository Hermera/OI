#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, maxl = 40, inf = 1e9;
int N, x, mn, f[maxn][maxl], v[maxn][maxl];
ll w[maxn][maxl], K, sm;

int main() {
	freopen("702E.in", "r", stdin);

	scanf("%d%lld", &N, &K);
	for(int i = 1; i <= N; ++i) f[i][0] = read()+1;
	for(int i = 1; i <= N; ++i) w[i][0] = v[i][0] = read();
	for(int i = 1; i < maxl; ++i)
	for(int j = 1; j <= N; ++j) {
		f[j][i] = f[ f[j][i-1] ][i-1];
		w[j][i] = w[ f[j][i-1] ][i-1] + w[j][i-1];
		v[j][i] = min(v[ f[j][i-1] ][i-1], v[j][i-1]);
	}
	
	for(int i = 1; i <= N; ++i) {
		x = i, mn = inf, sm = 0;
		for(int j = 0; j < maxl; ++j)
			if(K&(1LL<<j)) {
				sm += w[x][j];
				mn = min(mn, v[x][j]);
				x = f[x][j];
			}
		printf("%lld %d\n", sm, mn);
	}
	return 0;
}
