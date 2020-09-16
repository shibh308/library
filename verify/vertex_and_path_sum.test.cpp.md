---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/segtree.cpp
    title: lib/classes/segtree.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/heavylightdecomposition.cpp
    title: lib/classes/heavylightdecomposition.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_path_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_path_sum
  bundledCode: "#line 1 \"verify/vertex_and_path_sum.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing i64 = long long;\n\ntemplate <typename T>\nbool chmax(T&\
    \ x, T y){\n    if(x < y){\n        x = y;\n        return true;\n    }\n    return\
    \ false;\n}\n\n\n#line 1 \"lib/classes/segtree.cpp\"\ntemplate<typename T>\nstruct\
    \ Segtree{\n    int n;\n    T op;\n    vector<T> elm;\n    function<T(T, T)> f;\n\
    \n    Segtree(int n, T init, function<T(T, T)> f, T op = T()) :\n        n(n),\n\
    \        op(op),\n        elm(2 * n, init),\n        f(f)\n    {\n        for(int\
    \ i = n - 1; i >= 1; --i)\n            elm[i] = f(elm[2 * i], elm[2 * i + 1]);\n\
    \    }\n\n    Segtree(int n, vector<T> init, function<T(T, T)> f, T op = T())\
    \ :\n        n(n),\n        op(op),\n        elm(2 * n),\n        f(f)\n    {\n\
    \        for(int i = 0; i < n; ++i)\n            elm[i + n] = init[i];\n     \
    \   for(int i = n - 1; i >= 1; --i)\n            elm[i] = f(elm[2 * i], elm[2\
    \ * i + 1]);\n    }\n\n    void set(int x, T val){\n        x += n;\n        elm[x]\
    \ = val;\n        while(x >>= 1)\n            elm[x] = f(elm[2 * x], elm[2 * x\
    \ + 1]);\n    }\n\n    void update(int x, T val){\n        x += n;\n        elm[x]\
    \ = f(elm[x], val);\n        while(x >>= 1)\n            elm[x] = f(elm[2 * x],\
    \ elm[2 * x + 1]);\n    }\n\n    T get(int x, int y) const{\n        T l = op,\
    \ r = op;\n        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){\n      \
    \      if(x & 1)\n                l = f(l, elm[x++]);\n            if(!(y & 1))\n\
    \                r = f(elm[y--], r);\n        }\n        return f(l, r);\n   \
    \ }\n};\n\n#line 1 \"lib/classes/heavylightdecomposition.cpp\"\nstruct HeavyLightDecomposition{\n\
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
    \ heavy_depth[heavy_root[x]];\n    }\n};\n\n#line 19 \"verify/vertex_and_path_sum.test.cpp\"\
    \n\n\nsigned main(){\n\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    vector<i64>\
    \ a(n);\n    for(auto& x : a)\n        scanf(\"%lld\", &x);\n    vector<int> u(n\
    \ - 1), v(n - 1);\n    for(int i = 0; i < n - 1; ++i)\n        scanf(\"%d%d\"\
    , &u[i], &v[i]);\n    vector<tuple<int,int,int>> querys;\n    for(int i = 0; i\
    \ < q; ++i){\n        int a, b, c;\n        scanf(\"%d%d%d\", &a, &b, &c);\n \
    \       querys.emplace_back(a, b, c);\n    }\n    Segtree<i64> seg(n, 0, [](auto\
    \ x, auto y){return x + y;}, 0L);\n    vector<vector<int>> edges(n);\n    for(int\
    \ i = 0; i < n - 1; ++i) {\n        edges[u[i]].emplace_back(v[i]);\n        edges[v[i]].emplace_back(u[i]);\n\
    \    }\n    HeavyLightDecomposition hld(edges);\n    for(int i = 0; i < n; ++i)\n\
    \        seg.set(hld.in[i], a[i]);\n\n    for(auto& query : querys){\n       \
    \ int a, b, c;\n        tie(a, b, c) = query;\n        if(a == 0){\n         \
    \   seg.update(hld.get_idx(b), c);\n        }else{\n            vector<pair<int,int>>\
    \ l, r;\n            tie(l, r) = hld.two_point_path(b, c);\n            i64 sum\
    \ = 0;\n            for(auto& p : l){\n                sum += seg.get(p.first,\
    \ p.second);\n            }\n            for(auto& p : r){\n                sum\
    \ += seg.get(p.first, p.second);\n            }\n            printf(\"%lld\\n\"\
    , sum);\n        }\n    }\n\n    return 0;\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_path_sum\"\n\
    \n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long long;\n\ntemplate\
    \ <typename T>\nbool chmax(T& x, T y){\n    if(x < y){\n        x = y;\n     \
    \   return true;\n    }\n    return false;\n}\n\n\n#include \"../lib/classes/segtree.cpp\"\
    \n#include \"../lib/classes/heavylightdecomposition.cpp\"\n\n\nsigned main(){\n\
    \n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    vector<i64> a(n);\n    for(auto&\
    \ x : a)\n        scanf(\"%lld\", &x);\n    vector<int> u(n - 1), v(n - 1);\n\
    \    for(int i = 0; i < n - 1; ++i)\n        scanf(\"%d%d\", &u[i], &v[i]);\n\
    \    vector<tuple<int,int,int>> querys;\n    for(int i = 0; i < q; ++i){\n   \
    \     int a, b, c;\n        scanf(\"%d%d%d\", &a, &b, &c);\n        querys.emplace_back(a,\
    \ b, c);\n    }\n    Segtree<i64> seg(n, 0, [](auto x, auto y){return x + y;},\
    \ 0L);\n    vector<vector<int>> edges(n);\n    for(int i = 0; i < n - 1; ++i)\
    \ {\n        edges[u[i]].emplace_back(v[i]);\n        edges[v[i]].emplace_back(u[i]);\n\
    \    }\n    HeavyLightDecomposition hld(edges);\n    for(int i = 0; i < n; ++i)\n\
    \        seg.set(hld.in[i], a[i]);\n\n    for(auto& query : querys){\n       \
    \ int a, b, c;\n        tie(a, b, c) = query;\n        if(a == 0){\n         \
    \   seg.update(hld.get_idx(b), c);\n        }else{\n            vector<pair<int,int>>\
    \ l, r;\n            tie(l, r) = hld.two_point_path(b, c);\n            i64 sum\
    \ = 0;\n            for(auto& p : l){\n                sum += seg.get(p.first,\
    \ p.second);\n            }\n            for(auto& p : r){\n                sum\
    \ += seg.get(p.first, p.second);\n            }\n            printf(\"%lld\\n\"\
    , sum);\n        }\n    }\n\n    return 0;\n}\n"
  dependsOn:
  - lib/classes/segtree.cpp
  - lib/classes/heavylightdecomposition.cpp
  isVerificationFile: true
  path: verify/vertex_and_path_sum.test.cpp
  requiredBy: []
  timestamp: '2020-03-14 13:41:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/vertex_and_path_sum.test.cpp
layout: document
redirect_from:
- /verify/verify/vertex_and_path_sum.test.cpp
- /verify/verify/vertex_and_path_sum.test.cpp.html
title: verify/vertex_and_path_sum.test.cpp
---
