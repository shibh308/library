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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: lib/functions/twoedgeconnectedcomponents_tree.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#abc4d0f7246596dc1cbcc6b77896a2fc">lib/functions</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/functions/twoedgeconnectedcomponents_tree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-02 22:53:16+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/functions/twoedgeconnectedcomponents_tree.cpp"
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


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

