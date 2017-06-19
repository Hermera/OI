#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;


const int N = 305;
const int M = N * N;

int n, m;
char str[N];
struct ele {
	int val, sum, len;
	void init() {
		scanf("%s", str);

		val = N;
		for(int i = 0; str[i]; ++i) {
			if(str[i] == '(') ++sum, ++m;
			else --sum;
			++len, val = min(val, sum);
		}
	}
} a[N];

bool operator <(ele x, ele y) {
	if((x.sum > 0) != (y.sum > 0)) return x.sum > y.sum;
	if(x.sum < 0) return x.val > y.val;
	else return x.val < y.val;
}


int dp[N][M], o;
#define f dp[o]
#define g dp[!o]

void upd(int &x, int y) {
	x = x < y ? y : x;
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		a[i].init();
	sort(a + 1, a + n + 1);

	memset(dp, -63, sizeof(dp));

	g[0] = 0;
	for(int i = 1; i <= n; ++i, o ^= 1) {
		memset(f, -63, sizeof(f));
		for(int j = max(0, -a[i].sum); j <= m; ++j) 
			if(g[j] >= 0) {
				upd(f[j + a[i].sum], g[j] + a[i].len);
				upd(f[j], g[j]);
			}
	}
	
	int ans = g[0];
	printf("%d\n", ans);
	return 0;
}