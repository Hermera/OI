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


const int N = 5e5+5;

ll d[N], a[N], g[N];
int n, q;

int main() {
	n = read(), d[0] = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) {
		ll nd = abs(d[i-1] - a[i]);
		if(nd < d[i-1]) d[i] = nd;
		else d[i] = d[i-1];
	}

	g[n+1] = 1;
	for(int i = n; i; --i) {
		ll nd = abs(g[i+1] - a[i]);
		if(nd >= g[i+1]) g[i] = g[i+1];
		else g[i] = g[i+1] + a[i];
	}


	q = read();
	while(q--) {
		int x = read();
		int y = g[x+1] <= d[x-1];
		printf("%s\n", y ? "YES" : "NO");
	}
	return 0;
}