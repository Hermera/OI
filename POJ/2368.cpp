#include <cstdio>
#include <algorithm>
using namespace std;

const int N = 105;
int x, m, d[N];
int main() {
	scanf("%d", &x);
	for(int i = 1; i*i <= x; ++i) 
		if(x % i == 0) {
			d[++m] = i;
			d[++m] = x / i;
		}
	sort(d + 1, d + 1 + m);

	for(int i = 1; i <= m; ++i)
		if(d[i] > 2) {
			printf("%d\n", d[i] - 1);
			return 0;
		}

	printf("0\n");
	return 0;
}