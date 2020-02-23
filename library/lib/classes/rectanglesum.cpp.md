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


# :warning: lib/classes/rectanglesum.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/rectanglesum.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-30 20:08:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct RectangleSum{//O(HW)で初期化してO(1)で長方形の和を出す(半開区間)
    vector<vector<i64>> sum;
    int h, w;
    RectangleSum(vector<vector<i64>>& v) :
        h(v.size()),
        w(v[0].size()),
        sum(v)
    {}

    // 半開区間で設定する事に注意する
    void set(int sx, int sy, int ex, int ey, i64 val){
        sum[sx][sy] += val;
        sum[sx][ey] -= val;
        sum[ex][sy] -= val;
        sum[ex][ey] += val;
    }

    void run(){

        for(int i = 0; i < h; ++i)
            for(int j = 0; j < w + 1; ++j)
                sum[i + 1][j] += sum[i][j];

        for(int i = 0; i < h + 1; ++i)
            for(int j = 0; j < w; ++j)
                sum[i][j + 1] += sum[i][j];
    }

    i64 getSum(int sx, int sy, int ex, int ey){
        return sum[ex][ey] + sum[sx][sy] - sum[sx][ey] - sum[ex][sy];
    }
};



```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/rectanglesum.cpp"
struct RectangleSum{//O(HW)で初期化してO(1)で長方形の和を出す(半開区間)
    vector<vector<i64>> sum;
    int h, w;
    RectangleSum(vector<vector<i64>>& v) :
        h(v.size()),
        w(v[0].size()),
        sum(v)
    {}

    // 半開区間で設定する事に注意する
    void set(int sx, int sy, int ex, int ey, i64 val){
        sum[sx][sy] += val;
        sum[sx][ey] -= val;
        sum[ex][sy] -= val;
        sum[ex][ey] += val;
    }

    void run(){

        for(int i = 0; i < h; ++i)
            for(int j = 0; j < w + 1; ++j)
                sum[i + 1][j] += sum[i][j];

        for(int i = 0; i < h + 1; ++i)
            for(int j = 0; j < w; ++j)
                sum[i][j + 1] += sum[i][j];
    }

    i64 getSum(int sx, int sy, int ex, int ey){
        return sum[ex][ey] + sum[sx][sy] - sum[sx][ey] - sum[ex][sy];
    }
};



```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

