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


# :heavy_check_mark: lib/functions/mo_query.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#abc4d0f7246596dc1cbcc6b77896a2fc">lib/functions</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/functions/mo_query.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 20:05:33+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/mo_query.test.cpp.html">verify/mo_query.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename ResultType>
vector<ResultType> mo_query(Mo& mo, vector<pair<int,int>>& queries, function<ResultType(int)> get_func, int packet=512){
    int q = queries.size();
    vector<tuple<int,int,int>> sort_queries;
    for(int i = 0; i < q; ++i)
        sort_queries.emplace_back(queries[i].first / packet, queries[i].second, i);
    sort(sort_queries.begin(), sort_queries.end());
    vector<ResultType> ans(q);
    for(auto& query : sort_queries){
        int idx = get<2>(query);
        mo.move(queries[idx].first, queries[idx].second);
        ans[idx] = get_func(idx);
    }
    return ans;
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/functions/mo_query.cpp"
template <typename ResultType>
vector<ResultType> mo_query(Mo& mo, vector<pair<int,int>>& queries, function<ResultType(int)> get_func, int packet=512){
    int q = queries.size();
    vector<tuple<int,int,int>> sort_queries;
    for(int i = 0; i < q; ++i)
        sort_queries.emplace_back(queries[i].first / packet, queries[i].second, i);
    sort(sort_queries.begin(), sort_queries.end());
    vector<ResultType> ans(q);
    for(auto& query : sort_queries){
        int idx = get<2>(query);
        mo.move(queries[idx].first, queries[idx].second);
        ans[idx] = get_func(idx);
    }
    return ans;
}


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

