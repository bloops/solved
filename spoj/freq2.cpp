#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
using namespace std;

typedef pair<int,int> ii;

#define iter(c) typeof(c.begin())
#define foreach(it, c) for(iter(c) it = c.begin(); it != c.end(); it++)

const int N = 100010;
const int M = 330;
const int INF = 1<<30;

int A[N];
pair<ii,int> query[N]; // ([i,j],query_index)

// leastJ[x] (x < M) = for a fixed i, 
// is the minimum value of j s.t. maxfreq[i,j] >= x
int leastJ[M]; 

int freq[N]; // freq[c] = number of times c occurs in A
vector<int> hifreq; // values occurring >= M times
vector<int> occurrences[N]; // occurrences[c] = sorted list of positions where c occurs

int answer[N]; // answer[i] = answer to the ith query

int main()
{
    int n, q;
    scanf("%d %d",&n,&q);
    for (int i = 0; i < n; i++){
        scanf("%d",&A[i]);
        freq[A[i]]++;
        occurrences[A[i]].push_back(i);
    }

    for (int c = 0; c < n; c++){
        if(freq[c] >= M)
            hifreq.push_back(c);
    }
    for (int i = 0; i < q; i++){
        scanf("%d %d",&query[i].first.first,&query[i].first.second);
        query[i].second = i;
    }

    sort(query,query+q);

    for (int x = 1; x < M; x++){
        leastJ[x] = INF;
    }
    
    for(int i = n-1, qi = q-1; i >= 0; i--)
    {
        int c = A[i];
        if(freq[c] < M){
            int j = 0;
            while(occurrences[c][j] < i) // j < j0 where occurrences[c][j0] = i
                j++;
            for(int k = 1; j < occurrences[c].size(); j++,k++){
                leastJ[k] = min(leastJ[k],occurrences[c][j]);
            }
        }
        // qi is the next query we should process
        while(qi >= 0 and query[qi].first.first == i){
            // process the query qi
            int a = query[qi].first.first, b = query[qi].first.second;
            int ans = 1;

            // for the values occurring >= M times (there can be atmost N/M such values)
            // find each of their frequencies in the interval [a,b]
            foreach(h, hifreq){
                int occur_b = lower_bound(occurrences[*h].begin(),occurrences[*h].end()
                                          ,b+1) - occurrences[*h].begin();
                int occur_a = lower_bound(occurrences[*h].begin(),occurrences[*h].end()
                                          ,a) - occurrences[*h].begin();
                // *h occurs (occur_b - occur_a) times
                ans = max(ans,occur_b - occur_a);
            }

            // now to account for the values occurring less than M times
            // use binary search to find the greatest x such that leastJ[x] <= b
            int lo = 1, hi = M; 
            while(hi - lo > 1){ // our answer lies in the interval [lo,hi)
                int mi = (lo+hi)/2; 
                if(leastJ[mi] > b)
                    hi = mi;
                else
                    lo = mi;
            }
            ans = max(ans,lo);
            answer[query[qi].second] = ans;
            qi--;
        }
    }
    
    for (int i = 0; i < q; i++){
        printf("%d\n",answer[i]);
    }

    return 0;
}

