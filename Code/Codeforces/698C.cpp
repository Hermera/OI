#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 21;
int N, K, T;
double p[maxn], ans[maxn], sum[1<<maxn], dp[1<<maxn];

int main() {
	freopen("698C.in", "r", stdin);	
	
	scanf("%d%d", &N, &K);
	for(int i = 0; i < N; ++i) {
		scanf("%lf", p+i);
		if(p[i]) ++T;
	}
	K = min(K, T);
	
	dp[0] = 1;
	for(int i = 0; i < (1<<N); ++i) {
		for(int j = 0; j < N; ++j) 
			if(i&(1<<j)) {
				sum[i] = sum[i^(1<<j)]+p[j];
				break;
			}	
		
		int tot = 0;
		for(int j = 0; j < N; ++j) 
			if(~i&(1<<j)) dp[i|(1<<j)] += dp[i]*p[j]/(1.0-sum[i]);
			else ++tot;
			
		if(tot == K) 
			for(int j = 0; j < N; ++j)
				if(i&(1<<j)) ans[j] += dp[i];	
	}
	
	for(int i = 0; i < N; ++i) printf("%.8lf ", ans[i]);
	return 0;
}
