#include <cstdio>
#include <algorithm>
using namespace std;
int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}

const int maxn = 5e5+5;
typedef int arr32[maxn];

int n, m, p, q;
arr32 a, b, s, len, ans, vis;

namespace SuffixArray {
	arr32 c, t1, t2, sa, rk, hi;
	void build(int n, int m) {
		int i, j, k, *x = t1, *y=t2;
		for(i = 0; i <= m; ++i) c[i] = 0;
		for(i = 1; i <= n; ++i) ++c[x[i] = s[i]];
		for(i = 1; i <= m; ++i) c[i] += c[i-1];
		for(i = n; i; --i) sa[c[x[i]]--]=i;
		for(k = 1; k <= n; k <<= 1) {
		    j = 0;
		    for(i = 1; i <= n; ++i) if(sa[i]+k > n) y[++j] = sa[i];
		    for(i = 1; i <= n; ++i) if(sa[i]-k > 0) y[++j] = sa[i]-k;
		    for(i = 0; i <= m; ++i) c[i] = 0;
		    for(i = 1; i <= n; ++i) ++c[x[y[i]]];
		    for(i = 1; i <= m; ++i) c[i] += c[i-1];
		    for(i = n; i; i--) sa[c[x[y[i]]]--] = y[i];
		    swap(x, y); 
		    j = x[sa[1]] = 0;
		    for(i = 2; i <= n; ++i) 
		    	if(y[sa[i-1]] == y[sa[i]] && y[sa[i-1]+k] == y[sa[i]+k]) x[sa[i]] = j; 
		    	else x[sa[i]] = ++j;
		    if(j == n-1) break; 
		    m = j;
		}
		for(i = 1; i <= n; ++i) rk[sa[i]] = i;
		for(i = 1; i <= n; ++i) {
			if(k) --k;
			j = sa[rk[i]-1];
			while(s[i+k] == s[j+k]) ++k;
			hi[rk[i]] = k;
		}
	}
};


int ask(int x) {
	using namespace SuffixArray;
	
	int ret = 0;
	for(int i = rk[a[x]]-1, v; i; --i)
		if(hi[i+1] >= len[x]) {
			v = b[sa[i]];
			if(v && vis[v] != x) ++ret, vis[v] = x, ++ans[v];
		} else break;
	for(int i = rk[a[x]]+1, v; i <= p; ++i)
		if(hi[i] >= len[x]) {
			v = b[sa[i]];
			if(v && vis[v] != x) ++ret, vis[v] = x, ++ans[v];
		} else break;
	return ret;
}

int main() {
	n = read(), m = read(), q = 10000;
	for(int i = 1; i <= n; ++i) {
		for(int k = read(); k--; ) s[++p] = read(), b[p] = i; s[++p] = ++q;
		for(int k = read(); k--; ) s[++p] = read(), b[p] = i; s[++p] = ++q;
	}
	for(int i = 1; i <= m; ++i) {
		len[i] = read(), a[i] = p+1;
		for(int k = len[i]; k--; ) s[++p] = read(); s[++p] = ++q;
	}
	
	SuffixArray::build(p, q);
	for(int i = 1; i <= m; ++i) printf("%d\n", ask(i));
	for(int i = 1; i <= n; ++i) printf("%d%c", ans[i], i == n ? '\n' : ' ');
	return 0;
}
