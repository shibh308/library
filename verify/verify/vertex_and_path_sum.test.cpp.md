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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: verify/vertex_and_path_sum.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/vertex_and_path_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-14 13:41:21+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_path_sum">https://judge.yosupo.jp/problem/vertex_add_path_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/heavylightdecomposition.cpp.html">lib/classes/heavylightdecomposition.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/segtree.cpp.html">lib/classes/segtree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#include "../lib/classes/segtree.cpp"
#include "../lib/classes/heavylightdecomposition.cpp"


signed main(){

    int n, q;
    scanf("%d%d", &n, &q);
    vector<i64> a(n);
    for(auto& x : a)
        scanf("%lld", &x);
    vector<int> u(n - 1), v(n - 1);
    for(int i = 0; i < n - 1; ++i)
        scanf("%d%d", &u[i], &v[i]);
    vector<tuple<int,int,int>> querys;
    for(int i = 0; i < q; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        querys.emplace_back(a, b, c);
    }
    Segtree<i64> seg(n, 0, [](auto x, auto y){return x + y;}, 0L);
    vector<vector<int>> edges(n);
    for(int i = 0; i < n - 1; ++i) {
        edges[u[i]].emplace_back(v[i]);
        edges[v[i]].emplace_back(u[i]);
    }
    HeavyLightDecomposition hld(edges);
    for(int i = 0; i < n; ++i)
        seg.set(hld.in[i], a[i]);

    for(auto& query : querys){
        int a, b, c;
        tie(a, b, c) = query;
        if(a == 0){
            seg.update(hld.get_idx(b), c);
        }else{
            vector<pair<int,int>> l, r;
            tie(l, r) = hld.two_point_path(b, c);
            i64 sum = 0;
            for(auto& p : l){
                sum += seg.get(p.first, p.second);
            }
            for(auto& p : r){
                sum += seg.get(p.first, p.second);
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/vertex_and_path_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long long;

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#line 1 "verify/../lib/classes/segtree.cpp"
template<typename T>
struct Segtree{
    int n;
    T op;
    vector<T> elm;
    function<T(T, T)> f;

    Segtree(int n, T init, function<T(T, T)> f, T op = T()) :
        n(n),
        op(op),
        elm(2 * n, init),
        f(f)
    {
        for(int i = n - 1; i >= 1; --i)
            elm[i] = f(elm[2 * i], elm[2 * i + 1]);
    }

    Segtree(int n, vector<T> init, function<T(T, T)> f, T op = T()) :
        n(n),
        op(op),
        elm(2 * n),
        f(f)
    {
        for(int i = 0; i < n; ++i)
            elm[i + n] = init[i];
        for(int i = n - 1; i >= 1; --i)
            elm[i] = f(elm[2 * i], elm[2 * i + 1]);
    }

    void set(int x, T val){
        x += n;
        elm[x] = val;
        while(x >>= 1)
            elm[x] = f(elm[2 * x], elm[2 * x + 1]);
    }

    void update(int x, T val){
        x += n;
        elm[x] = f(elm[x], val);
        while(x >>= 1)
            elm[x] = f(elm[2 * x], elm[2 * x + 1]);
    }

    T get(int x, int y) const{
        T l = op, r = op;
        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){
            if(x & 1)
                l = f(l, elm[x++]);
            if(!(y & 1))
                r = f(elm[y--], r);
        }
        return f(l, r);
    }
};

#line 1 "verify/../lib/classes/heavylightdecomposition.cpp"
struct HeavyLightDecomposition{
    int n;
    vector<int> size, par, in, in_rev, heavy_root, depth, heavy_depth, out;
    vector<vector<int>> childs;
    HeavyLightDecomposition(vector<vector<int>>& edges, int root = 0) : n(edges.size()), size(n, 1), par(n, -2), depth(n, 0), childs(n), in(n), in_rev(n), heavy_root(n), heavy_depth(n, 0), out(n){
        function<void(int)> swap_dfs = [&](int x){
            int size_max = 0;
            int max_idx = 0;
            for(int i = 0; i < edges[x].size(); ++i){
                int y = edges[x][i];
                if(par[y] == -2){
                    par[y] = x;
                    depth[y] = depth[x] + 1;
                    childs[x].push_back(y);
                    swap_dfs(y);
                    size[x] += size[y];
                    if(chmax(size_max, size[y])){
                        max_idx = childs[x].size() - 1;
                    }
                }
            }
            if(max_idx){
                swap(childs[x][0], childs[x][max_idx]);
            }
        };
        par[root] = -1;
        swap_dfs(root);

        int cnt = 0;
        function<void(int,int)> dfs = [&](int x, int segment_root){
            heavy_root[x] = segment_root;
            in_rev[cnt] = x;
            in[x] = cnt++;
            for(int i = 0; i < childs[x].size(); ++i){
                int y = childs[x][i];
                if(i == 0){
                    dfs(y, segment_root);
                }
                else{
                    heavy_depth[y] = heavy_depth[segment_root] + 1;
                    dfs(y, y);
                }
            }
            out[x] = cnt;
        };
        dfs(root, root);
    }
    int lca(int x, int y){
        while(heavy_root[x] != heavy_root[y]){
            if(heavy_depth[heavy_root[x]] > heavy_depth[heavy_root[y]])
                swap(x, y);
            y = par[heavy_root[y]];
        }
        return depth[x] < depth[y] ? x : y;
    }
    // x以下の部分木を返す
    pair<int,int> subtree(int x){
        return make_pair(in[x], out[x]);
    }
    // x-zのパスとy-zのパスを返す(両方とも根側に進むので注意)
    // それぞれのHeavy-Pathは根側の方がindexが小さいので注意(可換クエリ処理で気をつける)
    pair<vector<pair<int,int>>, vector<pair<int,int>>> two_point_path(int x, int y){
        vector<pair<int,int>> xz, yz;
        int z = lca(x, y);
        while(heavy_root[x] != heavy_root[z]){
            xz.emplace_back(in[heavy_root[x]], in[x] + 1);
            x = par[heavy_root[x]];
        }
        while(heavy_root[y] != heavy_root[z]){
            yz.emplace_back(in[heavy_root[y]], in[y] + 1);
            y = par[heavy_root[y]];
        }
        // 辺属性にしたい場合はここをin[z] + 1, in[x] + 1にする
        xz.emplace_back(in[z], in[x] + 1);
        yz.emplace_back(in[z] + 1, in[y] + 1);
        return make_pair(xz, yz);
    }
    // 頂点xがEuler-Tour上で何番目に位置するかを返す
    // in[元の頂点index] = 内部でのindex
    // in_rev[内部でのindex] = 元の頂点index
    int get_idx(int x){
        return in[x];
    }
    // xが属するHeavy-Pathの深さを返す
    int get_heavy_depth(int x){
        return heavy_depth[heavy_root[x]];
    }
};

#line 19 "verify/vertex_and_path_sum.test.cpp"


signed main(){

    int n, q;
    scanf("%d%d", &n, &q);
    vector<i64> a(n);
    for(auto& x : a)
        scanf("%lld", &x);
    vector<int> u(n - 1), v(n - 1);
    for(int i = 0; i < n - 1; ++i)
        scanf("%d%d", &u[i], &v[i]);
    vector<tuple<int,int,int>> querys;
    for(int i = 0; i < q; ++i){
        int a, b, c;
        scanf("%d%d%d", &a, &b, &c);
        querys.emplace_back(a, b, c);
    }
    Segtree<i64> seg(n, 0, [](auto x, auto y){return x + y;}, 0L);
    vector<vector<int>> edges(n);
    for(int i = 0; i < n - 1; ++i) {
        edges[u[i]].emplace_back(v[i]);
        edges[v[i]].emplace_back(u[i]);
    }
    HeavyLightDecomposition hld(edges);
    for(int i = 0; i < n; ++i)
        seg.set(hld.in[i], a[i]);

    for(auto& query : querys){
        int a, b, c;
        tie(a, b, c) = query;
        if(a == 0){
            seg.update(hld.get_idx(b), c);
        }else{
            vector<pair<int,int>> l, r;
            tie(l, r) = hld.two_point_path(b, c);
            i64 sum = 0;
            for(auto& p : l){
                sum += seg.get(p.first, p.second);
            }
            for(auto& p : r){
                sum += seg.get(p.first, p.second);
            }
            printf("%lld\n", sum);
        }
    }

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

