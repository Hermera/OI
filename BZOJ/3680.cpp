#include <cmath>
#include <cstdio>
#include <cstdlib>
using namespace std;

double r01() { // Get a number in [0, 1]
	return rand() % 10000 / 10000.0;
}

double r11() { // Get a number in [-1, 1]
	return 2 * r01() - 1.0;
}

double sqr(double x) {
	return x * x;
}


const int N = 1e4 + 5;
const double inf = 1e100;

int n;
double sum = inf;

struct vec {
	double x, y, g;
	vec() {}
	vec(double _x, double _y): x(_x), y(_y) {}
} p[N], ans;

double dis(vec a, vec b) {
	return sqrt(sqr(a.x - b.x) + sqr(a.y - b.y));
}



double check(vec a) {
	double ret = 0;
	for(int i = 1; i <= n; ++i)
		ret += dis(a, p[i]) * p[i].g;
	if(ret < sum) sum = ret, ans = a;
	return ret;
}


const int seed = 20000909;
const int tim = 1000;
const double tem = 1e5;
const double lim = 1e-3;
const double sub = 0.991;

void SimulateAnneal(double T) {
	vec now = ans;
	for(; T > lim; T *= sub) {
		vec np(now.x + T*r11(), now.y + T*r11());
		double delta = check(now) - check(np);
		if(delta > 0 || exp(delta/T) > r01()) now = np;
	}
	
	for(int i = 1; i <= tim; ++i) {
		vec np(ans.x + T*r11(), ans.y + T*r11());
		check(np);
	}
}

int main() {
	srand(seed);
	
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].g);
		ans.x += p[i].x, ans.y += p[i].y;
	}
	
	ans.x /= n;
	ans.y /= n;
	SimulateAnneal(tem);
	
	printf("%.3lf %.3lf\n", ans.x, ans.y);
	return 0;
}
