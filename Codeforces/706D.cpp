#include <cstdio>
using namespace std;

const int maxn = 6e6+5, maxl = 30;
struct Trie {
	int ch[maxn][2], sz[maxn], root, cnt;
	int newnode() { ++cnt; ch[cnt][0] = ch[cnt][1] = -1; return cnt; }
	void init() { root = newnode(); }
	void modify(int x, int v) {
		int now = root;
		sz[now] += v;
		for(int i = maxl; ~i; --i) {
			bool w = x&(1<<i);
			if(ch[now][w] < 0) ch[now][w] = newnode();
			now = ch[now][w], sz[now] += v;
		}
	}
	
	int query(int x) {
		int now = root, ret = 0;
		for(int i = maxl; ~i; --i) {
			bool w = x&(1<<i);
			if(sz[ch[now][!w]]) now = ch[now][!w], ret += (1<<i);
			else now = ch[now][w];
		}
		return ret;
	}
} T;
int n;
char op[3];

int main() {
	freopen("706D.in", "r", stdin);

	T.init();
	scanf("%d", &n);
	T.modify(0, 1);
	for(int i = 1, x; i <= n; ++i) {
		scanf("%s%d", op, &x);
		if(*op == '+') T.modify(x, 1);
		if(*op == '-') T.modify(x, -1);
		if(*op == '?') printf("%d\n", T.query(x));
	}
	return 0;
}
