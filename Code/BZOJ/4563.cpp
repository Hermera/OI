#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 2005, maxd = 500, Mod = 10000;
struct Data
{
	int s[maxd], len;
	Data() { memset(s, 0, sizeof(s)); len = 1; }
	friend Data operator +(const Data &a, const Data &b)
	{
		Data x;
		for(int i = 1; i <= max(a.len, b.len); ++i)
			x.s[i] += a.s[i]+b.s[i], x.s[i+1] += x.s[i]/Mod, x.s[i] %= Mod;
		while(x.s[x.len+1]) ++x.len, x.s[x.len+1] += x.s[x.len]/Mod, x.s[x.len] %= Mod;
		return x;
	}
	friend Data operator *(const Data &a, const int &b)
	{
		Data x;
		for(int i = 1; i <= a.len; ++i)
			x.s[i] += a.s[i]*b, x.s[i+1] += x.s[i]/Mod, x.s[i] %= Mod;
		while(x.s[x.len+1]) ++x.len, x.s[x.len+1] += x.s[x.len]/Mod, x.s[x.len] %= Mod;
		return x;
	}
	void print()
	{
		printf("%d", s[len]);
		for(int i = len-1; i; --i) printf("%04d", s[i]);
		printf("\n");
	}
} dp[maxn];
int N;

int main()
{
	scanf("%d", &N);
	dp[2].s[1] = 1;
	for(int i = 3; i <= N; ++i)
		dp[i] = (dp[i-1]+dp[i-2])*(i-1);
	dp[N].print();
	return 0;
}
