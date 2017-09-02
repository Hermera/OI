#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int maxn = 1005;

struct BigNumber {
	int s[maxn], siz;
	int &operator [](int x) { return s[x]; }
} A, B[maxn];


char str[maxn];
int n, m, c[maxn], g[maxn], ss[maxn];
int f[maxn][maxn], sa[maxn][maxn];
void get(BigNumber &A) {
	scanf("%s", str);
	while(str[A.siz]) ++A.siz;
	m = max(m, A.siz + 1);
	for(int i = 0; str[i]; ++i) A[A.siz - i] = str[i];
}

int idx(char ch) { return !ch ? 0 : ch - '0'; }
int getval(int x, int y) {
	if(y > max(B[x].siz, A.siz) && !g[x]) return 0;
	return c[g[x]];
}


int main() {
	get(A);
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) get(B[i]);
	for(int i = 0; i < 10; ++i) scanf("%d", c + i);
	for(int i = 1; i <= n; ++i) sa[0][i] = i;
	
	memset(f, -63, sizeof f);
	f[0][0] = 0;
	
	for(int i = 1; i <= m; ++i) {
		memset(ss, 0, sizeof ss);
		
		for(int j = 1; j <= n; ++j) ++ss[idx(B[j][i])];
		for(int j = 9; j; --j) ss[j-1] += ss[j];
		for(int j = n; j; --j) sa[i][ss[idx(B[sa[i-1][j]][i])]--] = sa[i-1][j];
		
		int l = 0, r = 0;
		if(i > A.siz) l = r = 0;
		else if(A[i] == '?') l = (i == A.siz), r = 9;
		else l = r = idx(A[i]);
		
		for(int p, v; l <= r; ++l) {
			p = v = 0;
			for(int k = 1; k <= n; ++k) {
				g[k] = idx(B[k][i]) + l;
				if(g[k] > 9) g[k] -= 10, ++p;
				v += getval(k, i);
			}
			
			for(int k = 0;;) {
				f[i][p] = max(f[i][p], f[i-1][k] + v);
				if((k++) == n) break;
				
				v -= getval(sa[i-1][k], i);
				if((++g[sa[i-1][k]]) > 9) g[sa[i-1][k]] = 0, ++p;
				v += getval(sa[i-1][k], i);
			}
		}
	}
	
	printf("%d\n", f[m][0]);
	return 0;
}
