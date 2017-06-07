#include <cstdio>
using namespace std;
typedef long long ll;
const int maxn = 1e6+5, mod = 1e9+7;
int N, K, W[maxn], B[maxn];
ll f[maxn][3][2], tmp;
char s[maxn];

int main() {
	scanf("%d%d%s", &N, &K, s+1);	
	for(int i = 1; i <= N; ++i) {
		W[i] = W[i-1];
		B[i] = B[i-1];
		if(s[i] == 'W') ++W[i];
		if(s[i] == 'B') ++B[i];
	}
	
	f[0][0][1] = 1;
	for(int i = 1; i <= N; ++i) {
		if(s[i] != 'W') {
			if(i >= K && s[i-K] != 'B' && W[i] == W[i-K]) tmp = f[i-K][0][1];
			else tmp = 0;	
			f[i][0][0] = (f[i-1][0][0]+f[i-1][0][1]-tmp)%mod;
			f[i][1][0] = (f[i-1][1][0]+f[i-1][1][1]+tmp)%mod;
			f[i][2][0] = (f[i-1][2][0]+f[i-1][2][1])%mod;
		}
		
		if(s[i] != 'B') {
			if(i >= K && s[i-K] != 'W' && B[i] == B[i-K]) tmp = f[i-K][1][0];
			else tmp = 0;
			f[i][0][1] = (f[i-1][0][0]+f[i-1][0][1])%mod;
			f[i][1][1] = (f[i-1][1][0]+f[i-1][1][1]-tmp)%mod;
			f[i][2][1] = (f[i-1][2][0]+f[i-1][2][1]+tmp)%mod;
		}
	}
	
	printf("%lld\n", ((f[N][2][0]+f[N][2][1])%mod+mod)%mod);
	return 0;
}
