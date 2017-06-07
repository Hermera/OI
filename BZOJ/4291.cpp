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
int N, sum, tot, mst = 1e9;

int main()
{
	N = read();
	for(int i = 1; i <= N; ++i)
	{
		int a = read();
		sum += a;
		if(a&1) ++tot, mst = min(mst, a);
	}
	if(tot&1) sum -= mst;
	if(sum) printf("%d\n", sum);
	else printf("NIESTETY\n");
	return 0;
}
