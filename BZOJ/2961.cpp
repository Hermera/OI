#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 5e5+5;
const double eps = 1e-15;
struct vec {
	double x, y; int type, p;
} q[maxn], c[maxn], st[maxn];
double operator *(vec a, vec b) { return a.x*b.y - b.x*a.y; }
double operator ^(vec a, vec b) { return a.x*b.x + a.y*b.y; }
bool operator <(vec a, vec b) { return a*b > eps; }
vec operator -(vec a, vec b) { return (vec){ a.x-b.x, a.y-b.y }; }

int n, k, k1, k2;
bool ans[maxn], ask[maxn];

void solve(int l, int r) {
	if(l == r) return;
	int m = (l+r)>>1;
	
	k1 = l, k2 = m+1;
	for(int i = l; i <= r; ++i)
		if(q[i].p <= m) c[k1++] = q[i];
		else c[k2++] = q[i];
	for(int i = l; i <= r; ++i) q[i] = c[i];
	solve(l, m);
	
	int t = 0;
	for(int i = l; i <= m; ++i) if(!q[i].type) {
		while(t > 1 && (q[i]-st[t])*(st[t]-st[t-1]) > -eps) --t;
		st[++t] = q[i];
	}
	for(int i = m+1, j = 1; i <= r; ++i) if(q[i].type) {
		while(j < t && (q[i]^(st[j]-st[j+1])) > -eps) ++j;
		if(j <= t && (q[i]^st[j])*2.0 < (q[i]^q[i])) ans[q[i].p] = 0;
	}
	
	solve(m+1, r);
	k = k1 = l, k2 = m+1;
	while(k1 <= m && k2 <= r)
		if(q[k1].x < q[k2].x) c[k++] = q[k1++];
		else c[k++] = q[k2++];
	while(k1 <= m) c[k++] = q[k1++];
	while(k2 <= r) c[k++] = q[k2++];
	for(int i = l; i <= r; ++i) q[i] = c[i];
}


int main() {
	scanf("%d", &n);
	for(int i = 1, ok = 0; i <= n; ++i) {
		vec &e = q[i]; e.p = i;
		scanf("%d%lf%lf", &e.type, &e.x, &e.y);
		if(e.type) ask[i] = 1, ans[i] = ok;
		else ok = 1;
	}
	
	sort(q+1, q+1+n);
	solve(1, n);
	for(int i = 1; i <= n; ++i) if(ask[i])
		printf("%s\n", ans[i] ? "Yes" : "No");
	return 0;
}
