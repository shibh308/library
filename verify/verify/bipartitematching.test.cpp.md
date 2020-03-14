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


# :heavy_check_mark: verify/bipartitematching.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/bipartitematching.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-04 00:43:23+09:00


* see: <a href="https://judge.yosupo.jp/problem/bipartitematching">https://judge.yosupo.jp/problem/bipartitematching</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/dinic.cpp.html">lib/classes/dinic.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/dinic.cpp"


signed main() {

    int l, r, m;
    cin >> l >> r >> m;
    Dinic<int> d(l + r + 2);
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        d.add(a, l + b, 1);
    }
    for(int i = 0; i < l; ++i)
        d.add(l + r, i, 1);
    for(int i = 0; i < r; ++i)
        d.add(l + i, l + r + 1, 1);
    cout << d.solve(l + r, l + r + 1) << endl;
    for(int i = 0; i < l + r; ++i)
        for(auto& e : d.edges[i]){
            if(e.to >= l + r || i >= e.to)
                continue;
            if(e.cap == 0)
                cout << i << " " << e.to - l << endl;
        }
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/bipartitematching.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "verify/../lib/classes/dinic.cpp"
template <typename T>
struct Dinic{
    struct Edge{
        int to, rev;
        T cap;
        Edge(int to, T cap, int rev) : to(to), rev(rev), cap(cap){}
    };

    vector<vector<Edge>> edges;
    T _inf;
    vector<T> min_cost;
    vector<int> cnt;

    Dinic(int n) : edges(n), _inf(numeric_limits<T>::max()){}

    void add(int from, int to, T cap){
        edges[from].emplace_back(to, cap, static_cast<int>(edges[to].size()));
        edges[to].emplace_back(from, 0, static_cast<int>(edges[from].size()) - 1);
    }

    bool bfs(int s, int t){
        min_cost.assign(edges.size(), -1);
        queue<int> que;
        min_cost[s] = 0;
        que.emplace(s);
        while(!que.empty() && min_cost[t] == -1){
            int x = que.front();
            que.pop();
            for(auto& ed : edges[x])
                if(ed.cap > 0 && min_cost[ed.to] == -1){
                    min_cost[ed.to] = min_cost[x] + 1;
                    que.emplace(ed.to);
                }
        }
        return min_cost[t] != -1;
    }

    T dfs(int idx, int t, T flow){
        if(idx == t)
            return flow;
        T ret = 0;
        while(cnt[idx] < edges[idx].size()){
            auto& ed = edges[idx][cnt[idx]];
            if(ed.cap > 0 && min_cost[idx] < min_cost[ed.to]){
                T d = dfs(ed.to, t, min(flow, ed.cap));
                ed.cap -= d;
                edges[ed.to][ed.rev].cap += d;
                ret += d;
                flow -= d;
                if(flow == 0)
                    break;
            }
            ++cnt[idx];
        }
        return ret;
    }

    T solve(int s, int t){
        T flow = 0;
        while(bfs(s, t)){
            cnt.assign(edges.size(), 0);
            T f = 0;
            while((f = dfs(s, t, _inf)) > 0)
                flow += f;
        }
        return flow;
    }

};

#line 8 "verify/bipartitematching.test.cpp"


signed main() {

    int l, r, m;
    cin >> l >> r >> m;
    Dinic<int> d(l + r + 2);
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        d.add(a, l + b, 1);
    }
    for(int i = 0; i < l; ++i)
        d.add(l + r, i, 1);
    for(int i = 0; i < r; ++i)
        d.add(l + i, l + r + 1, 1);
    cout << d.solve(l + r, l + r + 1) << endl;
    for(int i = 0; i < l + r; ++i)
        for(auto& e : d.edges[i]){
            if(e.to >= l + r || i >= e.to)
                continue;
            if(e.cap == 0)
                cout << i << " " << e.to - l << endl;
        }
}


```
{% endraw %}

<a href="../../index.html">Back to top page</a>

