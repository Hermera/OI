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
#include <map>

using namespace std;

const int N = 55;
const int M = N * N;
const int mod = 1e9 + 9;

const int fx[] = { 0, 0, 1, -1 };
const int fy[] = { 1, -1, 0, 0 };

class CoinsGame {
    public:
    
    struct ele {
    	int x0, x1, x2, x3;
    	bool operator <(const ele &b) const {
    		if(x0 != b.x0) return x0 < b.x0;
    		if(x1 != b.x1) return x1 < b.x1;
    		if(x2 != b.x2) return x2 < b.x2;
    		return x3 < b.x3;
    	}
    };
    

    int n, m, b[N][N]; 
    int cur[N][N], col[N][N];
    int pw2[M], sum[M];
        
    
    int go(int x, int y, int d) {
    	int nx = x + fx[d];
    	int ny = y + fy[d];
    	if(nx < 0 || ny < 0 || nx >= n || ny >= m) return -1;
    	if(!b[nx][ny]) return col[nx][ny];
    	return col[x][y];
    }
    
    int ways(vector <string> a) {
    	n = a.size();
    	m = a[0].size();
    	
    	for(int i = 0; i < n; ++i)
    		for(int j = 0; j < m; ++j)
    			if(a[i][j] == '#') b[i][j] = 1;
    	
    	int now = 0;
		for(;;) {
			int tot = 0;
			map <ele, int> num;
			for(int i = 0; i < n; ++i)
				for(int j = 0; j < m; ++j) 
					if(!b[i][j]) {
						ele ret;
						ret.x0 = go(i, j, 0);
						ret.x1 = go(i, j, 1);
						ret.x2 = go(i, j, 2);
						ret.x3 = go(i, j, 3);
					
						if(!num.count(ret))
							num[ret] = ++tot;
						cur[i][j] = num[ret];
					}
			
			if(tot == now) break;
			now = tot;
			memcpy(col, cur, sizeof(col));
		}
		
		int tot = 0;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(!b[i][j]) ++tot;
		
		pw2[0] = 1;
		for(int i = 1; i <= tot; ++i)
			pw2[i] = (pw2[i-1] << 1) % mod;
		
		int ans = pw2[tot] - 1;
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < m; ++j)
				if(!b[i][j]) ++sum[col[i][j]];
		for(int i = 1; i <= now; ++i)
			(ans -= pw2[sum[i]] - 1) %= mod;
		(ans += mod) %= mod;
		return ans;
    }
};

// CUT begin
ifstream data("CoinsGame.sample");

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

bool do_test(vector<string> board, int __expected) {
    time_t startClock = clock();
    CoinsGame *instance = new CoinsGame();
    int __result = instance->ways(board);
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
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(board, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1495871982;
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
        cout << "CoinsGame (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
