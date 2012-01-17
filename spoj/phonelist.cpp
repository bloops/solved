#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <cstdio>
using namespace std;
#define foreach(it, c) for(typeof(c.begin()) it = c.begin(); it != c.end(); it++)

struct node {
    string value;
    map<char,int> children;
    bool final;
    node() : value(""), final(false) {}
};

vector<node> trie;

bool insert(int i, string s){
    if(s.empty())
        return false;
    if(trie[i].children.count(s[0])){
        int k = 0;
        int j = trie[i].children[s[0]];
        string t = trie[j].value;
        while(k < min(s.size(),t.size()) and s[k] == t[k]) 
            k++;
        if(k == t.size()){
            if(k == s.size())
                trie[j].final = true;
            bool ret = insert(trie[i].children[s[0]], s.substr(k));
            return trie[j].final or ret;
        }
        // now k < t.size()
        // we make this node have value t[0..(k-1)]
        // and make a new node with t[k..] and make it the only child of j
        node n = trie[j];
        trie[j].value = t.substr(0,k), trie[j].final = false;
        n.value = t.substr(k);
        trie[j].children.clear();
        trie[j].children[t[k]] = trie.size();
        trie.push_back(n);
        return insert(j,s.substr(k));
    }
    else {
        // make new node
        node n;
        n.value = s, n.final = true;
        trie[i].children[s[0]] = trie.size();
        trie.push_back(n);
        return false;
    }
}


void printTrie(int i = 0, string indent = ""){
    //printf("%s%s(%d)\n",indent.c_str(), trie[i].value.c_str(), trie[i].final);
    cout << indent << trie[i].value << endl;
    indent += "--";
    foreach(it,trie[i].children){
        printTrie(it->second, indent);
    }
}

int main()
{
    ios::sync_with_stdio(false);
    int T;
    cin >> T;
    while(T--){
        trie.clear();
        node root;
        trie.push_back(root);
        int n;
        cin >> n;
        vector<string> a(n);
        bool invalid = false;
        string s;
        for (int i = 0; i < n; i++){
            cin >> a[i];
        }
        sort(a.begin(),a.end());
        for (int i = 0; i < n; i++){
            invalid |= insert(0,a[i]);
        }
        //printTrie();
        string ans = invalid ? "NO" : "YES";
        printf("%s\n",ans.c_str());
    }

    
    return 0;
}

