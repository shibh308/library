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


# :warning: lib/classes/compression.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/compression.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-30 20:08:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<typename T>
struct Compression{
    vector<T> compvec;
    Compression(vector<T>& inp){//圧縮する
        compvec = inp;
        sort(compvec.begin(), compvec.end());
        compvec.erase(unique(compvec.begin(), compvec.end()), compvec.end());
    }
    int Index(T val){//圧縮を元に対応するインデックスを返す
        auto it = lower_bound(compvec.begin(), compvec.end(), val);
        return distance(compvec.begin(), it);
    }
    vector<T>& operator*(){
        return compvec;
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/compression.cpp"
template<typename T>
struct Compression{
    vector<T> compvec;
    Compression(vector<T>& inp){//圧縮する
        compvec = inp;
        sort(compvec.begin(), compvec.end());
        compvec.erase(unique(compvec.begin(), compvec.end()), compvec.end());
    }
    int Index(T val){//圧縮を元に対応するインデックスを返す
        auto it = lower_bound(compvec.begin(), compvec.end(), val);
        return distance(compvec.begin(), it);
    }
    vector<T>& operator*(){
        return compvec;
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

