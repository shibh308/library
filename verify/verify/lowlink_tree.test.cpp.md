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


# :heavy_check_mark: verify/lowlink_tree.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/verify/lowlink_tree.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 11:11:00+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/lowlink.cpp.html">lib/classes/lowlink.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/functions/twoedgeconnectedcomponents_tree.cpp.html">lib/functions/twoedgeconnectedcomponents_tree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#include "../lib/classes/lowlink.cpp"
#include "../lib/functions/twoedgeconnectedcomponents_tree.cpp"

signed main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> u(m), v(m);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    vector<vector<int>> edges(n);
    for(int i = 0; i < m; ++i){
        cin >> u[i] >> v[i];
        --u[i], --v[i];
        edges[u[i]].push_back(v[i]);
        edges[v[i]].push_back(u[i]);
    }
    auto res = two_edge_connected_components_tree(edges);
    int k = res.group_cnt;
    vector<int> values(k, 0);
    for(int i = 0; i < n; ++i)
        values[res.group[i]] += a[i];

    auto& par = res.par;
    auto& childs = res.childs;
    vector<int> dp(k, 0);
    vector<unordered_map<int, int>> dp2(k);
    function<void(int)> f = [&](int x){
        int val = 0;
        for(auto y : childs[x]){
            f(y);
            chmax(val, dp[y]);
        }
        dp[x] = values[x] + val;
    };
    f(0);

    int ans = 0;
    function<void(int)> g = [&](int x){
        multiset<int> v{0, 0};
        for(auto y : childs[x]){
            v.insert(dp[y]);
            v.erase(v.begin());
            g(y);
        }
        chmax(ans, values[x] + *prev(v.end()) + *prev(v.end(), 2));
    };
    g(0);
    cout << ans << endl;

    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/lowlink_tree.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415"
#include <bits/stdc++.h>

using namespace std;

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#line 1 "verify/../lib/classes/lowlink.cpp"
struct LowLink{
    vector<vector<int>>& edges;
    // 関節点
    vector<int> art;
    vector<pair<int,int>> bridge;

    vector<int> used, ord, low;
    int k;

    void dfs(int idx, int par){
        ord[idx] = k++;
        low[idx] = ord[idx];
        bool is_art = false;
        int cnt = 0;
        for(auto& to : edges[idx]){
            if(ord[to] == -1){
                ++cnt;
                dfs(to, idx);
                low[idx] = min(low[idx], low[to]);
                is_art |= par != -1 && low[to] >= ord[idx];
                if(ord[idx] < low[to])
                    bridge.emplace_back(idx, to);
            }else if(to != par)
                low[idx] = min(low[idx], ord[to]);
        }
        is_art |= (par == -1 && cnt > 1);
        if(is_art)
            art.emplace_back(idx);
    }

    LowLink(vector<vector<int>>& edges) :
        edges(edges),
        ord(edges.size(), -1),
        low(edges.size(), 0),
        k(0)
    {
        for(int i = 0; i < edges.size(); ++i)
            if(ord[i] == -1)
                dfs(i, -1);
        for(auto& b : bridge)
            b = make_pair(min(b.first, b.second), max(b.first, b.second));
        sort(art.begin(), art.end());
        sort(bridge.begin(), bridge.end());
    }
};

#line 1 "verify/../lib/functions/twoedgeconnectedcomponents_tree.cpp"
struct Result{
    int group_cnt;
    vector<int> group;
    vector<vector<int>> group_elm_list;
    // 同じ二重辺連結成分の辺をグループごとに列挙する, 片方向のみ(辺数倍化しない)
    vector<vector<pair<int,int>>> same_group_edges;
    // 橋, 片方向のみ
    vector<pair<int,int>> bridges;
    // 関節点
    vector<int> arts;
    vector<vector<int>> tree_graph;
    vector<int> par;
    vector<vector<int>> childs;
};

Result two_edge_connected_components_tree(vector<vector<int>>& edges){
    int n = edges.size();
    LowLink ll(edges);
    vector<vector<int>> not_bridge_graph(n);
    for(int i = 0; i < n; ++i)
        for(auto j : edges[i]){
            pair<int,int> min_max = minmax(i, j);
            auto iter = lower_bound(ll.bridge.begin(), ll.bridge.end(), min_max);
            if(iter == ll.bridge.end() || *iter != min_max)
                not_bridge_graph[i].push_back(j);
        }

    vector<int> group(n, -1);
    function<void(int)> group_dfs = [&](int x){
        for(auto y : not_bridge_graph[x])
            if(group[y] == -1){
                group[y] = group[x];
                group_dfs(y);
            }
    };
    int group_cnt = 0;
    for(int i = 0; i < n; ++i)
        if(group[i] == -1){
            group[i] = group_cnt++;
            group_dfs(i);
        }
    vector<vector<int>> group_elm_list(group_cnt);
    for(int i = 0; i < n; ++i)
        group_elm_list[group[i]].push_back(i);

    vector<vector<pair<int,int>>> same_group_edges(group_cnt);
    vector<vector<int>> tree_edges(group_cnt);
    vector<int> par(group_cnt, -1);
    vector<vector<int>> childs(group_cnt);

    for(int i = 0; i < n; ++i)
        for(auto j : edges[i])
            if(group[i] == group[j] && i < j)
                same_group_edges[group[i]].emplace_back(i, j);

    for(auto& p : ll.bridge){
        tree_edges[group[p.first]].push_back(group[p.second]);
        tree_edges[group[p.second]].push_back(group[p.first]);
    }
    vector<bool> flag(n, false);
    function<void(int)> tree_dfs = [&](int x){
        for(auto y : tree_edges[x])
            if(!flag[y]){
                flag[y] = true;
                par[y] = x;
                childs[x].push_back(y);
                tree_dfs(y);
            }
    };
    flag[0] = true;
    tree_dfs(0);

    Result res;
    res.group_cnt = group_cnt;
    res.group_elm_list = move(group_elm_list);
    res.same_group_edges = move(same_group_edges);
    res.bridges = move(ll.bridge);
    res.arts = move(ll.art);
    res.group = move(group);
    res.tree_graph = move(tree_edges);
    res.par = move(par);
    res.childs = move(childs);
    return res;
}

#line 18 "verify/lowlink_tree.test.cpp"

signed main(){
    int n, m;
    cin >> n >> m;
    vector<int> a(n);
    vector<int> u(m), v(m);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    vector<vector<int>> edges(n);
    for(int i = 0; i < m; ++i){
        cin >> u[i] >> v[i];
        --u[i], --v[i];
        edges[u[i]].push_back(v[i]);
        edges[v[i]].push_back(u[i]);
    }
    auto res = two_edge_connected_components_tree(edges);
    int k = res.group_cnt;
    vector<int> values(k, 0);
    for(int i = 0; i < n; ++i)
        values[res.group[i]] += a[i];

    auto& par = res.par;
    auto& childs = res.childs;
    vector<int> dp(k, 0);
    vector<unordered_map<int, int>> dp2(k);
    function<void(int)> f = [&](int x){
        int val = 0;
        for(auto y : childs[x]){
            f(y);
            chmax(val, dp[y]);
        }
        dp[x] = values[x] + val;
    };
    f(0);

    int ans = 0;
    function<void(int)> g = [&](int x){
        multiset<int> v{0, 0};
        for(auto y : childs[x]){
            v.insert(dp[y]);
            v.erase(v.begin());
            g(y);
        }
        chmax(ans, values[x] + *prev(v.end()) + *prev(v.end(), 2));
    };
    g(0);
    cout << ans << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

