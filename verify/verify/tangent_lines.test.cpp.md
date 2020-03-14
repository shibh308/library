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


# :heavy_check_mark: verify/tangent_lines.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/tangent_lines.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-25 16:29:27+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2201">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2201</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/geometry.cpp.html">lib/geometry.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2201"
#include "bits/stdc++.h"

using namespace std;

using i64 = long long;

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#include "../lib/geometry.cpp"

bool solve(){
    int n;
    cin >> n;
    if(!n)
        return false;
    vector<int> x(n);
    vector<int> y(n);
    vector<int> r(n);
    vector<int> m(n);
    for(int i = 0; i < n; ++i)
        cin >> x[i] >> y[i] >> r[i] >> m[i];
    if(n == 1){
        cout << 1 << endl;
        return true;
    }
    using namespace geometry;
    vector<C> circles, power;
    for(int i = 0; i < n; ++i){
        circles.emplace_back(x[i], y[i], r[i]);
        power.emplace_back(x[i], y[i], r[i] + m[i]);
    }

    vector<pair<P,P>> vs;
    for(int i = 0; i < n; ++i){
        for(int j = i + 1; j < n; ++j){
            auto res = tangent_lines(circles[i], circles[j]);
            for(auto p : res)
                vs.push_back(p);
            res = tangent_lines(circles[i], power[j]);
            for(auto p : res)
                vs.push_back(p);
            res = tangent_lines(power[i], circles[j]);
            for(auto p : res)
                vs.push_back(p);
            res = tangent_lines(power[i], power[j]);
            for(auto p : res)
                vs.push_back(p);
        }
    }
    int ans = 0;
    for(auto& p : vs){
        P p1, p2;
        tie(p1, p2) = p;
        int cnt = 0;
        for(int i = 0; i < n; ++i){
            D d = dist(p1, p2, circles[i]);
            if(r[i] < d + eps && d < r[i] + m[i] + eps)
                ++cnt;
        }
        chmax(ans, cnt);
    }
    cout << ans << endl;
    return true;
}

signed main(){
    while(solve());
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 340, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=pathlib.Path.cwd())
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 282, in update
    self.update(self._resolve(pathlib.Path(included), included_from=path))
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 162, in _resolve
    raise BundleError(path, -1, "no such header")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: bits/stdc++.h: line -1: no such header

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

