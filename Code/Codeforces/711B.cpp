#include <cstdio>
using namespace std;
typedef long long ll;

const int maxn = 505;
int n, X, Y;
ll sum, ret, a[maxn][maxn];

bool Judge() {
	int raw = 1;
	if(raw == X) ++raw;
	for(int i = 1; i <= n; ++i) sum += a[raw][i];
	
	for(int i = 1; i <= n; ++i)
	if(i != X) {
		ll tmp = 0;
		for(int j = 1; j <= n; ++j) tmp += a[i][j];
		if(tmp != sum) return false;
	}
	
	for(int j = 1; j <= n; ++j)
	if(j != Y) {
		ll tmp = 0;
		for(int i = 1; i <= n; ++i) tmp += a[i][j];
		if(tmp != sum) return false;
	}
	
	if(X != Y) {
		ll tmp = 0;
		for(int i = 1; i <= n; ++i) tmp += a[i][i];
		if(tmp != sum) return false;
	}
	
	if(Y != n-X+1) {
		ll tmp = 0;
		for(int i = 1; i <= n; ++i) tmp += a[i][n-i+1];
		if(tmp != sum) return false;
	}
	
	for(int i = 1; i <= n; ++i) ret += a[X][i];
	if(sum <= ret) return false;
	
	ll tmp = 0;
	for(int i = 1; i <= n; ++i) tmp += a[i][Y];
	if(tmp != ret) return false;
	
	if(X == Y) {
		tmp = 0;
		for(int i = 1; i <= n; ++i) tmp += a[i][i];
		if(tmp != ret) return false;
	}
	
	if(Y == n-X+1) {
		tmp = 0;
		for(int i = 1; i <= n; ++i) tmp += a[i][n-i+1];
		if(tmp != ret) return false;
	}
	return true;
}
	

int main() {
	freopen("711B.in", "r", stdin);

	scanf("%d", &n);
	if(n == 1) return printf("1\n"), 0;
	
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= n; ++j) {
		scanf("%lld", &a[i][j]);
		if(!a[i][j]) X = i, Y = j;
	}
	
	if(!Judge()) return printf("-1\n"), 0;
	printf("%lld\n", sum-ret);
	return 0;
}
