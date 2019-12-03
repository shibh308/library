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


# :warning: verify/lca_hld.test.cpp


[Back to top page](../../index.html)

* see: [https://judge.yosupo.jp/problem/lca](https://judge.yosupo.jp/problem/lca)


## Dependencies
* :warning: [lib/classes/heavylightdecomposition.cpp](../../library/lib/classes/heavylightdecomposition.cpp.html)


## Code
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/heavylightdecomposition.cpp"


signed main() {
    int n, q;
    cin >> n >> q;
    vector<vector<int>> edges(n);
    for(int i = 1; i < n; ++i){
        int j;
        cin >> j;
        edges[i].emplace_back(j);
        edges[j].emplace_back(i);
    }
    HeavyLightDecomposition hld(edges);
    for(int i = 0; i < q; ++i){
        int u, v;
        cin >> u >> v;
        cout << hld.lca(u, v) << endl;
    }
}


```

[Back to top page](../../index.html)

