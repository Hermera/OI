#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 3e6+5;
int K, N, ans, a[maxn];
set <int> S;

int main()
{
	freopen("data.in", "r", stdin);

	K = read(), N = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	
	int l = 1, r = 1;
	for(; r <= N; ++r)
	{
		S.insert(a[r]);
		while(1)
		{
			set <int> :: iterator s = S.begin(), t = S.end(); --t;
			if(*t - *s > K) S.erase(a[l]), ++l;
			else break;
		}
		ans = max(ans, r-l+1);
	}
	
	printf("%d\n", ans);
	return 0;
}
