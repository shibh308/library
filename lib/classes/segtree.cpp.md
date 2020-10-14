---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/eulertour.test.cpp
    title: verify/eulertour.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/hld_composite.test.cpp
    title: verify/hld_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/segtree_composite.test.cpp
    title: verify/segtree_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/vertex_and_path_sum.test.cpp
    title: verify/vertex_and_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/vertex_and_subtree_sum.test.cpp
    title: verify/vertex_and_subtree_sum.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/segtree.cpp\"\ntemplate<typename T>\nstruct\
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
    \ }\n};\n\n"
  code: "template<typename T>\nstruct Segtree{\n    int n;\n    T op;\n    vector<T>\
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
    \ r);\n        }\n        return f(l, r);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/segtree.cpp
  requiredBy: []
  timestamp: '2019-11-30 22:46:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/segtree_composite.test.cpp
  - verify/vertex_and_subtree_sum.test.cpp
  - verify/eulertour.test.cpp
  - verify/hld_composite.test.cpp
  - verify/vertex_and_path_sum.test.cpp
documentation_of: lib/classes/segtree.cpp
layout: document
redirect_from:
- /library/lib/classes/segtree.cpp
- /library/lib/classes/segtree.cpp.html
title: lib/classes/segtree.cpp
---
