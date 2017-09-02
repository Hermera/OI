#include <cstdio>
using namespace std;

const int N = 77;
const int S = (1<<20)+5;
const int mod = 1e9+7;

int n, m, ans, last;
int num[N][N], dp[N][S];
char s[N];

inline int inc(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}

int get(int l, int r) {
	int ret = 0;
	for(int i = l; i <= r; ++i) {
		ret <<= 1;
		if(s[i] == '1') ret |= 1;
		if(ret > 20) return -1;
	}
	return ret;
}


int main() {
	scanf("%d%s", &n, s + 1);
	for(int i = 1; i <= n; ++i)
	for(int j = i; j <= n; ++j)
		num[i][j] = get(i, j);
	
	for(int i = 1; i <= n; ++i) {
		dp[i][0] = 1;
		for(int s = 0; s < (1<<20); ++s) if(dp[i][s])
			for(int j = i; j <= n && (~num[i][j]); ++j)
				if(num[i][j]) inc(dp[j+1][s | (1<<num[i][j]-1)], dp[i][s]);
	}
	
	int ans = 0;
	for(int i = 1; i <= n+1; ++i)
		for(int j = 1; j <= 20; ++j)
			inc(ans, dp[i][(1<<j)-1]);
			
	printf("%d\n", ans);
	return 0;
}
