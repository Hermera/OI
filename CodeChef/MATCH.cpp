#include <map>
#include <cstdio>
#include <cstring>
using namespace std;


const int S = 505;
const int N = 105;

int t, siz[S], sta[S];
map <int, int> idx;

int num(int s) {
	if(!idx.count(s)) {
		idx[s] = ++t;
		sta[t] = s;
	}
	return idx[s];
}


int n, m, all;
double p[N][N], po[S];
double get(int s, int o) {
	double ret = 1;
	for(int i = 0; i < n; ++i)
		if(s & (1 << i)) ret *= p[i][o];
		else ret *= (1.0 - p[i][o]);
	return ret;
}


#define has(s, i) ((s) & (1 << (i)))
int insert(int s, int t) {
	int ret = s;
	for(int i = 0; i < all; ++i) if(has(s, i))
		for(int j = 0; j < n; ++j) if(has(t, j))
			ret |= 1 << (i | (1 << j));
	return ret;
}

int total(int s) {
	int ret = 0;
	for(int i = 0; i < all; ++i)
		if(has(s, i)) ret = max(ret, siz[i]);
	return ret;
}


double dp[N][S];
int main() {
	scanf("%d%d", &n, &m);
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			scanf("%lf", &p[i][j]);
	
	all = 1 << n;
	for(int i = 1; i < all; ++i)
		siz[i] = siz[i>>1] + (i & 1);
	
	dp[0][num(1)] = 1;
	for(int i = 0; i < m; ++i) {
		for(int s = 0; s < all; ++s) po[s] = get(s, i);
		for(int j = t; j; --j) if(dp[i][j])
			for(int s = 0; s < all; ++s)
				dp[i+1][num(insert(sta[j], s))] += po[s] * dp[i][j];
	}
	
	double ans = 0;
	for(int i = 1; i <= t; ++i)
		ans += dp[m][i] * total(sta[i]);
	printf("%.10lf\n", ans);
	return 0;
}
