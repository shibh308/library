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


# :heavy_check_mark: verify/rsq_dynamic.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/rsq_dynamic.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-25 07:58:59+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_add_range_sum">https://judge.yosupo.jp/problem/point_add_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/dynamicsegmenttree.cpp.html">lib/classes/dynamicsegmenttree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/dynamicsegmenttree.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);

    Segtree<i64> seg(1e9, [](auto x, auto y){return x + y;}, 0);
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        seg.set(i, a);
    }
    for(int i = 0; i < q; ++i){
        int t, a, c;
        cin >> t >> a >> c;
        if(t == 0){
            seg.update(a, c);
        }
        else{
            cout << seg.get(a, c) << endl;
        }
    }
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/rsq_dynamic.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "lib/classes/dynamicsegmenttree.cpp"
template <typename T>
struct Segtree{

    struct SegNode;

    struct SegNode{
        T val;
        SegNode* l;
        SegNode* r;

        SegNode(T val) : val(val), l(nullptr), r(nullptr){}
    };

    i64 n;
    function<T(T, T)> f;
    T op;
    SegNode* root;

    Segtree(int n_, function<T(T, T)> f, T op) : f(f), op(op){
        for(n = 1; n < n_; n <<= 1);
        root = new SegNode(op);
    }

    SegNode* getl(SegNode* node, T val){
        return node->l == nullptr ? node->l = new SegNode(val) : node->l;
    }

    SegNode* getr(SegNode* node, T val){
        return node->r == nullptr ? node->r = new SegNode(val) : node->r;
    }

    void eval(SegNode* node){
        node->val = f(node->l == nullptr ? op : node->l->val, node->r == nullptr ? op : node->r->val);
    }

    void set(i64 x, T val){
        assert(0 <= x && x < n);

        SegNode* node = root;
        stack<SegNode*> nodes;
        i64 l = 0, r = n;

        while(r - l > 1){
            nodes.push(node);
            i64 mid = (l + r) >> 1;

            if(x < mid){
                node = getl(node, x);
                r = mid;
            }else{
                node = getr(node, x);
                l = mid;
            }
        }

        node->val = val;
        while(!nodes.empty()){
            eval(nodes.top());
            nodes.pop();
        }
    }

    void update(i64 x, T val){
        assert(0 <= x && x < n);

        SegNode* node = root;
        stack<SegNode*> nodes;
        i64 l = 0, r = n;

        while(r - l > 1){
            nodes.push(node);
            i64 mid = (l + r) >> 1;

            if(x < mid){
                node = getl(node, x);
                r = mid;
            }else{
                node = getr(node, x);
                l = mid;
            }
        }

        node->val = f(node->val, val);
        while(!nodes.empty()){
            eval(nodes.top());
            nodes.pop();
        }
    }

    T get(i64 x, i64 y, SegNode* node = nullptr, i64 l = 0,  i64 r = 0){

        if(node == nullptr){
            node = root;
            r = n;
        }

        if(x <= l && r <= y)
            return node->val;

        if(r <= x || y <= l)
            return op;

        T val_l = op, val_r = op;
        i64 mid = (l + r) >> 1;

        if(node->l != nullptr)
            val_l = f(val_l, get(x, y, node->l, l, mid));
        if(node->r != nullptr)
            val_r = f(get(x, y, node->r, mid, r), val_r);

        return f(val_l, val_r);
    }

};

#line 8 "verify/rsq_dynamic.test.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);

    Segtree<i64> seg(1e9, [](auto x, auto y){return x + y;}, 0);
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        seg.set(i, a);
    }
    for(int i = 0; i < q; ++i){
        int t, a, c;
        cin >> t >> a >> c;
        if(t == 0){
            seg.update(a, c);
        }
        else{
            cout << seg.get(a, c) << endl;
        }
    }
}


```
{% endraw %}

<a href="../../index.html">Back to top page</a>
