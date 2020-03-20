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


# :heavy_check_mark: verify/rmq_raq.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/rmq_raq.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 20:41:12+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/lazysegtree.cpp.html">lib/classes/lazysegtree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/lazysegtree.cpp"


signed main() {
    int n, q;
    cin >> n >> q;

    Segtree<int,int> seg(n, 0, [](auto x, auto y){return min(x, y);}, [](auto x, auto y, int){return x + y;}, [](auto x, auto y){return x + y;}, 1e9, 0);
    for(int i = 0; i < q; ++i){
        int ty;
        cin >> ty;
        if(ty == 0){
            int s, t, x;
            cin >> s >> t >> x;
            seg.update(s, ++t, x);
        }
        else{
            int s, t;
            cin >> s >> t;
            cout << seg.get(s, ++t) << endl;
        };
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/rmq_raq.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "lib/classes/lazysegtree.cpp"
template<typename T, typename U>
struct Segtree{
    int n;
    T op_t;
    U op_u;
    vector<T> elm;
    vector<U> lazy;
    vector<int> length;
    function<T(T, T)> f;
    function<T(T, U, int)> g;
    function<U(U, U)> h;

    Segtree(int n, T init, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t = T(), U op_u = U()) :
        n(n),
        op_t(op_t),
        op_u(op_u),
        elm(2 * n, init),
        lazy(2 * n, op_u),
        length(2 * n, 0),
        f(f),
        g(g),
        h(h)
    {
        for(int i = n - 1; i > 0; --i){
            elm[i] = f(elm[2 * i], elm[2 * i + 1]);
            length[i] = length[2 * i] + 1;
        }
    }

    Segtree(int n, vector<T> init, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t = T(), U op_u = U()) :
        n(n),
        op_t(op_t),
        op_u(op_u),
        elm(2 * n),
        lazy(2 * n, op_u),
        length(2 * n, 0),
        f(f),
        g(g),
        h(h)
    {
        for(int i = 0; i < n; ++i)
            elm[i + n] = init[i];

        for(int i = n - 1; i > 0; --i){
            elm[i] = f(elm[2 * i], elm[2 * i + 1]);
            length[i] = length[2 * i] + 1;
        }
    }

    vector<int> get_list(int x, int y){

        vector<int> ret_list;
        for(x += n, y += n - 1; x; x >>= 1, y >>= 1){
            ret_list.emplace_back(x);
            if(x != y)
                ret_list.emplace_back(y);
        }

        return ret_list;
    }

    void eval(int x){

        elm[x] = g(elm[x], lazy[x], 1 << length[x]);
        if(x < n){
            lazy[2 * x] = h(lazy[2 * x], lazy[x]);
            lazy[2 * x + 1] = h(lazy[2 * x + 1], lazy[x]);
        }
        lazy[x] = op_u;
    }

    void update(int x, int y, U val){

        if(x == y)
            return;
        vector<int> index_list = get_list(x, y);
        for(int i = index_list.size() - 1; i >= 0; --i)
            eval(index_list[i]);

        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){
            if(x & 1){
                lazy[x] = h(lazy[x], val);
                eval(x++);
            }
            if(!(y & 1)){
                lazy[y] = h(lazy[y], val);
                eval(y--);
            }
        }

        for(auto index : index_list){
            if(index < n){
                eval(2 * index);
                eval(2 * index + 1);
                elm[index] = f(elm[2 * index], elm[2 * index + 1]);
            }
        }
    }

    T get(int x, int y){

        vector<int> index_list = get_list(x, y);
        for(int i = index_list.size() - 1; i >= 0; --i)
            eval(index_list[i]);

        T l = op_t, r = op_t;
        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){
            if(x & 1){
                eval(x);
                l = f(l, elm[x++]);
            }
            if(!(y & 1)){
                eval(y);
                r = f(elm[y--], r);
            }
        }
        return f(l, r);
    }
};

#line 8 "verify/rmq_raq.test.cpp"


signed main() {
    int n, q;
    cin >> n >> q;

    Segtree<int,int> seg(n, 0, [](auto x, auto y){return min(x, y);}, [](auto x, auto y, int){return x + y;}, [](auto x, auto y){return x + y;}, 1e9, 0);
    for(int i = 0; i < q; ++i){
        int ty;
        cin >> ty;
        if(ty == 0){
            int s, t, x;
            cin >> s >> t >> x;
            seg.update(s, ++t, x);
        }
        else{
            int s, t;
            cin >> s >> t;
            cout << seg.get(s, ++t) << endl;
        };
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

