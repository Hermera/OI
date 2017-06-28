#include <cstdio>
using namespace std;

int n, x1, x2, y1, y2;
int main() {
	scanf("%d", &n);
	
	printf("YES\n");
	while(n--) {
		scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
		printf("%d\n", (x1&1)*2 + (y1&1) + 1);
	}
	return 0;
}
