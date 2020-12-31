#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_1_A"

#include <bits/stdc++.h>
using namespace std;

#include "../lib/classes/persistentskewbinarylist.cpp"

signed main(){
    int q;
    cin >> q;
    vector<const PersistentSkewBinaryList<int>*> v;
    v.push_back(new PersistentSkewBinaryList<int>());
    for(int i = 0; i < q; ++i){
        int ty, val;
        cin >> ty;
        if(ty == 0){
            cin >> val;
            auto new_res = v.back()->push_front(val);
            v.emplace_back(new_res);
        }
        else if(ty == 1){
            cin >> val;
            cout << v.back()->access(v.back()->siz - val - 1) << endl;
        }
        else{
            v.pop_back();
        }
    }
}

