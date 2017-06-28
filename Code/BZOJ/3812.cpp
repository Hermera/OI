#include <cstdio>
using namespace std;

const int maxn = (1<<15)+5, Mod = 1e9+7;
int N, M, d[maxn], in[maxn], out[maxn];
long long f[maxn], g[maxn], h[maxn], pow[maxn], w[maxn];

int main() {
	scanf("%d%d", &N, &M);
	
	pow[0] = 1;
	for(int i = 1; i < (1<<N); ++i) d[i] = d[i>>1]+(i&1);
	for(int i = 1; i <= M; ++i) pow[i] = (pow[i-1]<<1)%Mod;
	
	for(int i = 1, x, y; i <= M; ++i) {
		scanf("%d%d", &x, &y); 
		--x, --y;
		out[1<<x] |= (1<<y);
		in[1<<y] |= (1<<x);
	}
	
	for(int i = 1; i < (1<<N); ++i) {
		int x = i&-i, y = i^x;
		h[i] = h[y] + d[in[x]&y] + d[out[x]&y];
		for(int j = y; j; (--j)&= y) 
			(g[i] -= f[i^j]*g[j]%Mod)%= Mod;
		
		f[i] = pow[h[i]];
		for(int j = i; j; (--j)&= i) {
			if(j == i) w[j] = 0;
			else {
				int t = (i^j)&-(i^j);
				w[j] = w[j^t] - d[(i^j)&out[t]] + d[j&in[t]];
			}
			(f[i] -= pow[ h[i^j]+w[j] ]*g[j]%Mod)%= Mod;
		}
		
		(g[i] += f[i])%= Mod;
	}
	
	printf("%lld\n", (f[(1<<N)-1]+Mod)%Mod);
	return 0;
}
