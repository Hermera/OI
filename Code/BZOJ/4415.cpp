#include <cstdio>
using namespace std;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x<<1)+(x<<3)+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e6+5;
int N, M = 1, R = 1, now, tree[maxn];

void modify(int x, int v) { while(x <= M) tree[x] += v, x += x&-x; }
int query(int x) {
	int ret = 0;
	while(x) ret += tree[x], x -= x&-x;
	return ret;
}

int get(int x) {
	int p = 0;
	for(int i = M; ; i >>= 1) {
		if(tree[p+i] < x) p += i, x -= tree[p];
		if(!i) break;
	}
	return now = p+1;
}

int main() {
	N = read();
	while(M < N) M <<= 1;
	for(int i = 1; i <= N; ++i) modify(i, 1);
	for(int i = N; i; --i) {
		R = (R+read()-1)%i+1; 
		modify(get(R), -1); 
		printf("%d\n", now);
	}
	return 0;
}
