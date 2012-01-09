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

const int MAXN = 150010;

lli best[MAXN]; // best[x] = maximum weight of a sequence ending in value x
lli BIT[MAXN]; // Binary indexed tree for prefix range maximum queries over best[1..N]

// returns max [1..i]
lli read(int i){
    lli ret = 0;
    while(i > 0){
        ret = max(ret,BIT[i]);
        i -= i & (-i);
    }
    return ret;
}

// make sure new value is >= old value
void update(int i, lli val){
    while(i < MAXN){
        BIT[i] = max(BIT[i],val);
        i += i & (-i);
    }
}


int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        memset(BIT,0,sizeof(BIT));
        memset(best,0,sizeof(best));

        int n;
        cin >> n;
        vector< pair<ii,int> > A(n);
        for (int i = 0; i < n; i++){
            cin >> A[i].first.first;
            A[i].second = i;
        }
        for (int i = 0; i < n; i++){
            cin >> A[i].first.second;
        }

        // map a1,..,an to rank(a1)..rank(an)
        sort(A.begin(),A.end());
        int idx = 0;
        vector<ii> B(n);
        for (int i = 0; i < n; i++){
            if(i == 0 or A[i].first.first != A[i-1].first.first)
                idx++;
            B[A[i].second] = ii(idx,A[i].first.second);
        }
        
        lli ans = 0;
        for (int i = 0; i < n; i++){
            int x = B[i].first;
            lli extend = read(x-1) + lli(B[i].second);
            if(best[x] < extend){
                best[x] = extend;
                update(x,extend);
                ans = max(ans,best[x]);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}

