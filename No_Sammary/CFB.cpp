#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e5+5;
int n, mx;
int a[N], b[N];


int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", a + i);
		mx = max(mx, a[i]);
	}
			
	for(int i = 1; i <= n; ++i) ++b[a[i]];
	
	int ans = 1;
	for(int i = 2; i <= mx; ++i) {
		int ret = 0;
		for(int j = i; j <= mx; j += i)
			ret += b[j];
		ans = max(ans, ret);
	}
	
	printf("%d\n", ans);
	return 0;
}
