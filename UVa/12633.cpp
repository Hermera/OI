#include <cmath>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;
inline int read() {
	char ch = getchar(); int x = 0;
	while(ch < '0' || ch > '9') ch = getchar();
	while(ch >= '0' && ch <= '9') x = x*10+ch-'0', ch = getchar();
	return x;
}


const int N = 3e5+5;
const double pi = acos(-1.0);

struct Atom {
	double r, i;
	Atom() {}
	Atom(double _r, double _i): r(_r), i(_i) {}
} A[N], B[N];

Atom operator +(Atom a, Atom b) { return Atom(a.r + b.r, a.i + b.i); }
Atom operator -(Atom a, Atom b) { return Atom(a.r - b.r, a.i - b.i); }
Atom operator *(Atom a, Atom b) {
	return Atom(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}

int l;
void FFT(Atom *s, int on) {
	for(int i = 0, t = 0; i < l; ++i) {
		if(i > t) swap(s[i], s[t]);
		for(int j = l >> 1; (t ^= j) < j; j >>= 1);
	}
	
	for(int h = 2; h <= l; h <<= 1) {
		Atom wn(cos(-2*on*pi/h), sin(-2*on*pi/h));
		for(int i = 0; i < l; i += h) {
			Atom w(1, 0), x, y;
			for(int j = i; j < i+h/2; ++j) {
				x = s[j], y = s[j+h/2] * w;
				s[j] = x + y, s[j+h/2] = x - y;
				w = w * wn;
			}
		}
	}
	
	if(on < 0)
		for(int i = 0; i < l; ++i)
			s[i].r /= l;
}


int cas, r, c, n;
int ro[N], co[N], oc[N];

int main() {
	freopen("12633.in", "r", stdin);

	cas = read();
	for(int t = 1; t <= cas; ++t) {
		r = read(), c = read(), n = read();
		for(int i = 1; i <= r; ++i) ro[i] = 1;
		for(int i = 1; i <= c; ++i) co[i] = 1;
		for(int i = 1; i <= r+c; ++i) oc[i] = 0;
		for(int i = 1; i <= n; ++i) {
			int x = r - read() + 1, y = read();
			ro[x] = co[y] = 0;
			oc[x + y] = 1;
		}
		
		
		ll rr = 0, cc = 0, ans = 0;
		for(int i = 1; i <= r; ++i) rr += ro[i];
		for(int i = 1; i <= c; ++i) cc += co[i];
		ans = rr * cc;
		
		
		l = 1;
		while(l <= r || l <= c) l <<= 1;
		l <<= 1;
		
		for(int i = 0; i < l; ++i) A[i] = B[i] = Atom(0, 0);
		for(int i = 1; i <= r; ++i) A[i] = Atom(ro[i], 0);
		for(int i = 1; i <= c; ++i) B[i] = Atom(co[i], 0);
		
		FFT(A, 1), FFT(B, 1);
		for(int i = 0; i < l; ++i) A[i] = A[i] * B[i];
		FFT(A, -1);
		
		for(int i = 1; i <= r+c; ++i)
			if(oc[i]) ans -= round(A[i].r);
		printf("Case %d: %lld\n", t, ans);
	}
	return 0;
}
