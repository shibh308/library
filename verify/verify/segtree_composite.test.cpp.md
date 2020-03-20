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


# :heavy_check_mark: verify/segtree_composite.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/segtree_composite.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-14 13:02:42+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_set_range_composite">https://judge.yosupo.jp/problem/point_set_range_composite</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/modint.cpp.html">lib/classes/modint.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/segtree.cpp.html">lib/classes/segtree.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 998244353;

#include "../lib/classes/modint.cpp"
#include "../lib/classes/segtree.cpp"


signed main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> b(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];
    vector<pair<mint,mint>> v(n);
    for(int i = 0; i < n; ++i)
        v[i] = make_pair(a[i], b[i]);
    auto func = [](auto p1, auto p2){
        mint a = p1.first;
        mint b = p1.second;
        mint c = p2.first;
        mint d = p2.second;
        return make_pair(c * a, c * b + d);
    };
    Segtree<pair<mint,mint>> seg(n, v, func, make_pair(1, 0));
    for(int i = 0; i < q; ++i){
        int type;
        cin >> type;
        if(type == 0){
            int p, c, d;
            cin >> p >> c >> d;
            seg.set(p, make_pair(c, d));
        }
        else{
            int l, r, x;
            cin >> l >> r >> x;
            auto ret = seg.get(l, r);
            cout << ret.first * x + ret.second << endl;
        }
    }
    return 0;
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/segtree_composite.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_set_range_composite"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

const i64 MOD = 998244353;

#line 1 "lib/classes/modint.cpp"
template <i64 mod = MOD>
struct ModInt{
    i64 p;

    ModInt() : p(0){}
    ModInt(i64 x){p = x >= 0 ? x % mod : x + (-x + mod - 1) / mod * mod;}

    ModInt& operator+=(const ModInt& y){p = p + *y - ((p + *y) >= mod ? mod : 0); return *this;}
    ModInt& operator-=(const ModInt& y){p = p - *y + (p - *y < 0 ? mod : 0); return *this;}
    ModInt& operator*=(const ModInt& y){p = (p * *y) % mod; return *this;}
    ModInt& operator%=(const ModInt& y){if(y)p %= *y; return *this;}

    ModInt operator+(const ModInt& y) const{ModInt x = *this; return x += y;}
    ModInt operator-(const ModInt& y) const{ModInt x = *this; return x -= y;}
    ModInt operator*(const ModInt& y) const{ModInt x = *this; return x *= y;}
    ModInt operator%(const ModInt& y) const{ModInt x = *this; return x %= y;}

    friend ostream& operator<<(ostream& stream, const ModInt<mod>& x){
        stream << *x;
        return stream;
    }

    friend ostream& operator>>(ostream& stream, const ModInt<mod>& x){
        stream >> *x;
        return stream;
    }

    ModInt& operator++(){p = (p + 1) % mod; return *this;}
    ModInt& operator--(){p = (p - 1 + mod) % mod; return *this;}

    bool operator==(const ModInt& y) const{return p == *y;}
    bool operator!=(const ModInt& y) const{return p != *y;}

    const i64& operator*() const{return p;}
    i64& operator*(){return p;}

};

using mint = ModInt<>;

#line 1 "lib/classes/segtree.cpp"
template<typename T>
struct Segtree{
    int n;
    T op;
    vector<T> elm;
    function<T(T, T)> f;

    Segtree(int n, T init, function<T(T, T)> f, T op = T()) :
        n(n),
        op(op),
        elm(2 * n, init),
        f(f)
    {
        for(int i = n - 1; i >= 1; --i)
            elm[i] = f(elm[2 * i], elm[2 * i + 1]);
    }

    Segtree(int n, vector<T> init, function<T(T, T)> f, T op = T()) :
        n(n),
        op(op),
        elm(2 * n),
        f(f)
    {
        for(int i = 0; i < n; ++i)
            elm[i + n] = init[i];
        for(int i = n - 1; i >= 1; --i)
            elm[i] = f(elm[2 * i], elm[2 * i + 1]);
    }

    void set(int x, T val){
        x += n;
        elm[x] = val;
        while(x >>= 1)
            elm[x] = f(elm[2 * x], elm[2 * x + 1]);
    }

    void update(int x, T val){
        x += n;
        elm[x] = f(elm[x], val);
        while(x >>= 1)
            elm[x] = f(elm[2 * x], elm[2 * x + 1]);
    }

    T get(int x, int y) const{
        T l = op, r = op;
        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){
            if(x & 1)
                l = f(l, elm[x++]);
            if(!(y & 1))
                r = f(elm[y--], r);
        }
        return f(l, r);
    }
};

#line 12 "verify/segtree_composite.test.cpp"


signed main(){
    int n, q;
    cin >> n >> q;
    vector<int> a(n);
    vector<int> b(n);
    for(int i = 0; i < n; ++i)
        cin >> a[i] >> b[i];
    vector<pair<mint,mint>> v(n);
    for(int i = 0; i < n; ++i)
        v[i] = make_pair(a[i], b[i]);
    auto func = [](auto p1, auto p2){
        mint a = p1.first;
        mint b = p1.second;
        mint c = p2.first;
        mint d = p2.second;
        return make_pair(c * a, c * b + d);
    };
    Segtree<pair<mint,mint>> seg(n, v, func, make_pair(1, 0));
    for(int i = 0; i < q; ++i){
        int type;
        cin >> type;
        if(type == 0){
            int p, c, d;
            cin >> p >> c >> d;
            seg.set(p, make_pair(c, d));
        }
        else{
            int l, r, x;
            cin >> l >> r >> x;
            auto ret = seg.get(l, r);
            cout << ret.first * x + ret.second << endl;
        }
    }
    return 0;
}


```
{% endraw %}

<a href="../../index.html">Back to top page</a>

