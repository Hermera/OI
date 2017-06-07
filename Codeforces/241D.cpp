#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;

const int maxn = 5e4+5;
int N, P, M, tot, a[maxn], ans[maxn], pos[maxn], dp[32][maxn][32];

void print(int p) {
	printf("Yes\n");
	int x = 0, y = 0;
	for(int i = p; i; --i) {
		if(dp[i][x][y] > 0) {
			ans[++tot] = pos[i];
			x = dp[i][x][y]-1;
			y ^= a[i];
		}
		if(!x && !y) break;
	}
	printf("%d\n", tot);
	for(int i = tot; i; --i) printf("%d ", ans[i]);
	printf("\n");
}

void update(int &x, int y) { x = max(x, y); }
int main() {
	scanf("%d%d", &N, &P);
	for(int i = 1, x; i <= N; ++i) {
		scanf("%d", &x);
		if(x < 32) a[++M] = x, pos[M] = i;
	}
	
	memset(dp, -1, sizeof(dp));	
	dp[0][0][0] = 0;
	for(int i = 1; i <= M; ++i)
	for(int j = 0; j < P; ++j)
	for(int k = 0; k < 32; ++k) if(~dp[i-1][j][k]) {
		int len = a[i] < 10 ? 10 : 100;
		int nj = (j*len+a[i])%P;
		int nk = k^a[i];
		
		update(dp[i][j][k], 0);
		update(dp[i][nj][nk], j+1);
		if(!nj && !nk) return print(i), 0;
	}
	printf("No\n");
	return 0;
}
