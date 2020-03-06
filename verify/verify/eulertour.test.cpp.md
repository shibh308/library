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


# :heavy_check_mark: verify/eulertour.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/verify/eulertour.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-06 18:23:18+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_subtree_sum">https://judge.yosupo.jp/problem/vertex_add_subtree_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/eulertour.cpp.html">lib/classes/eulertour.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/segtree.cpp.html">lib/classes/segtree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#include "../lib/classes/eulertour.cpp"
#include "../lib/classes/segtree.cpp"

signed main(){
    int n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int p;
        cin >> p;
        edges[p].push_back(i);
        edges[i].push_back(p);
    }
    EulerTour et(edges);
    vector<i64> b(n);
    for(int i = 0; i < n; ++i)
        b[et.get_pos(i)] = a[i];
    Segtree<i64> seg(n, b, [](auto x, auto y){return x + y;}, 0LL);
    for(int i = 0; i < q; ++i){
        int type;
        cin >> type;
        if(type == 0){
            int u, x;
            cin >> u >> x;
            seg.update(et.get_pos(u), x);
        }
        else{
            int u;
            cin >> u;
            auto p = et.get_subtree(u);
            cout << seg.get(p.first, p.second) << endl;
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/eulertour.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#line 1 "verify/../lib/classes/eulertour.cpp"
struct EulerTour{
    int n;
    vector<int> in, out;
    EulerTour(vector<vector<int>>& edges, int par = 0) : n(edges.size()), in(n, -1), out(n, -1){
        int cnt = 0;
        function<void(int)> f = [&](int x){
            in[x] = cnt++;
            for(auto y : edges[x]){
                if(in[y] == -1)
                    f(y);
            }
            out[x] = cnt;
        };
        f(par);
    }
    int get_pos(int x){
        return in[x];
    }
    // 自身を含みたくない場合は(in[x] + 1, out[x])
    pair<int,int> get_subtree(int x){
        return make_pair(in[x], out[x]);
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

#line 10 "verify/eulertour.test.cpp"

signed main(){
    int n, q;
    cin >> n >> q;
    vector<i64> a(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i];
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int p;
        cin >> p;
        edges[p].push_back(i);
        edges[i].push_back(p);
    }
    EulerTour et(edges);
    vector<i64> b(n);
    for(int i = 0; i < n; ++i)
        b[et.get_pos(i)] = a[i];
    Segtree<i64> seg(n, b, [](auto x, auto y){return x + y;}, 0LL);
    for(int i = 0; i < q; ++i){
        int type;
        cin >> type;
        if(type == 0){
            int u, x;
            cin >> u >> x;
            seg.update(et.get_pos(u), x);
        }
        else{
            int u;
            cin >> u;
            auto p = et.get_subtree(u);
            cout << seg.get(p.first, p.second) << endl;
        }
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

