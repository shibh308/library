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


# :heavy_check_mark: lib/classes/sparsetable.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/sparsetable.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-31 19:48:42+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/multi_str_matching.test.cpp.html">verify/multi_str_matching.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/string_seatch.test.cpp.html">verify/string_seatch.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct SparseTable{
    vector<int> len;
    vector<vector<T>> v;
    function<T(T, T)> f;
    SparseTable(){}
    SparseTable(vector<T>& a, function<T(T, T)> f) : len(a.size() + 1, 0), v(1, a), f(f){
        int n = a.size();
        for(int j = 0; (1 << j) < n; ++j){
            v.emplace_back(n);
            for(int i = 0; i < n; ++i)
                v[j + 1][i] = (i + (1 << j) < n ? f(v[j][i], v[j][i + (1 << j)]) : v[j][i]);
        }
        for(int i = 2; i <= n; ++i){
            len[i] = len[i >> 1] + 1;
        }
    }
    T get(int l, int r){
        int siz = r - l;
        return f(v[len[siz]][l], v[len[siz]][r - (1 << len[siz])]);
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/sparsetable.cpp"
template <typename T>
struct SparseTable{
    vector<int> len;
    vector<vector<T>> v;
    function<T(T, T)> f;
    SparseTable(){}
    SparseTable(vector<T>& a, function<T(T, T)> f) : len(a.size() + 1, 0), v(1, a), f(f){
        int n = a.size();
        for(int j = 0; (1 << j) < n; ++j){
            v.emplace_back(n);
            for(int i = 0; i < n; ++i)
                v[j + 1][i] = (i + (1 << j) < n ? f(v[j][i], v[j][i + (1 << j)]) : v[j][i]);
        }
        for(int i = 2; i <= n; ++i){
            len[i] = len[i >> 1] + 1;
        }
    }
    T get(int l, int r){
        int siz = r - l;
        return f(v[len[siz]][l], v[len[siz]][r - (1 << len[siz])]);
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

