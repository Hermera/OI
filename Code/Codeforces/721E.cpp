#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 100005;
int f[maxn], g[maxn], L, N, P, T;

void update(int i, int w, int p) {
	if(f[i] < w) f[i] = w, g[i] = p;
	else if(f[i] == w) g[i] = min(g[i], p);
}

int main() {
	L = read(), N = read(), P = read(), T = read();
	g[0] = -T;
	for(int i = 1, j = 0, l, r; i <= N; ++i) {
		l = read(), r = read();
		if(j) --j;
		while(j < i && g[j]+T <= r) {
			l = max(l, g[j]+T);
			update(i, f[j]+(r-l)/P, l+(r-l)/P*P);
			++j;
		}
		update(i, f[i-1], g[i-1]);
	}
	printf("%d\n", f[N]);
	return 0;
}
