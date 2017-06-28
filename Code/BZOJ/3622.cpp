#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 2005, Mod = 1e9+9;
int N, K, a[maxn], b[maxn], p[maxn];
long long c[maxn][maxn], f[maxn][maxn], fac[maxn], g[maxn];

int main() {
	freopen("3622.in", "r", stdin);

	scanf("%d%d", &N, &K);
	for(int i = 1; i <= N; ++i) scanf("%d", a+i);
	for(int i = 1; i <= N; ++i) scanf("%d", b+i);
	
	if((N-K)&1) return printf("0\n"), 0;
	K = (N+K)>>1;
	
	fac[0] = 1;
	for(int i = 1; i <= N; ++i) fac[i] = fac[i-1]*i%Mod;
	for(int i = 0; i <= N; ++i) c[i][0] = 1;
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= i; ++j)
		c[i][j] = (c[i-1][j]+c[i-1][j-1])%Mod;
	
	sort(a+1, a+1+N);
	sort(b+1, b+1+N);
	for(int i = 1; i <= N; ++i) {
		p[i] = p[i-1];
		while(a[i] > b[p[i]+1] && p[i] < N) ++p[i];
	}
	
	f[0][0] = 1;
	for(int i = 1; i <= N; ++i)
	for(int j = 0; j <= i; ++j) {
		f[i][j] = f[i-1][j];
		if(j && p[i]-j+1 > 0)
			(f[i][j] += (f[i-1][j-1]*(p[i]-j+1))%Mod)%= Mod;
	}
	
	for(int i = N; i; --i) {
		g[i] = f[N][i]*fac[N-i]%Mod;
		for(int j = i+1; j <= N; ++j)
			(g[i] -= c[j][i]*g[j]%Mod)%= Mod;
	}
	
	printf("%lld\n", (g[K]+Mod)%Mod);
	return 0;
}
