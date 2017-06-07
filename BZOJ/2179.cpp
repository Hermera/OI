#include <cstdio>
#include <cmath>
#include <algorithm>
#include <cstring>
#define mem(x) memset(x, 0, sizeof(x))
using namespace std;

const int maxn = 150005;
const double pi = acos(-1.0);
char a[maxn], b[maxn];
int sum[maxn], N;
struct complex
{
	double r, i;
	complex(double _r = 0.0, double _i = 0.0) { r = _r, i = _i; }
	complex operator +(const complex &b) { return complex(r+b.r, i+b.i); }
	complex operator -(const complex &b) { return complex(r-b.r, i-b.i); }
	complex operator *(const complex &b) { return complex(r*b.r-i*b.i, r*b.i+i*b.r); }
} A[maxn], B[maxn];

void REV(complex s[], int len)
{
	for(int i = 1, j = len/2, k; i < len-1; i++)
	{
		if(i < j) swap(s[i], s[j]);
		k = len/2;
		while(j >= k) 
		j -= k, k /= 2;
		if(j < k) j += k;
	}
}

void FFT(complex s[], int len, int on)
{
	REV(s, len);
	for(int h = 2; h <= len; h <<= 1)
	{
		complex wn(cos(-on*2*pi/h), sin(-on*2*pi/h));
		for(int j = 0; j < len; j += h)
		{
			complex w(1, 0);
			for(int k = j; k < j+h/2; k++)
			{
				complex u = s[k], t = w*s[k+h/2];
				s[k] = u+t, s[k+h/2] = u-t; w = w*wn;
			}
		}
	}
	if(on == -1)
	for(int i = 0; i < len; i++) s[i].r /= len;
}

int main()
{
	scanf("%d%s%s", &N, a, b);
	int lena = strlen(a), lenb = strlen(b), len = 1;
	while(len < lena*2 || len < lenb*2) len <<= 1;
	for(int i = 0; i < lena; i++) A[i] = complex(a[lena-1-i]-'0', 0);
	for(int i = lena; i < len; i++) A[i] = complex(0, 0);
	for(int i = 0; i < lenb; i++) B[i] = complex(b[lenb-1-i]-'0', 0);
	for(int i = lenb; i < len; i++) B[i] = complex(0, 0);
	
	FFT(A, len, 1); FFT(B, len, 1);
	for(int i = 0; i < len; i++) A[i] = A[i]*B[i];
	FFT(A, len, -1);
	
	for(int i = 0; i < len; i++) sum[i] = (int)(A[i].r+0.5);
	for(int i = 0; i < len; i++)
		sum[i+1] += sum[i]/10, sum[i] %= 10;
	len = lena + lenb - 1;
	while(sum[len] <= 0 && len > 0) len--;
	for(int i = len; i >= 0; i--) printf("%c", sum[i]+'0');
	printf("\n"); 
	return 0;
}
