#include <cstdio>
#include <algorithm>
using namespace std;

const int maxn = 1e5+5;
const double eps = 1e-9;
struct vec {
	double x, y, r; int p;
} p[maxn], q[maxn], c[maxn], st[maxn];
vec operator -(vec a, vec b) { return (vec){ a.x-b.x, a.y-b.y }; }
double operator *(vec a, vec b) { return a.x*b.y - a.y*b.x; }
double operator ^(vec a, vec b) { return a.x*b.x + a.y*b.y; }
bool operator <(vec a, vec b) { return a*b > eps; }

int n, t, t1, t2;
double f[maxn];

void solve(int l, int r) {
	if(l == r) {
		f[l] = max(f[l], f[l-1]);
		p[l].y = f[l]/(q[l].x*q[l].r + q[l].y);
		p[l].x = p[l].y*q[l].r;
		return;
	}
	
	int m = (l+r>>1);
	t1 = l, t2 = m+1;
	for(int i = l; i <= r; ++i)
		if(q[i].p <= m) c[t1++] = q[i];
		else c[t2++] = q[i];
	for(int i = l; i <= r; ++i) q[i] = c[i];
	solve(l, m);
	
	int top = 0;
	for(int i = l; i <= m; ++i) {
		while(top > 1 && (p[i]-st[top])*(st[top]-st[top-1]) < eps) --top;
		st[++top] = p[i];
	}
	for(int i = r, j = 1; i > m; --i) {
		while(j < top && (q[i]^(st[j]-st[j+1])) < eps) ++j;
		f[q[i].p] = max(f[q[i].p], st[j]^q[i]);
	}
	
	solve(m+1, r);
	t = t1 = l, t2 = m+1;
	while(t1 <= m && t2 <= r)
		if(p[t1].x < p[t2].x+eps) c[t++] = p[t1++];
		else c[t++] = p[t2++];
	while(t1 <= m) c[t++] = p[t1++];
	while(t2 <= r) c[t++] = p[t2++];
	for(int i = l; i <= r; ++i) p[i] = c[i];
}


int main() {
	scanf("%d%lf", &n, f);
	for(int i = 1; i <= n; ++i) {
		vec &e = q[i];
		scanf("%lf%lf%lf", &e.x, &e.y, &e.r);
		e.p = i;
	}
	sort(q+1, q+1+n);
	solve(1, n);
	printf("%.3lf\n", f[n]);
	return 0;
}
