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
const int M = 30;

class FoxAndHandle {
    public:

	int pre[M], suf[M];
	int idx(char ch) {
		return ch - 'a';
	}

	int n, m, vis[N];
	string s;

	bool judge(int x) {
		for(int i = 0; i < m; ++i) 
			pre[i] = suf[i] = 0;
		pre[idx(s[x])] = -1;
		for(int i = 0; i < n; ++i) {
			int w = idx(s[i]);
			if(!vis[i]) {
				if(i < x) ++pre[w];
				else ++suf[w];
			} else --pre[w];
		}
	
		for(int i = 0; i < m; ++i)
			if(pre[i] > suf[i] || pre[i] + suf[i] < 0)
				return 0;
		/*	pre[i] > suf[i]: the prefix string is too large
			pre[i] + suf[i] < 0: you must leave half of the string
		*/
		return 1;
	}


	string lexSmallestName(string a) {
		s = a;
		m = 26;
		n = s.size();

		int las = 0;	
		string ans = "";
		for(int i = 0; i < n; ++i) vis[i] = 0;
		for(int i = 0; i < n/2; ++i) {
			int now = -1;
			for(int j = las; j < n; ++j) 
				if(judge(j) && (now < 0 || s[now] > s[j])) 
					now = j;
			vis[now] = 1;
			ans = ans + s[now];
			las = now + 1;
		}
		return ans;
	}
};




// CUT begin
ifstream data("FoxAndHandle.sample");

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

bool do_test(string S, string __expected) {
    time_t startClock = clock();
    FoxAndHandle *instance = new FoxAndHandle();
    string __result = instance->lexSmallestName(S);
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
        string S;
        from_stream(S);
        next_line();
        string __answer;
        from_stream(__answer);

        cases++;
        if (case_set.size() > 0 && case_set.find(cases - 1) == case_set.end())
            continue;

        cout << "  Testcase #" << cases - 1 << " ... ";
        if ( do_test(S, __answer)) {
            passed++;
        }
    }
    if (mainProcess) {
        cout << endl << "Passed : " << passed << "/" << cases << " cases" << endl;
        int T = time(NULL) - 1495867527;
        double PT = T / 60.0, TT = 75.0;
        cout << "Time   : " << T / 60 << " minutes " << T % 60 << " secs" << endl;
        cout << "Score  : " << 300 * (0.3 + (0.7 * TT * TT) / (10.0 * PT * PT + TT * TT)) << " points" << endl;
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
        cout << "FoxAndHandle (300 Points)" << endl << endl;
    }
    return run_test(mainProcess, cases, argv[0]);
}
// CUT end
