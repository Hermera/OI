#include <cstdio>
#include <algorithm>
#include <queue>
using namespace std;

const int maxn = 150005;
struct Build{ int len, lim; } build[maxn];
struct comp
{
	bool operator ()(const Build a, const Build b) const
		{ return a.len < b.len; }
};
priority_queue <Build, vector<Build>, comp> q;
int N, ans;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
bool cmp(Build a, Build b) { return a.lim < b.lim; }

int main()
{
	//freopen("data.in", "r", stdin);
	N = read();
	for(int i = 1; i <= N; ++i)	build[i].len = read(), build[i].lim = read();
	sort(build+1, build+N+1, cmp);
	for(int i = 1, now = 0; i <= N; ++i)
	{
		Build e = build[i];
		if(now+e.len <= e.lim) q.push(e), now += e.len, ++ans;
		else
		{
			Build v = q.top();
			if(v.len < e.len) continue;
			else now = now-(v.len-e.len), q.pop(), q.push(e);
		}
	}
	printf("%d\n", ans);
	return 0;
}
