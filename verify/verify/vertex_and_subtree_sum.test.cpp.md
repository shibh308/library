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


# :warning: verify/vertex_and_subtree_sum.test.cpp


[Back to top page](../../index.html)

* see: [https://judge.yosupo.jp/problem/vertex_add_subtree_sum](https://judge.yosupo.jp/problem/vertex_add_subtree_sum)


## Dependencies
* :warning: [lib/classes/heavylightdecomposition.cpp](../../library/lib/classes/heavylightdecomposition.cpp.html)
* :warning: [lib/classes/segtree.cpp](../../library/lib/classes/segtree.cpp.html)


## Code
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

[Back to top page](../../index.html)

