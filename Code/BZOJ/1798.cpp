#include <cstdio>
#define lc node<<1, left, mid
#define rc node<<1|1, mid+1, right
typedef long long LL;
const int maxn = 100005;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}
  
int N, A, B, Q, K, C;
LL sum[maxn<<2], add[maxn<<2], mul[maxn<<2], P;
  
void up(int node) { sum[node] = (sum[node<<1]+sum[node<<1|1])%P; }
  
void Build(int node, int left, int right) 
{
    add[node] = 0, mul[node] = 1;
    if(left == right) { sum[node] = read(); return; }
    int mid = (left+right) >> 1;
    Build(lc); Build(rc);
    up(node);
}
  
void down(int node, int len) 
{
    add[node<<1] = (add[node<<1] * mul[node] + add[node]) %P;
    add[node<<1|1] = (add[node<<1|1] * mul[node] + add[node]) %P;
    mul[node<<1] = mul[node<<1] * mul[node] %P;
    mul[node<<1|1] = mul[node<<1|1] * mul[node] %P;
    sum[node<<1] = (sum[node<<1] * mul[node] + add[node] * (len-(len>>1))) %P;
    sum[node<<1|1] = (sum[node<<1|1] * mul[node] + add[node] * (len>>1)) %P;
    add[node] = 0, mul[node] = 1;
}
  
void Update(int node, int left, int right, int op) 
{
    if(A <= left && right <= B) 
    {
        if(op == 1) add[node] = add[node]*C%P, mul[node] = mul[node]*C%P, sum[node] = sum[node]*C%P;
        else add[node] = (add[node]+C)%P, sum[node] = (sum[node]+(LL)C*(right-left+1))%P;
        return;
    }
    down(node, right-left+1);
    int mid = (left+right) >> 1;
    if(A <= mid) Update(lc, op);
    if(mid < B) Update(rc, op);
    up(node);
}
  
LL Query(int node, int left, int right) 
{
    if(A <= left && right <= B) return sum[node]%P;
    down(node, right-left+1);
    int mid = (left+right) >> 1;
    LL ans = 0;
    if(A <= mid) ans = Query(lc);
    if(mid < B) ans += Query(rc);
    return ans%P;
}
  
int main()
{
	freopen("data.in", "r", stdin);
  	N = read(), P = read();
    Build(1, 1, N);
    Q = read();
    while(Q--) 
    {
        K = read(), A = read(), B = read();
        if(K != 3) C = read(), Update(1, 1, N, K);
        else printf("%lld\n", Query(1, 1, N));
    }
    return 0;
}
