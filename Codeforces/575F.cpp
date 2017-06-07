#include <cstdio>
#include <algorithm>
using namespace std;
int N, x, y;
int main() {
	scanf("%d%d", &N, &x);
	y = x;

	long long ans = 0;
	for(int i = 1, l, r; i <= N; ++i) {
		scanf("%d%d", &l, &r);
		if(x <= r && l <= y) x = max(x, l), y = min(y, r);
		else if(y < l) x = y, ans += l-y, y = l;
		else if(r < x) y = x, ans += x-r, x = r;
	}
	printf("%lld\n", ans);
	return 0;
}
