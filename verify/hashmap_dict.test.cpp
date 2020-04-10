#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

#include "../lib/classes/hashmap.cpp"


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

    HashMap<int, int> h((1 << 30) - 1, (1 << 30) - 2);

    for(int i = 0; i < n; ++i){
        if(type[i] == 0){
            h.add(v[i], 1);
        }
        else{
            printf(h.find(v[i]).second ? "yes\n" : "no\n");
        }
    }
}


