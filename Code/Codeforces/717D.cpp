#include <cstdio>
#include <vector>
using namespace std;

const int maxn = 305;
int N, K;
double p[maxn];

struct Matrix {
	vector <double> s;
	int n, m;
	double &operator ()(int r, int c) 
		{ return s[r*m+c]; }
	Matrix(int _n, int _m): n(_n), m(_m) {
		s.resize(n*m);
		for(int i = 0; i < n; ++i)
		for(int j = 0; j < m; ++j)
			s[i*m+j] = 0;
	}
	
	friend Matrix operator *(Matrix a, Matrix b) {
		Matrix c(a.n, b.m);
		for(int i = 0; i < c.n; ++i)
		for(int j = 0; j < c.m; ++j)
		for(int k = 0; k < a.m; ++k)
			c(i, j) += a(i, k)*b(k, j);
		return c;
	}
	
	friend Matrix operator ^(Matrix a, int k) {
		Matrix b(a.n, a.n);
		for(int i = 0; i < a.n; ++i) b(i, i) = 1;
		for( ; k; k >>= 1, a = a*a)
			if(k&1) b = b*a;
		return b;
	}
};

int main() {
	freopen("717D.in", "r", stdin);

	scanf("%d%d", &K, &N); 
	for(int i = 0; i <= N; ++i) scanf("%lf", p+i);
	++N;
	while(N&(N-1)) ++N;
	
	Matrix A(N, 1), B(N, N);
	for(int i = 0; i < N; ++i)
	for(int j = 0; j < N; ++j) 
		B(i^j, i) = p[j];
		
	A(0, 0) = 1;
	A = (B^K)*A;
	printf("%.8lf\n", 1.0-A(0, 0));
	return 0;
}
		
	
