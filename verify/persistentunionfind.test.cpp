#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/persistentunionfind.cpp"


template <typename T>
bool chmin(T& x, T y){
    if(x > y){
        x = y;
        return true;
    }
    return false;
}


signed main(){
    int n, m, k, q;
    cin >> n >> m >> k >> q;
    vector<vector<pair<int,int>>> edges(n);
    vector<int> a(m), b(m), l(m);
    for(int i = 0; i < m; ++i){
        cin >> a[i] >> b[i] >> l[i];
        --a[i], --b[i];
        edges[a[i]].emplace_back(b[i], l[i]);
        edges[b[i]].emplace_back(a[i], l[i]);
    }
    vector<int> v(k);
    unordered_set<int> vs;
    for(int i = 0; i < k; ++i){
        cin >> v[i];
        --v[i];
        vs.insert(v[i]);
    }
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> que;
    vector<int> range(n, MOD);
    for(int i = 0; i < k; ++i){
        range[v[i]] = 0;
        que.emplace(0, v[i]);
    }
    while(!que.empty()){
        int dist, x;
        tie(dist, x) = que.top();
        que.pop();
        if(range[x] != dist)
            continue;
        for(auto& ed : edges[x]){
            if(chmin(range[ed.first], dist + ed.second))
                que.emplace(range[ed.first], ed.first);
        }
    }
    vector<pair<int,int>> w;
    for(int i = 0; i < m; ++i){
        int dist_a = range[a[i]];
        int dist_b = range[b[i]];
        w.emplace_back(min(dist_a, dist_b), i);
    }
    sort(w.begin(), w.end(), greater<>());

    UnionFind uf(n);

    vector<int> query_time(m);
    for(int i = 0; i < m; ++i)
        query_time[i] = w[i].first;

    for(int i = 0; i < m; ++i)
        uf.Unite(a[w[i].second], b[w[i].second]);

    for(int i = 0; i < q; ++i){
        int s, t;
        cin >> s >> t;
        --s, --t;
        // [0, t]の間に併合されたかどうか
        // 現在のcount+1のタイミングで併合された事にする
        int ok = MOD, ng = 0;
        while(abs(ng - ok) > 1){
            int mid = (ok + ng) / 2;
            (uf.Find(s, mid) == uf.Find(t, mid) ? ok : ng) = mid;
        }
        if(ok >= m){
            cout << 0 << endl;
            continue;
        }
        cout << query_time[ng] << endl;
    }


}

