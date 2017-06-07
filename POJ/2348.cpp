#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

bool solve(ll x, ll y) {
	if(!y) return 0;
	if(x/y > 1) return 1;
	return !solve(y, x - y);
}

ll x, y;
int main() {
	freopen("x.in", "r", stdin);

	while(scanf("%lld%lld", &x, &y) != EOF) {
		if(!x && !y) break;
		if(x < y) swap(x, y);
		printf("%s wins\n", solve(x, y) ? "Stan" : "Ollie");
	}

	return 0;
}