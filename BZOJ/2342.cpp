#include <set>
#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e6+5;
char str[maxn];
int n, p[maxn];

void manacher() {
	int mx = 0, j = 0;
	for(int i = 1; i <= n; ++i) {
		if(mx <= i) p[i] = 0;
		else p[i] = min(p[j*2-i], mx-i);
		while(str[i+p[i]+1] == str[i-p[i]]) ++p[i];
		if(i+p[i] > mx) mx = i+p[i], j = i;
	}
}

struct ele {
	int x, y;
	ele(int _x = 0, int _y = 0): x(_x), y(_y) {}
	bool operator <(const ele &b) const {
		return x < b.x;
	}
} a[maxn];
set <int> s;

int main() {
	scanf("%d%s", &n, str+1), str[0] = '#';
	manacher();
	for(int i = 1; i <= n; ++i) a[i] = ele(i-p[i], i);
	sort(a+1, a+1+n);
	
	int ans = 0, t = 0;
	for(int i = 1; i <= n; ++i) {
		while(t < n && a[t+1].x <= i) ++t, s.insert(a[t].y);
		ans = max(ans, (*--s.lower_bound(i+p[i]/2+1) - i)*4);
	}
	printf("%d\n", ans);
	return 0;
}
