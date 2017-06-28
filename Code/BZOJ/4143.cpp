#include <cstdio>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
const int maxn = 5e5+5;
struct Data{ int s, t; } meet[maxn], ans[30];
int N, M;

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1; i <= N; ++i)
	{
		int a = read(), b = read();
		Data &d = ans[read()];
		meet[i] = (Data){a, b};
		if(!d.s || a > meet[d.s].s) d.s = i;
		if(!d.t || b < meet[d.t].t) d.t = i;
	}
	
	for(int i = 1; i <= M; ++i)
	{
		Data &d = ans[i];
		if(d.s && d.t && d.s != d.t && meet[d.s].s > meet[d.t].t) 
			printf("TAK %d %d\n", d.t, d.s);
		else printf("NIE\n");
	}
	
	return 0;
}
