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

class SetAndSet {
    public:
    	ll countandset(vector<int> A);
};


const int L = 21;
const int N = 55;

int getf(int *f, int x) { 
	return f[x] == x ? x : f[x] = getf(f, f[x]);
}

void merge(int *f, int x, int y) {
	f[getf(f, x)] = getf(f, y);
}


vector <int> d[L];
int n, l, f[N];


ll ans;
void dfs(int k, int *f, int on) {
	if(k == l) {
		int tot = 0;
		for(int i = 0; i < n; ++i) 
			if(getf(f, i) == i) ++tot;
		ans += (1LL << tot) * on;
		return;
	}
	
	dfs(k+1, f, on);
	
	if(!d[k].empty()) {
		int g[N], x = d[k][0];
		for(int i = 0; i < n; ++i) g[i] = f[i];
		for(int i = 1; i < d[k].size(); ++i)
			merge(g, x, d[k][i]);
		dfs(k+1, g, -on);
	}
}


ll SetAndSet::countandset(vector <int> a) {
	l = 20;
	n = a.size();
	
	int all = (1 << l) -1;
	for(int i = 0; i < n; ++i) all &= a[i];
	for(int i = 0; i < n; ++i) a[i] ^= all;
	for(int i = 0; i < n; ++i) f[i] = i;
	for(int i = 0; i < l; ++i) d[i].clear();
	
	ans = 0;
	for(int i = 0; i < l; ++i)
		for(int j = 0; j < n; ++j)
			if(~a[j] & (1 << i)) d[i].push_back(j);
			
	dfs(0, f, 1);
	return ans;
}




// CUT begin
ifstream data("SetAndSet.sample");

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

bool do_test(vector<int> A, long long __expected) {
    time_t startClock = clock();
    SetAndSet *instance = new SetAndSet();
    long long __result = instance->countandset(A);
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
        vector<int> A;
        from_stream(A);
        next_line();
        long long __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(A, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493991038;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 975 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "SetAndSet (975 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
