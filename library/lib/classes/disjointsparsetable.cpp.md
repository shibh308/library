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


# :heavy_check_mark: lib/classes/disjointsparsetable.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/disjointsparsetable.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-30 20:08:52+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/static_rmq.test.cpp.html">verify/static_rmq.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct DisjointSparseTable{
    function<T(T, T)> f;
    vector<vector<T>> v;

    DisjointSparseTable(vector<T>& inp, function<T(T, T)> f) : f(f){
        int n = inp.size();
        int b;
        for(b = 0; (1 << b) <= inp.size(); ++b);
        v.assign(b, vector<T>(n));
        for(int i = 0; i < n; ++i)
            v[0][i] = inp[i];
        for(int i = 1; i < b; ++i){
            int siz = 1 << i;
            for(int j = 0; j < n; j += siz << 1){
                int t = min(j + siz, n);
                v[i][t - 1] = inp[t - 1];
                for(int k = t - 2; k >= j; --k)
                    v[i][k] = f(inp[k], v[i][k + 1]);
                if(t >= n)
                    break;
                v[i][t] = inp[t];
                int r = min(t + siz, n);
                for(int k = t + 1; k < r; ++k)
                    v[i][k] = f(v[i][k - 1], inp[k]);
            }
        }
    }

    T get(int l, int r){
        if(l >= --r)
            return v[0][l];
        int p = 31 - __builtin_clz(l ^ r);
        return f(v[p][l], v[p][r]);
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/disjointsparsetable.cpp"
template <typename T>
struct DisjointSparseTable{
    function<T(T, T)> f;
    vector<vector<T>> v;

    DisjointSparseTable(vector<T>& inp, function<T(T, T)> f) : f(f){
        int n = inp.size();
        int b;
        for(b = 0; (1 << b) <= inp.size(); ++b);
        v.assign(b, vector<T>(n));
        for(int i = 0; i < n; ++i)
            v[0][i] = inp[i];
        for(int i = 1; i < b; ++i){
            int siz = 1 << i;
            for(int j = 0; j < n; j += siz << 1){
                int t = min(j + siz, n);
                v[i][t - 1] = inp[t - 1];
                for(int k = t - 2; k >= j; --k)
                    v[i][k] = f(inp[k], v[i][k + 1]);
                if(t >= n)
                    break;
                v[i][t] = inp[t];
                int r = min(t + siz, n);
                for(int k = t + 1; k < r; ++k)
                    v[i][k] = f(v[i][k - 1], inp[k]);
            }
        }
    }

    T get(int l, int r){
        if(l >= --r)
            return v[0][l];
        int p = 31 - __builtin_clz(l ^ r);
        return f(v[p][l], v[p][r]);
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

