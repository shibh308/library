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


# :warning: verify/2-sat.test.cpp


[Back to top page](../../index.html)

* see: [https://judge.yosupo.jp/problem/two_sat](https://judge.yosupo.jp/problem/two_sat)


## Dependencies
* :warning: [lib/functions/scc.cpp](../../library/lib/functions/scc.cpp.html)


## Code
```cpp
// #define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
// https://judge.yosupo.jp/submission/1776

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/functions/scc.cpp"


signed main() {
    string p, cnf;
    int n, m;
    cin >> p >> cnf >> n >> m;
    /*
     x |  y  :  !x =>  y
     x |  y  :  !y =>  x
    !x |  y  :   x =>  y
    !x |  y  :  !y => !x
     x | !y  :   y =>  x
     x | !y  :  !x => !y
    !x | !y  :   x => !y
    !x | !y  :   y => !x
     */

    vector<vector<int>> edges(2 * n);

    for(int i = 0; i < m; ++i){
        int a, b, tmp;
        cin >> a >> b >> tmp;
        int x = abs(a) - 1;
        int y = abs(b) - 1;
        // if x_plus: true
        bool x_plus = (a >= 0);
        bool y_plus = (b >= 0);

        edges[x + (x_plus ? 0 : n)].emplace_back(y + (y_plus ? n : 0));
        edges[y + (y_plus ? 0 : n)].emplace_back(x + (x_plus ? n : 0));
    }
    auto ret = scc(edges);

    for(int i = 0; i < n; ++i){
        if(ret[i] == ret[i + n]){
            cout << "s UNSATISFIABLE" << endl;

            return 0;
        }
    }

    cout << "s SATISFIABLE" << endl;
    cout << "v";

    for(int i = 0; i < n; ++i){
        cout << " " << (ret[i] < ret[i + n] ? 1 : -1) * (i + 1);
    }
    cout << " " << 0 << endl;

}

```

[Back to top page](../../index.html)

