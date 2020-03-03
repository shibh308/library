#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;


#include "../lib/classes/mo.cpp"

signed main(){
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(k), b(k);
    for(int i = 0; i < k; ++i){
        cin >> a[i] >> b[i];
        --a[i], --b[i];
    }
    constexpr int packet = 512;
    constexpr int size = (100000 + packet - 1) / packet;

    vector<vector<pair<int,int>>> queries(size);

    vector<int> type(q), s(q), t(q), x(q);
    for(int i = 0; i < q; ++i){
        cin >> type[i] >> s[i] >> t[i] >> x[i];
        --s[i], --x[i];
        queries[s[i] / packet].emplace_back(t[i], i);
    }
    for(int i = 0; i < size; ++i)
        sort(queries[i].begin(), queries[i].end());


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

    vector<int> ans(q, -1);

    for(int i = 0; i < size; ++i){
        mo.move(i * packet, i * packet);
        for(auto& query : queries[i]){
            int idx = query.second;
            int next_l = s[idx];
            int next_r = t[idx];
            int ty = type[idx];
            int val = x[idx];
            mo.move(next_l, next_r);

            if(ty == 1){
                ans[idx] = data[val];
            }
            else{
                ans[idx] = idxes[val];
            }
        }
    }

    for(int i = 0; i < q; ++i)
        cout << ans[i] + 1 << endl;

    return 0;
}
