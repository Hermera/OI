#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int maxn = 1e4+5;
const int bin = 1e6+3;

ll pow[maxn];
int a[maxn], n, cas;

struct BIT {
	ll t[maxn];
	void clear() { memset(t, 0, sizeof(t)); }
	void insert(int x, ll v) {
		for(; x <= n; x += x&-x) t[x] += v;
	}
	
	ll query(int x) {
		ll ret = 0;
		for(; x; x -= x&-x) ret += t[x];
		return ret;
	}
} obv, rev;


bool solve() {
	n = read(), pow[0] = 1;
	for(int i = 1; i <= n; ++i) pow[i] = pow[i-1] * bin;
	for(int i = 1; i <= n; ++i) a[i] = read();
	
	obv.clear();
	rev.clear();
	for(int i = 1; i <= n; ++i) {
		int x = a[i], l = min(x, n-x+1);
		obv.insert(x, pow[x]);
		rev.insert(n-x+1, pow[n-x+1]);

		ll pre = obv.query(x) - obv.query(x-l)*pow[l];
		ll suf = rev.query(n-x+1) - rev.query(n-(x+l)-1)*pow[l];
		if(pre != suf) return 1;
	}
	return 0;
}

int main() {
	freopen("2124.in", "r", stdin);

	cas = read();
	while(cas--) printf("%c\n", solve() ? 'Y' : 'N');
	return 0;
}
