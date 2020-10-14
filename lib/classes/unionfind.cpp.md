---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/unionfind.test.cpp
    title: verify/unionfind.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/unionfind.cpp\"\nstruct UnionFind{\n    vector<int>\
    \ par;\n    int count;\n    UnionFind(int n) : par(n, -1), count(0){}\n    int\
    \ Find(int x){return par[x] < 0 ? x : Find(par[x]);}\n    int Size(int x){return\
    \ par[x] < 0 ? -par[x] : Size(par[x]);}\n    bool Unite(int x, int y){\n     \
    \   x = Find(x);\n        y = Find(y);\n        if(x == y)\n            return\
    \ false;\n        if(par[x] > par[y])\n            swap(x, y);\n        par[x]\
    \ += par[y];\n        par[y] = x;\n        return ++count;\n    }\n};\n\n"
  code: "struct UnionFind{\n    vector<int> par;\n    int count;\n    UnionFind(int\
    \ n) : par(n, -1), count(0){}\n    int Find(int x){return par[x] < 0 ? x : Find(par[x]);}\n\
    \    int Size(int x){return par[x] < 0 ? -par[x] : Size(par[x]);}\n    bool Unite(int\
    \ x, int y){\n        x = Find(x);\n        y = Find(y);\n        if(x == y)\n\
    \            return false;\n        if(par[x] > par[y])\n            swap(x, y);\n\
    \        par[x] += par[y];\n        par[y] = x;\n        return ++count;\n   \
    \ }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/unionfind.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/unionfind.test.cpp
documentation_of: lib/classes/unionfind.cpp
layout: document
redirect_from:
- /library/lib/classes/unionfind.cpp
- /library/lib/classes/unionfind.cpp.html
title: lib/classes/unionfind.cpp
---
