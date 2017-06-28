#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

const int maxn = 2e6+5;
const ll inf = 2e18;
ll CirLen, N, K, Mod, len[maxn], next[maxn], f[maxn], first[maxn]; 
int CirBegin;
bool vis[maxn];

struct Matrix
{
	ll s[5][5];
	Matrix() { memset(s, 0, sizeof(s)); }
	
	friend Matrix operator *(const Matrix &a, const Matrix &b)
	{
		Matrix ret;
		for(int i = 1; i <= 3; ++i)
		for(int j = 1; j <= 3; ++j)
		for(int k = 1; k <= 3; ++k)
			ret.s[i][j] += a.s[i][k]*b.s[k][j], ret.s[i][j] %= Mod;
		return ret;
	}
	
	friend Matrix operator ^(const Matrix &a, const ll c)
	{
		Matrix ans, x = a; ll k = c;
		ans.s[1][1] = ans.s[2][2] = ans.s[3][3] = 1;
		for( ; k; k >>= 1, x = x*x)
			if(k&1) ans = ans*x;
		return ans;
	}
	
} A, B, C, Z;

void ExGcd(int a, int b, int &d, int &x, int &y)
{
	if(b == 0) { d = a, x = 1, y = 0; return; }
	ExGcd(b, a%b, d, x, y);
	int t = x; x = y, y = t-(a/b)*y;
}

int ModInv(int a, int n)
{
	int d = 0, x = 0, y = 0;
	ExGcd(a, n, d, x, y);
	if(d != 1) return 0;
	return (x+n)%n;
}

void init()
{
	scanf("%lld%lld%lld", &N, &K, &Mod);
	f[1] = f[2] = 1;
	for(int i = 3; i == 3 || f[i-1] != 1 || f[i-2] != 1; ++i)
	{
		f[i] = (f[i-1]+f[i-2])%K;
		if(!first[f[i]]) first[f[i]] = i;
	}
	for(int i = 1; i < K; ++i)
	{
		len[i] = first[ModInv(i, K)];
		if(ModInv(i, K) != 0 && len[i] != 0) next[i] = f[len[i]-1]*i%K;
		else next[i] = -1, len[i] = inf;
	}
	for(CirBegin = 1; CirBegin >= 0 && !vis[CirBegin]; CirBegin = next[CirBegin]) vis[CirBegin] = true;
	
	A.s[1][2] = A.s[2][1] = A.s[2][2] = A.s[3][3] = 1;
	B.s[1][1] = B.s[2][2] = B.s[3][3] = 1;
	B.s[3][2] = -1;
	C.s[1][1] = C.s[2][2] = C.s[3][3] = 1;
	Z.s[1][1] = Z.s[1][3] = 1;
}

void work()
{
	for(int i = 1; i != CirBegin; i = next[i])
	{
		if(N < len[i]) { Z = Z*(A^N); N = 0; break; }
		Z = Z*(A^len[i]), Z = Z*B, N -= len[i];
	}
	if(N == 0) return;
	
	int x = CirBegin;
	do  
	{
		C = C*(A^len[x]);
		C = C*B;
		CirLen += len[x];
		x = next[x];
	}
	while (x != CirBegin);
		
	Z = Z*(C^(N/CirLen));
	N %= CirLen;
		
	for(int i = CirBegin; ; i = next[i])
	{
		if(N < len[i]) { Z = Z*(A^N), N = 0; break; }
		Z = Z*(A^len[i]), Z = Z*B, N -= len[i];
	}
}

int main()
{
//	freopen("rabbit.in", "r", stdin);
//	freopen("rabbit.out", "w", stdout);
	init();
	work();
	printf("%lld\n", (Z.s[1][2]+Mod)%Mod);
	return 0;
}
		
