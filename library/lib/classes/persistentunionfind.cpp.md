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


# :warning: lib/classes/persistentunionfind.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/persistentunionfind.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-24 09:13:36+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct UnionFind{
    vector<int> par, time;
    int count;
    UnionFind(int n) : par(n, -1), time(n, MOD), count(0){}
    // [0, t]の間に併合されたかどうか
    int Find(int x, int t){return par[x] < 0 || time[x] > t ? x : Find(par[x], t);}
    int Size(int x){return par[x] < 0 ? -par[x] : Size(par[x]);}
    // 現在のcount+1のタイミングで併合された事にする
    // Unite失敗時もcountが増えるので注意
    int Unite(int x, int y){
        x = Find(x, MOD + 1);
        y = Find(y, MOD + 1);
        ++count;
        if(x == y)
            return 0;
        if(par[x] > par[y])
            swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = count;
        return count;
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/persistentunionfind.cpp"
struct UnionFind{
    vector<int> par, time;
    int count;
    UnionFind(int n) : par(n, -1), time(n, MOD), count(0){}
    // [0, t]の間に併合されたかどうか
    int Find(int x, int t){return par[x] < 0 || time[x] > t ? x : Find(par[x], t);}
    int Size(int x){return par[x] < 0 ? -par[x] : Size(par[x]);}
    // 現在のcount+1のタイミングで併合された事にする
    // Unite失敗時もcountが増えるので注意
    int Unite(int x, int y){
        x = Find(x, MOD + 1);
        y = Find(y, MOD + 1);
        ++count;
        if(x == y)
            return 0;
        if(par[x] > par[y])
            swap(x, y);
        par[x] += par[y];
        par[y] = x;
        time[y] = count;
        return count;
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

