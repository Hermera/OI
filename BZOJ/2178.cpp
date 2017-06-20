#include <map>
#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
<<<<<<< a2824b917e289d5fe1d2fa5151a17a549f4561fb

const int N = 2005;
const double inf = 1e9;
const double eps = 1e-13;

int n, t, del[N];
struct circle {
	double x, y, r;
	void init() {
		scanf("%lf%lf%lf", &x, &y, &r);
	}
} cir[N];

double sqr(double x) {
	return x * x;
}

double dis(circle &a, circle &b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}


=======
 
const int N = 2005;
const double inf = 1e9;
const double eps = 1e-13;
 
int n, t, del[N];
struct circle {
    double x, y, r;
    void init() {
        scanf("%lf%lf%lf", &x, &y, &r);
    }
} cir[N];
 
double sqr(double x) {
    return x * x;
}
 
double dis(circle &a, circle &b) {
    return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}
 
 
>>>>>>> merge
typedef pair<double, double> pdd;
#define fir first
#define sec second
pdd ran[N], dow[N];
<<<<<<< a2824b917e289d5fe1d2fa5151a17a549f4561fb

map <double, double> mem;
double F(double x) {
	if(mem.count(x)) return mem[x];
	
	t = 0;
	for(int i = 1; i <= n; ++i) {
		double a = fabs(x - cir[i].x);
		double c = cir[i].r;
		if(a > c) continue;
		double b = sqrt(c * c - a * a);
		dow[++t] = pdd(cir[i].y - b, cir[i].y + b);
	}
	
	sort(dow + 1, dow + 1 + t);
	
	double tmp = -inf;
	double ret = 0;
	for(int i = 1; i <= t; ++i) {
		if(dow[i].sec <= tmp) continue;
		ret += dow[i].sec - max(dow[i].fir, tmp);
		tmp = dow[i].sec;
	}
	return mem[x] = ret;
}

double calc(double l, double r) {
	double mid = (l + r) / 2;
	return (r - l) * (F(l) + F(r) + 4 * F(mid)) / 6;
}

int __count;
double simpson(double l, double r, double w) {
	double mid = (l + r) / 2;
	double lw = calc(l, mid);
	double rw = calc(mid, r);
	
	if(fabs(lw + rw - w) < eps) return lw + rw;
	return simpson(l, mid, lw) + simpson(mid, r, rw);
}


int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) cir[i].init();
	for(int i = 1; i <= n; ++i)
		for(int j = i + 1; j <= n; ++j) 
			if(cir[j].r - cir[i].r >= dis(cir[i], cir[j])) {
				del[i] = 1;
				break;
			}
			
	for(int i = 1; i <= n; ++i)
		if(!del[i]) cir[++t] = cir[i];
	n = t;
	
	for(int i = 1; i <= n; ++i)
		ran[i] = pdd(cir[i].x - cir[i].r, cir[i].x + cir[i].r);
	sort(ran + 1, ran + 1 + n);
	
	double tmp = -inf;
	double ans = 0;
	for(int i = 1; i <= n; ++i) {
		if(ran[i].sec <= tmp) continue;
		double l = max(ran[i].fir, tmp);
		double r = ran[i].sec;
		
		ans += simpson(l, r, calc(l, r));
		tmp = r;
	}
	
	printf("%.3lf\n", ans);
	return 0;
}
=======
 
map <double, double> mem;
double F(double x) {
    if(mem.count(x)) return mem[x];
     
    t = 0;
    for(int i = 1; i <= n; ++i) {
        double a = fabs(x - cir[i].x);
        double c = cir[i].r;
        if(a > c) continue;
        double b = sqrt(c * c - a * a);
        dow[++t] = pdd(cir[i].y - b, cir[i].y + b);
    }
     
    sort(dow + 1, dow + 1 + t);
     
    double tmp = -inf;
    double ret = 0;
    for(int i = 1; i <= t; ++i) {
        if(dow[i].sec <= tmp) continue;
        ret += dow[i].sec - max(dow[i].fir, tmp);
        tmp = dow[i].sec;
    }
    return mem[x] = ret;
}
 
double calc(double l, double r) {
    double mid = (l + r) / 2;
    return (r - l) * (F(l) + F(r) + 4 * F(mid)) / 6;
}
 
int __count;
double simpson(double l, double r, double w) {
    double mid = (l + r) / 2;
    double lw = calc(l, mid);
    double rw = calc(mid, r);
     
    if(fabs(lw + rw - w) < eps) return lw + rw;
    return simpson(l, mid, lw) + simpson(mid, r, rw);
}
 
 
int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) cir[i].init();
    for(int i = 1; i <= n; ++i)
        for(int j = i + 1; j <= n; ++j) 
            if(cir[j].r - cir[i].r >= dis(cir[i], cir[j])) {
                del[i] = 1;
                break;
            }
             
    for(int i = 1; i <= n; ++i)
        if(!del[i]) cir[++t] = cir[i];
    n = t;
     
    for(int i = 1; i <= n; ++i)
        ran[i] = pdd(cir[i].x - cir[i].r, cir[i].x + cir[i].r);
    sort(ran + 1, ran + 1 + n);
     
    double tmp = -inf;
    double ans = 0;
    for(int i = 1; i <= n; ++i) {
        if(ran[i].sec <= tmp) continue;
        double l = max(ran[i].fir, tmp);
        double r = ran[i].sec;
         
        ans += simpson(l, r, calc(l, r));
        tmp = r;
    }
     
    printf("%.3lf\n", ans);
    return 0;
}
>>>>>>> merge
