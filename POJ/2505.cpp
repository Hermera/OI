#include <cmath>
#include <cstdio>
using namespace std;
typedef long long ll;


bool solve(ll x) {
	int d = 0;
	for(; x > 1; d ^= 1) 
		x = ceil(d ? x / 2.0 : x / 9.0);
	return d;
}

ll x;
int main() {
	while(scanf("%lld", &x) != EOF)
		printf("%s wins.\n", solve(x) ? "Stan" : "Ollie");
	return 0;
}