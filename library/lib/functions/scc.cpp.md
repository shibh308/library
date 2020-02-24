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


# :heavy_check_mark: lib/functions/scc.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#abc4d0f7246596dc1cbcc6b77896a2fc">lib/functions</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/functions/scc.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-30 20:08:52+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/2-sat.test.cpp.html">verify/2-sat.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
vector<int> scc(vector<vector<int>>& edges){
    int n = edges.size();
    vector<vector<int>> rev(n);

    for(int i = 0; i < n; ++i)
        for(auto& x : edges[i])
            rev[x].emplace_back(i);

    vector<i64> dfs_num(n, -1);
    vector<i64> flag(n, 0);
    int num = 0;
    function<void(int)> dfs = [&](int pos){
        flag[pos] = 1;
        for(auto& xx : edges[pos])
            if(!flag[xx]){
                dfs(xx);
        }
        dfs_num[pos] = num++;
    };

    for(int i = 0; i < n; ++i)
        if(!flag[i])
            dfs(i);

    vector<int> dfs_inv(n);
    for(int i = 0; i < n; ++i)
        dfs_inv[n - 1 - dfs_num[i]] = i;

    num = 0;

    vector<int> scc_vec(n, -1);

    function<void(int)> rdfs = [&](int pos){
        scc_vec[pos] = num;
        for(auto t : rev[pos])
            if(scc_vec[t] == -1)
                rdfs(t);
    };

    for(int i = 0; i < n; ++i)
        if(scc_vec[dfs_inv[i]] == -1){
            rdfs(dfs_inv[i]);
            ++num;
        }

    return scc_vec;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/functions/scc.cpp"
vector<int> scc(vector<vector<int>>& edges){
    int n = edges.size();
    vector<vector<int>> rev(n);

    for(int i = 0; i < n; ++i)
        for(auto& x : edges[i])
            rev[x].emplace_back(i);

    vector<i64> dfs_num(n, -1);
    vector<i64> flag(n, 0);
    int num = 0;
    function<void(int)> dfs = [&](int pos){
        flag[pos] = 1;
        for(auto& xx : edges[pos])
            if(!flag[xx]){
                dfs(xx);
        }
        dfs_num[pos] = num++;
    };

    for(int i = 0; i < n; ++i)
        if(!flag[i])
            dfs(i);

    vector<int> dfs_inv(n);
    for(int i = 0; i < n; ++i)
        dfs_inv[n - 1 - dfs_num[i]] = i;

    num = 0;

    vector<int> scc_vec(n, -1);

    function<void(int)> rdfs = [&](int pos){
        scc_vec[pos] = num;
        for(auto t : rev[pos])
            if(scc_vec[t] == -1)
                rdfs(t);
    };

    for(int i = 0; i < n; ++i)
        if(scc_vec[dfs_inv[i]] == -1){
            rdfs(dfs_inv[i]);
            ++num;
        }

    return scc_vec;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

