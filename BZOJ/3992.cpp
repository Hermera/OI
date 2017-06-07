#include <cstdio>
#include <algorithm>
using namespace std;
const int maxn = 2e4+5, Mod = 1004535809;
typedef long long ll;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
int N, P, X, M, l, len = 1, invlen, root;
int ans[maxn], a[maxn], b[maxn], T[maxn], occ[maxn], wn[maxn], num[maxn], pos[maxn];

int QuickPow(int x, int k, int p)
{
	int ans = 1;
	for( ; k; k >>= 1, x = (ll)x*x%p)
	if(k&1) 
		ans = (ll)ans*x%p;
	return ans;
}

bool Judge(int x, int p)
{
	for(int i = 2; i*i <= p; ++i)
		if((p-1)%i == 0 && QuickPow(x, (p-1)/i, p) == 1) return false;
	return true;
}

int FindRoot(int p)
{
	if(p == 2) return 1;
	int ret = 2;
	for(; !Judge(ret, P); ++ret);
	return ret;
}

void Init()
{
	N = read(), P = read(), X = read(), M = read();
	for(int i = 1; i <= M; ++i) T[i] = read();
	while(len <= (P<<1)-2) len <<= 1, ++l;
	
	invlen = QuickPow(len, Mod-2, Mod);
	root = FindRoot(P);
	
	for(int i = 0; i < P-1; ++i) num[i] = !i ? 1 : num[i-1]*root%P, pos[num[i]] = i;
	for(int i = 0, t = 1; i <= l; ++i, t <<= 1)
		wn[i] = QuickPow(3, (P-1)/t, P);
    
    for(int i = 1; i <= M; ++i)
    if(T[i]) ++occ[pos[T[i]]];
}

void rev(int *y)
{
	for(int i = 1, j = len>>1, k; i < len-1; ++i)
	{
		if(i < j) swap(y[i], y[j]);
		k = len>>1;
		while(j >= k) j -= k, k >>= 1;
		if(j < k) j += k;
	}
}

void NTT(int *y, int on)
{
	rev(y);
	int id = 1;
	for(int h = 2; h <= len; h <<= 1, ++id)
	for(int j = 0; j < len; j += h)
		for(int k = j, w = 1; k < j+h/2; ++k)
		{
			int u = y[k]%Mod, t = w*y[k+h/2]%Mod;
			y[k] = (u+t)%Mod; y[k+h/2]=((u-t)%Mod+Mod)%Mod;
			w = w*wn[id]%Mod;
		}
	if(on == -1)
	{
		for(int i = 1; i < len/2; ++i) swap(y[i], y[len-i]);
		for(int i = 0; i < len; ++i)
			y[i] = (ll)y[i]*invlen%Mod;
	}
}

void Mul(int *ret, int *d1, int *d2)
{
	for(int i = 0; i < len; ++i) a[i] = d1[i], b[i] = d2[i];
	NTT(a, 1); NTT(b, 1);
	for(int i = 0; i < len; ++i) ret[i] = a[i]*b[i]%Mod;
	NTT(ret, -1);
	for(int i = len-1; i >= P-1; --i) ret[i-P+1] = 1LL*(ret[i-P+1]+ret[i])%Mod, ret[i] = 0;
}

int Solve(int *num, int k)
{
	ans[0] = 1;
	for( ; k; k >>= 1, Mul(num, num, num))
	if(k&1) Mul(ans, num, ans);
	return ans[pos[X]];
}

int main()
{
	freopen("data.in", "r", stdin);
	Init();
	printf("%d\n", Solve(occ, N));
	return 0;
}
