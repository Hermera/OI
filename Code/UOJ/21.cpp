#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int N = 1e6+5;
int n, len, a[N], b[N];
ll ans, sum;


int main() {
	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) ++b[a[i]];
	for(int i = 1; i <= n; ++i) sum += a[i];
	for(int i = 1; i <= n; ++i) len = max(len, a[i]);
	
	for(int i = len; i; --i) b[i] += b[i+1];
	for(int i = 1; i <= len; ++i) {	
		ll tmp = 0;
		for(int j = i; j <= len; j += i) tmp += b[j];
		ans = max(ans, tmp * (i-1));
	}
	
	printf("%lld\n", sum - ans);
	return 0;
}
