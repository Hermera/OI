#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0, t = 1;
	while (ch < '0' || ch > '9') {
		if (ch == '-') t = -1;
		ch = getchar();
	}
	while (ch >= '0' && ch <= '9') 
		x = x * 10 + ch - '0', ch = getchar();
	return x * t;
}


const double eps = 1e-8;
const int N = 1e5 + 5;

struct vec {
	double x, y;
	vec() {}
	vec(double _x, double _y): x(_x), y(_y) {}
	
	double len() {
		return sqrt(x * x + y * y);
	}
};

bool operator <(vec a, vec b) {
	return a.x < b.x || a.x == b.x && a.y < a.y;
}

vec operator +(vec a, vec b) {
	return vec(a.x + b.x, a.y + b.y);
}

vec operator -(vec a, vec b) {
	return vec(a.x - b.x, a.y - b.y);
}

vec operator *(vec a, double k) {
	return vec(a.x * k, a.y * k);
}

vec operator /(vec a, double k) {
	return vec(a.x / k, a.y / k);
}

double operator &(vec a, vec b) {
	return a.x * b.x + a.y * b.y;
}

double operator *(vec a, vec b) {
	return a.x * b.y - a.y * b.x;
}

double dis(vec a, vec b) {
	return (a - b).len();
}


struct line {
	vec x, y;
	line() {}
	line(vec _x, vec _y): x(_x), y(_y) {}
};

bool left(vec o, line t) {
	return (t.y - t.x) * (o - t.x) > -eps;
}

bool operator <(line a, line b) {
	double w = (a.y - a.x) * (b.y - b.x);
	if (fabs(w) < eps) return left(a.x, b);
	return w > eps;
}

vec cross(line a, line b) {
	vec u = a.y - a.x;
	vec v = b.y - b.x;
	vec w = b.x - a.x;
	double t = (w * v) / (u * v);
	return a.x + u * t;
}



vec b[N], c[N];
line a[N], q[N];
int n, m, k;

double hpi() {
	sort(a + 1, a + 1 + m);
	for (int i = 1; i <= m; ++i)
		if (fabs((a[i].y - a[i].x) * (a[k].y - a[k].x)) > eps)
			a[++k] = a[i];

	int h = 1, t = 0;
	q[++t] = a[1], m = k;
	for (int i = 2; i <= m; ++i) {
		while (h < t && !left(cross(q[t - 1], q[t]), a[i])) --t;
		while (h < t && !left(cross(q[h + 1], q[h]), a[i])) ++h;
		q[++t] = a[i];
	}
	while (h < t && !left(cross(q[t - 1], q[t]), q[h])) --t;
	
	m = 0;
	for (int i = h; i <= t; ++i)
		c[++m] = cross(q[i], q[i + 1]);
	c[0] = c[m];
	
	double ret = 0;
	for (int i = 1; i <= n; ++i)
		ret += dis(c[i - 1], c[i]);
	ret -= dis(b[1], b[n]);
	return ret;
}


vector <int> ban[N];
int main() {
	n = read(), m = read();
	for (int i = 1; i <= n; ++i) 
		b[i].x = read(), b[i].y = read();
	for (int i = 1; i <= m; ++i) {
		int x = read(), y = read();
		if (x > y) swap(x, y);
		ban[x].push_back(y);
	}
	
	m = 0;
	for (int i = 1; i <= n; ++i) 
		sort(ban[i].begin(), ban[i].end());
	if (ban[1].back() != n) {
		printf("%.10lf\n", dis(b[1], b[n]));
		return 0;
	}
	
	for (int i = 1; i <= n; ++i) {
		int k = ban[i].size() - 1;
		for (int j = n; j > i && k >= 0; --j) 
			if (j != ban[i][k--]) {
				a[++m] = line(b[j], b[i]);
				break;
			}
	}
	a[++m] = line(b[1], b[n]);
	
	double ans = hpi();
	printf("%.10lf\n", ans);
	return 0;
}
