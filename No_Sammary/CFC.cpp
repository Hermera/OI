#include <map>
#include <cstdio>
using namespace std;
typedef unsigned long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int N = 1e6+5;
const int B = 113;
const int mod = 1e9+7;

int n, m;
ll fac[N], pow[N], val[N];

map <ll, int> sum;
map <ll, int>:: iterator it;

int main() {
	n = read(), m = read();
	pow[0] = fac[0] = 1;
	for(int i = 1; i <= n; ++i) pow[i] = pow[i-1] * B;
	for(int i = 1; i <= n; ++i) 
		for(int j = read(); j--; )
			val[read()] += pow[i];
	
	ll ans = 1;
	for(int i = 1; i <= m; ++i) fac[i] = fac[i-1] * i % mod;
	for(int i = 1; i <= m; ++i) ++sum[val[i]];
	for(it = sum.begin(); it != sum.end(); ++it)
		(ans *= fac[it->second]) %= mod;
	printf("%lld\n", ans);
	return 0;
}
