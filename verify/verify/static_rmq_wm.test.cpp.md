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
    - Last commit date: 2020-04-15 15:28:12+09:00


* see: <a href="https://judge.yosupo.jp/problem/staticrmq">https://judge.yosupo.jp/problem/staticrmq</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/bitvector.cpp.html">lib/classes/bitvector.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/waveletmatrix.cpp.html">lib/classes/waveletmatrix.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

#include <bits/stdc++.h>
using namespace std;
using i64 = long;

#include "../lib/classes/bitvector.cpp"
#include "../lib/classes/waveletmatrix.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    WaveletMatrix<int, 31> wm(a);
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

#line 1 "lib/classes/bitvector.cpp"
struct BitVector{
    vector<uint64_t> v;
    vector<int> r;
    BitVector(){}
    void build(){
        r.assign(v.size() + 1, 0);
        for(int i = 0; i < v.size(); ++i)
            r[i + 1] = r[i] + __builtin_popcountll(v[i]);
    }
    bool access(int x){
        return (v[x >> 6] >> (x & 63)) & 1;
    }
    // [0, x)の1の出現回数
    int rank(int x){
        return r[x >> 6] + __builtin_popcountll(v[x >> 6] & ((1uLL << (x & 63)) - 1));
    }
    int rank(int x, bool fl){
        return fl ? rank(x) : x - rank(x);
    }
};

#line 1 "lib/classes/waveletmatrix.cpp"
template <typename T, int W>
struct WaveletMatrix{

    array<BitVector, W> bv;
    array<int, W> zero_cnt;

    WaveletMatrix(vector<T>& a){
        int n = a.size();
        vector<T> v(a);
        for(int i = W - 1; i >= 0; --i){
            vector<uint64_t> b((n >> 6) + 1, 0);
            vector<T> v1, v2;
            for(int j = 0; j < n; ++j){
                ((v[j] >> i) & 1 ? v2 : v1).push_back(v[j]);
                b[j >> 6] |= uint64_t((v[j] >> i) & 1) << (j & 63);
            }
            for(int j = 0; j < v.size(); ++j)
                v[j] = (j < v1.size() ? v1[j] : v2[j - v1.size()]);
            bv[i].v = move(b);
            bv[i].build();
            zero_cnt[i] = bv[i].rank(n, 0);
        }
    }

    // [l, r)内のxの数
    int count(int l, int r, T x){
        for(int i = W - 1; i >= 0; --i){
            bool fl = (x >> i) & 1;
            int st = bv[i].rank(l, fl);
            int en = bv[i].rank(r, fl);
            l = (fl ? zero_cnt[i] : 0) + st;
            r = (fl ? zero_cnt[i] : 0) + en;
        }
        return r - l;
    }

    // [l, r)内で[0, x)を満たす値の数
    int count_lower(int l, int r, T x){
        int cnt = 0;
        for(int i = W - 1; i >= 0; --i){
            bool fl = (x >> i) & 1;
            int st = bv[i].rank(l, fl);
            int en = bv[i].rank(r, fl);
            if(fl){
                st += zero_cnt[i];
                en += zero_cnt[i];
                cnt += (bv[i].rank(r, 0) - bv[i].rank(l, 0));
            }
            l = st, r = en;
        }
        return cnt;
    }

    // [l, r)内で[x, y)を満たす値の数
    int count_range(int l, int r, T x, T y){
        return count_lower(l, r, y) - count_lower(l, r, x);
    }

    // 0-indexedでk番目に小さいものを返す
    T kth_min(int l, int r, int k){
        T ans = 0;
        for(int i = W - 1; i >= 0; --i){
            int st = bv[i].rank(l, 0);
            int en = bv[i].rank(r, 0);
            if(en - st <= k){
                k -= en - st;
                l = zero_cnt[i] + bv[i].rank(l, 1);
                r = zero_cnt[i] + bv[i].rank(r, 1);
                ans |= (1uLL << i);
            }
            else{
                l = st, r = en;
            }
        }
        return ans;
    }

    // [l, r)でのx以上最小値
    pair<T, bool> predecessor(int l, int r, T x){
        int idx = count_lower(l, r, x);
        if(idx == r - l){
            return make_pair((1uLL << W) - 1, false);
        }
        return make_pair(kth_min(l, r, idx), true);
    }

    // [l, r)でのx以下最大値
    pair<T, bool> successor(int l, int r, T x){
        int idx = count_lower(l, r, x + 1);
        if(idx == 0)
            return make_pair(0, false);
        return make_pair(kth_min(l, r, idx - 1), true);
    }
};

#line 9 "verify/static_rmq_wm.test.cpp"


signed main() {

    int n, q;
    scanf("%d%d", &n, &q);
    vector<int> a(n);
    for(auto& x : a)
        cin >> x;
    WaveletMatrix<int, 31> wm(a);
    for(int i = 0; i < q; ++i){
        int l, r;
        cin >> l >> r;
        cout << wm.kth_min(l, r, 0) << endl;
    }
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

