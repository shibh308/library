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


# :warning: verify/rmq_raq.test.cpp


[Back to top page](../../index.html)

* see: [http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H](http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_H)


## Dependencies
* :warning: [lib/classes/lazysegtree.cpp](../../library/lib/classes/lazysegtree.cpp.html)


## Code
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

[Back to top page](../../index.html)

