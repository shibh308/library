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


# :warning: lib/functions/simple_graph.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#abc4d0f7246596dc1cbcc6b77896a2fc">lib/functions</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/functions/simple_graph.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-04 14:48:14+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T = pair<int,int>>
vector<vector<int>> simple_graph(vector<vector<T>>& edges, function<int(T)> f = [](auto x){return x.first;}){
    vector<vector<int>> simple_edges(edges.size());
    for(int i = 0; i < edges.size(); ++i)
        for(auto& x : edges[i])
            simple_edges[i].push_back(f(x));
    return simple_edges;
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/functions/simple_graph.cpp"
template <typename T = pair<int,int>>
vector<vector<int>> simple_graph(vector<vector<T>>& edges, function<int(T)> f = [](auto x){return x.first;}){
    vector<vector<int>> simple_edges(edges.size());
    for(int i = 0; i < edges.size(); ++i)
        for(auto& x : edges[i])
            simple_edges[i].push_back(f(x));
    return simple_edges;
}


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

