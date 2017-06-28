#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 1e5+5, oo = 1e9;
int n, h1, h2, t1, t2, a[maxn], q1[maxn], q2[maxn], ans[maxn];

int main() {
	freopen("245.in", "r", stdin);
	freopen("245.out", "w", stdout);

	n = read();
	for(int i = 1; i <= n; ++i) a[i] = read();
	for(int i = 1; i <= n; ++i) ans[i] = oo;
	for(int d = 0; d <= 2000000; d = max(d+1, int(1.05*d))) {
		h1 = h2 = 0, t1 = t2 = -1;
		for(int i = 1, j = 1; i <= n; ++i) {
			while(h1 <= t1 && a[q1[t1]] > a[i]) --t1;
			while(h2 <= t2 && a[q2[t2]] < a[i]) --t2;
			q1[++t1] = i, q2[++t2] = i;
			
			for(; a[q2[h2]]-a[q1[h1]] > d; ++j) {
				if(q1[h1] == j) ++h1;
				if(q2[h2] == j) ++h2;
			}
			ans[i-j+1] = min(ans[i-j+1], a[q2[h2]]-a[q1[h1]]);
		}
	}
	
	for(int i = n-1; i; --i) ans[i] = min(ans[i], ans[i+1]);
	for(int i = 2; i <= n; ++i) printf("%d\n", ans[i]);
	return 0;
}
