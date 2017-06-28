#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 1e6+5;
const int maxs = 26;
int n, a[maxn], s[maxn], t[maxn];
char str[maxn];

namespace ACautomation {
	int root, cnt, ch[maxn][maxs], fail[maxn], siz[maxn], q[maxn];
	int newnode() { memset(ch[cnt], -1, sizeof ch[cnt]); return cnt++; }
	void init() { root = newnode(); }

	void insert(int l, int r) {
		int now = root;
		for(int i = l; i <= r; ++i) {
			if(ch[now][a[i]] < 0) ch[now][a[i]] = newnode();
			now = ch[now][a[i]], ++siz[now];
		}
	}
	
	void build() {
		int h = 1, t = 0;
		for(int i = 0; i < maxs; ++i)
			if(ch[root][i] < 0) ch[root][i] = root;
			else fail[ch[root][i]] = root, q[++t] = ch[root][i];
		while(h <= t) {
			int v = q[h++];
			for(int i = 0; i < maxs; ++i)
				if(ch[v][i] < 0) ch[v][i] = ch[fail[v]][i];
				else fail[ch[v][i]] = ch[fail[v]][i], q[++t] = ch[v][i]; 
		}
		for(int i = t; i; --i) siz[fail[q[i]]] += siz[q[i]];
	}
	
	int query(int l, int r) {
		int now = root;
		for(int i = l; i <= r; ++i) now = ch[now][a[i]];
		return siz[now];
	}
}

int main() {
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		s[i] = t[i] = t[i-1];
		++s[i], scanf("%s", str);
		for(int j = 0; str[j]; ++j) 
			a[++t[i]] = str[j]-'a';
	}
	
	using namespace ACautomation;
	
	init();
	for(int i = 1; i <= n; ++i) 
		insert(s[i], t[i]); 
	build();
	for(int i = 1; i <= n; ++i) 
		printf("%d\n", query(s[i], t[i]));
	return 0;
}
