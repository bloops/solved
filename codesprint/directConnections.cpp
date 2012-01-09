#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long int lli;
typedef pair<int,int> ii;
typedef pair<lli,lli> li;

const int MAXN = 1000010;
int FBIT[MAXN]; 
lli SBIT[MAXN];

const lli MOD = 1000000007;

int readFreq(int i){
    int sum = 0;
    while(i > 0){
        sum += FBIT[i];
        i -= i & (-i);
    }
    return sum;
}

void incrementFreq(int i){
    while(i < MAXN){
        FBIT[i]++;
        i += i & (-i);
    }
}

lli readSum(int i){
    lli sum = 0;
    while(i > 0){
        sum += SBIT[i];
        i -= i & (-i);
    }
    return sum;
}

void updateSum(int i, lli val){
    while(i < MAXN){
        SBIT[i] += val;
        i += i & (-i);
    }
}

// process query when pop <= p_aug cities are considered
struct query {
    lli x, p_aug, p;
    int idx; // take a BIT of care (1-indexed)
    bool lessq;
};

bool operator<(const query& lhs, const query& rhs){
    return lhs.p_aug < rhs.p_aug;
}

bool firstsecondcompare(const pair<li,int>& lhs, const pair<li,int>& rhs){
    return lhs.first.second < rhs.first.second;
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        memset(SBIT,0,sizeof(SBIT));
        memset(FBIT,0,sizeof(FBIT));
        
        int n;
        cin >> n;
        vector< pair<li,int> > A(n);
        for (int i = 0; i < n; i++){
            cin >> A[i].first.first;
        }
        for (int i = 0; i < n; i++){
            cin >> A[i].first.second;
        }
        sort(A.begin(),A.end());
        for (int i = 0; i < n; i++){
            A[i].second = i+1;
        }

        vector<query> queries;
        for (int i = 0; i < n; i++){
            query q1 = {A[i].first.first, A[i].first.second, A[i].first.second, 
                        A[i].second, false};
            queries.push_back(q1);
            query q2 = {A[i].first.first, A[i].first.second-1, A[i].first.second, 
                        A[i].second, true};
            queries.push_back(q2);
        }
        sort(queries.begin(),queries.end());

        // sort by population
        sort(A.begin(),A.end(),firstsecondcompare);

        lli answer = 0;
        lli a, b, c, d, numcables;
        int ci = 0; // next city to consider
        for (int i = 0; i < queries.size(); i++){
            while(ci < n and A[ci].first.second <= queries[i].p_aug){
                incrementFreq(A[ci].second);
                updateSum(A[ci].second,A[ci].first.first);
                ci++;
            }
            if(!queries[i].lessq){
                b = readFreq(n+1) - readFreq(queries[i].idx);
                numcables = queries[i].p;
                a = readSum(n+1) - readSum(queries[i].idx);
                answer += (((a - b*queries[i].x) % MOD) * numcables) % MOD;
            }
            else {
                c = readSum(queries[i].idx - 1); 
                d = readFreq(queries[i].idx - 1);
                numcables = queries[i].p;
                answer += (((d*queries[i].x - c) % MOD) * numcables) % MOD;
            }
            answer %= MOD;
        }
        cout << answer << '\n';
    }
    return 0;
}

