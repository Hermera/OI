#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
const int maxn = 1e6+5;
const double inf = 1e60, eps = 1e-8;
struct Point
{
	double x, y;
	void init() { scanf("%lf%lf", &x, &y); }
	double slope() { return -sqrt(y/x); }
	bool operator < (const Point &b) const { return x != b.x ? x < b.x : y > b.y; }
	Point operator -(const Point &b) const { return (Point){x-b.x, y-b.y}; }
	double operator *(const Point &b) const { return x*b.y-y*b.x; }
	double operator /(const Point &b) const
	{
		if(x == b.x) return -inf;
		return (b.y-y)/(b.x-x);
	}
} p[maxn], s[maxn];
double ans = inf;
int N, top = 1;
double calc(Point x, double k)
{
	if(fabs(k) < eps) return inf;
	return x.x+x.y-x.x*k-x.y/k; 
}

int main()
{
	freopen("data.in", "r", stdin);
	freopen("my.out", "w", stdout);

	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) p[i].init();
	sort(p+1, p+N+1);
	
	s[1] = p[1];
	for(int i = 2; i <= N; ++i)
	{
		while(top > 1 && (p[i]-s[top])*(s[top]-s[top-1]) < 0) --top;
		s[++top] = p[i];
	}
	
	if(top == 1) ans = calc(s[1], s[1].slope());
	else
	{
		double sp, l, r;
		r = s[1]/s[2], sp = s[1].slope();
		if(sp >= r) ans = min(ans, calc(s[1], sp));
		for(int i = 2; i < top; ++i)
		{
			l = s[i-1]/s[i], r = s[i]/s[i+1], sp = s[i].slope();
			if(l >= sp && sp >= r) ans = min(ans, calc(s[i], sp));
			ans = min(ans, calc(s[i], l));
		}
		l = s[top-1]/s[top], sp = s[top].slope();
		ans = min(ans, calc(s[top], l));
		if(l >= sp) ans = min(ans, calc(s[top], sp));
	}
	printf("%.4lf\n", ans);
	
	return 0;
}
