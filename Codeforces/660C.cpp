#include <cstdio>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 3e5+5;
int N, K, a[maxn], c[maxn], s[maxn];

bool Judge(int x) {
	for(int i = 1; i <= N-x+1; ++i)
		if(s[i+x-1]-s[i-1]+K >= x) {
			for(int j = 1; j <= N; ++j) c[j] = a[j];
			for(int j = i; j <= i+x-1; ++j) c[j] = 1;
			return true;
		}
	return false;
}

int main() {
	freopen("660C.in", "r", stdin);

	N = read(), K = read();
	for(int i = 1; i <= N; ++i) a[i] = read(), s[i] = s[i-1]+a[i];
	
	int l = 0, r = N, ans = 0;
	while(l <= r) {
		int mid = (l+r)>>1;
		if(Judge(mid)) ans = mid, l = mid+1;
		else r = mid-1;
	}
	printf("%d\n", ans);
	for(int i = 1; i <= N; ++i) printf("%d ", c[i]);
	printf("\n");
	return 0;
}
