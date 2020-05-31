#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
#include "bits/stdc++.h"

using namespace std;


#include "./library/lib/classes/sparsetable.cpp"
#include "./library/lib/classes/lineartimesparsetable.cpp"
#include "./library/lib/classes/substrmatching.cpp"


signed main(){
    string s, t;
    cin >> s;
    SubstrMatching p(s);
    cin >> t;
    auto q = p.find(t);
    vector<int> v;
    for(int i = q.first; i < q.second; ++i){
        v.emplace_back(p.sa[i]);
    }
    sort(v.begin(), v.end());
    for(auto x : v)
        printf("%d\n", x);
}


