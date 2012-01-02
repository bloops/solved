#include <vector>
#include <map>
#include <set>
#include <queue>
#include <algorithm>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstring>

using namespace std;

#define foreach(it, c) for(typeof(c.begin()) it = c.begin(); it != c.end(); it++)

typedef long long int lli;
typedef pair<int,int> ii;

class Cut {
public:
    int getMaximum(vector <int> eelLengths, int maxCuts) {
        int ans = 0;
        vector<int> mult, others;
        for (int i = 0; i < eelLengths.size(); i++){
            if(eelLengths[i] < 10)
                continue;
            if(eelLengths[i] == 10){
                ans++;
                continue;
            }                
            if(eelLengths[i] % 10 == 0)
                mult.push_back(eelLengths[i]);
            else
                others.push_back(eelLengths[i]);
        }
        sort(mult.begin(),mult.end());

        for (int i = 0; i < mult.size(); i++){
            int x = mult[i]/10;
            if(maxCuts < x-1){
                ans += maxCuts;
                return ans;
            }
            ans += x;
            maxCuts -= x-1;
        }

        for (int i = 0; i < others.size(); i++){
            int x = others[i]/10;
            if(maxCuts < x){
                ans += maxCuts;
                return ans;
            }
            ans += x;
            maxCuts -= x;
        }
        return ans;
    }
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <int> p0, int p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << p0[i];
	}
	cout << "}" << "," << p1;
	cout << "]" << endl;
	Cut *obj;
	int answer;
	obj = new Cut();
	clock_t startTime = clock();
	answer = obj->getMaximum(p0, p1);
	clock_t endTime = clock();
	delete obj;
	bool res;
	res = true;
	cout << "Time: " << double(endTime - startTime) / CLOCKS_PER_SEC << " seconds" << endl;
	if (hasAnswer) {
		cout << "Desired answer:" << endl;
		cout << "\t" << p2 << endl;
	}
	cout << "Your answer:" << endl;
	cout << "\t" << answer << endl;
	if (hasAnswer) {
		res = answer == p2;
	}
	if (!res) {
		cout << "DOESN'T MATCH!!!!" << endl;
	} else if (double(endTime - startTime) / CLOCKS_PER_SEC >= 2) {
		cout << "FAIL the timeout" << endl;
		res = false;
	} else if (hasAnswer) {
		cout << "Match :-)" << endl;
	} else {
		cout << "OK, but is it right?" << endl;
	}
	cout << "" << endl;
	return res;
}
int main() {
	bool all_right;
	all_right = true;
	
	vector <int> p0;
	int p1;
	int p2;
	
	{
	// ----- test 0 -----
        int t0[] = {10,10,30,30};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 3;
	p2 = 8;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	int t0[] = {5,5,5,5};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 2;
	p2 = 0;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	int t0[] = {34,10,48};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 4;
	p2 = 5;
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	int t0[] = {30,50,30,50};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	p1 = 350;
	p2 = 16;
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	if (all_right) {
		cout << "You're a stud (at least on the example cases)!" << endl;
	} else {
		cout << "Some of the test cases had errors." << endl;
	}
	return 0;
}
// END KAWIGIEDIT TESTING

//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!