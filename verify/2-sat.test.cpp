#define PROBLEM "https://judge.yosupo.jp/problem/two_sat"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/functions/scc.cpp"


signed main() {
    string p, cnf;
    int n, m;
    cin >> p >> cnf >> n >> m;
    /*
     x |  y  :  !x =>  y
     x |  y  :  !y =>  x
    !x |  y  :   x =>  y
    !x |  y  :  !y => !x
     x | !y  :   y =>  x
     x | !y  :  !x => !y
    !x | !y  :   x => !y
    !x | !y  :   y => !x
     */

    vector<vector<int>> edges(2 * n);

    for(int i = 0; i < m; ++i){
        int a, b, tmp;
        cin >> a >> b >> tmp;
        int x = abs(a) - 1;
        int y = abs(b) - 1;
        // if x_plus: true
        bool x_plus = (a >= 0);
        bool y_plus = (b >= 0);

        edges[x + (x_plus ? 0 : n)].emplace_back(y + (y_plus ? n : 0));
        edges[y + (y_plus ? 0 : n)].emplace_back(x + (x_plus ? n : 0));
    }
    auto ret = scc(edges);

    for(int i = 0; i < n; ++i){
        if(ret[i] == ret[i + n]){
            cout << "s UNSATISFIABLE" << endl;

            return 0;
        }
    }

    cout << "s SATISFIABLE" << endl;
    cout << "v";

    for(int i = 0; i < n; ++i){
        cout << " " << (ret[i] < ret[i + n] ? 1 : -1) * (i + 1);
    }
    cout << " " << 0 << endl;

}
