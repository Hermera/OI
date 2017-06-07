#include <cstdio>
#include <algorithm>
#include <map>
using namespace std;
typedef pair<int, int> Pi;

const int maxn = 2e5+5;
map <Pi, int> vis;
char s[maxn];
int n, ans, J, O, I;

int main() {
	scanf("%d%s", &n, s+1);
	vis[make_pair(0, 0)] = 0;
	for(int i = 1; i <= n; ++i) {
		if(s[i] == 'J') ++J;
		if(s[i] == 'O') ++O;
		if(s[i] == 'I') ++I;
	
		Pi x = make_pair(J-O, J-I);
		if(!vis.count(x)) vis[x] = i;
		ans = max(ans, i-vis[x]);
	}
	printf("%d\n", ans);
	return 0;
}
			
