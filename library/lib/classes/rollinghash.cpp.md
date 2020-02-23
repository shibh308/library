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


# :warning: lib/classes/rollinghash.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/rollinghash.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-30 20:08:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <i64 mod1 = MOD, i64 mod2 = MOD + 2, i64 base = 10007, typename T = string>
struct RollingHash{

    using mint1 = ModInt<mod1>;
    using mint2 = ModInt<mod2>;
    using pair_type = pair<mint1, mint2>;
    int len;
    std::vector<pair_type> v;
    static std::vector<pair_type> power, inv;

    RollingHash(T s) :
    len(s.size())
    {
        v.assign(1, make_pair(mint1(0), mint2(0)));
        for(int i = 0; i < len; ++i){
            auto c = s[i];
            v.emplace_back(v.back().first + power[i].first * c,
                           v.back().second + power[i].second * c);
            if(static_cast<int>(power.size()) == i + 1){
                power.emplace_back(power.back().first * base,
                                   power.back().second * base);
                inv.emplace_back(mpow<mint1>(power.back().first, mod1 - 2),
                                 mpow<mint2>(power.back().second, mod2 - 2));
            }
        }
    };

    pair_type get(int l = 0, int r = -1){
        if(r == -1)
            r = len;
        assert(l <= r);
        assert(r <= len);
        auto l_cut = make_pair(v[r].first - v[l].first,
                               v[r].second - v[l].second);
        return make_pair(l_cut.first * inv[l].first,
                         l_cut.second * inv[l].second);
    }

    pair_type connect(pair_type l, pair_type r, int l_len){
        return make_pair(l.first + power[l_len].first * r.first,
                         l.second + power[l_len].second * r.second);
    }
};

using RH = RollingHash<MOD, MOD + 2, 10007>;
template<> vector<pair<ModInt<MOD>, ModInt<MOD + 2>>> RH::power = {make_pair(ModInt<MOD>(1), ModInt<MOD + 2>(1))};
template<> vector<pair<ModInt<MOD>, ModInt<MOD + 2>>> RH::inv = {make_pair(ModInt<MOD>(1), ModInt<MOD + 2>(1))};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/rollinghash.cpp"
template <i64 mod1 = MOD, i64 mod2 = MOD + 2, i64 base = 10007, typename T = string>
struct RollingHash{

    using mint1 = ModInt<mod1>;
    using mint2 = ModInt<mod2>;
    using pair_type = pair<mint1, mint2>;
    int len;
    std::vector<pair_type> v;
    static std::vector<pair_type> power, inv;

    RollingHash(T s) :
    len(s.size())
    {
        v.assign(1, make_pair(mint1(0), mint2(0)));
        for(int i = 0; i < len; ++i){
            auto c = s[i];
            v.emplace_back(v.back().first + power[i].first * c,
                           v.back().second + power[i].second * c);
            if(static_cast<int>(power.size()) == i + 1){
                power.emplace_back(power.back().first * base,
                                   power.back().second * base);
                inv.emplace_back(mpow<mint1>(power.back().first, mod1 - 2),
                                 mpow<mint2>(power.back().second, mod2 - 2));
            }
        }
    };

    pair_type get(int l = 0, int r = -1){
        if(r == -1)
            r = len;
        assert(l <= r);
        assert(r <= len);
        auto l_cut = make_pair(v[r].first - v[l].first,
                               v[r].second - v[l].second);
        return make_pair(l_cut.first * inv[l].first,
                         l_cut.second * inv[l].second);
    }

    pair_type connect(pair_type l, pair_type r, int l_len){
        return make_pair(l.first + power[l_len].first * r.first,
                         l.second + power[l_len].second * r.second);
    }
};

using RH = RollingHash<MOD, MOD + 2, 10007>;
template<> vector<pair<ModInt<MOD>, ModInt<MOD + 2>>> RH::power = {make_pair(ModInt<MOD>(1), ModInt<MOD + 2>(1))};
template<> vector<pair<ModInt<MOD>, ModInt<MOD + 2>>> RH::inv = {make_pair(ModInt<MOD>(1), ModInt<MOD + 2>(1))};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

