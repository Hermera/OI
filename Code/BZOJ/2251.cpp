#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 1e7+5;

int n;
char s[maxn];

namespace Trie {
	int root, cnt, ch[maxn][2], siz[maxn];
	int newnode() { memset(ch[cnt], -1, sizeof ch[cnt]); return cnt++; }
	void init() { root = newnode(); }
	
	void insert(int x) {
		int now = root;
		for(int i = x; i <= n; ++i) {
			if(ch[now][s[i]] < 0) ch[now][s[i]] = newnode();
			now = ch[now][s[i]], ++siz[now];
		}
	}
	
	void dfs(int x) {
		if(x && siz[x] > 1) printf("%d\n", siz[x]);
		if(ch[x][0]) dfs(ch[x][0]);
		if(ch[x][1]) dfs(ch[x][1]);
	}
};

int main() {
	using namespace Trie;
	
	init();
	scanf("%d%s", &n, s+1);
	for(int i = 1; i <= n; ++i) s[i] -= '0';
	for(int i = 1; i <= n; ++i) insert(i);
	dfs(root);
	return 0;
}
