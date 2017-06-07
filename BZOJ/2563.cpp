#include <cstdio>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 1e4+5;
int N, M, w[maxn], ans;

int main() {
	N = read(), M = read();
	for(int i = 1, c; i <= N; ++i) 
		c = read(), w[i] += 2*c, ans -= c;
	for(int i = 1, a, b, c; i <= M; ++i) {
		a = read(), b = read(), c = read();
		ans -= c, w[a] += c, w[b] += c;
	}
	
	sort(w+1, w+1+N);
	for(int i = N; i; i -= 2) ans += w[i];
	printf("%d\n", ans);
	return 0;
}
