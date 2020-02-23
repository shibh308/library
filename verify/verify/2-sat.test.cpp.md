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


# :x: verify/2-sat.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/verify/2-sat.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-04 01:33:57+09:00


* see: <a href="https://judge.yosupo.jp/problem/two_sat">https://judge.yosupo.jp/problem/two_sat</a>


## Depends on

* :x: <a href="../../library/lib/functions/scc.cpp.html">lib/functions/scc.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
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
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/2-sat.test.cpp"
// #define PROBLEM "https://judge.yosupo.jp/problem/two_sat"
// https://judge.yosupo.jp/submission/1776

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "verify/../lib/functions/scc.cpp"
vector<int> scc(vector<vector<int>>& edges){
    int n = edges.size();
    vector<vector<int>> rev(n);

    for(int i = 0; i < n; ++i)
        for(auto& x : edges[i])
            rev[x].emplace_back(i);

    vector<i64> dfs_num(n, -1);
    vector<i64> flag(n, 0);
    int num = 0;
    function<void(int)> dfs = [&](int pos){
        flag[pos] = 1;
        for(auto& xx : edges[pos])
            if(!flag[xx]){
                dfs(xx);
        }
        dfs_num[pos] = num++;
    };

    for(int i = 0; i < n; ++i)
        if(!flag[i])
            dfs(i);

    vector<int> dfs_inv(n);
    for(int i = 0; i < n; ++i)
        dfs_inv[n - 1 - dfs_num[i]] = i;

    num = 0;

    vector<int> scc_vec(n, -1);

    function<void(int)> rdfs = [&](int pos){
        scc_vec[pos] = num;
        for(auto t : rev[pos])
            if(scc_vec[t] == -1)
                rdfs(t);
    };

    for(int i = 0; i < n; ++i)
        if(scc_vec[dfs_inv[i]] == -1){
            rdfs(dfs_inv[i]);
            ++num;
        }

    return scc_vec;
}
#line 9 "verify/2-sat.test.cpp"


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
{% endraw %}

<a href="../../index.html">Back to top page</a>

