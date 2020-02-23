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


# :heavy_check_mark: verify/rmq_raq_dynamic.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/verify/rmq_raq_dynamic.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-05 02:54:01+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/dynamiclazysegmenttree.cpp.html">lib/classes/dynamiclazysegmenttree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/dynamiclazysegmenttree.cpp"


signed main() {
    int n, q;
    cin >> n >> q;
    Segtree<int,int> seg(n, [](auto x, auto y){return min(x, y);}, [](auto x, auto y, int){return x + y;}, [](auto x, auto y){return x + y;}, 1e9, 0);
    seg.update(0, n, -1e9);
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
#line 1 "verify/rmq_raq_dynamic.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "verify/../lib/classes/dynamiclazysegmenttree.cpp"
template<typename T, typename U>
struct Segtree{

    struct SegNode{
        T val;
        U lazy;

        SegNode* l;
        SegNode* r;
        SegNode(T val, U lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr){}
    };

    i64 n;
    function<T(T, T)> f;
    function<T(T, U, int)> g;
    function<U(U, U)> h;
    T op_t;
    U op_u;

    SegNode* root;

    Segtree(int n_, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t), op_u(op_u){
        for(n = 1; n < n_; n <<= 1);
        root = new SegNode(op_t, op_u);
    }

    SegNode* getl(SegNode* node){
        return node->l ? node->l : node->l = new SegNode(op_t, op_u);
    }

    SegNode* getr(SegNode* node){
        return node->r ? node->r : node->r = new SegNode(op_t, op_u);
    }

    void eval(SegNode* node, i64 len){
        node->val = g(node->val, node->lazy, len);
        getl(node);
        node->l->lazy = h(node->l->lazy, node->lazy);
        getr(node);
        node->r->lazy = h(node->r->lazy, node->lazy);
        node->lazy = op_u;
    }

    void update(i64 x, i64 y, U val, SegNode* node = nullptr, i64 l = 0, i64 r = 0){
        if(node == nullptr){
            node = root;
            r = n;
        }
        eval(node, r - l);
        if(r <= x || y <= l)
            return ;
        if(x <= l && r <= y){
            node->lazy = h(node->lazy, val);
            eval(node, r - l);
        }else{
            i64 mid = (l + r) >> 1;
            update(x, y, val, getl(node), l, mid);
            update(x, y, val, getr(node), mid, r);
            node->val = f(node->l->val, node->r->val);
        }
    }

    T get(i64 x, i64 y, SegNode* node = nullptr, i64 l = 0, i64 r = 0){
        if(node	== nullptr){
            node = root;
            r = n;
        }

        if(r <= x || y <= l)
            return op_t;
        eval(node, r - l);
        if(x <= l && r <= y)
            return node->val;

        i64 val_l = op_t, val_r = op_t;
        i64 mid = (l + r) >> 1;

        if(node->l)
            val_l = get(x, y, node->l, l, mid);
        if(node->r)
            val_r = get(x, y, node->r, mid, r);
        return f(val_l, val_r);
    }

};

#line 8 "verify/rmq_raq_dynamic.test.cpp"


signed main() {
    int n, q;
    cin >> n >> q;
    Segtree<int,int> seg(n, [](auto x, auto y){return min(x, y);}, [](auto x, auto y, int){return x + y;}, [](auto x, auto y){return x + y;}, 1e9, 0);
    seg.update(0, n, -1e9);
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

