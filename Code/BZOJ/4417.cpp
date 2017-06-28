#include <cstdio>
#include <cstring>
using namespace std;

const int mod = 30011, maxn = 105;
int n, m, r;
struct Matrix {
	int t[maxn][maxn];
	Matrix() { memset(t, 0, sizeof(t)); }
	int &operator()(int x, int y) { return t[x][y]; }
	friend Matrix operator *(Matrix a, Matrix b) {
		Matrix c;
		for(int i = 1; i <= r; ++i)
		for(int j = 1; j <= r; ++j)
		for(int k = 1; k <= r; ++k)
			(c(i, j) += a(i, k)*b(k, j))%= mod;
		return c;
	}
	
	friend Matrix operator ^(Matrix a, int k) {
		Matrix c;
		for(int i = 1; i <= r; ++i) c(i, i) = 1;
		for( ; k; k >>= 1, a = a*a)
			if(k&1) c = c*a;
		return c;
	}
} A;

int main() {
	scanf("%d%d", &n, &m), r = n<<1;
	for(int i = 1; i <= n; ++i) A(i, i+n) = 1;
	for(int i = n+1; i <= 2*n; ++i) {
		A(i, i-n) = A(i-n, i-n) = 1;
		if(i-n > 1) A(i-n-1, i-n) = 1;
		if(i-n < n) A(i-n+1, i-n) = 1;
	}
	
	A = A^(m-1);
	int ans = A(r, 1);
	if(n > 1) (ans += A(r-1, 1))%= mod;
	printf("%d\n", (ans+mod)%mod);
	return 0;
}
