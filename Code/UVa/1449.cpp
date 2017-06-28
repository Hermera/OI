#include <cstdio>
#include <queue>
#include <cstring>
#define mem(x, a) memset(x, a, sizeof(x))
using namespace std;

const int maxs = 1e6+5;
const int maxn = 20005;
const int size = 26;
int N, once[maxn];
char s[maxs], str[maxn/100][100];

struct Trie
{
	int ch[maxn][size], fail[maxn], root, cnt, tot;
	vector <int> end[maxn];
	int newnode(){ end[++cnt].clear(); mem(ch[cnt], -1); return cnt; }
	void init() { cnt = root = tot = 0; mem(ch[root], -1); mem(fail, 0); mem(once, 0);}
	void insert(char *s)
	{
		int len = strlen(s), now = root;
		for(int i = 0; i < len; ++i)
			if(ch[now][s[i]-'a'] < 0) ch[now][s[i]-'a'] = newnode(), now = ch[now][s[i]-'a'];
			else now = ch[now][s[i]-'a'];
		end[now].push_back(++tot);
	}
	void build()
	{
		queue <int> q;
		for(int i = 0; i < size; ++i)
			if(ch[root][i] < 0) ch[root][i] = root;
			else fail[ch[root][i]] = root, q.push(ch[root][i]);
		while(!q.empty())
		{
			int e = q.front(); q.pop();
			for(int i = 0; i < size; ++i)
				if(ch[e][i] < 0) ch[e][i] = ch[fail[e]][i];
				else fail[ch[e][i]] = ch[fail[e]][i], q.push(ch[e][i]);
		}
	}
	void query(char *s)
	{
		int len = strlen(s), now = root, ans = 0;
		for(int i = 0; i < len; ++i)
		{
			now = ch[now][s[i]-'a'];
			int temp = now;
			while(temp)
			{
				for(int i = 0; i < end[temp].size(); ++i) once[end[temp][i]]++;
				temp = fail[temp];
			}
		}
	}
} ac;

int main()
{
	while(scanf("%d", &N) == 1 && N)
	{
		ac.init();
		for(int i = 1; i <= N; ++i)
			scanf("%s", str[i]), ac.insert(str[i]);
		ac.build();
		scanf("%s", s);
		ac.query(s);
		int e = 0;
		for(int i = 1; i <= N; ++i) e = max(e, once[i]);
		printf("%d\n", e);
		for(int i = 1; i <= N; ++i)
		if(once[i] == e) printf("%s\n", str[i]);
	}
	return 0;
} 
