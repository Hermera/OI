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


class TPS {
	public: 
		int minimalBeacons(vector <string>);
};


const int N = 55;

int h[N], n, cnt;
struct Data {
	int next, to;
} g[N << 1];

void add(int x, int y) {
	g[++cnt] = (Data) { h[x], y }; h[x] = cnt;
}


int dp[N][2];
int dfs(int x, int p, int k) {
	if(~dp[x][k]) return dp[x][k];
	
	int son = 0, sum = 0;
	for(int v, i = h[x]; i; i = g[i].next)
		if((v = g[i].to) != p) 
			sum += dfs(v, x, 1), ++son;
	
	if(!son) return dp[x][k] = k;
	if(!k || son != 1) {
		int tmp = 0;
		for(int v, i = h[x]; i; i = g[i].next)
			if((v = g[i].to) != p)
				tmp = max(tmp, dfs(v, x, 1) - dfs(v, x, 0));
		sum -= tmp;
	}
	return dp[x][k] = sum;
}


int TPS::minimalBeacons(vector <string> edge) {
	n = edge.size();
	for(int i = 0; i < n; ++i) h[i] = cnt = 0;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j)
			if(edge[i][j] == 'Y') add(i, j);
	if(n == 1) return 0;
	
	int ans = n;
	for(int i = 0; i < n; ++i) {
		memset(dp, -1,  sizeof(dp));
		ans = min(ans, dfs(i, -1, 0) + 1);
	}
	return ans;
}


// CUT begin
ifstream data("TPS.sample");

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

bool do_test(vector<string> linked, int __expected) {
    time_t startClock = clock();
    TPS *instance = new TPS();
    int __result = instance->minimalBeacons(linked);
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
        vector<string> linked;
        from_stream(linked);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(linked, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1493901828;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 950 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "TPS (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
