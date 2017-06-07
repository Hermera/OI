#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 2e6+5;
int n, m, q, v[maxn], nxt[maxn], rig[maxn], xn[maxn], xr[maxn];

int p(int x, int y) { return x*(m+1)+y+1; }
int Get(int x, int y) {
	int o = p(0, 0);
	while(x--) o = nxt[o];
	while(y--) o = rig[o];
	return o;
}

void modify_r(int n1, int n2, int len) {
	for(int i = 1; i <= len; ++i) {
		xn[n1] = nxt[n2];
		xn[n2] = nxt[n1];
		n1 = rig[n1], n2 = rig[n2];
	}
}

void modify_c(int n1, int n2, int len) {
	for(int i = 1; i <= len; ++i) {
		xr[n1] = rig[n2];
		xr[n2] = rig[n1];
		n1 = nxt[n1], n2 = nxt[n2];
	}
}

void done_r(int n1, int n2, int len) {
	for(int i = 1; i <= len; ++i) {	
		nxt[n1] = xn[n1], nxt[n2] = xn[n2];
		n1 = rig[n1], n2 = rig[n2];
	}
}

void done_c(int n1, int n2, int len) {
	for(int i = 1; i <= len; ++i) {	
		rig[n1] = xr[n1], rig[n2] = xr[n2];
		n1 = nxt[n1], n2 = nxt[n2];
	}
}

void print() {
	for(int i = 1; i <= n; ++i) {
		int o = Get(i, 1);
		for(int j = 1; j <= m; ++j) 
			printf("%d ", v[o]), o = rig[o];
		printf("\n");
	}
	printf("\n");
}
	
int main() {
	freopen("706E.in", "r", stdin);

	n = read(), m = read(), q = read();
	for(int i = 1; i <= n; ++i)
	for(int j = 1; j <= m; ++j)
		v[p(i, j)] = read();
		
	for(int i = 0; i <= n; ++i)
	for(int j = 0; j <= m; ++j) {
		nxt[p(i, j)] = p(i+1, j),
		rig[p(i, j)] = p(i, j+1);
	}
		
	for(int i = 1, x1, y1, x2, y2, h, w; i <= q; ++i) {
		x1 = read(), y1 = read();
		x2 = read(), y2 = read();
		h = read(), w = read();
		
		int a = Get(x1-1, y1), b = Get(x2-1, y2);
		int c = Get(x1+h-1, y1), d = Get(x2+h-1, y2);
		int e = Get(x1, y1-1), f = Get(x2, y2-1);
		int g = Get(x1, y1+w-1), k = Get(x2, y2+w-1);
		
		
		modify_r(a, b, w);
		modify_r(c, d, w);
		modify_c(e, f, h);
		modify_c(g, k, h);
		
		done_r(a, b, w);
		done_r(c, d, w);
		done_c(e, f, h);
		done_c(g, k, h);
		
	}
	
	print();
	return 0;
}
