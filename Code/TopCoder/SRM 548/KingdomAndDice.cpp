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

const int N = 55;
const int M = N * N;
class KingdomAndDice {
    public:
    
    int n, m, k;
    int w[M], v[M];
    
    void work(int vv, int ww) {
		for(int i = 0; (1 << i) <= ww; ++i) {
    		if((1 << (i+1)) > ww) 
    			w[++m] = ww - (1 << i) + 1;
    		else w[++m] = 1 << i;
    		v[m] = w[m] * vv; 
    	}
    }
    
    bool dp[N][M];
    int a[N], b[N], c[M], f[N];
    
    double newFairness(vector <int> A, vector <int> B, int s) {
		n = A.size();
		for(int i = 1; i <= n; ++i) a[i] = A[i-1];
		for(int i = 1; i <= n; ++i) b[i] = B[i-1];
		for(int i = 1; i <= n; ++i) if(a[i]) c[++k] = a[i];
		for(int i = 1; i <= n; ++i) if(b[i]) c[++k] = b[i];

		sort(c + 1, c + 1 + k);
		
		c[0] = -1;
		c[k + 1] = s + 1;
		for(int i = 0; i <= k; ++i) {
			int ret = 0;
			for(int j = 1; j <= n; ++j) 
				if(b[j] <= c[i]) ++ret;
			f[ret] += c[i + 1] - c[i] - 1;
		}
		
		for(int i = 0; i <= n; ++i)
			work(i, f[i]);
		
		int tot = 0, sum = 0, lim = n * n;
		for(int i = 1; i <= n; ++i) 
			if(a[i]) {
				for(int j = 1; j <= n; ++j)
					if(b[j] < a[i]) ++sum;
			} else ++tot;
		
		
		dp[0][0] = 1;
		for(int i = 1; i <= m; ++i)
			for(int j = tot; j >= w[i]; --j)
			for(int k = lim; k >= v[i]; --k)
				dp[j][k] |= dp[j - w[i]][k - v[i]];
				
		double ans = sum;
		double std = 1.0 * n * n / 2;
		for(int j = 0; j <= tot; ++j)
		for(int i = 0; i <= lim; ++i)
			if(dp[j][i]) {
				double ret = i + sum;
				if(abs(ans - std) > abs(ret - std)) ans = ret;
				if(abs(ans - std) == abs(ret - std) && ret < ans) ans = ret;
			}
		return ans / lim;
    }
};

// CUT begin
ifstream data("KingdomAndDice.sample");

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

template <typename T> void from_stream(vector<T> &ts) {
    int len;
    from_stream(len);
    ts.clear();
    for (int i = 0; i < len; ++i) {
        T t;
        from_stream(t);
        ts.push_back(t);
    }
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

bool double_equal(const double &a, const double &b) { return b==b && a==a && fabs(b - a) <= 1e-9 * max(1.0, fabs(a) ); }

bool do_test(vector<int> firstDie, vector<int> secondDie, int X, double __expected) {
    time_t startClock = clock();
    KingdomAndDice *instance = new KingdomAndDice();
    double __result = instance->newFairness(firstDie, secondDie, X);
    double elapsed = (double)(clock() - startClock) / CLOCKS_PER_SEC;
    delete instance;

    if (double_equal(__expected, __result)) {
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
        vector<int> firstDie;
        from_stream(firstDie);
        vector<int> secondDie;
        from_stream(secondDie);
        int X;
        from_stream(X);
        next_line();
        double __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(firstDie, secondDie, X, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1496973922;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 450 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "KingdomAndDice (450 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
