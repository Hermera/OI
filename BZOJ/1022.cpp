#include <cstdio>
using namespace std;

int n, t;
int main() {	
	scanf("%d", &t);
	while(t--) {
		int ans = 0, flag = 0;
		scanf("%d", &n);
		for(int x; n--;) 
			scanf("%d", &x),
			flag |= (x != 1),
			ans ^= x;
		printf("%s\n", (bool)ans == flag ? "John" : "Brother");
	}
	return 0;
}
