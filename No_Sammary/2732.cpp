#include <cmath>
#include <cstdio>
#include <algorithm>
//#define double long double
using namespace std;
const int maxn = 2e5+5;
const double eps = 0;
int m, c;
struct poi {
    double x, y;
    poi(double _x = .0, double _y = .0): x(_x), y(_y) {}
} p[maxn];
poi operator +(poi a, poi b) { return poi(a.x+b.x, a.y+b.y); }
poi operator -(poi a, poi b) { return poi(a.x-b.x, a.y-b.y); }
poi operator *(poi a, double b) { return poi(a.x*b, a.y*b); }
double operator *(poi a, poi b) { return a.x*b.y - a.y*b.x; }
struct line {
    poi u, v; double sp; int id;
    line() {}
    line(poi _u, poi _v, int i): u(_u), v(_v) {
        sp = atan2(v.y - u.y, v.x - u.x), id = i;
    }
} a[maxn], b[maxn], q[maxn];
poi inter(line a, line b) {
   	poi u = a.v - a.u;
	poi v = b.v - b.u;
	poi w = b.u - a.u;
	double t = (w * v) / (u * v);
	return a.u + u * t;
}
bool left(poi o, line t) { return (t.v-t.u) * (o-t.u) > -eps; }
bool operator <(line a, line b) {
    if(fabs(a.sp-b.sp) < eps) return left(a.u, b);
    return a.sp < b.sp;
}
bool HPIS(int x) {
    int n = 0, h = 1, t = 0;
    for(int i = 1; i <= c; ++i)
        if(b[i].id <= x)
            if(fabs(b[i].sp-a[n].sp) > eps)
                a[++n] = b[i];
    q[++t] = a[1];
    for(int i = 2; i <= n; ++i) {
        while(h < t && !left(inter(q[t-1], q[t]), a[i])) --t;
        while(h < t && !left(inter(q[h+1], q[h]), a[i])) ++h;
        q[++t] = a[i];   
    }
    while(h < t && !left(inter(q[t-1], q[t]), q[h])) --t;
    return t - h > 1;
}
int main() {
	freopen("2732.in", "r", stdin);

    scanf("%d", &m);
    for(int i = 1; i <= m; ++i) {
        static double x, y1, y2;
        scanf("%lf%lf%lf", &x, &y1, &y2);
        b[++c] = line(poi(0, y2/x), poi(-1/x, y2/x + 1), i);
        b[++c] = line(poi(0, y1/x), poi(1/x,  y1/x - 1), i);
    }
    
    sort(b+1, b+1+c);
    int l = 1, r = m, ans = 0;
    while(l <= r) {
        int mid = (l+r)>>1;
        if(HPIS(mid)) ans = mid, l = mid+1;
        else r = mid-1;
    }
    printf("%d\n", ans);
    return 0;
}
