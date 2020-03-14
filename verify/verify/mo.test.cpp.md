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


# :heavy_check_mark: verify/mo.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/mo.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 14:01:09+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/mo.cpp.html">lib/classes/mo.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;


#include "../lib/classes/mo.cpp"

signed main(){
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(k), b(k);
    for(int i = 0; i < k; ++i){
        cin >> a[i] >> b[i];
        --a[i], --b[i];
    }
    constexpr int packet = 512;
    constexpr int size = (100000 + packet - 1) / packet;

    vector<vector<pair<int,int>>> queries(size);

    vector<int> type(q), s(q), t(q), x(q);
    for(int i = 0; i < q; ++i){
        cin >> type[i] >> s[i] >> t[i] >> x[i];
        --s[i], --x[i];
        queries[s[i] / packet].emplace_back(t[i], i);
    }
    for(int i = 0; i < size; ++i)
        sort(queries[i].begin(), queries[i].end());


    vector<int> data(n), idxes(n);
    iota(data.begin(), data.end(), 0);
    iota(idxes.begin(), idxes.end(), 0);
    auto right_f = [&](int idx){
        if(idx >= k)
            return;
        swap(data[a[idx]], data[b[idx]]);
        idxes[data[a[idx]]] = a[idx];
        idxes[data[b[idx]]] = b[idx];
    };
    auto left_f = [&](int idx){
        if(idx >= k)
            return;
        swap(data[idxes[a[idx]]], data[idxes[b[idx]]]);
        int idx_1 = idxes[a[idx]];
        int data_idx_1 = data[idx_1];
        int idx_2 = idxes[b[idx]];
        int data_idx_2 = data[idx_2];
        idxes[data_idx_1] = idx_1;
        idxes[data_idx_2] = idx_2;
    };
    Mo mo(left_f, left_f, right_f, right_f);

    vector<int> ans(q, -1);

    for(int i = 0; i < size; ++i){
        mo.move(i * packet, i * packet);
        for(auto& query : queries[i]){
            int idx = query.second;
            int next_l = s[idx];
            int next_r = t[idx];
            int ty = type[idx];
            int val = x[idx];
            mo.move(next_l, next_r);

            if(ty == 1){
                ans[idx] = data[val];
            }
            else{
                ans[idx] = idxes[val];
            }
        }
    }

    for(int i = 0; i < q; ++i)
        cout << ans[i] + 1 << endl;

    return 0;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/mo.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;


#line 1 "verify/../lib/classes/mo.cpp"
struct Mo{
    int l, r;
    function<void(int)> left_add, left_erase, right_add, right_erase;
    Mo(function<void(int)> left_add, function<void(int)> left_erase,
       function<void(int)> right_add, function<void(int)> right_erase,
       int sl = 0, int sr = 0) :
       l(sl), r(sr), left_add(left_add), left_erase(left_erase), right_add(right_add), right_erase(right_erase){}
    void move(int next_l, int next_r){
        for(int i = l; i < next_l; ++i)
            left_erase(i);
        for(int i = l - 1; i >= next_l; --i)
            left_add(i);
        for(int i = r; i < next_r; ++i)
            right_add(i);
        for(int i = r - 1; i >= next_r; --i)
            right_erase(i);
        l = next_l, r = next_r;
    }
};

#line 10 "verify/mo.test.cpp"

signed main(){
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(k), b(k);
    for(int i = 0; i < k; ++i){
        cin >> a[i] >> b[i];
        --a[i], --b[i];
    }
    constexpr int packet = 512;
    constexpr int size = (100000 + packet - 1) / packet;

    vector<vector<pair<int,int>>> queries(size);

    vector<int> type(q), s(q), t(q), x(q);
    for(int i = 0; i < q; ++i){
        cin >> type[i] >> s[i] >> t[i] >> x[i];
        --s[i], --x[i];
        queries[s[i] / packet].emplace_back(t[i], i);
    }
    for(int i = 0; i < size; ++i)
        sort(queries[i].begin(), queries[i].end());


    vector<int> data(n), idxes(n);
    iota(data.begin(), data.end(), 0);
    iota(idxes.begin(), idxes.end(), 0);
    auto right_f = [&](int idx){
        if(idx >= k)
            return;
        swap(data[a[idx]], data[b[idx]]);
        idxes[data[a[idx]]] = a[idx];
        idxes[data[b[idx]]] = b[idx];
    };
    auto left_f = [&](int idx){
        if(idx >= k)
            return;
        swap(data[idxes[a[idx]]], data[idxes[b[idx]]]);
        int idx_1 = idxes[a[idx]];
        int data_idx_1 = data[idx_1];
        int idx_2 = idxes[b[idx]];
        int data_idx_2 = data[idx_2];
        idxes[data_idx_1] = idx_1;
        idxes[data_idx_2] = idx_2;
    };
    Mo mo(left_f, left_f, right_f, right_f);

    vector<int> ans(q, -1);

    for(int i = 0; i < size; ++i){
        mo.move(i * packet, i * packet);
        for(auto& query : queries[i]){
            int idx = query.second;
            int next_l = s[idx];
            int next_r = t[idx];
            int ty = type[idx];
            int val = x[idx];
            mo.move(next_l, next_r);

            if(ty == 1){
                ans[idx] = data[val];
            }
            else{
                ans[idx] = idxes[val];
            }
        }
    }

    for(int i = 0; i < q; ++i)
        cout << ans[i] + 1 << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

