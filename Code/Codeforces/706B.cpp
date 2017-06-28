#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e5+5;
int n, q, x[maxn];

int main() {
	freopen("706B.in", "r", stdin);

	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d", x+i);
	sort(x+1, x+1+n);
	scanf("%d", &q);
	for(int i = 1, a; i <= q; ++i) {
		scanf("%d", &a);
		if(a < x[1]) printf("0\n");
		else printf("%d\n", (int)(upper_bound(x+1, x+1+n, a)-x-1));
	}
	return 0;
}
