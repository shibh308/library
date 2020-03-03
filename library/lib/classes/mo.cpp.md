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


# :heavy_check_mark: lib/classes/mo.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/mo.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 14:01:09+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/mo.test.cpp.html">verify/mo.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct Mo{
    int l, r;
    function<void(int)> left_add, left_erase, right_add, right_erase;
    Mo(function<void(int)> left_add, function<void(int)> left_erase,
       function<void(int)> right_add, function<void(int)> right_erase,
       int sl = 0, int sr = 0) :
       l(sl), r(sr), left_add(left_add), left_erase(left_erase), right_add(right_add), right_erase(right_erase){}
    void move(int next_l, int next_r){
        for(int i = l; i < next_l; ++i)
            left_erase(i);
        for(int i = l - 1; i >= next_l; --i)
            left_add(i);
        for(int i = r; i < next_r; ++i)
            right_add(i);
        for(int i = r - 1; i >= next_r; --i)
            right_erase(i);
        l = next_l, r = next_r;
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/mo.cpp"
struct Mo{
    int l, r;
    function<void(int)> left_add, left_erase, right_add, right_erase;
    Mo(function<void(int)> left_add, function<void(int)> left_erase,
       function<void(int)> right_add, function<void(int)> right_erase,
       int sl = 0, int sr = 0) :
       l(sl), r(sr), left_add(left_add), left_erase(left_erase), right_add(right_add), right_erase(right_erase){}
    void move(int next_l, int next_r){
        for(int i = l; i < next_l; ++i)
            left_erase(i);
        for(int i = l - 1; i >= next_l; --i)
            left_add(i);
        for(int i = r; i < next_r; ++i)
            right_add(i);
        for(int i = r - 1; i >= next_r; --i)
            right_erase(i);
        l = next_l, r = next_r;
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

