#include <cstdio>
using namespace std;

const int maxn = 1e4+5;
char s[maxn][10];
int n, flag;

int main() {
	freopen("711A.in", "r", stdin);

	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) scanf("%s", s[i]);
	for(int i = 1; i <= n; ++i) {
		if(s[i][0] == s[i][1] && s[i][0] == 'O') {
			s[i][0] = s[i][1] = '+';
			flag = true;
			break;
		}
		if(s[i][3] == s[i][4] && s[i][3] == 'O') {
			s[i][3] = s[i][4] = '+';
			flag = true;
			break;
		}
	}
	
	if(!flag) printf("NO\n");
	else {
		printf("YES\n");
		for(int i = 1; i <= n; ++i) printf("%s\n", s[i]);
	}
	return 0;
}
