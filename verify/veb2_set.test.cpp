#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#include "../lib/classes/hashmap.cpp"
#include "../lib/classes/vanemdeboastree2.cpp"

signed main(){
    int n;
    cin >> n;
    VanEmdeBoasTree<32> b;
    vector<int> type(n);
    vector<int> v(n, 0);
    for(int i = 0; i < n; ++i)
        scanf("%d%d", &type[i], &v[i]);

    int m = 0;

    for(int i = 0; i < n; ++i){
        int x = v[i];
        if(type[i] == 0){
            m += b.insert(x);
            printf("%d\n", m);
        }
        else if(type[i] == 1){
            printf("%d\n", b.lower_bound(x) == x);
        }
        else if(type[i] == 2){
            m -= b.erase(x);
        }
    }
}

