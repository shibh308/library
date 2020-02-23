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


# :heavy_check_mark: verify/vertex_and_subtree_sum.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/verify/vertex_and_subtree_sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-04 00:43:23+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_subtree_sum">https://judge.yosupo.jp/problem/vertex_add_subtree_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/heavylightdecomposition.cpp.html">lib/classes/heavylightdecomposition.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/segtree.cpp.html">lib/classes/segtree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/heavylightdecomposition.cpp"
#include "../lib/classes/segtree.cpp"

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int j;
        cin >> j;
        edges[i].emplace_back(j);
        edges[j].emplace_back(i);
    }
    HeavyLightDecomposition hld(edges);
    Segtree<i64> seg(n, 0L, [](auto x, auto y){return x + y;}, 0L);
    for(int i = 0; i < n; ++i)
        seg.set(hld.in[i], a[i]);
    for(int i = 0; i < q; ++i){
        int t;
        cin >> t;
        if(t == 0){
            int u, x;
            cin >> u >> x;
            seg.update(hld.in[u], x);
        }
        else{
            int u;
            cin >> u;
            auto v = hld.subtree(u);
            cout << seg.get(v.first, v.second) << endl;
        }
    }
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/vertex_and_subtree_sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "verify/../lib/classes/heavylightdecomposition.cpp"
class HeavyLightDecomposition{
public:
    int n;
    vector<vector<int>> g;
    vector<int> rev, in, out, nxt, rin, size, depth;

    HeavyLightDecomposition(vector<vector<int>>& inp) :
        n(inp.size()),
        g(n),
        rev(n, 0),
        in(n, 0),
        out(n, 0),
        nxt(n, 0),
        rin(n, 0),
        size(n, 0),
        depth(n, -1)
    {

        function<void(int, int)> dfs_ed = [&](int pos, int dep){
            depth[pos]=dep;
            for(auto ed : inp[pos])
                if(depth[ed] == -1){
                    g[pos].emplace_back(ed);
                    rev[ed] = pos;
                    dfs_ed(ed, dep + 1);
                }
        };
        dfs_ed(0, 0);

        function<void(int)> dfs_sz = [&](int v){
            size[v] = 1;
            for(auto &u: g[v]){
                dfs_sz(u);
                size[v] += size[u];
                if(size[u] > size[g[v][0]])
                    swap(u, g[v][0]);
            }
        };
        dfs_sz(0);

        int t = 0;

        function<void(int)> dfs_hld = [&](int v){
            in[v] = t++;
            rin[in[v]] = v;
            for(auto u: g[v]){
                nxt[u] = (u == g[v][0] ? nxt[v] : u);
                dfs_hld(u);
            }
            out[v] = t;
        };
        dfs_hld(0);
    }

    pair<int,int> subtree(int x){
        return make_pair(in[x], out[x]);
    }

    vector<int> subtree_path(int x){
        return vector<int>(next(rin.begin(), in[x]), next(rin.begin(), out[x]));
    }

    pair<int,int> subsegment(int x){
        return make_pair(in[nxt[x]], in[x] + 1);
    }

    vector<int> subsegment_path(int x){
        return vector<int>(next(rin.begin(), in[nxt[x]]), next(rin.begin(), in[x] + 1));
    }

    vector<pair<int,int>> root_path_query(int x){
        vector<pair<int,int>> ret;
        ret.emplace_back(subsegment(x));
        while(ret.back().first)
            ret.emplace_back(subsegment(rev[rin[ret.back().first]]));

        return ret;
    }

    int lca(int x, int y){

        int sx = rin[subsegment(x).first];
        int sy = rin[subsegment(y).first];
        while(sx != sy){
            if(depth[sx] > depth[sy])
                x = rev[sx];
            else
                y = rev[sy];
            sx = rin[subsegment(x).first];
            sy = rin[subsegment(y).first];
        }

        return depth[x] < depth[y] ? x : y;
    }

    pair<vector<pair<int,int>>,vector<pair<int,int>>> two_point_path(i64 x, i64 y){
        i64 z = lca(x, y);
        pair<int,int> z_par = subsegment(z);

        vector<pair<int,int>> ret_x;
        ret_x.emplace_back(subsegment(x));

        while(ret_x.back().first != z_par.first)
            ret_x.emplace_back(subsegment(rev[rin[ret_x.back().first]]));

        ret_x.back().first = in[z];

        vector<pair<int,int>> ret_y;
        ret_y.emplace_back(subsegment(y));

        while(ret_y.back().first != z_par.first)
            ret_y.emplace_back(subsegment(rev[rin[ret_y.back().first]]));

        ret_y.back().first = in[z] + 1;

        return make_pair(ret_x, ret_y);
    }


};

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

#line 9 "verify/vertex_and_subtree_sum.test.cpp"

signed main() {
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int j;
        cin >> j;
        edges[i].emplace_back(j);
        edges[j].emplace_back(i);
    }
    HeavyLightDecomposition hld(edges);
    Segtree<i64> seg(n, 0L, [](auto x, auto y){return x + y;}, 0L);
    for(int i = 0; i < n; ++i)
        seg.set(hld.in[i], a[i]);
    for(int i = 0; i < q; ++i){
        int t;
        cin >> t;
        if(t == 0){
            int u, x;
            cin >> u >> x;
            seg.update(hld.in[u], x);
        }
        else{
            int u;
            cin >> u;
            auto v = hld.subtree(u);
            cout << seg.get(v.first, v.second) << endl;
        }
    }
}


```
{% endraw %}

<a href="../../index.html">Back to top page</a>

