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


# :warning: verify/static_rmq.test.cpp


[Back to top page](../../index.html)

* see: [https://judge.yosupo.jp/problem/staticrmq](https://judge.yosupo.jp/problem/staticrmq)


## Dependencies
* :warning: [lib/classes/disjointsparsetable.cpp](../../library/lib/classes/disjointsparsetable.cpp.html)


## Code
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/disjointsparsetable.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    DisjointSparseTable<int> d(a, [](auto x, auto y){return min(x, y);});
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;
        cout << d.get(l, r) << endl;
    }
}

```

[Back to top page](../../index.html)

