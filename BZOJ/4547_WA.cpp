#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int read() {
	char ch = getchar(); int x = 0, t = 1;
	while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x*t;
}

const int mod = 10000007;
struct Matrix {
	ll s[4][4]; int r, c;
	ll &operator ()(int x, int y) { return s[x][y]; }
	Matrix(int x = 0, int y = 0) {
		r = x, c = y;
		memset(s, 0, sizeof(s));
	}
	
	friend Matrix operator *(Matrix a, Matrix b) {
		Matrix x(a.r, b.c);
		for(int i = 1; i <= a.r; ++i)
		for(int j = 1; j <= b.c; ++j)
		for(int k = 1; k <= a.c; ++k)
			(x(i, j) += a(i, k)*b(k, j))%= mod;
		return x;
	}
	
	friend Matrix operator ^(Matrix a, int k) {
		Matrix x(a.r, a.r);
		for(int i = 1; i <= a.r; ++i) x(i, i) = 1;
		for( ; k; k >>= 1, a = a*a)
			if(k&1) x = x*a;
		return x;
	}
};

int n, k, fir, sec;
ll sum;

int main() {
	freopen("4547.in", "r", stdin);
	freopen("4547.out", "w", stdout);
	
	while(scanf("%d%d", &n, &k) != EOF) {
		fir = sec = -mod, sum = 0;
		for(int i = 1, x; i <= n; ++i) {
			x = read(), (sum += x)%= mod;
			if(x > fir) sec = fir, fir = x;
			else if(x > sec) sec = x;
		}
		
		if(fir < 0) {
			(sum += 1ll*k%mod*(fir+sec))%= mod;
			printf("%lld\n", (sum+mod)%mod);
			return 0;
		} 
		
		while(k && sec < 0)
			--k, sec += fir, (sum += sec)%= mod;
		Matrix P(3, 3), A(3, 1);
		A(1, 1) = sum;
		A(2, 1) = fir;
		A(3, 1) = sec;
		P(1, 1) = P(1, 2) = P(1, 3) = 1;
		P(2, 2) = P(2, 3) = 1;
		P(3, 2) = 1;
		
		printf("%lld\n", (((P^k)*A)(1, 1)+mod)%mod);
	}
	return 0;
}
