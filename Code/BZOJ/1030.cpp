#include <queue>
#include <cstdio>
#include <cstring>
using namespace std;

const int maxn = 6005;
const int maxm = 105;
const int maxs = 26;
const int mod = 10007;
int n, m, f[maxm][maxn], g[maxm][maxn];
char str[maxm];

int idx(char ch) { return ch-'A'; }
void add(int &x, int y) {
	x += y;
	if(x >= mod) x -= mod;
}

struct ACM {
	int t, root, ch[maxn][maxs], fail[maxn];
	bool end[maxn];
	int newnode() { ++t, memset(ch[t], -1, sizeof(ch[t])); return t; }
	void init() { t = 0; root = newnode(); }
	
	void insert() {
		scanf("%s", str);
		int now = root;
		for(int i = 0; str[i]; ++i) {
			int w = idx(str[i]);
			if(ch[now][w] < 0) ch[now][w] = newnode();
			now = ch[now][w];
		}
		end[now] = 1;
	}
	
	void build() {
		queue <int> q;
		for(int i = 0; i < maxs; ++i)
			if(ch[root][i] < 0) ch[root][i] = root;
			else fail[ch[root][i]] = root, q.push(ch[root][i]);
		while(!q.empty()) {
			int v = q.front(); q.pop();
			end[v] |= end[fail[v]];
			for(int i = 0; i < maxs; ++i)
				if(ch[v][i] < 0) ch[v][i] = ch[fail[v]][i];
				else fail[ch[v][i]] = ch[fail[v]][i], q.push(ch[v][i]);
		}
	}
	
	int query() {
		f[0][root] = 1;
		for(int i = 0; i < m; ++i) 
		for(int j = 1; j <= t; ++j) if(f[i][j]) {
			if(end[j]) continue;
			for(int k = 0; k < 26; ++k)
				(f[i+1][ch[j][k]] += f[i][j])%= mod;
		}
		
		int ans = 1;
		for(int i = 1; i <= m; ++i) (ans *= 26)%= mod;
		for(int i = 1; i <= t; ++i) if(!end[i]) (ans -= f[m][i])%= mod;
		return (ans+mod)%mod;
	}
} ac;

int main() {
	ac.init();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i) ac.insert();
	ac.build();
	printf("%d\n", ac.query());
	return 0;
}
