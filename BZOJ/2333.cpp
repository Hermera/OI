#include <set>
#include <cstdio>
#include <cstdlib>
using namespace std;
inline int read() {
    char ch = getchar(); int x = 0, t = 1;
    while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x * t;
}
 
const int maxn = 6e5+5;
const int INF = 1e9;
 
struct node {
    node *p, *s[2];
    int val, tag;
    node(int v = -INF): val(v) { 
        tag = 0;
    } 
     
    int pos() { return p->s[1] == this; }
    void sets(node *x, int d) { 
        s[d] = x;
        if(x) x->p = this;
    }
     
    void pushdown() {
        if(tag) {
            if(s[0]) s[0]->val += tag, s[0]->tag += tag;
            if(s[1]) s[1]->val += tag, s[1]->tag += tag;
            tag = 0;
        }
    }
} gen[maxn], *rev[maxn], *st[maxn];
int cnt;
node *newnode(int v = -INF) {
    node *o = gen + (++cnt);
    return o->val = v, o;
}
 
struct LIT {
    node *root;
    int top() { 
        return root->val; 
    }
     
    node *merge(node *x, node *y) {
        if(!x) return y;
        if(!y) return x;
        if(x->val < y->val) swap(x, y);
 
        x->pushdown();
        if(rand() & 1) x->sets(merge(x->s[0], y), 0);
        else x->sets(merge(x->s[1], y), 1);
        return x;
    }
     
    void insert(LIT x) {
        root = merge(root, x.root);
    }
     
    void insert(int x, int y) {
        rev[x] = newnode(y);
        root = merge(root, rev[x]);
    }
     
    void remove(int x) {
        node *o = rev[x];
        if(o == root) {
            root = merge(o->s[0], o->s[1]);
            if(root) root->p = NULL;
        }
        else o->p->sets(merge(o->s[0], o->s[1]), o->pos());
        rev[x] = NULL;
    }
     
    void modify(int v) {
        root->tag += v, root->val += v;
        root->pushdown();
    }
} q[maxn];
 
multiset <int> s;
 
 
int n, m, sum, pa[maxn], a[maxn];
int getpa(int x) { return pa[x] == x ? x : pa[x] = getpa(pa[x]); }
 
void merge(int x, int y) {
    x = getpa(x), y = getpa(y);
    if(x == y) return;
    if(q[x].top() > q[y].top()) s.erase(s.find(q[y].top()));
    else s.erase(s.find(q[x].top()));
    q[x].insert(q[y]);
    pa[y] = x;
}
 
int query(int x) {
    int top = 0;
    for(node *i = rev[x]; i; i = i->p) st[++top] = i;
    for(int i = top; i; --i) st[i]->pushdown();
    return rev[x]->val;
}
 
void modify(int x, int v) {
    int y = getpa(x), w = query(x);     
    s.erase(s.find(q[y].top()));
    q[y].remove(x);
    q[y].insert(x, w+v);
    s.insert(q[y].top());
}
 
void update(int x, int v) {
    x = getpa(x);
    s.erase(s.find(q[x].top()));
    q[x].modify(v);
    s.insert(q[x].top());
}
 
 
char op[10];
int main() {
    srand(20000909);
 
    n = read();
    for(int i = 1; i <= n; ++i) a[i] = read(), pa[i] = i;
    for(int i = 1; i <= n; ++i) q[i].insert(i, a[i]), s.insert(a[i]);
     
    m = read();
    int tot = 0;
    for(int x, y; m--;) {
        scanf("%s", op);
        if(op[0] == 'U') merge(read(), read());
        if(op[0] == 'A') {
            x = read();
            if(op[1] == '1') modify(x, read());
            if(op[1] == '2') update(x, read());
            if(op[1] == '3') sum += x;
        }
        if(op[0] == 'F') {
            ++tot;
            if(op[1] == '1') printf("%d\n", query(read()) + sum);
            if(op[1] == '2') printf("%d\n", q[getpa(read())].top() + sum);
            if(op[1] == '3') printf("%d\n", *s.rbegin() + sum);
        }
    }
    return 0;
}