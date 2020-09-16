---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/modint.cpp
    title: lib/classes/modint.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/segtree.cpp
    title: lib/classes/segtree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "#line 1 \"verify/segtree_composite.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/point_set_range_composite\"\n#include <bits/stdc++.h>\n\
    \nusing namespace std;\n\nusing i64 = long long;\n\nconst i64 MOD = 998244353;\n\
    \n#line 1 \"lib/classes/modint.cpp\"\ntemplate <i64 mod = MOD>\nstruct ModInt{\n\
    \    i64 p;\n\n    ModInt() : p(0){}\n    ModInt(i64 x){p = x >= 0 ? x % mod :\
    \ x + (-x + mod - 1) / mod * mod;}\n\n    ModInt& operator+=(const ModInt& y){p\
    \ = p + *y - ((p + *y) >= mod ? mod : 0); return *this;}\n    ModInt& operator-=(const\
    \ ModInt& y){p = p - *y + (p - *y < 0 ? mod : 0); return *this;}\n    ModInt&\
    \ operator*=(const ModInt& y){p = (p * *y) % mod; return *this;}\n    ModInt&\
    \ operator%=(const ModInt& y){if(y)p %= *y; return *this;}\n\n    ModInt operator+(const\
    \ ModInt& y) const{ModInt x = *this; return x += y;}\n    ModInt operator-(const\
    \ ModInt& y) const{ModInt x = *this; return x -= y;}\n    ModInt operator*(const\
    \ ModInt& y) const{ModInt x = *this; return x *= y;}\n    ModInt operator%(const\
    \ ModInt& y) const{ModInt x = *this; return x %= y;}\n\n    friend ostream& operator<<(ostream&\
    \ stream, const ModInt<mod>& x){\n        stream << *x;\n        return stream;\n\
    \    }\n\n    friend ostream& operator>>(ostream& stream, const ModInt<mod>& x){\n\
    \        stream >> *x;\n        return stream;\n    }\n\n    ModInt& operator++(){p\
    \ = (p + 1) % mod; return *this;}\n    ModInt& operator--(){p = (p - 1 + mod)\
    \ % mod; return *this;}\n\n    bool operator==(const ModInt& y) const{return p\
    \ == *y;}\n    bool operator!=(const ModInt& y) const{return p != *y;}\n\n   \
    \ const i64& operator*() const{return p;}\n    i64& operator*(){return p;}\n\n\
    };\n\nusing mint = ModInt<>;\n\n#line 1 \"lib/classes/segtree.cpp\"\ntemplate<typename\
    \ T>\nstruct Segtree{\n    int n;\n    T op;\n    vector<T> elm;\n    function<T(T,\
    \ T)> f;\n\n    Segtree(int n, T init, function<T(T, T)> f, T op = T()) :\n  \
    \      n(n),\n        op(op),\n        elm(2 * n, init),\n        f(f)\n    {\n\
    \        for(int i = n - 1; i >= 1; --i)\n            elm[i] = f(elm[2 * i], elm[2\
    \ * i + 1]);\n    }\n\n    Segtree(int n, vector<T> init, function<T(T, T)> f,\
    \ T op = T()) :\n        n(n),\n        op(op),\n        elm(2 * n),\n       \
    \ f(f)\n    {\n        for(int i = 0; i < n; ++i)\n            elm[i + n] = init[i];\n\
    \        for(int i = n - 1; i >= 1; --i)\n            elm[i] = f(elm[2 * i], elm[2\
    \ * i + 1]);\n    }\n\n    void set(int x, T val){\n        x += n;\n        elm[x]\
    \ = val;\n        while(x >>= 1)\n            elm[x] = f(elm[2 * x], elm[2 * x\
    \ + 1]);\n    }\n\n    void update(int x, T val){\n        x += n;\n        elm[x]\
    \ = f(elm[x], val);\n        while(x >>= 1)\n            elm[x] = f(elm[2 * x],\
    \ elm[2 * x + 1]);\n    }\n\n    T get(int x, int y) const{\n        T l = op,\
    \ r = op;\n        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){\n      \
    \      if(x & 1)\n                l = f(l, elm[x++]);\n            if(!(y & 1))\n\
    \                r = f(elm[y--], r);\n        }\n        return f(l, r);\n   \
    \ }\n};\n\n#line 12 \"verify/segtree_composite.test.cpp\"\n\n\nsigned main(){\n\
    \    int n, q;\n    cin >> n >> q;\n    vector<int> a(n);\n    vector<int> b(n);\n\
    \    for(int i = 0; i < n; ++i)\n        cin >> a[i] >> b[i];\n    vector<pair<mint,mint>>\
    \ v(n);\n    for(int i = 0; i < n; ++i)\n        v[i] = make_pair(a[i], b[i]);\n\
    \    auto func = [](auto p1, auto p2){\n        mint a = p1.first;\n        mint\
    \ b = p1.second;\n        mint c = p2.first;\n        mint d = p2.second;\n  \
    \      return make_pair(c * a, c * b + d);\n    };\n    Segtree<pair<mint,mint>>\
    \ seg(n, v, func, make_pair(1, 0));\n    for(int i = 0; i < q; ++i){\n       \
    \ int type;\n        cin >> type;\n        if(type == 0){\n            int p,\
    \ c, d;\n            cin >> p >> c >> d;\n            seg.set(p, make_pair(c,\
    \ d));\n        }\n        else{\n            int l, r, x;\n            cin >>\
    \ l >> r >> x;\n            auto ret = seg.get(l, r);\n            cout << ret.first\
    \ * x + ret.second << endl;\n        }\n    }\n    return 0;\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \nconst i64 MOD = 998244353;\n\n#include \"../lib/classes/modint.cpp\"\n#include\
    \ \"../lib/classes/segtree.cpp\"\n\n\nsigned main(){\n    int n, q;\n    cin >>\
    \ n >> q;\n    vector<int> a(n);\n    vector<int> b(n);\n    for(int i = 0; i\
    \ < n; ++i)\n        cin >> a[i] >> b[i];\n    vector<pair<mint,mint>> v(n);\n\
    \    for(int i = 0; i < n; ++i)\n        v[i] = make_pair(a[i], b[i]);\n    auto\
    \ func = [](auto p1, auto p2){\n        mint a = p1.first;\n        mint b = p1.second;\n\
    \        mint c = p2.first;\n        mint d = p2.second;\n        return make_pair(c\
    \ * a, c * b + d);\n    };\n    Segtree<pair<mint,mint>> seg(n, v, func, make_pair(1,\
    \ 0));\n    for(int i = 0; i < q; ++i){\n        int type;\n        cin >> type;\n\
    \        if(type == 0){\n            int p, c, d;\n            cin >> p >> c >>\
    \ d;\n            seg.set(p, make_pair(c, d));\n        }\n        else{\n   \
    \         int l, r, x;\n            cin >> l >> r >> x;\n            auto ret\
    \ = seg.get(l, r);\n            cout << ret.first * x + ret.second << endl;\n\
    \        }\n    }\n    return 0;\n}\n\n"
  dependsOn:
  - lib/classes/modint.cpp
  - lib/classes/segtree.cpp
  isVerificationFile: true
  path: verify/segtree_composite.test.cpp
  requiredBy: []
  timestamp: '2020-03-14 13:02:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/segtree_composite.test.cpp
layout: document
redirect_from:
- /verify/verify/segtree_composite.test.cpp
- /verify/verify/segtree_composite.test.cpp.html
title: verify/segtree_composite.test.cpp
---
