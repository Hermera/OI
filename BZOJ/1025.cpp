#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
const int maxn = 1005;
int N, cnt, prime[maxn];
ll f[2][maxn];
bool vis[maxn];

void MakePrime()
{
	for(int i = 2; i <= N; ++i)
	{
		if(!vis[i]) prime[++cnt] = i;
		for(int j = 1; j <= cnt && i*prime[j] <= N; ++j)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j] == 0) break;
		}
	}
}

ll solve()
{
	ll *pre = f[0], *cur = f[1], ans = 0;
	cur[0] = 1;
	for(int i = 1; i <= cnt; ++i)
	{
		for(int j = 0; j <= N; ++j) pre[j] = cur[j];
		for(int j = prime[i]; j <= N; j *= prime[i])
		for(int k = N-j; k >= 0; --k) cur[k+j] += pre[k];
	}
	for(int i = 0; i <= N; ++i) ans += cur[i];
	return ans;
}

int main()
{
	scanf("%d", &N);
	MakePrime();
	printf("%lld\n", solve());
	return 0;
}
