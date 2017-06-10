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

const int N = 20;
const int S = 2e6+5;
const int inf = 1e9;

class MagicalHats {
    public:
    
	// 0: haven't open
	// 1: opened and found there's no coin
	// 2: opened and found thers's a coin
	int rs[N], cs[N], ro[N], co[N];
	int xp[N], yp[N], pow[N];
	
	int dp[S], vis[S];
	int n, r, c;
	
	int at(int s, int i) {
		return s / pow[i] % 3;
	}
	
    int dfs(int s, int t, int k) {
    	if(vis[s]) return dp[s];
    	vis[s] = 1;
    
    	if(!k) {
    		for(int i = 0; i < r; ++i) rs[i] = 0;
	   		for(int i = 0; i < c; ++i) cs[i] = 0;
    		for(int i = 0; i < n; ++i)
    			if(at(s, i) == 2) ++rs[xp[i]], ++cs[yp[i]];
    		for(int i = 0; i < r; ++i)
    			if((ro[i] + rs[i]) & 1) return dp[s] = inf;
    		for(int i = 0; i < c; ++i)
    			if((co[i] + cs[i]) & 1) return dp[s] = inf;
    		return dp[s] = 0;
    	}
    	
    	if(!t) {
    		for(int i = 0; i < n; ++i)
    			if(!at(s, i) && !dfs(s + pow[i]*2, t, k-1)) 
    				return dp[s] = 0;
    		return dp[s] = inf;
    	}
    	
    	for(int i = 0; i < n; ++i)
    		if(!at(s, i)) {
    			int ret = inf;
    			ret = min(ret, dfs(s + pow[i]*2, t-1, k-1)+1);
    			ret = min(ret, dfs(s + pow[i]*1, t-1, k));
    			
    			dp[s] = max(ret, dp[s]);
    		}
    	return dp[s];
    }
    
    int findMaximumReward(vector <string> board, vector <int> coins, int s) {
		r = board.size();
		c = board[0].size();
		for(int i = 0; i < r; ++i)
			for(int j = 0; j < c; ++j) 
				if(board[i][j] == 'H') {
					++ro[i], ++co[j];
					xp[n] = i, yp[n++] = j;
				}
				
		pow[0] = 1;
		for(int i = 1; i <= n; ++i) pow[i] = pow[i-1] * 3;
		sort(coins.begin(), coins.end());
		
		int num = dfs(0, s, coins.size()), ans = 0;
		if(num > coins.size()) return -1;
		
		for(int i = 0; i < num; ++i)
			ans += coins[i];
		return ans;
    }
};

// CUT begin
ifstream data("MagicalHats.sample");

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

bool do_test(vector<string> board, vector<int> coins, int numGuesses, int __expected) {
    time_t startClock = clock();
    MagicalHats *instance = new MagicalHats();
    int __result = instance->findMaximumReward(board, coins, numGuesses);
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
        vector<string> board;
        from_stream(board);
        vector<int> coins;
        from_stream(coins);
        int numGuesses;
        from_stream(numGuesses);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, coins, numGuesses, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1496991342;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 600 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "MagicalHats (600 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
