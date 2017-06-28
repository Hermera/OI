 
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;
int read() {
    char ch = getchar(); int x = 0, t = 1;
    while(ch < '0' || ch > '9') { if(ch == '-') t = -1; ch = getchar(); }
    while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
    return x * t;
}
 
const int maxn = 805;
const ll INF = 1e16;
 
#define REP(i, x, y) for(register int i = x; i <= y; ++i)
#define mset(x, a) memset(x, a, sizeof(x))
inline bool cmax(ll &x, ll y) { return x < y ? x = y, 1 : 0; }
 
struct DPmachine {
    int a[maxn][maxn], n, m;
    int &operator ()(int x, int y) { return a[x][y]; }
     
    struct Matrix {
        int a[maxn][maxn], n, m;
        ll weisum[maxn][maxn], heisum[maxn][maxn];
        int &operator ()(int x, int y) { return a[x][y]; }
        void getsum() {
            REP(i, 1, n) REP(j, 1, m)
                weisum[i][j] = weisum[i][j-1] + a[i][j],
                heisum[i][j] = heisum[i-1][j] + a[i][j];
        }
         
        ll Rval(int x, int l, int r) { return weisum[x][r] - weisum[x][l-1]; }
        ll Cval(int x, int l, int r) { return heisum[r][x] - heisum[l-1][x]; }
    } val, inv;
     
    void prework() {
        REP(i, 1, n) REP(j, 1, m) val(i, j) = a[i][j];
        REP(i, 1, n) REP(j, 1, m) inv(i, j) = a[n-i+1][m-j+1];
        val.n = n, val.m = m, val.getsum();
        inv.n = n, inv.m = m, inv.getsum();
    }
     
     
    ll UL[maxn][maxn][2], DR[maxn][maxn][2];
    void getdouble(ll f[][maxn][2], Matrix &a) {
        f[1][1][0] = f[1][1][1] = a(1, 1);
        REP(i, 1, n) REP(j, 1, m) {
            cmax(f[i][j][0], f[i-1][j-1][1] + a.Rval(i, 1, j-1) + a.Cval(j, 1, i));
            cmax(f[i][j][1], f[i-1][j-1][0] + a.Rval(i, 1, j-1) + a.Cval(j, 1, i));
            cmax(f[i][j][0], f[i][j-1][0] + a(1, j));
            cmax(f[i][j][1], f[i-1][j][1] + a(i, 1));
            cmax(f[i][j][0], f[i-1][j][0]);
            cmax(f[i][j][1], f[i][j-1][1]);
        }
    }
     
    ll DL[maxn][maxn], UR[maxn][maxn];
    void getsingle(ll f[][maxn], Matrix &a) {
        REP(i, 1, n) REP(j, 1, m) {
            cmax(f[i][j], a.Rval(n-i+1, 1, j-1) + a.Cval(j, n-i+1, n));
            cmax(f[i][j], f[i][j-1] + a(n, j));
            cmax(f[i][j], f[i-1][j] + a(n-i+1, 1));
        }
    }
     
    ll mid[maxn][maxn][2][2], U[maxn][2], D[maxn][2];
    ll solve() {
        prework(); 
        mset(UL, -63), mset(DR, -63);
        mset(DL, -63), mset(UR, -63);
        mset(U, -63), mset(D, -63);
        mset(mid, -63);
         
        getdouble(UL, val);
        getdouble(DR, inv);
        getsingle(DL, val);
        getsingle(UR, inv);
         
        REP(i, 1, n) mid[i][i-1][0][0] = mid[i][i-1][1][1] = 0;     
        REP(i, 1, n) REP(j, i, n) REP(d, 0, 1) {
            cmax(mid[i][j][d][0], mid[i][j-1][d][0] + a[j][1]);
            cmax(mid[i][j][d][0], mid[i][j-1][d][1] + val.Rval(j, 1, m));
            cmax(mid[i][j][d][1], mid[i][j-1][d][1] + a[j][m]);
            cmax(mid[i][j][d][1], mid[i][j-1][d][0] + val.Rval(j, 1, m));
        }
         
        REP(i, 1, n) REP(j, 1, m) 
            cmax(U[i][1], UL[i][j][0] + UR[i][m-j]),
            cmax(U[i][0], UL[i][j][1]);
        REP(i, 1, n) REP(j, 1, m) 
            cmax(D[i][0], DR[i][j][0] + DL[i][m-j]),
            cmax(D[i][1], DR[i][j][1]);
         
        ll ret = -INF;
        REP(i, 1, n) REP(j, i, n) 
            REP(d1, 0, 1) REP(d2, 0, 1)
                cmax(ret, U[i-1][d1] + mid[i][j][d1][d2] + D[n-j][d2]); 
        REP(i, 1, n) REP(d, 0, 1) cmax(ret, U[i][d] + D[n-i][d]);
         
        return ret;
    }
     
} wei, hei;
 
 
int a[maxn][maxn], n, m;
void input() {
    n = read(), m = read();
    REP(i, 1, n) REP(j, 1, m) a[i][j] = read();
    REP(i, 1, n) REP(j, 1, m) wei(i, j) = a[i][j];
    REP(i, 1, m) REP(j, 1, n) hei(i, j) = a[j][i];
    wei.n = n, wei.m = m;
    hei.n = m, hei.m = n;
}
 
int main() {
    input();
     
    ll ans = -INF;
    cmax(ans, wei.solve());
    cmax(ans, hei.solve());
    printf("%lld\n", ans);
    return 0;
}
﻿