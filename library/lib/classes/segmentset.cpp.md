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


# :warning: lib/classes/segmentset.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/segmentset.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-25 22:20:24+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct SegmentSet{
    set<pair<T, T>> s;
    set<pair<T, T>> s_rev;
    SegmentSet(){}
    // [l, r)を追加する
    void insert(T l, T r){
        auto iter = get(l).second;
        if(iter != s.end() && iter->first <= l && r <= iter->second)
            return;
        vector<pair<T, T>> erase_elm;
        for(auto it = s.lower_bound(make_pair(l, numeric_limits<T>::min())); it != s.end() && it->first <= r; ++it)
            erase_elm.emplace_back(*it);
        for(auto it = s_rev.lower_bound(make_pair(l, numeric_limits<T>::min())); it != s_rev.end() && it->first <= r; ++it)
            erase_elm.emplace_back(it->second, it->first);
        for(auto& p : erase_elm){
            chmin(l, p.first);
            chmax(r, p.second);
            s.erase(p);
            s_rev.erase(make_pair(p.second, p.first));
        }
        s.emplace(l, r);
        s_rev.emplace(r, l);
    }
    // xが含まれるような区間を返す
    pair<bool, typename set<pair<T, T>>::const_iterator> get(T x){
        auto it = s.lower_bound(make_pair(x, numeric_limits<T>::min()));
        if(it != s.begin())
            --it;
        return make_pair(x < it->second, it);
    }
    set<pair<T, T>>& operator*(){return s;}
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/segmentset.cpp"
template <typename T>
struct SegmentSet{
    set<pair<T, T>> s;
    set<pair<T, T>> s_rev;
    SegmentSet(){}
    // [l, r)を追加する
    void insert(T l, T r){
        auto iter = get(l).second;
        if(iter != s.end() && iter->first <= l && r <= iter->second)
            return;
        vector<pair<T, T>> erase_elm;
        for(auto it = s.lower_bound(make_pair(l, numeric_limits<T>::min())); it != s.end() && it->first <= r; ++it)
            erase_elm.emplace_back(*it);
        for(auto it = s_rev.lower_bound(make_pair(l, numeric_limits<T>::min())); it != s_rev.end() && it->first <= r; ++it)
            erase_elm.emplace_back(it->second, it->first);
        for(auto& p : erase_elm){
            chmin(l, p.first);
            chmax(r, p.second);
            s.erase(p);
            s_rev.erase(make_pair(p.second, p.first));
        }
        s.emplace(l, r);
        s_rev.emplace(r, l);
    }
    // xが含まれるような区間を返す
    pair<bool, typename set<pair<T, T>>::const_iterator> get(T x){
        auto it = s.lower_bound(make_pair(x, numeric_limits<T>::min()));
        if(it != s.begin())
            --it;
        return make_pair(x < it->second, it);
    }
    set<pair<T, T>>& operator*(){return s;}
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

