#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 505;
int n, c, h[maxn], s[maxn], t[maxn];
int g[maxn][maxn], sum[maxn][maxn], pre[maxn][maxn], suf[maxn][maxn];
void upd(int &x, int y) { if(y > x) x = y; }

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%d%d", s+i, t+i), t[i] += s[i];
	for(int i = 1; i <= n; ++i) h[++c] = s[i], h[++c] = t[i];
	sort(h+1, h+1+c);
	c = unique(h+1, h+1+c) - h-1;
	for(int i = 1; i <= n; ++i)
		s[i] = lower_bound(h+1, h+1+c, s[i])-h,
		t[i] = lower_bound(h+1, h+1+c, t[i])-h;
	
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= s[i]; ++j)
	for(int k = t[i]; k <= c; ++k)
		++sum[j][k];
	
	memset(pre, -1, sizeof(pre)), pre[1][0] = 0;
	memset(suf, -1, sizeof(suf)), suf[c][0] = 0;
	for(int i = 1; i <= c; ++i)
	for(int j = 0; j <= n; ++j) {
		upd(pre[i][j], pre[i-1][j]);
		for(int k = 1; k < i; ++k) {
			if(~pre[k][j]) upd(pre[i][j], pre[k][j]+sum[k][i]);
			if(j >= sum[k][i]) upd(pre[i][j], pre[k][j-sum[k][i]]);
		}
	}
	for(int i = c; i >= 1; --i)
	for(int j = 0; j <= n; ++j) {
		upd(suf[i][j], suf[i+1][j]);
		for(int k = c; k > i; --k) {
			if(~suf[k][j]) upd(suf[i][j], suf[k][j]+sum[i][k]);
			if(j >= sum[i][k]) upd(suf[i][j], suf[k][j-sum[i][k]]);
		}
	}
	
	for(int i = 1; i <= c; ++i)
	for(int j = i; j <= c; ++j) 
		for(int l = 0, r = n; l <= n; ++l) {
			if(pre[i][l] < 0) continue;
			while(~r && (suf[j][r] < 0 || l+r > pre[i][l]+suf[j][r]+sum[i][j])) --r;
			if(~r) upd(g[i][j], l+r);
		}
	
	int ans = 0;
	for(int i = 0; i <= n; ++i)
		ans = max(ans, min(i, pre[c][i]));
	printf("%d\n", ans);
	for(int i = 1; i <= n; ++i) {
		ans = 0;
		for(int j = 1; j <= s[i]; ++j)
		for(int k = c; k >= t[i]; --k)
			upd(ans, g[j][k]);
		printf("%d\n", ans);
	}
	return 0;
}
