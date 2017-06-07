#include <cstdio>
using namespace std;
int main()
{
	int sum = 0, N; long long pre = -1, now;
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i)
	{
		scanf("%lld", &now);
		if(pre == now) ++sum;
		else
		{
			if(!sum) pre = now, sum = 1;
			else --sum;
		}
	}
	printf("%lld\n", pre);
	return 0;
}
