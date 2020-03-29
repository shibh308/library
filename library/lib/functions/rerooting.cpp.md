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


# :warning: lib/functions/rerooting.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#abc4d0f7246596dc1cbcc6b77896a2fc">lib/functions</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/functions/rerooting.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-30 02:03:55+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
// T f(T, T): 子の累積に使うもの 直径ならf(x, y): max(x, y)
// T g(T, int): 子の累積を元に適用する際に使うもの 直径ならg(x, idx): x + 1
vector<T> rerooting(vector<vector<int>>& edges, vector<T> v, function<T(T, T)> f, function<T(T, int)> g, T op){
    int n = edges.size();
    vector<int> visit(n, 0);
    vector<T> dp1(v), dp2(n);
    vector<vector<int>> childs(n);
    vector<vector<T>> child_val(n), child_l(n), child_r(n);
    function<void(int)> f1 = [&](int x){
        visit[x] = true;
        T res = op;
        for(auto y : edges[x]){
            if(visit[y])
                continue;
            f1(y);
            childs[x].push_back(y);
            child_val[x].push_back(dp1[y]);
            res = f(res, dp1[y]);
        }
        dp1[x] = g(res, x);
        child_l[x].push_back(op);
        child_r[x].push_back(op);
        for(int i = 0; i < childs[x].size(); ++i){
            child_l[x].push_back(f(child_l[x].back(), child_val[x][i]));
            child_r[x].push_back(f(child_r[x].back(), child_val[x][childs[x].size() - i - 1]));
        }
    };
    f1(0);
    function<void(int, T)> f2 = [&](int x, T par_val){
        T res = par_val;
        for(int i = 0; i < childs[x].size(); ++i){
            int y = childs[x][i];
            auto p = f(par_val, f(child_l[x][i], child_r[x][childs[x].size() - i - 1]));
            T val = g(f(par_val, f(child_l[x][i], child_r[x][childs[x].size() - i - 1])), y);
            res = f(res, dp1[y]);
            f2(y, val);
        }
        dp2[x] = g(res, x);
    };
    f2(0, op);
    return dp2;
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/functions/rerooting.cpp"
template <typename T>
// T f(T, T): 子の累積に使うもの 直径ならf(x, y): max(x, y)
// T g(T, int): 子の累積を元に適用する際に使うもの 直径ならg(x, idx): x + 1
vector<T> rerooting(vector<vector<int>>& edges, vector<T> v, function<T(T, T)> f, function<T(T, int)> g, T op){
    int n = edges.size();
    vector<int> visit(n, 0);
    vector<T> dp1(v), dp2(n);
    vector<vector<int>> childs(n);
    vector<vector<T>> child_val(n), child_l(n), child_r(n);
    function<void(int)> f1 = [&](int x){
        visit[x] = true;
        T res = op;
        for(auto y : edges[x]){
            if(visit[y])
                continue;
            f1(y);
            childs[x].push_back(y);
            child_val[x].push_back(dp1[y]);
            res = f(res, dp1[y]);
        }
        dp1[x] = g(res, x);
        child_l[x].push_back(op);
        child_r[x].push_back(op);
        for(int i = 0; i < childs[x].size(); ++i){
            child_l[x].push_back(f(child_l[x].back(), child_val[x][i]));
            child_r[x].push_back(f(child_r[x].back(), child_val[x][childs[x].size() - i - 1]));
        }
    };
    f1(0);
    function<void(int, T)> f2 = [&](int x, T par_val){
        T res = par_val;
        for(int i = 0; i < childs[x].size(); ++i){
            int y = childs[x][i];
            auto p = f(par_val, f(child_l[x][i], child_r[x][childs[x].size() - i - 1]));
            T val = g(f(par_val, f(child_l[x][i], child_r[x][childs[x].size() - i - 1])), y);
            res = f(res, dp1[y]);
            f2(y, val);
        }
        dp2[x] = g(res, x);
    };
    f2(0, op);
    return dp2;
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

