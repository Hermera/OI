#include <cstdio>
#include <algorithm>
using namespace std;
typedef unsigned long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = (x<<1)+(x<<3)+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e5+5;
const ll Bin = 20000909;
int N, M, K, cnt, a[maxn], root[maxn];;
ll P = 1, b[maxn], h[maxn];
struct Tree { int tot, l, r; } tree[maxn*25];

void insert(int &o, int l, int r, ll v) {
	tree[++cnt] = tree[o], o = cnt;
	++tree[o].tot;
	if(l == r) return;
	int mid = (l+r)>>1;
	if(v <= h[mid]) insert(tree[o].l, l, mid, v);
	else insert(tree[o].r, mid+1, r, v);
}

bool query(int x, int y, int l, int r, ll v) {
	if(l == r) return (tree[y].tot-tree[x].tot > 0 && h[l] == v);
	int mid = (l+r)>>1;
	if(v <= h[mid]) return query(tree[x].l, tree[y].l, l, mid, v);
	else return query(tree[x].r, tree[y].r, mid+1, r, v);
}


int main() {
	N = read(), M = read(), K = read();
	for(int i = 2; i <= K; ++i) P *= Bin;
	for(int i = 1; i <= N; ++i) a[i] = read();
	for(int i = 1; i <= K; ++i) b[1] = b[1]*Bin+a[i];
	
	h[1] = b[1];
	for(int i = 2; i <= N-K+1; ++i) {
		b[i] = b[i-1]-P*a[i-1];
		b[i] = b[i]*Bin+a[i+K-1];
		h[i] = b[i];
	}
	N = N-K+1;
	sort(h+1, h+1+N);
	for(int i = 1; i <= N; ++i) insert(root[i] = root[i-1], 1, N, b[i]);
	
	while(M--) {
		ll op = 0;
		int x = read(), y = read()-K+1;
		for(int i = 1; i <= K; ++i) op = op*Bin+read();
		if(y < x) { printf("Yes\n"); continue; }
		printf("%s\n", query(root[x-1], root[y], 1, N, op) ? "No" : "Yes");
	}
	return 0;
}
