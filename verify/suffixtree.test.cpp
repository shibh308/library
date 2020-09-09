#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"

#include <bits/stdc++.h>

using namespace std;


#include "../lib/classes/avl_map.cpp"
#include "../lib/classes/suffixtree.cpp"


signed main(){
    string s, t;
    cin >> s >> t;
    SuffixTree st(s);
    vector<int> res;
    res.reserve(s.size());
    stack<int> sta;
    int node = st.match(t).first;
    sta.push(node);
    while(!sta.empty()){
        int x = sta.top();
        sta.pop();
        if(x == st.n)
            continue;
        if(x < st.n)
            res.emplace_back(x);
        for(auto p : st.avl.list(st.nodes[x].child)){
            sta.push(p.second);
        }
    }
    sort(res.begin(), res.end());
    for(auto x : res)
        printf("%d\n", x);
}


