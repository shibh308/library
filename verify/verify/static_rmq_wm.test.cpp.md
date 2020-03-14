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


# :heavy_check_mark: verify/static_rmq_wm.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/static_rmq_wm.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-05 02:12:16+09:00


* see: <a href="https://judge.yosupo.jp/problem/staticrmq">https://judge.yosupo.jp/problem/staticrmq</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/waveletmatrix.cpp.html">lib/classes/waveletmatrix.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/waveletmatrix.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    WaveletMatrix<int> wm(a);
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;
        cout << wm.kth_min(l, r, 0) << endl;
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/static_rmq_wm.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#line 1 "verify/../lib/classes/waveletmatrix.cpp"

struct BitVector{
    int n, m;
    vector<int> l;
    vector<uint64_t> s;

    BitVector(int n) : n(n){
        m = (n + 63) >> 6;
        l.assign(m, 0);
        s.assign(m, 0);
    }

    void set(int i, bool flag = true){
        if(flag)
            s[i >> 6] |= (1uLL << (i & 63));
        else
            s[i >> 6] &= ~(1uLL << (i & 63));
    }

    void build(){
        l[0] = 0;
        for(int i = 1; i < m; ++i)
            l[i] = l[i - 1] + __builtin_popcountll(s[i - 1]);
    }

    // [0, r) count flag
    int rank(int r, bool flag = true){
        if(flag)
            return l[r >> 6] + __builtin_popcountll(s[r >> 6] & ((1uLL << (r & 63)) - 1));
        else
            return r - (l[r >> 6] + __builtin_popcountll(s[r >> 6] & ((1uLL << (r & 63)) - 1)));
    }

};

template <typename T>
struct WaveletMatrix{
    int n, m;
    vector<BitVector> b;
    vector<int> border;
    WaveletMatrix(vector<T> a) : n(a.size()){
        T max_val = *max_element(a.begin(), a.end());
        m = (max_val == 0) ? 1 : 64 - __builtin_clzll(max_val);
        b.resize(m, BitVector(n));
        border.resize(m);
        vector<vector<T>> v(2, vector<T>(n));
        for(int j = m - 1; j >= 0; --j){
            vector<int> cnt(2, 0);
            for(int i = 0; i < n; ++i){
                bool fl = ((a[i] >> j) & 1);
                if(fl)
                    b[j].set(i);
                v[fl][cnt[fl]++] = a[i];
            }
            swap(a, v[0]);
            for(int i = 0; i < cnt[1]; ++i) {
                a[i + cnt[0]] = v[1][i];
            }
            b[j].build();
            border[j] = cnt[0];
        }
    }

    // [l, r) count x
    int count(int l, int r, T x){
        for(int j = m - 1; j >= 0; --j){
            bool fl = (x >> j) & 1;
            r = b[j].rank(r, fl) + (fl ? border[j] : 0);
            l = b[j].rank(l, fl) + (fl ? border[j] : 0);
        }
        return r - l;
    }

    // [l, r) count k (x <= k)
    int count_lower(int l, int r, T x){
        int cnt = 0;
        for(int j = m - 1; j >= 0; --j){
            bool fl = (x >> j) & 1;
            if(fl)
                cnt += (l - r) - b[j].rank(l, 0);
            r = b[j].rank(r, fl) + (fl ? border[j] : 0);
            l = b[j].rank(l, fl) + (fl ? border[j] : 0);
        }
        return cnt + (r - l);
    }

    // [l, r) count k (x <= k < y)
    int count_range(int l, int r, T x, T y){
        return count_lower(l, r, y - 1) - count_lower(l, r, x - 1);
    }

    // [l, r) k-th min value (k: 0-indexed)
    T kth_min(int l, int r, int k){
        if(r - l < k)
            return -1;
        T ret = 0;
        for(int j = m - 1; j >= 0; --j){
            int x = b[j].rank(r, false) - b[j].rank(l, false);
            bool fl = (k >= x);
            if(fl){
                ret |= (1uLL << j);
                k -= x;
            }
            r = b[j].rank(r, fl) + (fl ? border[j] : 0);
            l = b[j].rank(l, fl) + (fl ? border[j] : 0);
        }
        return ret;
    }

    // [l, r) k-th min value (k: 0-indexed)
    T kth_max(int l, int r, int k){
        return kth_min(l, r, (r - l - 1) - k);
    }

    // [l, r) upper_bound(k) value
    T next_value_T(int l, int r, T k){
        return kth_min(count_lower(l, r, k) + 1);
    }

    // [l, r) prev(lower_bound(k)) value
    T prev_value(int l, int r, T k){
        return kth_min(count_lower(l, r, k - 1));
    }

};
#line 8 "verify/static_rmq_wm.test.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    WaveletMatrix<int> wm(a);
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;
        cout << wm.kth_min(l, r, 0) << endl;
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

