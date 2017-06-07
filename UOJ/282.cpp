#include <cstdio>
using namespace std;

int cas, n;
int main() {
	scanf("%d", &cas);
	while(cas--) {
		scanf("%d", &n);
		printf("%d\n", n > 3 ? -1 : 1);
	}
	return 0;
}
