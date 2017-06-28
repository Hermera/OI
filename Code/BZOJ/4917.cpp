#include <cstdio>
using namespace std;

int q, x;
int main() {
	scanf("%d", &q);
	while(q--) {
		scanf("%u", &x);

		for(int i = 0 ; i <= 15; ++i) x -= ((x >> i) & 1) * (1 << (i + 16));
		for(int i = 31; i >= 11; --i) x ^= ((x >> i) & 1) * (1 << (i - 11));
		for(int i = 0 ; i <= 28; ++i) x -= ((x >> i) & 1) * (1 << (i + 3));
		for(int i = 31; i >= 6 ; --i) x ^= ((x >> i) & 1) * (1 << (i - 6));
		for(int i = 0 ; i <= 21; ++i) x -= ((x >> i) & 1) * (1 << (i + 10));

		printf("%u\n", x);
	}
	return 0;
}