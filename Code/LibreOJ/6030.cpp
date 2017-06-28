#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1005;
const int inf = 1e9;

int n, flag;
int r[N], c[N], has[N];
char str[N];

int main() {
	freopen("6030.in", "r", stdin);

	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s", str + 1);
		for (int j = 1; j <= n; ++j)
			if (str[j] == '#') {
				has[j] = 1;
				++r[i], ++c[j];
				flag = 1;
			}
	}

	if (!flag) {
		puts("-1");
		return 0;
	}

	int ans = inf;
	for (int i = 1; i <= n; ++i)
		ans = min(n - r[i] + (!has[i]), ans);
	for (int i = 1; i <= n; ++i)
		if (c[i] != n) ++ans;
	printf("%d\n", ans);
	return 0;
}