#include <cstdio>
#include <algorithm>
using namespace std;
inline int read()
{
	char ch = getchar(); int sum = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') sum = sum*10+ch-'0', ch = getchar();
	return sum;
}

const int maxn = 1e6+5, inf = 1e9, maxk = 2;

int N, M, D, root;
struct P
{
	int d[maxk], mn[maxk], mx[maxk], l, r;//记录当前节点的各维度的最小值、最大值、边界，和这个节点是什么。
	P(int x = 0, int y = 0) { d[0] = x, d[1] = y; l = r = 0; }
	int &operator[] (int x) { return d[x]; }
	friend bool operator <(P a, P b) { return a[D] < b[D]; }
} p[maxn];

inline int dis(P a, P b) { return abs(a[0]-b[0])+abs(a[1]-b[1]); }

struct KDtree
{
	int ans;
	P t[maxn], T;
	
	void update(int x)//用儿子节点更新父亲的值
	{
		P l = t[t[x].l], r = t[t[x].r];
		for(int i = 0; i < 2; ++i)
		{
			if(t[x].l) t[x].mn[i] = min(t[x].mn[i], l.mn[i]), t[x].mx[i] = max(t[x].mx[i], l.mx[i]);
			if(t[x].r) t[x].mn[i] = min(t[x].mn[i], r.mn[i]), t[x].mx[i] = max(t[x].mx[i], r.mx[i]);
		}
	}

	int build(int l, int r, int now)//建树
	{
		D = now;
		int mid = (l+r)>>1;
		nth_element(p+l, p+mid, p+r+1);//保证第mid个排第mid位，小的在前大的在后，但前后不一定排好了
		
		t[mid] = p[mid];
		for(int i = 0; i < 2; ++i) t[mid].mn[i] = t[mid].mx[i] = t[mid][i];
		if(l < mid) t[mid].l = build(l, mid-1, now^1);
		if(r > mid) t[mid].r = build(mid+1, r, now^1);
		update(mid);
		return mid;
	}
	
	void insert(int &x, int now)//插入一个节点
	{
		if(!x)
		{
			x = ++N, t[x] = T;
			for(int i = 0; i < 2; ++i) t[x].mn[i] = t[x].mx[i] = t[x][i];
			return;
		}
		if(T[now] >= t[x][now]) insert(t[x].r, now^1);
		else insert(t[x].l, now^1);
		update(x);
	}
	
	int get(int x, P p)//求两个点的曼哈顿距离
	{
		int tmp = 0;
		for(int i = 0; i < 2; ++i) tmp += max(0, t[x].mn[i]-p[i]);
		for(int i = 0; i < 2; ++i) tmp += max(0, p[i]-t[x].mx[i]);
		return tmp;
	}
	
	void query(int x, int now)//查询最近的值
	{
		int dl = inf, dr = inf;
		ans = min(ans, dis(t[x], T));
		if(t[x].l) dl = get(t[x].l, T);
		if(t[x].r) dr = get(t[x].r, T);
		if(dl < dr)
		{
			if(dl < ans) query(t[x].l, now^1);
			if(dr < ans) query(t[x].r, now^1);
		}
		else
		{
			if(dr < ans) query(t[x].r, now^1);
			if(dl < ans) query(t[x].l, now^1);
		}//回溯：这里的写法不可以改变，不然会使运行时间发生质的变化
	}
	
	void insert(P p) { T = p; insert(root, 0); }
	int query(P p) { ans = inf, T = p; query(root, 0); return ans; }
} KD;

int main()
{
	freopen("data.in", "r", stdin);

	N = read(), M = read();
	for(int i = 1; i <= N; ++i) p[i][0] = read(), p[i][1] = read();
	root = KD.build(1, N, 0);
	
	while(M--)
	{
		int op = read(), x = read(), y = read();
		if(op == 1) KD.insert(P(x, y));
		else printf("%d\n", KD.query(P(x, y)));
	}
	return 0;
}
