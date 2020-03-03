#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 1e9 + 7;
const i64 INF = i64(1e18) + 7;

template <typename T>
bool chmin(T& x, T y){
    if(x > y){
        x = y;
        return true;
    }
    return false;
}

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#include "../lib/classes/mo.cpp"
#include "../lib/functions/mo_query.cpp"


signed main(){
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(k), b(k);
    for(int i = 0; i < k; ++i){
        cin >> a[i] >> b[i];
        --a[i], --b[i];
    }

    vector<pair<int,int>> queries;
    vector<int> type(q), s(q), t(q), x(q);
    for(int i = 0; i < q; ++i){
        cin >> type[i] >> s[i] >> t[i] >> x[i];
        --s[i], --x[i];
        queries.emplace_back(s[i], t[i]);
    }

    vector<int> data(n), idxes(n);
    iota(data.begin(), data.end(), 0);
    iota(idxes.begin(), idxes.end(), 0);
    auto right_f = [&](int idx){
        if(idx >= k)
            return;
        swap(data[a[idx]], data[b[idx]]);
        idxes[data[a[idx]]] = a[idx];
        idxes[data[b[idx]]] = b[idx];
    };
    auto left_f = [&](int idx){
        if(idx >= k)
            return;
        swap(data[idxes[a[idx]]], data[idxes[b[idx]]]);
        int idx_1 = idxes[a[idx]];
        int data_idx_1 = data[idx_1];
        int idx_2 = idxes[b[idx]];
        int data_idx_2 = data[idx_2];
        idxes[data_idx_1] = idx_1;
        idxes[data_idx_2] = idx_2;
    };
    Mo mo(left_f, left_f, right_f, right_f);
    auto ans = mo_query<int>(mo, queries, [&](int idx){return type[idx] == 1 ? data[x[idx]] : idxes[x[idx]];});

    for(int i = 0; i < q; ++i)
        cout << ans[i] + 1 << endl;

    return 0;
}