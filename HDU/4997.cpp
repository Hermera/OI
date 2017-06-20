#include <cstdio>
#include <cstring>
#define b(x) (1LL<<(x))
using namespace std;
typedef long long ll;

const int maxn = 11;
const int maxs = (1<<10)+5;
const int mod = 1e9+7;

int n, m, cas, cnt[maxs][maxs];
ll ncc[maxs], bcc[maxs], ex[maxs][maxs];
bool a[maxn][maxn];

int main() {
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d%d", &n, &m);
		memset(a, 1, sizeof a);
		memset(ex, 0, sizeof ex);
		memset(cnt, 0, sizeof cnt);
		
		for(int i = 0; i < n; ++i) a[i][i] = 0;
		for(int x, y; m--; ) 
			scanf("%d%d", &x, &y), --x, --y,
			a[x][y] = a[y][x] = 0;
	
		int sta = b(n);
		for(int s = 0; s < sta; ++s)
			for(int i = 0; i < n; ++i) if(s&b(i))
			for(int j = i; j < n; ++j) if(s&b(j))
				cnt[s][s] += a[i][j];
		for(int s = 0; s < sta; ++s)
		for(int t = 0; t < sta; ++t) if(!(s&t)) 
			for(int i = 0; i < n; ++i) if(s&b(i))
			for(int j = 0; j < n; ++j) if(t&b(j))
				cnt[s][t] += a[i][j];
			
		
		ncc[0] = bcc[0] = 1;
		for(int s = 0; s < sta; ++s) {
			ncc[s] = b(cnt[s][s]);
			
			int x = s&-s, fx = s^x;
			for(int t = fx; t; (--t)&= fx)
				ncc[s] -= ncc[s^t]*b(cnt[t][t]);
			
			ex[s][s] = 1;
			for(int t = fx; t; (--t)&= fx) {
				int p = s^t, y = t&-t, fy = t^y;
				for(int q = fy; ; (--q)&= fy) {
					ex[s][p] += ncc[t^q]*cnt[t^q][p]*ex[s^(t^q)][p];
					if(!q) break;
				}
			}
			
			bcc[s] = ncc[s];
			for(int t = fx; t; (--t)&= fx)
				bcc[s] -= bcc[s^t]*ex[s][s^t];
		}
		printf("%lld\n", bcc[sta-1] % mod);
	}
	return 0;
}
