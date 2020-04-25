#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"
#include "bits/stdc++.h"


using namespace std;

using i64 = long long;


#include "./lib/classes/memorypool.cpp"
#include "./lib/classes/dynamicbitvector.cpp"
#include "./lib/classes/dynamicwaveletmatrix.cpp"


signed main(){

    int n, q;
    cin >> n >> q;

    vector<uint64_t> a(n, (1uLL << 31) - 1);
    WaveletMatrix<uint64_t, 33> wm(a);
    for(int i = 0; i < q; ++i){
        int t, x, y;
        scanf("%d%d%d", &t, &x, &y);
        if(t == 0){
            wm.erase(x);
            wm.insert(x, y);
        }
        else{
            printf("%lu\n", wm.kth_min(x, ++y, 0));
        }
    }
}

