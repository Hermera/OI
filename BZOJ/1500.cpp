#include <cstdio>
#include <cstring>
#include <algorithm>
#include <stack>
using namespace std;
int read() {
    char ch = getchar(); int x = 0, t = 1;
    while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x*t;
}
 
const int maxn = 6e5+5;
const int NONE = 1e9;
struct node {
    int val, siz, tag, sum, pre, suf, bst; bool rev;
    node *p, *s[2];
    node() { val = siz = sum = pre = suf = bst = rev = 0, tag = NONE; }
    node(node*, int);
 
    void rever();
    void modify(int v);
    void pushdown();
    void sets(node *x, int d) { (s[d] = x)->p = this; }
    bool pos() { return p->s[1] == this; }
    void update() {
        siz = s[0]->siz+s[1]->siz+1;
        sum = s[0]->sum+s[1]->sum+val;
        pre = max(s[0]->pre, s[0]->sum+val+max(s[1]->pre, 0));
        suf = max(s[1]->suf, s[1]->sum+val+max(s[0]->suf, 0));
        bst = max(max(s[0]->suf, 0)+max(s[1]->pre, 0)+val, max(s[0]->bst, s[1]->bst));
    }
} *emt = new node(emt, 0), *root = emt;
int n, m, a[maxn];
char op[20];
 
node::node(node* fa, int v) {
    p = fa, s[0] = s[1] = emt;
    val = sum = pre = suf = bst = v, rev = siz = 0, tag = NONE;
}
 
void node::rever() {
    if(this == emt) return;
    swap(pre, suf);
    swap(s[0], s[1]);
    rev ^= 1;
}
 
void node::modify(int v) {
    if(this == emt) return;
    tag = val = v;
    if(v >= 0) sum = pre = suf = bst = siz*v;
    else sum = siz*v, pre = suf = bst = v;
}
 
void node::pushdown() {
    if(rev) s[0]->rever(), s[1]->rever(), rev = 0;
    if(tag != NONE) s[0]->modify(tag), s[1]->modify(tag), tag = NONE;
}
 
#define mid (l+r>>1)
#define half (x->s[0]->siz+1)
stack <node*> pool;
struct splaytree {
    node *st[maxn], gen[maxn];
    int cnt, top;
    void init() { cnt = 0, emt->p = emt, emt->pre = emt->suf = emt->bst = -NONE; }
 
    void rotate(node *x) {
        node *y = x->p, *z = y->p;
        int d = x->pos();
        y->sets(x->s[!d], d);
        if(z == emt) x->p = y->p;
        else z->sets(x, y->pos());
        x->sets(y, !d), y->update();
    }
 
    void splay(node *x, node *g = emt) {
        top = 0, st[++top] = x;
        for(node *i = x; i->p != g; i = i->p) st[++top] = i->p;
        for(int i = top; i; --i) st[i]->pushdown();
        for(node *y; (y = x->p) != g; rotate(x))
            if(y->p != g) rotate(x->pos() == y->pos() ? y : x);
        x->update();
        if(g == emt) root = x;
    }
 
    node* find_kth(int k, node *x = root) {
        x->pushdown();
        if(k == half) return x;
        if(k < half) return find_kth(k, x->s[0]);
        return find_kth(k-half, x->s[1]);
    }
 
    void build(int l, int r, node *&x = root, node *fa = emt) {
        if(l > r) return;
        if(pool.empty()) x = &gen[++cnt];
        else x = pool.top(), pool.pop();
        *x = node(fa, a[mid]);
        build(l, mid-1, x->s[0], x);
        build(mid+1, r, x->s[1], x);
        x->update();
    }
 
    node *range(int l, int r) {
        node *x = find_kth(l-1), *y = find_kth(r+1);
        splay(y), splay(x, root);
        return x->s[1];
    }
 
    void insert(node *x, int k) {
        for(int i = 1; i <= k; ++i) a[i] = read();
        x->pushdown();
        build(1, k, x->s[1], x);
        splay(x->s[1]);
    }
 
    void recycle(node *x) {
        if(x == emt) return;
        pool.push(x);
        recycle(x->s[0]);
        recycle(x->s[1]);
    }
 
    void remove(node *x) {
        recycle(x);
        x->p->s[x->pos()] = emt;
        splay(x->p);
    }
 
    void print(node *x = root) {
        if(x == emt) return;
        x->pushdown();
        print(x->s[0]);
        printf("%d ", x->val);
        print(x->s[1]);
    }
 
} s;
 
int tot;
int main() {
    n = read(), m = read();
    a[0] = a[1] = a[n+2] = a[n+3] = -NONE;
    for(int i = 2; i <= n+1; ++i) a[i] = read();
    s.init(), s.build(0, n+3);
 
    for(int p, t; m--; ) {
        scanf("%s", op);
        if(!strcmp(op, "MAX-SUM")) printf("%d\n", root->bst), ++tot;
        else {
            p = read()+2, t = read();
            if(*op == 'I') s.insert(s.range(p, p), t);
            else {
                node *x = s.range(p, p+t-1);
                if(*op == 'D') s.remove(x);
                if(*op == 'M') x->modify(read()), s.splay(x);
                if(*op == 'R') x->rever(), s.splay(x);
                if(*op == 'G') printf("%d\n", x->sum), ++tot;
            }
        }
        //s.print();
        //printf("\n");
    }
    return 0;
}
﻿
