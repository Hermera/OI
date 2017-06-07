#include <cstdio>
using namespace std;

const int maxn = 1e4+5;
int a[maxn], ly[maxn], N;

int calc(int x)
{
	ly[1] = x;
	for(int i = 2; i <= N; ++i)
	{
		ly[i] = a[i-1]-ly[i-1]-ly[i-2];
		if(ly[i] < 0 || ly[i] > 1) return 0;
	}
	if(a[N] != ly[N]+ly[N-1]) return 0;
	return 1;
}

int main()
{
	int ans = 0;
	scanf("%d", &N);
	for(int i = 1; i <= N; ++i) scanf("%d", a+i);
 	printf("%d\n", calc(0)+calc(1));
}
