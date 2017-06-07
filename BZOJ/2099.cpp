#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 2e5+5, Size = 26;
struct State
{
	int len;
	State *par, *trans[Size];
	State(int len = 0): len(len), par(0) { memset(trans, 0, sizeof(trans)); } 
}*root, *last, gen[maxn]; 
int N, M, cnt, ans = 1, s[maxn], t[maxn];

void extend(int w)
{
	State *fa = last, *lst = &gen[cnt++]; *lst = State(fa->len+1);
	while(fa && fa->trans[w] == 0) fa->trans[w] = lst, fa = fa->par;
	if(!fa) lst->par = root;
	else
	{
		State *now = fa->trans[w];
		if(fa->len+1 == now->len) lst->par = now;
		else
		{
			State *newpo = &gen[cnt++]; *newpo = State(fa->len+1);
			memcpy(newpo->trans, now->trans, sizeof(now->trans));
			newpo->par = now->par;
			lst->par = now->par = newpo;
			while(fa && fa->trans[w] == now) fa->trans[w] = newpo, fa = fa->par;
		}
	}
	last = lst;
}

void read(int *s, int n)
{
	for(int i = 1; i <= n; ++i)
	{
		char ch = getchar();
		if(ch == '\n' || ch == '\r') --i;
		else s[i] = ch-'A';
	}
}

int main()
{
	freopen("data.in", "r", stdin);

	scanf("%d%d", &N, &M);
	read(s, N), read(t, M);
	
	root = last = &gen[cnt++]; *root = State();
	for(int i = 1; i <= N; ++i) extend(s[i]);
	
	State *now = root;
	for(int i = 1; i <= M; ++i)
		if(now->trans[t[i]]) now = now->trans[t[i]];
		else ++ans, now = root->trans[t[i]];
	
	printf("%d\n", ans);
	return 0;
}
