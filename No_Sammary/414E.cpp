include<bits/stdc++.h>
using namespace std;
const int maxn = 2e5+5;
#define lc ch[0][x]
#define rc ch[1][x]

inline int read(){
	int x = 0 ; char ch = getchar();
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch <= '9' && ch >= '0') x = x*10+ch-'0',ch = getchar();
	return x;
}

int ch[2][maxn],fa[maxn],mn[maxn],mx[maxn],T[maxn];
int N,M,Rt,idx,S[2][maxn],val[maxn],Pa[maxn],num[maxn]; 
vector<int>G[maxn];

void update(int x){
	T[x] = T[lc] + T[rc] + val[x];
	mn[x] = min(T[lc]+val[x],min(mn[lc],mn[rc]+T[lc]+val[x]));
	mx[x] = max(T[lc]+val[x],max(mx[lc],mx[rc]+T[lc]+val[x]));
}

void rotate(int x){
	int y = fa[x],p = fa[y],d = ch[1][y] == x;
	if(p) ch[ch[1][p] == y][p] = x;
	fa[x] = p; fa[y] = x; fa[ch[!d][x]] = y;
	ch[d][y] = ch[!d][x]; ch[!d][x] = y;
	fa[0] = 0; update(y); update(x);
}

void Splay(int x,int to){
	for(int y = fa[x]; y != to; rotate(x),y = fa[x])
		if(fa[y] != to) rotate((ch[0][y] == x) == (ch[0][fa[y]] == y) ? y : x);
	update(x); Rt = to ? Rt : x;
}

int Pre(int x){Splay(x,0); for(x = lc ; rc ; x = rc); return x;}
int Nxt(int x){Splay(x,0); for(x = rc ; lc ; x = lc); return x;}

int Delet(int l,int r){
	int tl = Pre(l),tr = Nxt(r);
	if(!(tl | tr)) return r;
	else if(!tl || !tr){
		Splay(tr + tl , 0); int t = ch[!tr][Rt];
		if(!tl){fa[ch[0][Rt]] = ch[0][Rt] = 0; update(Rt);}
		if(!tr){fa[ch[1][Rt]] = ch[1][Rt] = 0; update(Rt);}
		return t; 
	}
	Splay(tl,0); Splay(tr,tl); int t = ch[0][tr];
	ch[0][tr] = fa[ch[0][tr]] = 0; update(tr);
	update(tl); return t;
}

void Insert(int x,int y){
	if(!x){Rt = y; return;} int t = Nxt(x);
	if(!t) rc = y,fa[y] = x,update(x);
	else Splay(t,x),ch[0][t] = y,fa[y] = t,update(t),update(x);
	Splay(y,0);
}

void DFS(int x){
	S[0][x] = ++idx; num[idx] = x;
	mn[idx] = T[idx] = mx[idx] = val[idx] = 1; Insert(Rt,idx);
	for(int i = 0 ; i < G[x].size() ; ++i)
		Pa[G[x][i]] = x,DFS(G[x][i]);
	S[1][x] = ++idx; num[idx] = x;
	mn[idx] = T[idx] = mx[idx] = val[idx] = -1; Insert(Rt,idx);
}

int query(int x,int k){
	for( ++k ; ; ){
		if(mn[rc]+T[lc]+val[x] <= k && mx[rc]+T[lc]+val[x] >= k)
			k -= T[lc] + val[x],x = rc;
		else if(T[lc] + val[x] == k){
			Splay(x,0); return x == S[0][num[x]] ? num[x] : Pa[num[x]];
		}
		else x = lc;
	}
}

int Dist(int x,int y){
	x = S[0][x],y = S[0][y];
	if(x == y) return 0;
	Splay(y,0); Splay(x,y);
	if(x == ch[1][y]) swap(x,y);
	Splay(y,0); Splay(x,y);
	int lcadep = min(T[lc]+val[x],min(mn[rc]+T[lc]+val[x],T[x]+val[y]));
	return T[lc]+val[x]+T[x]+val[y]-2*lcadep;
}

void Move(int x,int h){
	int t = x,par; x = S[0][x]; Splay(x,0);
	par = query(lc,T[lc]+val[x]-h-1);
	Pa[t] = par; t = Delet(S[0][t],S[1][t]);
	Insert(Pre(S[1][par]) , t);
}

int main(){
	N = read(); M = read();
	for(int i = 0 ; i <= 2*N ; ++i) mx[i] = -maxn,mn[i] = maxn;
	for(int i = 1 ; i <= N ; ++i){
		int x = read();
		while(x--) G[i].push_back(read());
	}
	DFS(1); int opt,u,v;
	while(M--){
		opt = read(); u = read();
		if(opt == 1) v = read(),printf("%d\n",Dist(u,v));
		else if(opt == 2) v = read(),Move(u , v);
		else printf("%d\n",query(Rt,u));
	}
	return 0;
}
