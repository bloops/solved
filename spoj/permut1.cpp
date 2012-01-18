#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cstdio>
using namespace std;
typedef long long int lli;

const int N = 13;
lli DP[N][N*N];
// DP[i][x] = number of ordered partitions of x into 
//            i+1 parts such that jth part <= j

int main()
{
    ios::sync_with_stdio(false);
    DP[0][0] = 1;
    
    for (int i = 1; i < N; i++){
        for (int j = 0; j <= i; j++){
            for (int x = 0; x+j < N*N; x++){
                DP[i][x+j] += DP[i-1][x];
            }
        }
    }

    int T;
    int n,k;
    cin >> T;
    while(T--){
        cin >> n >> k;
        cout << DP[n-1][k] << '\n';
    }
    return 0;
}

