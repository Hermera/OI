#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 4e5+5, maxl = 30;
struct Trie {
	int ch[maxn*30][2], root, cnt;
	void clear() {
		root = cnt = 0;
		ch[0][0] = ch[0][1] = -1;
	}
	
	int newnode() {
		++cnt;
		ch[cnt][0] = ch[cnt][1] = -1;
		return cnt;
	}
	
	void insert(int x) {
		int now = root;
		for(int i = maxl; ~i; --i) {
			bool w = x&(1<<i);
			if(ch[now][w] < 0) ch[now][w] = newnode();
			now = ch[now][w];
		}
	}
	
	int query(int x) {
		int now = root, ret = 0;
		for(int i = maxl; ~i; --i) {
			bool w = x&(1<<i);
			if(ch[now][!w] < 0) now = ch[now][w];
			else now = ch[now][!w], ret += (1<<i);
		}
		return ret;
	}
} T;
int N, a[maxn], b[maxn], c[maxn], f[maxn], g[maxn];

int main() {
	N = read();
	for(int i = 1; i <= N; ++i) a[i] = read();
	for(int i = 1; i <= N; ++i) b[i] = a[i]^b[i-1];
	for(int i = N; i >= 1; --i) c[i] = a[i]^c[i+1];
	
	T.clear();
	for(int i = 1; i <= N; ++i) 
		T.insert(b[i-1]), f[i] = T.query(b[i]);
	
	T.clear();
	for(int i = N; i >= 1; --i)
		T.insert(c[i+1]), g[i] = T.query(c[i]);
	
	int ans = 0;
	for(int i = 1; i <= N; ++i) f[i] = max(f[i], f[i-1]);
	for(int i = N; i >= 1; --i) g[i] = max(g[i], g[i+1]);
	for(int i = 2; i <= N; ++i) ans = max(ans, f[i-1]+g[i]);
	printf("%d\n", ans);
	return 0;
}
