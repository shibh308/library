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


# :heavy_check_mark: lib/functions/scc_dag.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#abc4d0f7246596dc1cbcc6b77896a2fc">lib/functions</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/functions/scc_dag.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-24 19:52:28+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/scc_dag.test.cpp.html">verify/scc_dag.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Result{
    int dag_size;
    vector<vector<int>> dag_graph;
    // 元のグラフでi番目の頂点が何番目の強連結成分に含まれるか
    vector<int> elements;
    // i番目の強連結成分に含まれる頂点のリスト
    vector<vector<int>> tps_list;
    // トポソしてi番目にくる頂点のindex
    vector<int> tps_order;
    // DAGのi番目の頂点をトポソした時の番号
    vector<int> tps_index;
};

Result scc_dag(vector<vector<int>>& edges){
    int n = edges.size();
    vector<int> scc_vec = scc(edges);
    int m = *max_element(scc_vec.begin(), scc_vec.end()) + 1;
    vector<vector<int>> dag_graph(m);

    queue<int> tps_que;
    vector<int> in_count(m, 0);
    vector<int> tps(m, -1);
    vector<int> tps_idx(m);
    for(int i = 0; i < n; ++i){
        for(auto j : edges[i]){
            if(scc_vec[i] == scc_vec[j])
                continue;
            dag_graph[scc_vec[i]].push_back(scc_vec[j]);
            ++in_count[scc_vec[j]];
        }
    }
    for(int i = 0; i < m; ++i)
        if(in_count[i] == 0)
            tps_que.push(i);
    int cnt = 0;
    while(!tps_que.empty()){
        int x = tps_que.front();
        tps_idx[x] = cnt;
        tps[cnt++] = x;
        tps_que.pop();
        for(auto y : dag_graph[x])
            if(--in_count[y] == 0)
                tps_que.push(y);
    }
    assert(cnt == m);

    vector<vector<int>> tps_list(m);
    for(int i = 0; i < n; ++i)
        tps_list[scc_vec[i]].push_back(i);

    Result res;
    res.dag_size = m;
    res.elements = move(scc_vec);
    res.tps_index = move(tps_idx);
    res.tps_order = move(tps);
    res.tps_list = move(tps_list);
    res.dag_graph = move(dag_graph);
    return res;
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/functions/scc_dag.cpp"
struct Result{
    int dag_size;
    vector<vector<int>> dag_graph;
    // 元のグラフでi番目の頂点が何番目の強連結成分に含まれるか
    vector<int> elements;
    // i番目の強連結成分に含まれる頂点のリスト
    vector<vector<int>> tps_list;
    // トポソしてi番目にくる頂点のindex
    vector<int> tps_order;
    // DAGのi番目の頂点をトポソした時の番号
    vector<int> tps_index;
};

Result scc_dag(vector<vector<int>>& edges){
    int n = edges.size();
    vector<int> scc_vec = scc(edges);
    int m = *max_element(scc_vec.begin(), scc_vec.end()) + 1;
    vector<vector<int>> dag_graph(m);

    queue<int> tps_que;
    vector<int> in_count(m, 0);
    vector<int> tps(m, -1);
    vector<int> tps_idx(m);
    for(int i = 0; i < n; ++i){
        for(auto j : edges[i]){
            if(scc_vec[i] == scc_vec[j])
                continue;
            dag_graph[scc_vec[i]].push_back(scc_vec[j]);
            ++in_count[scc_vec[j]];
        }
    }
    for(int i = 0; i < m; ++i)
        if(in_count[i] == 0)
            tps_que.push(i);
    int cnt = 0;
    while(!tps_que.empty()){
        int x = tps_que.front();
        tps_idx[x] = cnt;
        tps[cnt++] = x;
        tps_que.pop();
        for(auto y : dag_graph[x])
            if(--in_count[y] == 0)
                tps_que.push(y);
    }
    assert(cnt == m);

    vector<vector<int>> tps_list(m);
    for(int i = 0; i < n; ++i)
        tps_list[scc_vec[i]].push_back(i);

    Result res;
    res.dag_size = m;
    res.elements = move(scc_vec);
    res.tps_index = move(tps_idx);
    res.tps_order = move(tps);
    res.tps_list = move(tps_list);
    res.dag_graph = move(dag_graph);
    return res;
}


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

