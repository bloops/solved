#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cstdio>
using namespace std;
typedef pair<int,int> ii;

const int MAXN = 1000010;
int BIT[MAXN]; 

// returns sum [1..i]
int read(int i){
    int sum = 0;
    while(i > 0){
        sum += BIT[i];
        i -= i & (-i);
    }
    return sum;
}

void increment(int i){
    while(i < MAXN){
        BIT[i]++;
        i += i & (-i);
    }
}

// query is a vertical segment [x,(y1,y2)]
struct query { 
    int x;
    ii ys;   // add the points if y1 < y2, subtract otherwise
    int idx; // the polygon it contributes to
    bool positive;
};

bool operator<(const query& lhs, const query& rhs){
    return lhs.x < rhs.x;
}

int main()
{
    ios::sync_with_stdio(false);
    int n, q;
    cin >> n >> q;

    vector<ii> points(n);
    set<int> Y;
    for (int i = 0; i < n; i++){
        cin >> points[i].first >> points[i].second;
        Y.insert(points[i].second);
    }
    sort(points.rbegin(),points.rend());
    
    vector<query> queries;
    vector<int> answer(q);
    
    int m;
    vector<ii> vertices(20);
    for (int i = 0; i < q; i++){
        cin >> m;
        for (int j = 0; j < m; j++){
            cin >> vertices[j].first >> vertices[j].second;
            Y.insert(vertices[j].second);
        }
        for (int j = 0; j < m; j++){
            int k = j == m-1 ? 0 : j + 1;
            // consider segment (vertices[j], vertices[k])
            // horizontal
            if(vertices[j].second == vertices[k].second){
                continue;
            }
            query qr = {vertices[j].first, 
                        ii(min(vertices[j].second, vertices[k].second),
                           max(vertices[j].second, vertices[k].second)),
                        i, vertices[j].second < vertices[k].second};
            if(!qr.positive) // negative query
                qr.x ++;

            int a = j == 0 ? m-1 : j-1, b = k == m-1 ? 0 : k+1;
            if(qr.positive){
                if(vertices[a].first < vertices[j].first){
                    qr.ys.first++;
                }
                if(vertices[b].first < vertices[k].first){
                    qr.ys.second--;
                }
            }else{
                if(vertices[a].first > vertices[j].first){
                    qr.ys.second--;
                }
                if(vertices[b].first > vertices[k].first){
                    qr.ys.first++;
                }
            }
            Y.insert(qr.ys.first), Y.insert(qr.ys.second);
            queries.push_back(qr);
        }
    }

    map<int,int> ymap;
    int idx = 1;
    for(set<int>::iterator it = Y.begin(); it != Y.end(); it++, idx++){
        ymap[*it] = idx;
    }

    for (int i = 0; i < n; i++){
        points[i].second = 2*ymap[points[i].second];
    }

    for (int i = 0; i < queries.size(); i++){
        queries[i].ys.first = 2*ymap[queries[i].ys.first];
        queries[i].ys.second = 2*ymap[queries[i].ys.second];
    }
    sort(queries.rbegin(),queries.rend());
    
    int pi = 0; // next point to consider
    for (int i = 0; i < queries.size(); i++){
        while(pi < points.size() and points[pi].first >= queries[i].x){
            increment(points[pi].second);
            pi++;
            //cout << "Inserting point!" << endl;
        }
        int qret = read(queries[i].ys.second) - read(queries[i].ys.first-1);
        // cout << "ID: " << queries[i].idx  << " Got a query: " << qret << " with sign " << queries[i].positive << "! :D" << endl;
        answer[queries[i].idx] += (queries[i].positive ? 1 : -1) * qret;
    }
    
    for (int i = 0; i < q; i++){
        cout << answer[i] << '\n';
    }
    return 0;
}

