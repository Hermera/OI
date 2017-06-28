#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1005, maxs = 22;
int n, m, t, g[maxn][maxs], f[1<<maxs];
char s[maxn];

int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d%s", &n, s+1);
		m = strlen(s+1);		
		if(n > 21) {
			printf("NO\n");
			continue;
		}
		
		for(int i = 0; i < n; ++i) g[m][i] = g[m+1][i] = m+1;
		for(int i = m; i; --i) {
			for(int k = 0; k < n; ++k) g[i-1][k] = g[i][k];
			g[i-1][s[i]-'a'] = i;
		}
		
		memset(f, 0, sizeof(f));
		for(int i = 1; i < (1<<n); ++i) 
		for(int j = 0; j < n; ++j) if(i&(1<<j))
			f[i] = max(f[i], g[f[i^(1<<j)]][j]);
		printf("%s\n", f[(1<<n)-1] <= m ? "YES" : "NO");
	}
	return 0;
}
