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


# :heavy_check_mark: verify/rsq_bit.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/rsq_bit.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-05 03:16:14+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_add_range_sum">https://judge.yosupo.jp/problem/point_add_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/binaryindexedtree.cpp.html">lib/classes/binaryindexedtree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
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
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/rsq_bit.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "verify/../lib/classes/binaryindexedtree.cpp"
template <typename T>
struct BIT{
    vector<T> elm;
    BIT(int n, T init = T()) : elm(n + 1, init){
    }

    // [0, x)
    T sum(int x){
        T val = 0;
        for(; x > 0; x -= x & -x)
            val += elm[x];
        return val;
    }

    // [l, r)
    T sum(int l, int r){
        return sum(r) - sum(l);
    }

    void add(int x, T val){
        for(++x; x < elm.size(); x += x & -x)
            elm[x] += val;
    }
};

#line 8 "verify/rsq_bit.test.cpp"


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
{% endraw %}

<a href="../../index.html">Back to top page</a>

