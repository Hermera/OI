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

const int N = 7;
const int inf = 1e9;

typedef pair<int, int> pii;
#define fir first
#define sec second
#define pb push_back

class CosmicBlocks {
    public:

	int n, am[N], dg[N];
	int suf[N][N], pre[N][N], st[N], pt[N];
	int deg[N], tie[N], q[N];


	bool topsort() {
		memcpy(deg, dg, sizeof(dg));
		memset(tie, 0, sizeof(tie));
		
		int flo = 1, fi = 1, ed = 0;
		for(int i = 1; i <= n; ++i)
			if(!deg[i]) tie[i] = flo, q[++ed] = i;
		while(fi <= ed) {
			int u = q[fi++];
			for(int i = 1; i <= st[u]; ++i) {
				int v = suf[u][i];
				if(tie[v] && tie[v] != tie[u] + 1) return 0; // 不是严格分层
				else tie[v] = tie[u] + 1;
				if(!(--deg[v])) q[++ed] = v;
			}
		}
		return ed == n; // 有环
	}

	int poi[N], vis[N], du[N];
	bool check() {
		memcpy(du, am, sizeof(am));
		for(int i = 1; i <= n; ++i) 
			if(am[i] < pt[i]) return 0;
		if(!topsort()) return 0;
		
		for(int i = 2; i <= n; ++i) {
			int t = 0;
			for(int j = 1; j <= n; ++j)
				if(tie[j] == i) poi[++t] = j;
			if(!t) break;
			
			for(int j = 1; j <= t; ++j)
				for(int k = 1; k <= pt[poi[j]]; ++k)
					if((--du[pre[poi[j]][k]]) < 0) return 0; 
					// 首先需要满足当前边集的条件
			
			for(int j = 1; j < (1 << t); ++j) { // Hall 定理
				int tot = 0;
				memset(vis, 0, sizeof(vis));
				for(int k = 1; k <= n; ++k) 
					if(j & (1 << (k-1))) {
						int u = poi[k];
						tot -= du[u] - pt[u];
						for(int p = 1; p <= pt[u]; ++p) {
							int v = pre[u][p];
							if(!vis[v]) {
								vis[v] = 1;
								tot += du[v];
							}
						}
					}
				if(tot < 0) return 0;
			}
		}
		return 1;
	}


	int rnk[N];
	bool judge() {
		memcpy(deg, dg, sizeof(deg));
		for(int i = 1; i <= n; ++i) {
			int x = rnk[i];
			if(deg[x]) return 0;
			for(int j = 1; j <= st[x]; ++j)
				--deg[suf[x][j]];
		}
		return 1;
	}
	
	int minW, maxW;
	bool calc() {
		int ret = 0;
		for(int i = 1; i <= n; ++i) rnk[i] = i;
		do ret += judge();
		while(next_permutation(rnk + 1, rnk + 1 + n)); // 枚举排列，分别判断合法性
		return minW <= ret && ret <= maxW;
	}	
	



	void add(int x, int y) {
		suf[x][++st[x]] = y;
		pre[y][++pt[y]] = x;
		++dg[y];
	}

	int solve() {
		int e = 1;
		int ans = 0;
		for(int i = 1; i <= n * (n - 1) / 2; ++i) e *= 3;
		
		for(int i = 0; i < e; ++i) { // 枚举边集
			int now = i;
			memset(pt, 0, sizeof(pt));
			memset(st, 0, sizeof(st));
			memset(dg, 0, sizeof(dg));
			for(int u = 1; u <= n; ++u) 
				for(int v = u + 1; v <= n; ++v) {
					if(now % 3 == 1) add(u, v);
					if(now % 3 == 2) add(v, u);
					now /= 3;
				}
			
			if(check()) // 判断边集是否合法
				ans += calc(); // 计数
		}
		return ans;
	}

    int getNumOrders(vector <int> blockTypes, int minWays, int maxWays) {
    	n = blockTypes.size();
    	minW = minWays;
    	maxW = maxWays;
    	
    	for(int i = 1; i <= n; ++i)
    		am[i] = blockTypes[i - 1];
    	int ans = solve();
    	return ans;
    }
};





// CUT begin
ifstream data("CosmicBlocks.sample");

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

bool do_test(vector<int> blockTypes, int minWays, int maxWays, int __expected) {
    time_t startClock = clock();
    CosmicBlocks *instance = new CosmicBlocks();
    int __result = instance->getNumOrders(blockTypes, minWays, maxWays);
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
        vector<int> blockTypes;
        from_stream(blockTypes);
        int minWays;
        from_stream(minWays);
        int maxWays;
        from_stream(maxWays);
        next_line();
        int __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(blockTypes, minWays, maxWays, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1496997741;
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
        cout << "CosmicBlocks (950 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
