#include <cmath>
#include <cstdio>
using namespace std;
 
const int maxn = 1500;
const double pi = acos(-1);
int n, m;
 
struct vec {
    double x, y, z;
    vec() { x = y = z; }
    vec(double a, double b, double c): x(a), y(b), z(c) {}
} p[maxn], gc;
 
double operator ^(vec a, vec b) { return a.x*b.x + a.y*b.y + a.z*b.z; }
vec operator *(vec a, vec b) { 
    return vec(a.y*b.z-a.z*b.y, a.z*b.x-a.x*b.z, a.x*b.y-a.y*b.x); 
}
 
vec operator *(vec a, double v) { return vec(a.x*v, a.y*v, a.z*v); }
vec operator /(vec a, double v) { return vec(a.x/v, a.y/v, a.z/v); }
vec operator +(vec a, vec b) { return vec(a.x+b.x, a.y+b.y, a.z+b.z); }
vec operator -(vec a, vec b) { return vec(a.x-b.x, a.y-b.y, a.z-b.z); }
double abs(vec a) { return sqrt(a ^ a); }
 
vec getGC(vec a, vec b, vec c, vec d) { return (a+b+c+d) / 4; }
double volume(vec a, vec b, vec c, vec d) { return abs(((b-a)*(c-a))^(d-a)) / 6; }
 
struct surface {
    int t;
    vec a[maxn];
    vec &operator [](int x) { return a[x]; }
} suf[maxn];
 
vec getGC() {
    vec O, C;
    for(int i = 1; i <= n; ++i) O = O + p[i];
    O = O / n;
     
    double v = 0;
    for(int i = 1; i <= m; ++i) 
        for(int j = 2; j < suf[i].t; ++j) {
            double now = volume(O, suf[i][1], suf[i][j], suf[i][j+1]);
            C = C + getGC(O, suf[i][1], suf[i][j], suf[i][j+1]) * now;
            v = v + now;
        }
    return C = C / v, C;
}
 
double getPJ(vec a, vec b, vec c) {
    vec r1 = (a - gc) * (b - gc); r1 = r1 / abs(r1);
    vec r2 = (b - gc) * (c - gc); r2 = r2 / abs(r2);
    vec r3 = (c - gc) * (a - gc); r3 = r3 / abs(r3);
    double a1 = pi - acos(r1 ^ r2);
    double a2 = pi - acos(r2 ^ r3);
    double a3 = pi - acos(r1 ^ r3);
    return a1 + a2 + a3 - pi;
}
 
double area(surface &x) {
    double ret = 0;
    for(int i = 2; i < x.t; ++i)
        ret += getPJ(x[1], x[i], x[i+1]);
    return ret;
}
 
int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i) 
        scanf("%lf%lf%lf", &p[i].x, &p[i].y, &p[i].z);
    for(int i = 1; i <= m; ++i) {
        scanf("%d", &suf[i].t);
        for(int x, j = 1; j <= suf[i].t; ++j)
            scanf("%d", &x), suf[i][j] = p[x];
    }
     
    gc = getGC();
    for(int i = 1; i <= m; ++i)
        printf("%.7lf\n", area(suf[i]) / (pi * 4));
    return 0;
}