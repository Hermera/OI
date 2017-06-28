#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
const int p[] = { 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 
	71, 73, 79, 83, 89, 97 };
const int maxn = 3e6+5;
int N, L, R, P, a[maxn], dp[maxn];
bool ok[maxn];

void dfs(int now, int i) {
	a[N++] = now;
	for (; p[i]; ++i) {
		if (1LL*now*p[i] > R) break;
		dfs(now*p[i], i);
	}
}
int main() {
	scanf("%d%d%d", &L, &R, &P);
	
	dfs(1, 0);
	sort(a, a+N);
	memset(dp, 63, sizeof(dp));
	dp[0] = 0, ok[0] = true;
	
	for(int i = 2; i <= P; ++i) {
		int now = 0;
		for(int j = 0; j < N; ++j) {
			while(now < N && a[now] < a[j]*i) ++now;
			if(now == N) break;
			if(a[now] == a[j]*i) {
				dp[now] = min(dp[now], dp[j]+1);
				if(dp[now]+i <= P) ok[now] = true;
			}
		}
	}
	
	int ans = 0;
	for(int i = 0; i < N; ++i) if(a[i] >= L && ok[i]) ++ans;
	printf("%d\n", ans);
	return 0;
}
	
