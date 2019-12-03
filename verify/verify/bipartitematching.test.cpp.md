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


# :warning: verify/bipartitematching.test.cpp


[Back to top page](../../index.html)

* see: [https://judge.yosupo.jp/problem/bipartitematching](https://judge.yosupo.jp/problem/bipartitematching)


## Dependencies
* :warning: [lib/classes/dinic.cpp](../../library/lib/classes/dinic.cpp.html)


## Code
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/bipartitematching"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/dinic.cpp"


signed main() {

    int l, r, m;
    cin >> l >> r >> m;
    Dinic<int> d(l + r + 2);
    for(int i = 0; i < m; ++i){
        int a, b;
        cin >> a >> b;
        d.add(a, l + b, 1);
    }
    for(int i = 0; i < l; ++i)
        d.add(l + r, i, 1);
    for(int i = 0; i < r; ++i)
        d.add(l + i, l + r + 1, 1);
    cout << d.solve(l + r, l + r + 1) << endl;
    for(int i = 0; i < l + r; ++i)
        for(auto& e : d.edges[i]){
            if(e.to >= l + r || i >= e.to)
                continue;
            if(e.cap == 0)
                cout << i << " " << e.to - l << endl;
        }
}


```

[Back to top page](../../index.html)

