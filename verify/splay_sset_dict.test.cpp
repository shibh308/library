#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C"
#include "bits/stdc++.h"

using namespace std;

#include "../lib/classes/splaytree_sset.cpp"

signed main(){
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> type(n);
    vector<int> v(n, 0);
    string l = "0ACGT";
    for(int i = 0; i < n; ++i){
        string s, t;
        cin >> s >> t;
        type[i] = (s == "find");
        int k = 1;
        for(int j = 0; j < t.size(); ++j, k *= 5)
            v[i] += l.find(t[j]) * k;
    }

    SplayTree<int> sp;
    auto root = sp.nil;

    for(int i = 0; i < n; ++i){
        if(type[i] == 0){
            root = sp.insert(root, v[i]).first;
        }
        else{
            bool fl;
            SplayTree<int>::NodePtr ptr;
            tie(ptr, fl) = sp.lower_bound(root, v[i]);
            if(fl)
                root = ptr;
            printf(fl && root->val == v[i] ? "yes\n" : "no\n");
        }
    }
}



