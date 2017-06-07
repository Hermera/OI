#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
const int maxn = 3e4+5;
const int maxl = 205;
const int maxs = 70;
const ll Mod = 100000000009;
const ll prime = 97;
ll prev[maxn][maxl], next[maxn][maxl], f[maxn], ans;
int N, L, S, K;
char s[maxn][maxl];

int H(char ch)
{
	if(ch >= 'a' && ch <= 'z') return ch-'a';
	if(ch >= 'A' && ch <= 'Z') return ch-'A'+26;
	if(ch >= '0' && ch <= '9') return ch-'0'+52;
	if(ch == '_') return 62;
	if(ch == '@') return 63;
}

void init()
{
	scanf("%d%d%d", &N, &L, &S);
	for(int i = 1; i <= N; ++i)
	{
		scanf("%s", s[i]+1);
		for(int j = 1; j <= L; ++j)
			prev[i][j] = prev[i][j-1]*prime+H(s[i][j]), prev[i][j] %= Mod;
		for(int j = L; j >= 1; --j)
			next[i][j] = next[i][j+1]*prime+H(s[i][j]), next[i][j] %= Mod;
	}
}

ll calc()
{
	ll sum = 0, tot = 1;
	for(int i = 2; i <= N+1; ++i)
		if(f[i] == f[i-1]) ++tot;
		else sum += tot*(tot-1), tot = 1;
	return sum;
}

int main()
{
	freopen("data.in", "r", stdin);
	init();
	for(int i = 1; i <= L; ++i)
	{
		for(int j = 1; j <= N; ++j)
		f[j] = prev[j][i-1]*233+next[j][i+1]*113;
		sort(f+1, f+1+N);
		ans += calc();
	}
	printf("%lld\n", ans>>1);
	return 0;
}
