#include <cstdio>
#include <cstring>
#define mset(x, a) memset(x, 0, sizeof(x))
using namespace std;
const int maxn = 105, Mod = 2009;
int N, T;
char s[maxn];
struct Matrix { int p[maxn][maxn], len; } ans;

Matrix operator *(const Matrix a, const Matrix b)
{
	Matrix c; c.len = a.len;
	mset(c.p, 0);
	for(int i = 1; i <= a.len; ++i)
	for(int j = 1; j <= b.len; ++j)
	for(int k = 1; k <= a.len; ++k)
		c.p[i][j] += a.p[i][k]*b.p[k][j], c.p[i][j] %= Mod;
	return c;
}

Matrix QuickPow(Matrix a, int k)
{
	Matrix ans; ans.len = a.len;
	for(int i = 1; i <= a.len; ++i)
		ans.p[i][i] = 1;
	for(; k; k >>= 1, a = a*a)
	if(k&1) ans = ans*a;
	return ans;
}

int main()
{
	freopen("data.in", "r", stdin);
	scanf("%d%d", &N, &T); ans.len = 9*N;
	for(int i = 1; i <= N; ++i)
	for(int j = 1; j <= 8; ++j)
		ans.p[9*(i-1)+j][9*(i-1)+j+1] = 1;
	for(int i = 1; i <= N; ++i)
	{
		scanf("%s", s+1);
		for(int j = 1; j <= N; ++j)
		if(s[j] > '0')
			ans.p[9*(i-1)+s[j]-'0'][9*(j-1)+1] = 1;
	}
	ans = QuickPow(ans, T);
	printf("%d\n", ans.p[1][9*(N-1)+1]);
	return 0;
}
