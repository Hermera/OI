#include <cstdio>
using namespace std;

const int maxn = 1e6+5;
int N, P, Q, R, t, pow[maxn], f[maxn], inv[maxn], c[maxn];
bool can1[maxn], can3[maxn];
char a[maxn];

int main() {
	freopen("4277.in", "r", stdin);

	scanf("%d%d%d%d%s", &N, &P, &Q, &R, a+1);
	for(int i = 1; i <= N; ++i) a[i] -= '0';
	
	t = 0;
	for(int i = 1; i <= N; ++i) {
		t = (t*10+a[i])%P;
		if(!t && (i == 1 || a[1])) can1[i] = 1;
	}
	
	t = 0, pow[0] = 1;
	for(int i = 1; i <= N; ++i) pow[i] = pow[i-1]*10%R;
	for(int i = N; i; --i) {
		t = (t+pow[N-i]*a[i])%R;
		if(!t && (i == N || a[i])) can3[i] = 1;
	}
	
	pow[0] = inv[1] = 1;
	for(int i = 1; i <= N; ++i) 
		pow[i] = pow[i-1]*10%Q, f[i] = (f[i-1]*10+a[i])%Q;
	for(int i = 2; i <  Q; ++i) inv[i] = 1LL*(Q-inv[Q%i])*(Q/i)%Q;
	for(int i = 1; i <= N; ++i) f[i] = 1LL*f[i]*inv[pow[i]]%Q;
	
	long long ans = 0;
	for(int i = 2; i < N; ++i) {
		if(can3[i+1]) {
			if(can1[i-1] && !a[i]) ++ans;
			ans += c[f[i]];
		}
		if(can1[i-1] && a[i]) ++c[f[i-1]];
	}
	printf("%lld\n", ans);
	return 0;
}
	
