#include <cstdio>
using namespace std;
typedef long long ll;

ll gcd(ll x, ll y) {
	return !y ? x : gcd(y, x % y);
}

ll a, b, c, k;
int cas;

int main() {
	scanf("%d", &cas);
	while (cas--) {
		scanf("%lld%lld%lld%lld", &a, &b, &c, &k);
		printf("%s\n", !(c % gcd(b, gcd(a, k - 1))) ? "Yes" : "No");
	}
	return 0;
}
