#include <cstdio>
using namespace std;
typedef long long ll;
typedef long double ld;

const int maxn = 1e6+5;
ll A, B, C, a[maxn], dp[maxn];
int n, q[maxn];

ld f(int x) { return (ld)dp[x] + A*a[x]*a[x] - B*a[x]; }
ld g(int x) { return (ld)2*A*a[x]; }
ld slp(int x, int y) { return (f(x) - f(y))/(g(x) - g(y)); }

int main() {
	scanf("%d", &n);
	scanf("%lld%lld%lld", &A, &B, &C);
	for(int i = 1; i <= n; ++i) scanf("%lld", a+i);
	for(int i = 1; i <= n; ++i) a[i] += a[i-1];
	
	int h = 1, t = 1;
	for(int i = 1; i <= n; ++i) {
		while(h < t && slp(q[h], q[h+1]) < a[i]) ++h;
		dp[i] = dp[q[h]] + A*(a[i]-a[q[h]])*(a[i]-a[q[h]]) + B*(a[i]-a[q[h]]) + C;
		while(h < t && slp(q[t], i) < slp(q[t-1], q[t])) --t;
		q[++t] = i;
	}
	printf("%lld\n", dp[n]);
	return 0;
}
