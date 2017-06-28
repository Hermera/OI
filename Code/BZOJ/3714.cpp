#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;


const int N = 2e5+5;
const double inf = 1e100;


int cas, n, t;
struct vec {
	double x, y;
	bool type;
	
	void init(int i) {
		type = i;
		scanf("%lf%lf", &x, &y);
	}
} p[N], q[N];

bool cmpx(vec a, vec b) {
	return a.x < b.x || a.x == b.x && a.y < b.y;
}

bool cmpy(vec a, vec b) {
	return a.y < b.y || a.y == b.y && a.x < b.x;
}
	
double sqr(double x) {
	return x * x;
}


double dis(vec a, vec b) {
	if(a.type == b.type) return inf;
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}

double solve(int l, int r) {
	if(l == r) return inf;
	if(l+1 == r) return dis(p[l], p[r]);
	
	int mid = (l + r) >> 1;
	double ret = inf;
	ret = min(ret, solve(l, mid));
	ret = min(ret, solve(mid+1, r));
	
	t = 0;
	for(int i = l; i <= r; ++i) 
		if(fabs(p[mid].x - p[i].x) <= ret)
			q[++t] = p[i];
	sort(q + 1, q + 1 + t, cmpy);
	
	for(int i = 1; i <= t; ++i)
		for(int j = i+1; j <= t; ++j) {
			if(q[j].y - q[i].y >= ret) break;
			ret = min(ret, dis(q[i], q[j]));
		}
	return ret;
}

int main() {
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d", &n), n <<= 1;
		for(int i = 1; i <= n/2; ++i) p[i].init(0);
		for(int i = n/2+1; i <= n; ++i) p[i].init(1);
		
		sort(p + 1, p + 1 + n, cmpx);
		printf("%.3lf\n", solve(1, n));
	}
	return 0;
}
