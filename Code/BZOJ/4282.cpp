#include <cstdio>
#include <algorithm>
#include <cstring>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int maxn = 1e5+5;
int N, M, sum, ans, a[maxn], p[maxn];
char c[5];

int main() {
	N = read();
	for(int i = 1; i <= N; ++i) {
		scanf("%s", c);
		if(*c == 'N') ++sum;
		else a[++M] = read()-sum;
	}
	
	memset(p, 63, sizeof(p));
	for(int i = 1; i <= M; ++i) {
		int x = lower_bound(p+1, p+1+N, a[i])-p;
		ans = max(ans, x);
		p[x] = a[i];
	}
	
	printf("%d\n", ans+sum);
	return 0;
}
