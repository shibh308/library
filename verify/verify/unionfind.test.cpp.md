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


# :warning: verify/unionfind.test.cpp


[Back to top page](../../index.html)

* see: [https://judge.yosupo.jp/problem/unionfind](https://judge.yosupo.jp/problem/unionfind)


## Dependencies
* :warning: [lib/classes/unionfind.cpp](../../library/lib/classes/unionfind.cpp.html)


## Code
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/unionfind.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> t(q), u(q), v(q);
    for(int i = 0; i < q; ++i)
        cin >> t[i] >> u[i] >> v[i];

    UnionFind uf(n);
    for(int i = 0; i < q; ++i){
        if(t[i] == 0)
            uf.Unite(u[i], v[i]);
        else
            cout << (uf.Find(u[i]) == uf.Find(v[i])) << endl;
    }
}

```

[Back to top page](../../index.html)

