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


# :heavy_check_mark: verify/mo_query.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/mo_query.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-03 20:06:33+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/mo.cpp.html">lib/classes/mo.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/functions/mo_query.cpp.html">lib/functions/mo_query.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 1e9 + 7;
const i64 INF = i64(1e18) + 7;

template <typename T>
bool chmin(T& x, T y){
    if(x > y){
        x = y;
        return true;
    }
    return false;
}

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


#include "../lib/classes/mo.cpp"
#include "../lib/functions/mo_query.cpp"


signed main(){
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(k), b(k);
    for(int i = 0; i < k; ++i){
        cin >> a[i] >> b[i];
        --a[i], --b[i];
    }

    vector<pair<int,int>> queries;
    vector<int> type(q), s(q), t(q), x(q);
    for(int i = 0; i < q; ++i){
        cin >> type[i] >> s[i] >> t[i] >> x[i];
        --s[i], --x[i];
        queries.emplace_back(s[i], t[i]);
    }

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
    auto ans = mo_query<int>(mo, queries, [&](int idx){return type[idx] == 1 ? data[x[idx]] : idxes[x[idx]];});

    for(int i = 0; i < q; ++i)
        cout << ans[i] + 1 << endl;

    return 0;
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/mo_query.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 1e9 + 7;
const i64 INF = i64(1e18) + 7;

template <typename T>
bool chmin(T& x, T y){
    if(x > y){
        x = y;
        return true;
    }
    return false;
}

template <typename T>
bool chmax(T& x, T y){
    if(x < y){
        x = y;
        return true;
    }
    return false;
}


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

#line 1 "verify/../lib/functions/mo_query.cpp"
template <typename ResultType>
vector<ResultType> mo_query(Mo& mo, vector<pair<int,int>>& queries, function<ResultType(int)> get_func, int packet=512){
    int q = queries.size();
    vector<tuple<int,int,int>> sort_queries;
    for(int i = 0; i < q; ++i)
        sort_queries.emplace_back(queries[i].first / packet, queries[i].second, i);
    sort(sort_queries.begin(), sort_queries.end());
    vector<ResultType> ans(q);
    for(auto& query : sort_queries){
        int idx = get<2>(query);
        mo.move(queries[idx].first, queries[idx].second);
        ans[idx] = get_func(idx);
    }
    return ans;
}

#line 32 "verify/mo_query.test.cpp"


signed main(){
    int n, k, q;
    cin >> n >> k >> q;
    vector<int> a(k), b(k);
    for(int i = 0; i < k; ++i){
        cin >> a[i] >> b[i];
        --a[i], --b[i];
    }

    vector<pair<int,int>> queries;
    vector<int> type(q), s(q), t(q), x(q);
    for(int i = 0; i < q; ++i){
        cin >> type[i] >> s[i] >> t[i] >> x[i];
        --s[i], --x[i];
        queries.emplace_back(s[i], t[i]);
    }

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
    auto ans = mo_query<int>(mo, queries, [&](int idx){return type[idx] == 1 ? data[x[idx]] : idxes[x[idx]];});

    for(int i = 0; i < q; ++i)
        cout << ans[i] + 1 << endl;

    return 0;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

