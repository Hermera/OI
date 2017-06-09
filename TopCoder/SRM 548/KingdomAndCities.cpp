#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include <sstream>
#include <typeinfo>
#include <fstream>

using namespace std;

const int mod = 1e9 + 7;
const int N = 55;
const int M = N * N;

int comb[M][N];
int e[N], f[N][N];
class KingdomAndCities {


    public:
    int howMany(int n, int p, int m) {
        for(int i = 1; i <= n; ++i)
            e[i] = i * (i - 1) / 2;
        comb[0][0] = 1;
        for(int i = 1; i <= e[n] || i <= n; ++i) {
            comb[i][0] = comb[i][i] = 1;
            for(int j = 1; j <= i && (j <= n || j <= m); ++j)
                comb[i][j] = (comb[i - 1][j] + comb[i - 1][j - 1]) % mod;
        }
        
        f[1][0] = 1;
        for(int i = 2; i <= n; ++i)
            for(int j = i - 1; j <= e[i] && j <= m; ++j) {
                int tmp = comb[e[i]][j];
                for(int a = 1; a < i; ++a) {
                    int tmp1 = 0;
                    for(int b = a - 1; b <= e[a] && b <= j; ++b)
                        tmp1 = (tmp1 - 1ll * f[a][b] * comb[e[i - a]][j - b]) % mod;
                    tmp = (tmp + 1ll * tmp1 * comb[i - 1][i - a]) % mod;
                }
                f[i][j] = (tmp >= 0 ? tmp : tmp + mod);
            }
            
        if(p == 0) return f[n][m];
        if(p == 1) {
            int ans = 0;
            int n1 = n - 1, m2 = m - 2;
            ans = (ans + 1ll * f[n1][m2] * comb[n1][2]) % mod;
            for(int i = 1; i < n1; ++i) {
                int tmp = 0, vi = n1 - i;
                for(int j = i - 1; j <= e[i] && j <= m2; ++j)
                    tmp = (tmp + 1ll * f[i][j] * f[vi][m2 - j]) % mod;
                ans = (ans + 1ll * tmp * i % mod * vi % mod * comb[n1 - 1][vi]) % mod;
            }
            return ans;
        }
        
        if(p == 2) {
		    int ans = 0;
	        int n2 = n - 2, m3 = m - 3;
	        ans = (ans + 1ll * f[n2][m3] * n2 * n2) % mod;
	        for(int i = 1; i < n2; ++i) {
	            int tmp = 0, vi = n2 - i;
	            for(int j = i - 1; j <= e[i] && j <= m3; ++j)
	                tmp = (tmp + 1ll * f[i][j] * f[vi][m3 - j]) % mod;
	            ans = (ans + 1ll * 2ll * tmp * i % mod * vi % mod * comb[n2 - 1][i]) % mod;
	        }

		    if(m >= 4) {
		        int n2 = n - 2, m4 = m - 4;

		        ans = (ans + 1ll * f[n2][m4] * comb[n2][2] * comb[n2][2]) % mod;
		        
		        for(int i = 1; i < n2; ++i) {
		            int tmp = 0, vi = n2 - i;
		            for(int j = i - 1; j <= e[i] && j <= m4; ++j)
		                tmp = (tmp + 1ll * f[i][j] * f[vi][m4 - j]) % mod;
		            
		            int coef_1 = 0, coef_2 = 0;
		            coef_1 = (comb[i][2] + comb[vi][2]) * 2 * i * vi % mod;
		            coef_2 = i * vi * i * vi % mod;
		            ans = (ans + 1ll * tmp * comb[n2 - 1][i - 1] % mod * (coef_1 + coef_2)) % mod;
		        }

		        for(int A = 1; A < n2; ++A)
		            for(int B = 1; A + B < n2; ++B) {
		                int C = n2 - A - B;
		                int split = 1ll * comb[n2 - 1][A + B] * comb[A + B][A] % mod;
		                int tmp = 0;
		                for(int x = A - 1; x <= e[A] && x <= m4; ++x)
		                    for(int y = B - 1; y <= e[B] && x + y <= m4; ++y)
		                        tmp = (tmp + 1ll * f[A][x] * f[B][y] % mod * f[C][m4 - x - y]) % mod;
		                int coef = 0;
		                (coef += A * A * B * C) %= mod;
		                (coef += A * B * B * C) %= mod;
		                (coef += A * B * C * C) %= mod;
		                ans = (ans + 1ll * split * tmp % mod * coef) % mod;
		            }
		    }
		    return ans;
		}
		
        return -1;
    }
};

// CUT begin
ifstream data("KingdomAndCities.sample");

string next_line() {
    string s;
    getline(data, s);
    return s;
}

template <typename T> void from_stream(T &t) {
    stringstream ss(next_line());
    ss >> t;
}

void from_stream(string &s) {
    s = next_line();
}

template <typename T>
string to_string(T t) {
    stringstream s;
    s << t;
    return s.str();
}

string to_string(string t) {
    return "\"" + t + "\"";
}

bool do_test(int N, int M, int K, int __expected) {
    time_t startClock = clock();
    KingdomAndCities *instance = new KingdomAndCities();
    int __result = instance->howMany(N, M, K);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (__result == __expected) {
        cout << "PASSED!" << " (" << elapsed << " seconds)" << endl;
        return true;
    }
    else {
        cout << "FAILED!" << " (" << elapsed << " seconds)" << endl;
        cout << "           Expected: " << to_string(__expected) << endl;
        cout << "           Received: " << to_string(__result) << endl;
        return false;
    }
}

int run_test(bool mainProcess, const set<int> &case_set, const string command) {
    int cases = 0, passed = 0;
    while (true) {
        if (next_line().find("--") != 0)
            break;
        int N;
        from_stream(N);
        int M;
        from_stream(M);
        int K;
        from_stream(K);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(N, M, K, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1496977877;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 1000 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
    }
    return 0;
}

int main(int argc, char *argv[]) {
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(2);
    set<int> cases;
    bool mainProcess = true;
    for (int i = 1; i < argc; ++i) {
        if ( string(argv[i]) == "-") {
            mainProcess = false;
        } else {
            cases.insert(atoi(argv[i]));
        }
    }
    if (mainProcess) {
        cout << "KingdomAndCities (1000 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
