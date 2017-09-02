#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

ll Sa, Sb, Sc, Sd, mod;
int F(int x) {  
    ll re = Sd, temp = x;  
    re += Sc * temp % mod; (temp *= x) %= mod;  
    re += Sb * temp % mod; (temp *= x) %= mod;  
    re += Sa * temp % mod;  
    return int(re % mod);  
}  

const int N = 5e6+5;
int a[N], n;

int main() {
	freopen("3613.in", "r", stdin);

	scanf("%d%lld%lld%lld%lld%d%lld", &n, &Sa, &Sb, &Sc, &Sd, &a[1], &mod);
	
	int mx = 0, ans = 0;
	for(int i = 2; i <= n; ++i) a[i] = (F(a[i-1]) + F(a[i-2])) % mod;
	for(int i = 1; i <= n; ++i) {
		mx = max(mx, a[i]);
		ans = max(ans, (mx-a[i]+1) >> 1);
	}
	printf("%d\n", ans);
	return 0;
}
