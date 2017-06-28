#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
typedef long long ll;
const int maxn = 5e4+5;
const int maxm = 1003;
const int Mod = 10007;
int N, M, L[maxn], f[2][maxn], sum[maxn];

bool judge(int x)
{
	int re = 0, now = x;
	for(int i = 1; i <= N; ++i)
	{
		if(now+L[i] > x) ++re, now = L[i];
		else now += L[i];
		if(re > M) return false;
	}
	return true;
}

ll calc(int x)
{
	int ret = 0, pre = 0, cur = 1;
	f[0][0] = 1;
	for(int i = 1; i <= M; i++)
	{
		int temp = 0, k = i-2;
		for(int j = i; j <= N; j++)
		{
			temp += f[pre][j-1], temp %= Mod;
			while(sum[j]-sum[k+1] > x)
				temp += Mod-f[pre][++k], temp %= Mod;
			f[cur][j] = temp;
		}
		ret += f[cur][N], ret %= Mod;
		cur ^= 1, pre ^= 1;
	}
	return ret;
}

int main()
{
	freopen("data.in", "r", stdin);
	N = read(), M = read()+1;
	int left = 0, right = 0, ans = 0;
	for(int i = 1; i <= N; ++i) L[i] = read(), sum[i] = sum[i-1]+L[i], left = max(left, L[i]), right += L[i];
	while(left <= right)
	{
		int mid = (left+right)>>1;
		if(judge(mid)) ans = mid, right = mid-1;
		else left = mid+1;
	}
	printf("%d %lld\n", ans, calc(ans));
	return 0;
}
