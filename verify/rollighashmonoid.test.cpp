#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
#include <bits/stdc++.h>

using namespace std;

#include "../lib/classes/rollinghashmonoid.cpp"

signed main(){
    string s, t;
    cin >> s >> t;
    auto sh = Hash::make(s);
    auto th = Hash::make(t);
    for(int i = 0; i < int(s.size()) - int(t.size()) + 1; ++i){
        if(sh[i + t.size()].sub(sh[i]) == th.back()){
            cout << i << endl;
        }
    }
}

