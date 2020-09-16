#define PROBLEM "https://judge.yosupo.jp/problem/runenumerate"
#include <bits/stdc++.h>

using namespace std;


#include "../lib/classes/stringutils.cpp"
#include "../lib/functions/run.cpp"


signed main(){
    string s;
    cin >> s;
    set<tuple<int,int,int>> v = getRunInfo(s).run;
    cout << v.size() << endl;
    for(auto x : v){
        int t, l, r;
        tie(t, l, r) = x;
        cout << t << " " << l << " " << r << endl;
    }
}
