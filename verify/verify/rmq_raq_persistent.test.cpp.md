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


# :heavy_check_mark: verify/rmq_raq_persistent.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/rmq_raq_persistent.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-05 02:54:01+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/persistentdynamiclazysegmenttree.cpp.html">lib/classes/persistentdynamiclazysegmenttree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/persistentdynamiclazysegmenttree.cpp"


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
#line 1 "verify/rmq_raq_persistent.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "verify/../lib/classes/persistentdynamiclazysegmenttree.cpp"
template<typename T, typename U>
struct Segtree{

    struct SegNode{
        T val;
        U lazy;

        shared_ptr<SegNode> l;
        shared_ptr<SegNode> r;
        SegNode(T val, U lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr){}
    };

    i64 n;
    shared_ptr<SegNode> nil;
    function<T(T, T)> f;
    function<T(T, U, int)> g;
    function<U(U, U)> h;
    T op_t;
    U op_u;

    shared_ptr<SegNode> root;

    Segtree(int n_, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t), op_u(op_u){
        for(n = 1; n < n_; n <<= 1);
        root = make_shared<SegNode>(op_t, op_u);
    }

    void eval(shared_ptr<SegNode> node, i64 len, bool make = true){
        node->val = g(node->val, node->lazy, len);
        if(make){
            node->l = node->l ? make_shared<SegNode>(*node->l) : make_shared<SegNode>(op_t, op_u);
            node->r = node->r ? make_shared<SegNode>(*node->r) : make_shared<SegNode>(op_t, op_u);
        }
        node->l->lazy = h(node->l->lazy, node->lazy);
        node->r->lazy = h(node->r->lazy, node->lazy);
        node->lazy = op_u;
    }

    // if root -> make new node      -> eval(make child)
    void update(i64 x, i64 y, U val, shared_ptr<SegNode> node = nullptr, i64 l = -1, i64 r = -1){
        bool root_flag = (node == nullptr);
        if(root_flag){
            root = make_shared<SegNode>(*root);
            node = root;
        }
        if(l == -1){
            l = 0;
            r = n;
        }
        eval(node, r - l);
        if(r <= x || y <= l)
            return ;
        if(x <= l && r <= y){
            node->lazy = h(node->lazy, val);
            eval(node, r - l, false);
        }else{
            eval(node, r - l);
            i64 mid = (l + r) >> 1;
            update(x, y, val, node->l, l, mid);
            update(x, y, val, node->r, mid, r);
            node->val = f(node->l->val, node->r->val);
        }
        return ;
    }

    T get(i64 x, i64 y, shared_ptr<SegNode> node = nullptr, i64 l = -1, i64 r = -1){
        bool root_flag = (node == nullptr);
        if(root_flag){
            root = make_shared<SegNode>(*root);
            node = root;
        }
        if(l == -1){
            l = 0;
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


#line 8 "verify/rmq_raq_persistent.test.cpp"


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

