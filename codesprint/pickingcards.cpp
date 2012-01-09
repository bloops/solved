#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cstdio>
using namespace std;

typedef long long int lli;

const int MOD = 1000000007;
const int MAXN = 50010;
int C[MAXN];

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        int n;
        cin >> n;
        for (int i = 0; i < n; i++){
            cin >> C[i];
        }
        sort(C,C+n);

        lli answer = 1;
        int current = 0, numcards = 0;
        for(int placed = 0; placed < n; placed++){
            while(current < n and C[current] <= placed){
                current++;
                numcards++;
            }
            answer *= numcards;
            answer %= MOD;
            numcards--;
        }
        cout << answer << '\n';
    }
    return 0;
}

