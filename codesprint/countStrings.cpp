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
#define foreach(it, c) for(set<int>::iterator it = c.begin(); it != c.end(); it++)

string regex;

struct node {
    char symbol;
    ii child;
    int position_id;
};

vector<node> tree;

vector<int> positions; // positions[i] = node index of ith position in syntax tree

// parse regex[i..j] and returns index of node in syntax tree.
int parse(int i, int j){
    if(i == j) { // position
        int node_id = tree.size();
        node n = {regex[i], ii(-1,-1), int(positions.size())};
        tree.push_back(n);
        positions.push_back(node_id);
        return node_id;
    }
    // is of the form (R1R2) or (R1|R2) or (R1*)
    int k = i+1; // want: [i+1..k] to be R1
    if(regex[i+1] == '('){
        int match = 1; // find matching closing brace
        while(match > 0){
            k++;
            if(regex[k] == '(') match++;
            else if(regex[k] == ')') match--;
        }
    }
    
    int node_id;
    node n;
    // find the op
    if(regex[k+1] == '|') n.symbol = '|';
    else if(regex[k+1] == '*') n.symbol = '*';
    else n.symbol = 'o';

    if(n.symbol == '*'){
        n.child.first = parse(i+1,k);
        n.child.second = -1;
        node_id = tree.size();
        tree.push_back(n);
        return node_id;
    }

    int l = n.symbol == 'o' ? k+1 : k+2; // want: [l..j-1] to be R2

    n.child.first = parse(i+1,k);
    n.child.second = parse(l,j-1);
    node_id = tree.size();
    tree.push_back(n);
    return node_id;
}

vector<bool> nullable;
vector< set<int> > firstpos, lastpos, followpos;

void computeNullable(int n){
    if(tree[n].child.first == -1){ // leaf node
        nullable[n] = false;
    }
    else if(tree[n].symbol == '*'){
        nullable[n] = true;
        computeNullable(tree[n].child.first);
    }
    else {
        int l = tree[n].child.first, r = tree[n].child.second;
        computeNullable(l);
        computeNullable(r);
        
        if(tree[n].symbol == '|') 
            nullable[n] = nullable[l] or nullable[r];
        if(tree[n].symbol == 'o') 
            nullable[n] = nullable[l] and nullable[r];
    }
}

void computeFirstLastpos(int n){
    if(tree[n].child.first == -1){ // leaf
        firstpos[n].insert(tree[n].position_id);
        lastpos[n].insert(tree[n].position_id);
    }
    else if(tree[n].symbol == '*'){
        computeFirstLastpos(tree[n].child.first);
        firstpos[n] = firstpos[tree[n].child.first];
        lastpos[n] = lastpos[tree[n].child.first];
    }
    else {
        int l = tree[n].child.first, r = tree[n].child.second;
        computeFirstLastpos(l);
        computeFirstLastpos(r);

        firstpos[n] = firstpos[l];
        lastpos[n] = lastpos[r];
        if(tree[n].symbol == '|' or (tree[n].symbol == 'o' and nullable[l])){
            // union
            foreach(it,firstpos[r])
                firstpos[n].insert(*it);
        }

        if(tree[n].symbol == '|' or (tree[n].symbol == 'o' and nullable[r])){
            // union
            foreach(it,lastpos[l])
                lastpos[n].insert(*it);
        }
    }
}

void computeFollowpos(int p){
    for (int i = 0; i < tree.size(); i++){
        if(tree[i].symbol == '*'){
            if(lastpos[i].find(p) != lastpos[i].end()){
                foreach(it,firstpos[i])
                    followpos[p].insert(*it);
            }
        }
        if(tree[i].symbol == 'o'){
            if(lastpos[tree[i].child.first].find(p) != lastpos[tree[i].child.first].end()){
                foreach(it,firstpos[tree[i].child.second])
                    followpos[p].insert(*it);
            }
        }
    }
}

map< set<int>, int> statemap;
vector<ii> states;
vector<bool> final;
vector< set<int> > statesets;

void constructDFA(int root){
    statesets.push_back(firstpos[root]);
    statemap[firstpos[root]] = 0;
    states.push_back(ii(-1,-1));

    for(int i = 0; i < statesets.size(); i++){
        set<int> a, b;
        foreach(it,statesets[i]){
            char c = tree[positions[*it]].symbol;
            if(c == 'a')
                foreach(jt,followpos[*it])
                    a.insert(*jt);
            else if(c == 'b')
                foreach(jt,followpos[*it])
                    b.insert(*jt);
        }
        if(statemap.count(a)){
            states[i].first = statemap[a];
        }
        else {
            statemap[a] = states[i].first = statesets.size();
            statesets.push_back(a);
            states.push_back(ii(-1,-1));
        }

        if(statemap.count(b)){
            states[i].second = statemap[b];
        }
        else {
            statemap[b] = states[i].second = statesets.size();
            statesets.push_back(b);
            states.push_back(ii(-1,-1));
        }
    }
    
    final = vector<bool>(states.size());
    int finalpos = positions.size() - 1;
    for (int i = 0; i < final.size(); i++){
        if(statesets[i].find(finalpos) != statesets[i].end())
            final[i] = true;
    }
    
}

const int MOD = 1000000007; 
const int N = 510;
lli DP[N][N][31]; // DP[i][j][k] = no. of ways to go from i to j in exactly 2^k steps
lli ways[N];  // WAYS[i] = no. of ways to reach state i from 0 so far
lli tways[N];

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){

        cin >> regex;
        regex = "(" + regex + "#)";

        tree.clear();
        positions.clear();

        parse(0,int(regex.size())-1);

        int root = tree.size() - 1;

        nullable = vector<bool>(tree.size());
        computeNullable(root);

        firstpos = vector< set<int> >(tree.size());
        lastpos = vector< set<int> >(tree.size());
        computeFirstLastpos(root);

        followpos = vector< set<int> >(positions.size());
        for (int i = 0; i < positions.size(); i++){
            computeFollowpos(i);
        }

        statemap.clear();
        states.clear();
        final.clear();
        statesets.clear();

        constructDFA(root);

        memset(DP,0,sizeof(DP));

        int n = states.size();
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                DP[i][j][0] += states[i].first == j;
                DP[i][j][0] += states[i].second == j;
            }
        }
    
        for (int l = 1; l <= 30; l++){
            for (int k = 0; k < n; k++){
                for (int i = 0; i < n; i++){
                    for (int j = 0; j < n; j++){
                        DP[i][j][l] += (DP[i][k][l-1] * DP[k][j][l-1]) % MOD;
                        DP[i][j][l] %= MOD;
                    }
                }
            }
        }

        int L;
        cin >> L;
        memset(ways,0,sizeof(ways));
        ways[0] = 1;

        for (int k = 0; k <= 30; k++){
            if((L & (1<<k)) == 0)
                continue;

            memset(tways,0,sizeof(tways));
            for (int i = 0; i < n; i++){
                for (int j = 0; j < n; j++){
                    tways[j] += (ways[i] * DP[i][j][k]) % MOD;
                    tways[j] %= MOD;
                }
            }
            for (int i = 0; i < n; i++){
                ways[i] = tways[i];
            }
        }

        lli ans = 0;
        for (int i = 0; i < n; i++){
            if(final[i]){
                ans += ways[i];
                ans %= MOD;
            }
        }
        cout << ans << endl;
    }
    return 0;
}

