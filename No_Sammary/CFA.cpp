#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 1e5+5;
const int INF = 1e9;
char str[N];

int cnt[N];
int idx(char ch) {
	if('a' <= ch && ch <= 'z')
		return ch - 'a';
	return 26 + ch - 'A';
}

int main() {
	scanf("%s", str);
	for(int i = 0; str[i]; ++i) ++cnt[idx(str[i])];
	
	int ans = INF;
	ans = min(ans, cnt[idx('B')]);
	ans = min(ans, cnt[idx('u')]/2);
	ans = min(ans, cnt[idx('l')]);
	ans = min(ans, cnt[idx('b')]);
	ans = min(ans, cnt[idx('a')]/2);
	ans = min(ans, cnt[idx('s')]);
	ans = min(ans, cnt[idx('r')]);
	printf("%d\n", ans);
	return 0;
}
