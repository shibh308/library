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


# :heavy_check_mark: verify/unionfind.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/unionfind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-04 00:43:23+09:00


* see: <a href="https://judge.yosupo.jp/problem/unionfind">https://judge.yosupo.jp/problem/unionfind</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/unionfind.cpp.html">lib/classes/unionfind.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
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
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/unionfind.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/unionfind"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "verify/../lib/classes/unionfind.cpp"
struct UnionFind{
    vector<int> par;
    int count;
    UnionFind(int n) : par(n, -1), count(0){}
    int Find(int x){return par[x] < 0 ? x : Find(par[x]);}
    int Size(int x){return par[x] < 0 ? -par[x] : Size(par[x]);}
    bool Unite(int x, int y){
        x = Find(x);
        y = Find(y);
        if(x == y)
            return false;
        if(par[x] > par[y])
            swap(x, y);
        par[x] += par[y];
        par[y] = x;
        return ++count;
    }
};

#line 8 "verify/unionfind.test.cpp"


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
{% endraw %}

<a href="../../index.html">Back to top page</a>

