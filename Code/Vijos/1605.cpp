#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

const int maxn = 1005;
int n, go[2], a[maxn], c[maxn], mn[maxn], d[maxn][maxn];
stack <int> S1, S2;
vector <char> ans;

bool dfs(int x, int k) {
	c[x] = k;
	for(int i = 1; i <= n; ++i) if(d[x][i]) {
		if(c[i] == k) return 0;
		if(c[i] < 0 && !dfs(i, k^1)) return 0;
	}
	return 1;
}

void A(int x) { S1.push(x), ans.push_back('a'); }
void C(int x) { S2.push(x), ans.push_back('c'); }
void B() { S1.pop(), ans.push_back('b'); }
void D() { S2.pop(), ans.push_back('d'); }

int main() {
	scanf("%d", &n), mn[n+1] = n;
	for(int i = 1; i <= n; ++i) scanf("%d", a+i);
	for(int i = n; i; --i) mn[i] = min(a[i], mn[i+1]);
	
	for(int i = 1; i <= n; ++i)
	for(int j = i; j <= n; ++j)
		if(a[i] < a[j] && mn[j+1] < a[i])
			d[i][j] = d[j][i] = 1;
	
	for(int i = 1; i <= n; ++i) c[i] = -1;
	for(int i = 1; i <= n; ++i)
		if(c[i] < 0 && !dfs(i, 1)) return printf("0\n"), 0;
	
	int now = 1;
	for(int i = 1, x; i <= n; ++i) {
		x = a[i];
		if(S1.empty() && S2.empty()) {
			go[c[i]] = 0, go[c[i]^1] = 1, A(x);
			continue;
		}
		
		while(!S1.empty() && S1.top() == now) B(), ++now;
		if(!go[c[i]]) A(x);
		else {
			while(!S2.empty() && S2.top() == now) D(), ++now;
			C(x);
		}
	}
	while(now <= n) {
		if(!S1.empty() && S1.top() == now) B(), ++now;
		if(!S2.empty() && S2.top() == now) D(), ++now;
	}
	
	for(int i = 0; i < ans.size(); ++i)
		printf("%c%c", ans[i], i+1 == ans.size() ? '\n' : ' ');
	return 0;
}
		
