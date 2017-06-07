#include <cstdio>
#include <cstring>
using namespace std;
const int maxn = 205;
const int size = 26;
const int maxs = 1e6+5;
int N, M;
char s[maxs];

struct Trie
{
	int ch[maxn][size], cnt;
	bool end[maxn], check[maxs];
	void insert(char *s)
	{
		int len = strlen(s), now = 0;
		for(int i = 0; i < len; ++i)
			if(ch[now][s[i]-'a']) now = ch[now][s[i]-'a'];
			else ch[now][s[i]-'a'] = ++cnt, now = cnt;
		end[now] = true;
	}
	void FindSub(char *s, int x, int len)
	{
		int now = 0;
		do
		{
			now = ch[now][s[x]-'a'];
			if(end[now]) check[x] = true;
			++x;
		}
		while(now && x < len);
	}
	int query(char *s)
	{
		int len = strlen(s);
		bool flag = false;
		memset(check, 0, sizeof(check));
		FindSub(s, 0, len);
		for(int i = 0; i < len; ++i) if(check[i]) FindSub(s, i+1, len);
		for(int i = len-1; i >= 0; --i)
			if(check[i]) return i+1;
		return 0;
	}
} trie;

int main()
{
	freopen("data.in", "r", stdin);
	scanf("%d%d", &N, &M);
	for(int i = 1; i <= N; ++i)
		scanf("%s", s), trie.insert(s);
	for(int i = 1; i <= M; ++i)
		scanf("%s", s), printf("%d\n", trie.query(s));
}
