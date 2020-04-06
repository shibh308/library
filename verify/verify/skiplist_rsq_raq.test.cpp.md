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


# :heavy_check_mark: verify/skiplist_rsq_raq.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/skiplist_rsq_raq.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 15:38:29+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/lazyskiplist.cpp.html">lib/classes/lazyskiplist.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/lazyskiplist.cpp"


signed main(){
    int n, q;
    cin >> n >> q;
    SkipList<i64,i64> slist([](auto x, auto y){return x + y;}, [](auto x, auto y, int z){return x + y * z;}, [](auto x, auto y){return x + y;}, 0LL, 0LL);
    for(int i = 0; i < n; ++i)
        slist.insert_index(i, 0);
    for(int i = 0; i < q; ++i){
        int t;
        scanf("%d", &t);
        if(t == 0){
            int l, r, x;
            scanf("%d%d%d", &l, &r, &x);
            slist.update(--l, r, x);
        }else{
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", slist.get(--l, r));
        }
    }
}



```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 170, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 162, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: bits/stdc++.h: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

