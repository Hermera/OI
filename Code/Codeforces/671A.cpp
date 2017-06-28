#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

struct Point {
	double x, y;
	void init() {
		x = read(), y = read(); 
	}
} A, B, T, D;

double dis(Point a, Point b) {
	return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}

int N;
int main() {
	A.init();
	B.init();
	T.init();
	
	double ans = 0;
	double fa = 1e20, fb = 1e20, fab = 1e20;
	N = read();
	while(N--) {
		D.init();
		ans += 2*dis(D, T);
		double af = dis(A, D)-dis(D, T);
		double bf = dis(B, D)-dis(D, T);
		
		fab = min(fab, min(fa+bf, fb+af));
		fa = min(fa, af);
		fb = min(fb, bf);
	}
	
	printf("%.12lf\n", ans + min(fab, min(fa, fb)));
	return 0;
}
