#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int N = 1010;
const int INF = 1<<30;

map<char,vector<int> > positions;

// Given i, DP[i][k] = maximum j over all common subsequences $\sigma$ of
// A[0]..A[i] of length exactly k, where j is the minimum 
// ending position of \sigma as a subsequence of B
int DP[N];

// DP[i][k] = max(DP[i-1][k], 
//    first occurrence of A[i] in B after DP[i-1][k-1] (if DP[i-1][k-1] is defined)

// If an answer is a subsequence of length k ending with A[i],
// a necessary and sufficient condition is: 
// (DP[i-1][k-1] is defined or k=0) and A[i] does not occur in B after DP[i-1][k-1]

int main()
{
    ios::sync_with_stdio(false);
    string A, B;
    cin >> A >> B;

    for (int i = 0; i < B.length(); i++){
        positions[B[i]].push_back(i);
    }

    // if A[0] is not found in B, we already have a solution of length 1
    if(positions[A[0]].empty()){
        cout << 1 << endl;
        return 0;
    }
    
    DP[0] = -1;
    DP[1] = positions[A[0]][0]; // first position of A[0] in B
    for (int k = 2; k <= A.length(); k++){
        DP[k] = -INF;
    }

    int shortest = INF;

    for (int i = 1; i < A.length(); i++){
        for (int k = A.length(); k >= 1; k--){
            int c = A[i];
            // find the first position occurrence of A[i] after DP[k-1]
            vector<int>::iterator it = 
                upper_bound(positions[c].begin(),
                            positions[c].end(),
                            DP[k-1]);
            if(k > 1 and DP[k-1] < 0) // DP[k-1] is not defined
                continue;
            if(it == positions[c].end()) // update answer if A[i] not found after DP[k-1]
                shortest = min(shortest,k);
            if(it != positions[c].end())
                DP[k] = max(DP[k],*it);
        }
    }
    
    cout << shortest << endl;
    return 0;
}

