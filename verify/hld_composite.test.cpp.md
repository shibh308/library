---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/heavylightdecomposition.cpp
    title: lib/classes/heavylightdecomposition.cpp
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
    PROBLEM: https://judge.yosupo.jp/problem/vertex_set_path_composite
    links:
    - https://judge.yosupo.jp/problem/vertex_set_path_composite
  bundledCode: "#line 1 \"verify/hld_composite.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \nconst i64 MOD = 998244353;\n\ntemplate <typename T>\nbool chmax(T& x, T y){\n\
    \    if(x < y){\n        x = y;\n        return true;\n    }\n    return false;\n\
    }\n\n#line 1 \"lib/classes/heavylightdecomposition.cpp\"\nstruct HeavyLightDecomposition{\n\
    \    int n;\n    vector<int> size, par, in, in_rev, heavy_root, depth, heavy_depth,\
    \ out;\n    vector<vector<int>> childs;\n    HeavyLightDecomposition(vector<vector<int>>&\
    \ edges, int root = 0) : n(edges.size()), size(n, 1), par(n, -2), depth(n, 0),\
    \ childs(n), in(n), in_rev(n), heavy_root(n), heavy_depth(n, 0), out(n){\n   \
    \     function<void(int)> swap_dfs = [&](int x){\n            int size_max = 0;\n\
    \            int max_idx = 0;\n            for(int i = 0; i < edges[x].size();\
    \ ++i){\n                int y = edges[x][i];\n                if(par[y] == -2){\n\
    \                    par[y] = x;\n                    depth[y] = depth[x] + 1;\n\
    \                    childs[x].push_back(y);\n                    swap_dfs(y);\n\
    \                    size[x] += size[y];\n                    if(chmax(size_max,\
    \ size[y])){\n                        max_idx = childs[x].size() - 1;\n      \
    \              }\n                }\n            }\n            if(max_idx){\n\
    \                swap(childs[x][0], childs[x][max_idx]);\n            }\n    \
    \    };\n        par[root] = -1;\n        swap_dfs(root);\n\n        int cnt =\
    \ 0;\n        function<void(int,int)> dfs = [&](int x, int segment_root){\n  \
    \          heavy_root[x] = segment_root;\n            in_rev[cnt] = x;\n     \
    \       in[x] = cnt++;\n            for(int i = 0; i < childs[x].size(); ++i){\n\
    \                int y = childs[x][i];\n                if(i == 0){\n        \
    \            dfs(y, segment_root);\n                }\n                else{\n\
    \                    heavy_depth[y] = heavy_depth[segment_root] + 1;\n       \
    \             dfs(y, y);\n                }\n            }\n            out[x]\
    \ = cnt;\n        };\n        dfs(root, root);\n    }\n    int lca(int x, int\
    \ y){\n        while(heavy_root[x] != heavy_root[y]){\n            if(heavy_depth[heavy_root[x]]\
    \ > heavy_depth[heavy_root[y]])\n                swap(x, y);\n            y =\
    \ par[heavy_root[y]];\n        }\n        return depth[x] < depth[y] ? x : y;\n\
    \    }\n    // x\u4EE5\u4E0B\u306E\u90E8\u5206\u6728\u3092\u8FD4\u3059\n    pair<int,int>\
    \ subtree(int x){\n        return make_pair(in[x], out[x]);\n    }\n    // x-z\u306E\
    \u30D1\u30B9\u3068y-z\u306E\u30D1\u30B9\u3092\u8FD4\u3059(\u4E21\u65B9\u3068\u3082\
    \u6839\u5074\u306B\u9032\u3080\u306E\u3067\u6CE8\u610F)\n    // \u305D\u308C\u305E\
    \u308C\u306EHeavy-Path\u306F\u6839\u5074\u306E\u65B9\u304Cindex\u304C\u5C0F\u3055\
    \u3044\u306E\u3067\u6CE8\u610F(\u53EF\u63DB\u30AF\u30A8\u30EA\u51E6\u7406\u3067\
    \u6C17\u3092\u3064\u3051\u308B)\n    pair<vector<pair<int,int>>, vector<pair<int,int>>>\
    \ two_point_path(int x, int y){\n        vector<pair<int,int>> xz, yz;\n     \
    \   int z = lca(x, y);\n        while(heavy_root[x] != heavy_root[z]){\n     \
    \       xz.emplace_back(in[heavy_root[x]], in[x] + 1);\n            x = par[heavy_root[x]];\n\
    \        }\n        while(heavy_root[y] != heavy_root[z]){\n            yz.emplace_back(in[heavy_root[y]],\
    \ in[y] + 1);\n            y = par[heavy_root[y]];\n        }\n        // \u8FBA\
    \u5C5E\u6027\u306B\u3057\u305F\u3044\u5834\u5408\u306F\u3053\u3053\u3092in[z]\
    \ + 1, in[x] + 1\u306B\u3059\u308B\n        xz.emplace_back(in[z], in[x] + 1);\n\
    \        yz.emplace_back(in[z] + 1, in[y] + 1);\n        return make_pair(xz,\
    \ yz);\n    }\n    // \u9802\u70B9x\u304CEuler-Tour\u4E0A\u3067\u4F55\u756A\u76EE\
    \u306B\u4F4D\u7F6E\u3059\u308B\u304B\u3092\u8FD4\u3059\n    // in[\u5143\u306E\
    \u9802\u70B9index] = \u5185\u90E8\u3067\u306Eindex\n    // in_rev[\u5185\u90E8\
    \u3067\u306Eindex] = \u5143\u306E\u9802\u70B9index\n    int get_idx(int x){\n\
    \        return in[x];\n    }\n    // x\u304C\u5C5E\u3059\u308BHeavy-Path\u306E\
    \u6DF1\u3055\u3092\u8FD4\u3059\n    int get_heavy_depth(int x){\n        return\
    \ heavy_depth[heavy_root[x]];\n    }\n};\n\n#line 1 \"lib/classes/modint.cpp\"\
    \ntemplate <i64 mod = MOD>\nstruct ModInt{\n    i64 p;\n\n    ModInt() : p(0){}\n\
    \    ModInt(i64 x){p = x >= 0 ? x % mod : x + (-x + mod - 1) / mod * mod;}\n\n\
    \    ModInt& operator+=(const ModInt& y){p = p + *y - ((p + *y) >= mod ? mod :\
    \ 0); return *this;}\n    ModInt& operator-=(const ModInt& y){p = p - *y + (p\
    \ - *y < 0 ? mod : 0); return *this;}\n    ModInt& operator*=(const ModInt& y){p\
    \ = (p * *y) % mod; return *this;}\n    ModInt& operator%=(const ModInt& y){if(y)p\
    \ %= *y; return *this;}\n\n    ModInt operator+(const ModInt& y) const{ModInt\
    \ x = *this; return x += y;}\n    ModInt operator-(const ModInt& y) const{ModInt\
    \ x = *this; return x -= y;}\n    ModInt operator*(const ModInt& y) const{ModInt\
    \ x = *this; return x *= y;}\n    ModInt operator%(const ModInt& y) const{ModInt\
    \ x = *this; return x %= y;}\n\n    friend ostream& operator<<(ostream& stream,\
    \ const ModInt<mod>& x){\n        stream << *x;\n        return stream;\n    }\n\
    \n    friend ostream& operator>>(ostream& stream, const ModInt<mod>& x){\n   \
    \     stream >> *x;\n        return stream;\n    }\n\n    ModInt& operator++(){p\
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
    \ }\n};\n\n#line 22 \"verify/hld_composite.test.cpp\"\n\n\nsigned main(){\n  \
    \  int n, q;\n    cin >> n >> q;\n    vector<int> a(n);\n    vector<int> b(n);\n\
    \    for(int i = 0; i < n; ++i)\n        cin >> a[i] >> b[i];\n    vector<vector<int>>\
    \ edges(n);\n    for(int i = 0; i < n - 1; ++i){\n        int u, v;\n        cin\
    \ >> u >> v;\n        edges[u].push_back(v);\n        edges[v].push_back(u);\n\
    \    }\n    HeavyLightDecomposition hld(edges);\n    vector<pair<mint, mint>>\
    \ v(n);\n    for(int i = 0; i < n; ++i)\n        v[hld.get_idx(i)] = make_pair(a[i],\
    \ b[i]);\n    auto func = [](auto p1, auto p2){\n        mint a = p1.first;\n\
    \        mint b = p1.second;\n        mint c = p2.first;\n        mint d = p2.second;\n\
    \        return make_pair(c * a, c * b + d);\n    };\n\n    Segtree<pair<mint,mint>>\
    \ seg(n, v, func, make_pair(1, 0));\n    Segtree<pair<mint,mint>> seg_rev(n, v,\
    \ [&func](auto x, auto y){return func(y, x);}, make_pair(1, 0));\n    for(int\
    \ i = 0; i < q; ++i){\n        int type;\n        cin >> type;\n        if(type\
    \ == 0){\n            int p, c, d;\n            cin >> p >> c >> d;\n        \
    \    seg.set(hld.get_idx(p), make_pair(c, d));\n            seg_rev.set(hld.get_idx(p),\
    \ make_pair(c, d));\n        }\n        else{\n            int u, v, x;\n    \
    \        cin >> u >> v >> x;\n            auto res = hld.two_point_path(u, v);\n\
    \            pair<mint,mint> l(1, 0), r(1, 0);\n            for(auto p : res.first){\n\
    \                l = func(l, seg_rev.get(p.first, p.second));\n            }\n\
    \            for(auto p : res.second){\n                r = func(seg.get(p.first,\
    \ p.second), r);\n            }\n            auto ret = func(l, r);\n        \
    \    cout << ret.first * x + ret.second << endl;\n        }\n    }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_set_path_composite\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \nconst i64 MOD = 998244353;\n\ntemplate <typename T>\nbool chmax(T& x, T y){\n\
    \    if(x < y){\n        x = y;\n        return true;\n    }\n    return false;\n\
    }\n\n#include \"../lib/classes/heavylightdecomposition.cpp\"\n#include \"../lib/classes/modint.cpp\"\
    \n#include \"../lib/classes/segtree.cpp\"\n\n\nsigned main(){\n    int n, q;\n\
    \    cin >> n >> q;\n    vector<int> a(n);\n    vector<int> b(n);\n    for(int\
    \ i = 0; i < n; ++i)\n        cin >> a[i] >> b[i];\n    vector<vector<int>> edges(n);\n\
    \    for(int i = 0; i < n - 1; ++i){\n        int u, v;\n        cin >> u >> v;\n\
    \        edges[u].push_back(v);\n        edges[v].push_back(u);\n    }\n    HeavyLightDecomposition\
    \ hld(edges);\n    vector<pair<mint, mint>> v(n);\n    for(int i = 0; i < n; ++i)\n\
    \        v[hld.get_idx(i)] = make_pair(a[i], b[i]);\n    auto func = [](auto p1,\
    \ auto p2){\n        mint a = p1.first;\n        mint b = p1.second;\n       \
    \ mint c = p2.first;\n        mint d = p2.second;\n        return make_pair(c\
    \ * a, c * b + d);\n    };\n\n    Segtree<pair<mint,mint>> seg(n, v, func, make_pair(1,\
    \ 0));\n    Segtree<pair<mint,mint>> seg_rev(n, v, [&func](auto x, auto y){return\
    \ func(y, x);}, make_pair(1, 0));\n    for(int i = 0; i < q; ++i){\n        int\
    \ type;\n        cin >> type;\n        if(type == 0){\n            int p, c, d;\n\
    \            cin >> p >> c >> d;\n            seg.set(hld.get_idx(p), make_pair(c,\
    \ d));\n            seg_rev.set(hld.get_idx(p), make_pair(c, d));\n        }\n\
    \        else{\n            int u, v, x;\n            cin >> u >> v >> x;\n  \
    \          auto res = hld.two_point_path(u, v);\n            pair<mint,mint> l(1,\
    \ 0), r(1, 0);\n            for(auto p : res.first){\n                l = func(l,\
    \ seg_rev.get(p.first, p.second));\n            }\n            for(auto p : res.second){\n\
    \                r = func(seg.get(p.first, p.second), r);\n            }\n   \
    \         auto ret = func(l, r);\n            cout << ret.first * x + ret.second\
    \ << endl;\n        }\n    }\n}\n\n"
  dependsOn:
  - lib/classes/heavylightdecomposition.cpp
  - lib/classes/modint.cpp
  - lib/classes/segtree.cpp
  isVerificationFile: true
  path: verify/hld_composite.test.cpp
  requiredBy: []
  timestamp: '2020-03-14 13:59:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/hld_composite.test.cpp
layout: document
redirect_from:
- /verify/verify/hld_composite.test.cpp
- /verify/verify/hld_composite.test.cpp.html
title: verify/hld_composite.test.cpp
---
