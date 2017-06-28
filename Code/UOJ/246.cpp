#include <cstdio>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5;
int n, m, k, b, ans;
int a[maxn], f[maxn], g[maxn], last[maxn];

int main() {
	n = read(), m = read(), k = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	
	b = sqrt(m);
	memset(f, 63, sizeof f);
	for(int i = 2; i <= b; ++i)
	for(int j = 1; j <= n-i+1; ++j) {
		f[j] = min(abs(a[j]-a[j+i-1]), min(f[j], f[j+1]));
		if(i >= k) ans = max(ans, f[j]*(i-1));
	}
	
	for(int i = 0; i <= b; ++i) g[i] = 1;
	for(int i = 1; i <= n; ++i) {
		for(int j = 0; j <= b; ++j) {
			if(i-g[j]+1 >= k) ans = max(ans, (i-g[j])*j);
			if(a[i]-j >= 1) g[j+1] = max(g[j+1], last[a[i]-j]);
			if(a[i]+j <= m) g[j+1] = max(g[j+1], last[a[i]+j]);
			g[j+1] = max(g[j+1], g[j]);
		}
		last[a[i]] = i+1;
	}
	printf("%d\n", ans);
	return 0;
}
