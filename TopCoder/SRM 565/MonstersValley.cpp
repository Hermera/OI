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
typedef long long ll;

const int N = 105;

class MonstersValley {
    public:
    int n, m, p[N];
    ll d[N], dp[N][N];
    void cmax(ll &x, ll y) {
    	x = x < y ? y : x;
    }
    
    int minimumPrice(vector <ll> de, vector <int> pi) {
    	n = pi.size();
    	m = n << 1;
    	memset(dp, -63, sizeof(dp));
    	
    	dp[0][0] = 0;
    	for(int i = 1; i <= n; ++i) d[i] = de[i-1], p[i] = pi[i-1];
    	for(int i = 1; i <= n; ++i)
	    	for(int j = 0; j <= m; ++j) {
				if(j >= p[i]) cmax(dp[i][j], dp[i-1][j-p[i]] + d[i]);
				if(dp[i-1][j] >= d[i]) cmax(dp[i][j], dp[i-1][j]);
	    	}
	    
	    for(int i = 1; i <= m; ++i)
	    	if(dp[n][i] >= 0) return i;
	    return -1;
    }
};

// CUT begin
ifstream data("MonstersValley.sample");

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

bool do_test(vector<long long> dread, vector<int> price, int __expected) {
    time_t startClock = clock();
    MonstersValley *instance = new MonstersValley();
    int __result = instance->minimumPrice(dread, price);
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
        vector<long long> dread;
        from_stream(dread);
        vector<int> price;
        from_stream(price);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(dread, price, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1496477736;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 250 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MonstersValley (250 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
