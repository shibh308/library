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


# :heavy_check_mark: lib/classes/bitvector.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/bitvector.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-15 14:51:12+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/static_rmq_wm.test.cpp.html">verify/static_rmq_wm.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/waveletmatrix_kthmin.test.cpp.html">verify/waveletmatrix_kthmin.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/waveletmatrix_lowerbound.test.cpp.html">verify/waveletmatrix_lowerbound.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/waveletmatrix_rangefreq.test.cpp.html">verify/waveletmatrix_rangefreq.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct BitVector{
    vector<uint64_t> v;
    vector<int> r;
    BitVector(){}
    void build(){
        r.assign(v.size() + 1, 0);
        for(int i = 0; i < v.size(); ++i)
            r[i + 1] = r[i] + __builtin_popcountll(v[i]);
    }
    bool access(int x){
        return (v[x >> 6] >> (x & 63)) & 1;
    }
    // [0, x)の1の出現回数
    int rank(int x){
        return r[x >> 6] + __builtin_popcountll(v[x >> 6] & ((1uLL << (x & 63)) - 1));
    }
    int rank(int x, bool fl){
        return fl ? rank(x) : x - rank(x);
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/bitvector.cpp"
struct BitVector{
    vector<uint64_t> v;
    vector<int> r;
    BitVector(){}
    void build(){
        r.assign(v.size() + 1, 0);
        for(int i = 0; i < v.size(); ++i)
            r[i + 1] = r[i] + __builtin_popcountll(v[i]);
    }
    bool access(int x){
        return (v[x >> 6] >> (x & 63)) & 1;
    }
    // [0, x)の1の出現回数
    int rank(int x){
        return r[x >> 6] + __builtin_popcountll(v[x >> 6] & ((1uLL << (x & 63)) - 1));
    }
    int rank(int x, bool fl){
        return fl ? rank(x) : x - rank(x);
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

