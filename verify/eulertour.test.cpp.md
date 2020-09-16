---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/eulertour.cpp
    title: lib/classes/eulertour.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/segtree.cpp
    title: lib/classes/segtree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "#line 1 \"verify/eulertour.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n#line 1 \"lib/classes/eulertour.cpp\"\nstruct EulerTour{\n    int n;\n    vector<int>\
    \ in, out;\n    EulerTour(vector<vector<int>>& edges, int par = 0) : n(edges.size()),\
    \ in(n, -1), out(n, -1){\n        int cnt = 0;\n        function<void(int)> f\
    \ = [&](int x){\n            in[x] = cnt++;\n            for(auto y : edges[x]){\n\
    \                if(in[y] == -1)\n                    f(y);\n            }\n \
    \           out[x] = cnt;\n        };\n        f(par);\n    }\n    int get_pos(int\
    \ x){\n        return in[x];\n    }\n    // \u81EA\u8EAB\u3092\u542B\u307F\u305F\
    \u304F\u306A\u3044\u5834\u5408\u306F(in[x] + 1, out[x])\n    pair<int,int> get_subtree(int\
    \ x){\n        return make_pair(in[x], out[x]);\n    }\n};\n\n#line 1 \"lib/classes/segtree.cpp\"\
    \ntemplate<typename T>\nstruct Segtree{\n    int n;\n    T op;\n    vector<T>\
    \ elm;\n    function<T(T, T)> f;\n\n    Segtree(int n, T init, function<T(T, T)>\
    \ f, T op = T()) :\n        n(n),\n        op(op),\n        elm(2 * n, init),\n\
    \        f(f)\n    {\n        for(int i = n - 1; i >= 1; --i)\n            elm[i]\
    \ = f(elm[2 * i], elm[2 * i + 1]);\n    }\n\n    Segtree(int n, vector<T> init,\
    \ function<T(T, T)> f, T op = T()) :\n        n(n),\n        op(op),\n       \
    \ elm(2 * n),\n        f(f)\n    {\n        for(int i = 0; i < n; ++i)\n     \
    \       elm[i + n] = init[i];\n        for(int i = n - 1; i >= 1; --i)\n     \
    \       elm[i] = f(elm[2 * i], elm[2 * i + 1]);\n    }\n\n    void set(int x,\
    \ T val){\n        x += n;\n        elm[x] = val;\n        while(x >>= 1)\n  \
    \          elm[x] = f(elm[2 * x], elm[2 * x + 1]);\n    }\n\n    void update(int\
    \ x, T val){\n        x += n;\n        elm[x] = f(elm[x], val);\n        while(x\
    \ >>= 1)\n            elm[x] = f(elm[2 * x], elm[2 * x + 1]);\n    }\n\n    T\
    \ get(int x, int y) const{\n        T l = op, r = op;\n        for(x += n, y +=\
    \ n - 1; x <= y; x >>= 1, y >>= 1){\n            if(x & 1)\n                l\
    \ = f(l, elm[x++]);\n            if(!(y & 1))\n                r = f(elm[y--],\
    \ r);\n        }\n        return f(l, r);\n    }\n};\n\n#line 10 \"verify/eulertour.test.cpp\"\
    \n\nsigned main(){\n    int n, q;\n    cin >> n >> q;\n    vector<i64> a(n);\n\
    \    for(int i = 0; i < n; ++i)\n        cin >> a[i];\n    vector<vector<int>>\
    \ edges(n);\n    for(int i = 1; i < n; ++i){\n        int p;\n        cin >> p;\n\
    \        edges[p].push_back(i);\n        edges[i].push_back(p);\n    }\n    EulerTour\
    \ et(edges);\n    vector<i64> b(n);\n    for(int i = 0; i < n; ++i)\n        b[et.get_pos(i)]\
    \ = a[i];\n    Segtree<i64> seg(n, b, [](auto x, auto y){return x + y;}, 0LL);\n\
    \    for(int i = 0; i < q; ++i){\n        int type;\n        cin >> type;\n  \
    \      if(type == 0){\n            int u, x;\n            cin >> u >> x;\n   \
    \         seg.update(et.get_pos(u), x);\n        }\n        else{\n          \
    \  int u;\n            cin >> u;\n            auto p = et.get_subtree(u);\n  \
    \          cout << seg.get(p.first, p.second) << endl;\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n#include \"../lib/classes/eulertour.cpp\"\n#include \"../lib/classes/segtree.cpp\"\
    \n\nsigned main(){\n    int n, q;\n    cin >> n >> q;\n    vector<i64> a(n);\n\
    \    for(int i = 0; i < n; ++i)\n        cin >> a[i];\n    vector<vector<int>>\
    \ edges(n);\n    for(int i = 1; i < n; ++i){\n        int p;\n        cin >> p;\n\
    \        edges[p].push_back(i);\n        edges[i].push_back(p);\n    }\n    EulerTour\
    \ et(edges);\n    vector<i64> b(n);\n    for(int i = 0; i < n; ++i)\n        b[et.get_pos(i)]\
    \ = a[i];\n    Segtree<i64> seg(n, b, [](auto x, auto y){return x + y;}, 0LL);\n\
    \    for(int i = 0; i < q; ++i){\n        int type;\n        cin >> type;\n  \
    \      if(type == 0){\n            int u, x;\n            cin >> u >> x;\n   \
    \         seg.update(et.get_pos(u), x);\n        }\n        else{\n          \
    \  int u;\n            cin >> u;\n            auto p = et.get_subtree(u);\n  \
    \          cout << seg.get(p.first, p.second) << endl;\n        }\n    }\n}\n"
  dependsOn:
  - lib/classes/eulertour.cpp
  - lib/classes/segtree.cpp
  isVerificationFile: true
  path: verify/eulertour.test.cpp
  requiredBy: []
  timestamp: '2020-03-06 18:23:18+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/eulertour.test.cpp
layout: document
redirect_from:
- /verify/verify/eulertour.test.cpp
- /verify/verify/eulertour.test.cpp.html
title: verify/eulertour.test.cpp
---
