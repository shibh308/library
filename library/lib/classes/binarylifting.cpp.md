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


# :heavy_check_mark: lib/classes/binarylifting.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/binarylifting.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-20 18:12:37+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/lca_binarylifting.test.cpp.html">verify/lca_binarylifting.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct BinaryLifting{
    int n;
    vector<vector<int>> next;
    vector<int> par;
    vector<vector<int>> childs;
    vector<int> depth;

    BinaryLifting(vector<vector<int>>& edges, int root = 0) : n(edges.size()), depth(n, -1), par(n, -1), childs(n){
        function<void(int)> dfs = [&](int x){
            for(auto y : edges[x])
                if(depth[y] == -1){
                    depth[y] = depth[x] + 1;
                    par[y] = x;
                    childs[x].push_back(y);
                    dfs(y);
                }
        };
        depth[root] = 0;
        dfs(root);

        next.push_back(par);
        for(int k = 0;; ++k){
            bool fl = false;
            next.emplace_back(n, -1);
            for(int i = 0; i < n; ++i){
                next[k + 1][i] = (next[k][i] == -1 ? -1 : next[k][next[k][i]]);
                if(next[k + 1][i] != -1)
                    fl = true;
            }
            if(!fl)
                break;
        }
    }
    // kth_next(x, 0) => x
    int kth_next(int x, int k){
        for(int i = 0; i < next.size() && k; ++i){
            if(k & (1 << i)){
                x = next[i][x];
                if(x == -1)
                    break;
            }
        }
        return x;
    }

    int lca(int x, int y){
        int min_depth = min(depth[x], depth[y]);
        x = kth_next(x, depth[x] - min_depth);
        y = kth_next(y, depth[y] - min_depth);
        if(x == y)
            return x;
        for(int i = next.size() - 1; i >= 0; --i)
            if(next[i][x] != next[i][y]){
                x = next[i][x];
                y = next[i][y];
            }
        return next[0][x];
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/binarylifting.cpp"
struct BinaryLifting{
    int n;
    vector<vector<int>> next;
    vector<int> par;
    vector<vector<int>> childs;
    vector<int> depth;

    BinaryLifting(vector<vector<int>>& edges, int root = 0) : n(edges.size()), depth(n, -1), par(n, -1), childs(n){
        function<void(int)> dfs = [&](int x){
            for(auto y : edges[x])
                if(depth[y] == -1){
                    depth[y] = depth[x] + 1;
                    par[y] = x;
                    childs[x].push_back(y);
                    dfs(y);
                }
        };
        depth[root] = 0;
        dfs(root);

        next.push_back(par);
        for(int k = 0;; ++k){
            bool fl = false;
            next.emplace_back(n, -1);
            for(int i = 0; i < n; ++i){
                next[k + 1][i] = (next[k][i] == -1 ? -1 : next[k][next[k][i]]);
                if(next[k + 1][i] != -1)
                    fl = true;
            }
            if(!fl)
                break;
        }
    }
    // kth_next(x, 0) => x
    int kth_next(int x, int k){
        for(int i = 0; i < next.size() && k; ++i){
            if(k & (1 << i)){
                x = next[i][x];
                if(x == -1)
                    break;
            }
        }
        return x;
    }

    int lca(int x, int y){
        int min_depth = min(depth[x], depth[y]);
        x = kth_next(x, depth[x] - min_depth);
        y = kth_next(y, depth[y] - min_depth);
        if(x == y)
            return x;
        for(int i = next.size() - 1; i >= 0; --i)
            if(next[i][x] != next[i][y]){
                x = next[i][x];
                y = next[i][y];
            }
        return next[0][x];
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

