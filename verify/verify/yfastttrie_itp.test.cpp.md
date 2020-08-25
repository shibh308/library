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


# :heavy_check_mark: verify/yfastttrie_itp.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/yfastttrie_itp.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-11 13:43:20+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/hashmap.cpp.html">lib/classes/hashmap.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/splaytree_sset.cpp.html">lib/classes/splaytree_sset.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/xfasttrie_yft.cpp.html">lib/classes/xfasttrie_yft.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/yfasttrie.cpp.html">lib/classes/yfasttrie.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;


#include "../lib/classes/hashmap.cpp"
#include "../lib/classes/splaytree_sset.cpp"
#include "../lib/classes/xfasttrie_yft.cpp"
#include "../lib/classes/yfasttrie.cpp"


signed main(){
    int q;
    scanf("%d", &q);
    YFastTrie<int, 31> s;
    for(int i = 0; i < q; ++i){
        int t, x;
        scanf("%d%d", &t, &x);
        if(t == 0){
            auto ptr = s.lower_bound(x);
            if(ptr == s.splay.nil || ptr->val != x)
                s.insert(x);
            printf("%d\n", s.n - 1);
        }
        else if(t == 2){
            s.erase(x);
        }
        else{
            auto ptr = s.lower_bound(x);
            printf("%d\n", ptr != s.splay.nil && ptr->val == x);
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 349, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 185, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 399, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 258, in _resolve
    raise BundleErrorAt(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>
