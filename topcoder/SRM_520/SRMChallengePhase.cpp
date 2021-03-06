#include <vector>
#include <algorithm>
#include <iostream>
#include <cstring>

using namespace std;

#define foreach(it, c) for(typeof(c.begin()) it = c.begin(); it != c.end(); it++)

typedef long long int lli;

const int MOD = 1000000007;
const int MAX_N = 2510;

class SRMChallengePhase {
public:

    int factorial[MAX_N];
    int spreadFactorial[MAX_N][MAX_N];
    int choose[MAX_N][MAX_N];
    int DP[MAX_N][MAX_N];

    void factorialPrecompute(int limit){
        factorial[0] = 1;
        for (int i = 1; i <= limit; i++){
            factorial[i] = (i*(lli)factorial[i-1]) % MOD;
        }
    }

    void choosePrecompute(int limit){
        choose[0][0] = 1;
        for (int n = 1; n <= limit; n++){
            choose[n][0] = 1;
            for (int k = 1; k <= n; k++){
                choose[n][k] = (choose[n-1][k] + choose[n-1][k-1]) % MOD;
            }
        }
    }

    int countWays(vector <string> codersAttemptedParts, 
                  vector <string> codersChallengedParts) {

        string codersAttempted, codersChallenged;
        foreach(s,codersAttemptedParts) codersAttempted.append(*s);
        foreach(s,codersChallengedParts) codersChallenged.append(*s);
        
        int N = codersAttempted.size();
        int A = 0, B = 0, C = 0;
        for (int i = 0; i < codersAttempted.size(); i++){
            A += codersAttempted[i] == 'Y' and codersChallenged[i] == 'N';
            B += codersAttempted[i] == 'Y' and codersChallenged[i] == 'Y';
            C += codersAttempted[i] == 'N' and codersChallenged[i] == 'Y';
        }

        factorialPrecompute(N);
        choosePrecompute(N);

        // the answer is A!B!C!(A choose C) (N-1)^(A-C) * DP[A][B]
        lli sum = 1;
        
        sum *= factorial[A]; sum %= MOD;
        sum *= factorial[B]; sum %= MOD;
        sum *= factorial[C]; sum %= MOD;
        sum *= choose[A][C]; sum %= MOD;

        for (int i = 1; i <= A-C; i++){
            sum *= N-1;
            sum %= MOD;
        }

        // we need to count strings over {a,b} each with a weight:
        //    product # of a's to the right of each b
        
        // let DP[i][j] be weighted sum of such strings with exactly i a's and j b's
        // then DP[i][j] = DP[i-1][j] (put an a first) + i * DP[i][j-1] (b first)
        // with base case DP[0][0] = 1

        DP[0][0] = 1;
        for (int i = 0; i <= A; i++){
            for (int j = 0; j <= B; j++){
                DP[i][j] += i > 0 ? DP[i-1][j] : 0;
                DP[i][j] += j > 0 ? (i * (lli)DP[i][j-1]) % MOD : 0;
                DP[i][j] %= MOD;
            }
        }

        sum *= DP[A][B]; sum %= MOD;

        return int(sum);
    }

};

// BEGIN KAWIGIEDIT TESTING
// Generated by KawigiEdit 2.1.4 (beta) modified by pivanof
bool KawigiEdit_RunTest(int testNum, vector <string> p0, vector <string> p1, bool hasAnswer, int p2) {
	cout << "Test " << testNum << ": [" << "{";
	for (int i = 0; int(p0.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p0[i] << "\"";
	}
	cout << "}" << "," << "{";
	for (int i = 0; int(p1.size()) > i; ++i) {
		if (i > 0) {
			cout << ",";
		}
		cout << "\"" << p1[i] << "\"";
	}
	cout << "}";
	cout << "]" << endl;
	SRMChallengePhase *obj;
	int answer;
	obj = new SRMChallengePhase();
	clock_t startTime = clock();
	answer = obj->countWays(p0, p1);
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
	
	vector <string> p0;
	vector <string> p1;
	int p2;
	
	{
	// ----- test 0 -----
	string t0[] = {"YYYY"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"YYNN"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 252;
	all_right = KawigiEdit_RunTest(0, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 1 -----
	string t0[] = {"YY","NN"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"N","NYY"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 4;
	all_right = KawigiEdit_RunTest(1, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 2 -----
	string t0[] = {"YNNN"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"NYY","Y"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 0;
	all_right = KawigiEdit_RunTest(2, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 3 -----
	string t0[] = {"N"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"N"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 1;
	all_right = KawigiEdit_RunTest(3, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 4 -----
	string t0[] = {"YYY"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"NNY"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 24;
	all_right = KawigiEdit_RunTest(4, p0, p1, true, p2) && all_right;
	// ------------------
	}
	
	{
	// ----- test 5 -----
	string t0[] = {"YY","N","YYYY","NN","YYYYY"};
			p0.assign(t0, t0 + sizeof(t0) / sizeof(t0[0]));
	string t1[] = {"N","YYYYY","N","Y","N","YYYY","N"};
			p1.assign(t1, t1 + sizeof(t1) / sizeof(t1[0]));
	p2 = 807026001;
	all_right = KawigiEdit_RunTest(5, p0, p1, true, p2) && all_right;
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
