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


# :warning: verify/vertex_and_path_sum.test.cpp


[Back to top page](../../index.html)

* see: [https://judge.yosupo.jp/problem/vertex_add_path_sum](https://judge.yosupo.jp/problem/vertex_add_path_sum)


## Dependencies
* :warning: [lib/classes/heavylightdecomposition.cpp](../../library/lib/classes/heavylightdecomposition.cpp.html)
* :warning: [lib/classes/segtree.cpp](../../library/lib/classes/segtree.cpp.html)


## Code
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/segtree.cpp"
#include "../lib/classes/heavylightdecomposition.cpp"


signed main(){

    int n, q;
    scanf("%d%d", &n, &q);
    vector<i64> a(n);
    for(auto& x : a)
        scanf("%d", &x);
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
            seg.update(hld.in[b], c);
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

[Back to top page](../../index.html)

