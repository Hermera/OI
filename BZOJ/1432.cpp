#include <cstdio>
#include <algorithm>
using namespace std;
int main()
{
	int N, K;
	scanf("%d%d", &N, &K);
	if(K == 1) { printf("%d", min(N, 2)); return 0; }
	printf("%d", min(K*2, (N-K+1)*2));
	return 0;
}
