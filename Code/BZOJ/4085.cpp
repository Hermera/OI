#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
    char ch = getchar(); int x = 0;
    while(ch < '0' || ch > '9') ch = getchar();
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x;
}
 
typedef pair<int, int> Pi;
#define fir first
#define sec second
 
const int maxn = 3e5+5;
const int maxm = 1e4+5;
const int Lim = 2048;
const int mod = 1e9+7;
int n, m, w[maxn];
 
ll quickpow(ll x, int k) {
    ll ret = 1;
    for(; k; k >>= 1, (x *= x) %= mod)
        if(k & 1) (ret *= x) %= mod;
    return ret;
}
 
 
struct Matrix {
    ll s[3][3];
    Matrix () { memset(s, 0, sizeof(s)); }
    ll &operator ()(int x, int y) { return s[x-1][y-1]; }
     
    friend Matrix operator *(Matrix a, Matrix b) {
        Matrix x;
        for(int i = 1; i <= 3; ++i)
        for(int j = 1; j <= 3; ++j)
        for(int k = 1; k <= 3; ++k)
            (x(i, j) += a(i, k)*b(k, j)) %= mod;
        return x;
    }
     
    friend Matrix operator +(Matrix a, Matrix b) {
        Matrix x;
        for(int i = 1; i <= 3; ++i)
        for(int j = 1; j <= 3; ++j)
            x(i, j) = (a(i, j) + b(i, j)) % mod;
        return x;
    }
} LP, RP, LQ, RQ, I, B, H, S, O;
 
Matrix LM1[Lim], LM2[Lim], LM3[Lim];
Matrix RM1[Lim], RM2[Lim], RM3[Lim];
Matrix pa[maxm<<1], pb[maxm<<1];
Matrix *Lx = pa + maxm;
Matrix *Rx = pb + maxm;
 
Matrix askL(int x) { 
    return LM1[x & (Lim-1)] * LM2[(x>>11) & (Lim-1)] * LM3[(x>>22) & (Lim-1)]; 
}
 
Matrix askR(int x) { 
    return RM1[x & (Lim-1)] * RM2[(x>>11) & (Lim-1)] * RM3[(x>>22) & (Lim-1)]; 
}
 
 
#define ls o<<1
#define rs o<<1|1
#define mid (l+r>>1)
#define lc ls, l, mid
#define rc rs, mid+1, r
struct Segment {
    struct Node {
        Pi tag;
        Matrix S;
        void upd(Pi x) {
            S = Lx[x.fir] * S * Rx[x.sec];
            tag.fir += x.fir;
            tag.sec += x.sec;
        }
    } t[maxn<<2];
     
    void pushup(int o) { t[o].S = t[ls].S + t[rs].S; }
    void pushdown(int o) {
        if(t[o].tag.fir || t[o].tag.sec) {
            t[ls].upd(t[o].tag);
            t[rs].upd(t[o].tag);
            t[o].tag = Pi(0, 0);
        }
    }
 
    void build(int o, int l, int r) {
        if(l == r) {
            t[o].S = askL(w[l-1]+1) * B * askR(w[l+1]-1);
            return;
        }
        build(lc), build(rc), pushup(o);
    }
     
    void modify(int o, int l, int r, int L, int R, Pi mark) {
        if(L <= l && r <= R) {
            t[o].upd(mark);
            return;
        }
        if(R < l || r < L) return;
        pushdown(o);
        modify(lc, L, R, mark);
        modify(rc, L, R, mark);
        pushup(o);
    }
     
    Matrix query(int o, int l, int r, int L, int R) {
        if(R < l || r < L) return O;
        if(L <= l && r <= R) return t[o].S;
        pushdown(o);
        return query(lc, L, R) + query(rc, L, R);
    }
} T;
 
 
void input() {
    n = read(), m = read();
     
    int a = read() % mod;
    int b = read() % mod, ob = b;
    int ia = quickpow(a, mod-2);
    bool flag = 0;
    if(!a) {
        flag = 1;
        a = ia = mod-1, b = 0;
    }
     
 
    for(int i = 1; i <= n; ++i) w[i] = read() - 1 - flag;
    RP(1, 1) = 1, RP(2, 1) = 1, RP(3, 3) = 1;
    RP(1, 2) = a, RP(1, 3) = b;
    RQ(1, 2) = 1, RQ(3, 3) = 1, RQ(2, 1) = ia;
    RQ(2, 2) = mod - ia;
    RQ(2, 3) = mod - 1LL * b * ia % mod;
    if(flag) RP(1, 1) = RQ(2, 2) = 2;
    for(int i = 1; i <= 3; ++i)
    for(int j = 1; j <= 3; ++j)
        LP(i, j) = RP(j, i),
        LQ(i, j) = RQ(j, i);
     
    H(1, 3) = S(3, 1) = B(2, 2) = 1;
    I(1, 1) = I(2, 2) = I(3, 3) = 1;
    if(flag) {
        H(1, 1) = S(1, 1) = 2 + ob;
        H(1, 2) = S(2, 1) = 2;
    } else {
        H(1, 1) = S(1, 1) = 2;
        H(1, 2) = S(2, 1) = 1;
    }
     
    Lx[0] = Rx[0] = I;
    for(int i = -1; i >= -m; --i) Lx[i] = Lx[i+1] * LQ, Rx[i] = Rx[i+1] * RQ;
    for(int i =  1; i <=  m; ++i) Lx[i] = Lx[i-1] * LP, Rx[i] = Rx[i-1] * RP;
 
    Matrix L2, L3, R2, R3;
    LM1[0] = LM2[0] = LM3[0] = I;
    RM1[0] = RM2[0] = RM3[0] = I;
    for(int i = 1; i < Lim; ++i) LM1[i] = LM1[i-1] * LP, RM1[i] = RM1[i-1] * RP;
    L2 = LM1[Lim-1] * LP, R2 = RM1[Lim-1] * RP;
    for(int i = 1; i < Lim; ++i) LM2[i] = LM2[i-1] * L2, RM2[i] = RM2[i-1] * R2;
    L3 = LM2[Lim-1] * L2, R3 = RM2[Lim-1] * R2;
    for(int i = 1; i < Lim; ++i) LM3[i] = LM3[i-1] * L3, RM3[i] = RM3[i-1] * R3;
}
 
 
void update(int l, int r, int on) {
    T.modify(1, 1, n, l+1, r-1, Pi(on, on));
    T.modify(1, 1, n, r, r+1, Pi(on, 0));
    T.modify(1, 1, n, l-1, l, Pi(0, on));
}
 
ll query(int l, int r) {
    if(l > r) return 0;
    Matrix ans = T.query(1, 1, n, l, r);
    return (H * ans * S)(1, 1);
}
 
char op[10];
int main() {
    input();
     
    T.build(1, 1, n);
    for(int x, y; m--;) {
        scanf("%s", op);
        x = read(), y = read();
        if(*op == 'p') update(x, y, 1);
        if(*op == 'm') update(x, y, -1);
        if(*op == 'q') printf("%lld\n", query(x+1, y-1));
    }
    return 0;
}