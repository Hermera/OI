#include <cstdio>
#include <cstring>
#define mset(x) memset(x, 0, sizeof(x))
using namespace std;
typedef long long ll;

const int maxn = 305;
int t, n, m, mod, s[maxn];
ll f[maxn][maxn], c[maxn][maxn];

bool Judge() {
	for(int i = n; i; --i) {
		s[i] += s[i+1];
		if(s[i] > n-i+1) return 0;
	}
	return 1;
}

int main() {
	scanf("%d", &t);
	while(t--) {
		mset(f), mset(s);
		scanf("%d%d%d", &n, &m, &mod);
		for(int i = 1, x, y; i <= m; ++i)
			scanf("%d%d", &x, &y), ++s[y];
		
		if(!Judge()) {
			printf("NO\n");
			continue;
		}
		
		for(int i = 0; i <= n; ++i) c[i][0] = 1;
		for(int i = 1; i <= n; ++i)
		for(int j = 1; j <= i; ++j)
			c[i][j] = (c[i-1][j-1]+c[i-1][j])%mod;
		
		f[n+1][0] = 1;
		for(int i = n; i; --i) 
		for(int j = 0; j <= n-i+1-s[i]; ++j) 
		for(int k = 0; k <= j; ++k)
			(f[i][j] += f[i+1][j-k]*c[j][k])%= mod;
		
		printf("YES %lld\n", f[1][n-m]);
	}
	return 0;
}
