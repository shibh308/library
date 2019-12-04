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


# :warning: verify/rsq_bit.test.cpp


[Back to top page](../../index.html)

* see: [https://judge.yosupo.jp/problem/point_add_range_sum](https://judge.yosupo.jp/problem/point_add_range_sum)


## Dependencies
* :warning: [lib/classes/binaryindexedtree.cpp](../../library/lib/classes/binaryindexedtree.cpp.html)


## Code
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/binaryindexedtree.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);

    BIT<i64> b(n);
    for(int i = 0; i < n; ++i){
        int a;
        cin >> a;
        b.add(i, a);
    }
    for(int i = 0; i < q; ++i){
        int t, a, c;
        cin >> t >> a >> c;
        if(t == 0){
            b.add(a, c);
        }
        else{
            cout << b.sum(a, c) << endl;
        }
    }
}


```

[Back to top page](../../index.html)

