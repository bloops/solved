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

bool notPrime[500000];
int numMoves[500000]; // +ve if winning, -ve if losing

class PrimeCompositeGame {
public:
    int theOutcome(int N, int K) {
        notPrime[0] = notPrime[1] = true;
        for (int i = 2; i < N; i++){
            if(!notPrime[i]){
                for (int j = 2*i; j < N; j+=i){
                    notPrime[j] = true;
                }
            }
        }
        memset(numMoves,0,sizeof(numMoves));
        // take care of N separately
        set<ii> optimalMoves[2]; // (val,pos) 0 is for primes, 1 for composites
        set<int> kPos;
        for(int i = 2; i <= N; i++){
            while(!kPos.empty() and *kPos.begin() < i-K){
                int r = *kPos.begin();
                optimalMoves[notPrime[r]].erase(ii(numMoves[r],r));
                kPos.erase(kPos.begin());
            }
            int p = 1;
            if(notPrime[i] or i==N){ // go to prime position
                p = 0;
            }

            if(optimalMoves[p].empty()) // no valid moves, lose in 0
                numMoves[i] = 0;
            else if(optimalMoves[p].begin()->first <= 0){
                // there is a losing position to go to
                set<ii>::iterator it = optimalMoves[p].upper_bound(ii(1,0));
                // it cant be begin
                it--;
                numMoves[i] = -it->first + 1;
            }
            else {
                // all are winning positions
                numMoves[i] = -optimalMoves[p].rbegin()->first - 1;
            }

            kPos.insert(i);
            optimalMoves[notPrime[i]].insert(ii(numMoves[i],i));
        }
        
        return numMoves[N];
        
    }
};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, int p0, int p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << p0 << "," << p1;
	cout << "]" << endl;
	PrimeCompositeGame *obj;
	int answer;
	obj = new PrimeCompositeGame();
	clock_t startTime = clock();
	answer = obj->theOutcome(p0, p1);
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
	
	int p0;
	int p1;
	int p2;
	
	{
	// ----- test 0 -----
	p0 = 3;
	p1 = 2;
	p2 = 1;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	p0 = 58;
	p1 = 1;
	p2 = 0;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	p0 = 30;
	p1 = 3;
	p2 = -2;
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	p0 = 6;
	p1 = 3;
	p2 = 1;
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	p0 = 526;
	p1 = 58;
	p2 = 19;
	all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
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