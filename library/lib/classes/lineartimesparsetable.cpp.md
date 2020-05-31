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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: lib/classes/lineartimesparsetable.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/lineartimesparsetable.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-31 22:09:43+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/multi_str_matching.test.cpp.html">verify/multi_str_matching.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/string_seatch.test.cpp.html">verify/string_seatch.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template<typename T>
struct LinearTimeSparseTable{
    int n, m;
    vector<T> a;
    SparseTable<T> b;
    vector<vector<uint32_t>> c;
    static constexpr uint32_t block = 32;
    LinearTimeSparseTable(vector<T>& v) : n(v.size()), a(v), m((n + block - 1) / block){
        n = m * block;
        v.resize(n, 0);
        vector<T> big_table(m);
        for(int i = 0; i < n; ++i)
            big_table[i / block] = (i & (block - 1) ? min(big_table[i / block], v[i]) : v[i]);
        b = SparseTable<T>(big_table, [](auto x, auto y){return min(x, y);});
        c.assign(m, vector<uint32_t>(block, 0));
        for(int i = 0; i < m; ++i){
            stack<pair<T, int>> st;
            vector<int> g(block, -1);
            for(int j = 0; j < block; ++j){
                T x = v[i * block + j];
                while(!st.empty() && x <= st.top().first)st.pop();
                if(!st.empty())
                    g[j] = st.top().second;
                st.emplace(x, j);
            }
            for(int j = 0; j < block; ++j){
                c[i][j] = (g[j] == -1 ? 0 : c[i][g[j]] | (1u << g[j]));
            }
        }
    }
    T get_small(int i, int j, int k){
        uint32_t w = c[k][j] & ~((1u << i) - 1);
        if(w == 0)
            return a[k * block + j];
        return a[k * block + (__builtin_ffs(w) - 1)];
    }
    T get(int l, int r){
        --r;
        int lb = l / block;
        int rb = r / block;
        int lc = l & (block - 1);
        int rc = r & (block - 1);
        if(lb == rb)
            return get_small(lc, rc, lb);
        T l_res = get_small(lc, block - 1, lb);
        T r_res = get_small(0, rc, rb);
        if(rb - lb == 1)
            return min(l_res, r_res);
        return min({l_res, r_res, b.get(lb + 1, rb)});
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/lineartimesparsetable.cpp"
template<typename T>
struct LinearTimeSparseTable{
    int n, m;
    vector<T> a;
    SparseTable<T> b;
    vector<vector<uint32_t>> c;
    static constexpr uint32_t block = 32;
    LinearTimeSparseTable(vector<T>& v) : n(v.size()), a(v), m((n + block - 1) / block){
        n = m * block;
        v.resize(n, 0);
        vector<T> big_table(m);
        for(int i = 0; i < n; ++i)
            big_table[i / block] = (i & (block - 1) ? min(big_table[i / block], v[i]) : v[i]);
        b = SparseTable<T>(big_table, [](auto x, auto y){return min(x, y);});
        c.assign(m, vector<uint32_t>(block, 0));
        for(int i = 0; i < m; ++i){
            stack<pair<T, int>> st;
            vector<int> g(block, -1);
            for(int j = 0; j < block; ++j){
                T x = v[i * block + j];
                while(!st.empty() && x <= st.top().first)st.pop();
                if(!st.empty())
                    g[j] = st.top().second;
                st.emplace(x, j);
            }
            for(int j = 0; j < block; ++j){
                c[i][j] = (g[j] == -1 ? 0 : c[i][g[j]] | (1u << g[j]));
            }
        }
    }
    T get_small(int i, int j, int k){
        uint32_t w = c[k][j] & ~((1u << i) - 1);
        if(w == 0)
            return a[k * block + j];
        return a[k * block + (__builtin_ffs(w) - 1)];
    }
    T get(int l, int r){
        --r;
        int lb = l / block;
        int rb = r / block;
        int lc = l & (block - 1);
        int rc = r & (block - 1);
        if(lb == rb)
            return get_small(lc, rc, lb);
        T l_res = get_small(lc, block - 1, lb);
        T r_res = get_small(0, rc, rb);
        if(rb - lb == 1)
            return min(l_res, r_res);
        return min({l_res, r_res, b.get(lb + 1, rb)});
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

