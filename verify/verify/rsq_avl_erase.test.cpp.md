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


# :heavy_check_mark: verify/rsq_avl_erase.test.cpp

<a href="../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/verify/rsq_avl_erase.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-26 07:59:33+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_add_range_sum">https://judge.yosupo.jp/problem/point_add_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/avl.cpp.html">lib/classes/avl.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

#include "../lib/classes/avl.cpp"

signed main(){

    int n, q;
    scanf("%d%d", &n, &q);

    AVL<i64> avl([](auto x, auto y){return x + y;}, 0);
    auto root = avl.nil;
    for(int i = 0; i < n; ++i){
        int a;
        scanf("%d", &a);
        root = avl.insert(root, i, a);
    }

    vector<int> t(q), a(q), c(q);
    for(int i = 0; i < q; ++i)
        scanf("%d%d%d", &t[i], &a[i], &c[i]);
    for(int i = 0; i < q; ++i){
        if(t[i] == 0){
            i64 res = avl.getNode(root, a[i])->val;
            root = avl.erase(root, a[i], false);
            root = avl.insert(root, a[i], res + c[i]);
        }else{
            printf("%lld\n", avl.get(root, a[i], c[i]));
        }
    }

}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 348, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 63, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 182, in update
    self.update(self._resolve(included, included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.1/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 77, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: bits/stdc++.h: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

