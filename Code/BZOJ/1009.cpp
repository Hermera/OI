#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 105;
struct Matrix {
	int r, c, s[maxn][maxn];
	Matrix(int x = 0, int y = 0): r(x), c(y) {
		memset(s, 0, sizeof(s));
	}
	int &operator ()(int x, int y) { return s[x][y]; }
};
int n, m, mod, go[maxn][15];
char s[maxn];

Matrix operator *(Matrix a, Matrix b) {
	Matrix x(a.r, b.c);
	for(int i = 0; i < a.r; ++i)
	for(int j = 0; j < b.c; ++j)
	for(int k = 0; k < a.c; ++k)
		(x(i, j) += a(i, k)*b(k, j))%= mod;
	return x;
}

Matrix operator ^(Matrix a, int k) {
	Matrix x(a.r, a.r);
	for(int i = 0; i < a.r; ++i) x(i, i) = 1;
	for( ; k; k >>= 1, a = a*a)
		if(k&1) x = x*a;
	return x;
}

bool judge(int x, int y, int c) {
	if(s[y]-'0' != c) return 0;
	for( --y; y; --x, --y)
		if(s[x] != s[y]) return 0;
	return 1;
}

int trans(int x, int y) {
	for(int i = x+1; i; --i) 
		if(judge(x, i, y)) return i;
	return 0;
}

int main() {
	scanf("%d%d%d", &n, &m, &mod);
	scanf("%s", s+1);

	for(int i = 0; i < m; ++i)
	for(int j = 0; j <= 9; ++j)
		go[i][j] = trans(i, j);
	
	Matrix A(m, 1), P(m, m);
	A(0, 0) = 1;
	for(int i = 0; i < m; ++i)
	for(int j = 0; j < 10; ++j)
		if(go[i][j] < m) ++P(go[i][j], i);
	A = (P^n)*A;
	
	int ans = 0;
	for(int i = 0; i < m; ++i) (ans += A(i, 0))%= mod;
	printf("%d\n", ans);
	return 0;
}
