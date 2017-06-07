#include <cstdio>
using namespace std;

const int maxn = 200005;
typedef long long ll;
ll M, D, t, top, sum;
char s[5];
struct Node { ll pos, val; } q[maxn];
inline ll read()
{
	char ch = getchar(); ll sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10 + ch - '0', ch = getchar();
	return sum;
}

ll Query(int len)
{
	int left = 1, right = top, ans;
	while(left <= right)
	{
		int mid = (left+right)>>1;
		if(sum-q[mid].pos < len) ans = mid, right = mid-1;
		else left = mid+1; 
	}
	return q[ans].val;
}

void Insert(int p, ll n)
{
	while(top && q[top].pos <= p && q[top].val <= n) top--;
	q[++top] = (Node){ p, n };
}

int main()
{
	//freopen("data.in", "r", stdin);
	M = read(), D = read();
	for(int i = 1; i <= M; ++i)
	{
		scanf("%s", s);
		if(*s == 'Q') printf("%lld\n", t = Query(read()));
		else ++sum, Insert(sum, (t+read())%D);
	}
	return 0;
}
