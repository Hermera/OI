#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

struct Point {
	int x, y;
	void init() {
		scanf("%d%d", &x, &y);
	}
} A, B;
int N;

double dis(Point a, Point b) {
	return sqrt( (a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) );
}


int main() {
	freopen("706A.in", "r", stdin);

	double tim = 1e9, v;
	A.init();
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) 
		B.init(), scanf("%lf", &v), tim = min(tim, dis(A, B)/v);
	
	printf("%.10lf\n", tim);
	return 0;
}
