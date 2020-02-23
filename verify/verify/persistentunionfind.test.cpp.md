---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: verify/persistentunionfind.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/verify/persistentunionfind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-24 09:29:30+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/persistentunionfind.cpp.html">lib/classes/persistentunionfind.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

const i64 MOD = 1e9 + 7;

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


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/persistentunionfind.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

const i64 MOD = 1e9 + 7;

#line 1 "verify/../lib/classes/persistentunionfind.cpp"
struct UnionFind{
    vector<int> par, time;
    int count;
    UnionFind(int n) : par(n, -1), time(n, MOD), count(0){}
    // [0, t]の間に併合されたかどうか
    int Find(int x, int t){return par[x] < 0 || time[x] > t ? x : Find(par[x], t);}
    int Size(int x){return par[x] < 0 ? -par[x] : Size(par[x]);}
    // 現在のcount+1のタイミングで併合された事にする
    // Unite失敗時もcountが増えるので注意
    int Unite(int x, int y){
        x = Find(x, MOD + 1);
        y = Find(y, MOD + 1);
        ++count;
        if(x == y)
            return 0;
        if(par[x] > par[y])
            swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = count;
        return count;
    }
};

#line 10 "verify/persistentunionfind.test.cpp"


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


```
{% endraw %}

<a href="../../index.html">Back to top page</a>

