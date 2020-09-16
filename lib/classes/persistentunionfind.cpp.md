---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/persistentunionfind.test.cpp
    title: verify/persistentunionfind.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/persistentunionfind.cpp\"\nstruct UnionFind{\n\
    \    vector<int> par, time;\n    int count;\n    UnionFind(int n) : par(n, -1),\
    \ time(n, MOD), count(0){}\n    // [0, t]\u306E\u9593\u306B\u4F75\u5408\u3055\u308C\
    \u305F\u304B\u3069\u3046\u304B\n    int Find(int x, int t){return par[x] < 0 ||\
    \ time[x] > t ? x : Find(par[x], t);}\n    int Size(int x){return par[x] < 0 ?\
    \ -par[x] : Size(par[x]);}\n    // \u73FE\u5728\u306Ecount+1\u306E\u30BF\u30A4\
    \u30DF\u30F3\u30B0\u3067\u4F75\u5408\u3055\u308C\u305F\u4E8B\u306B\u3059\u308B\
    \n    // Unite\u5931\u6557\u6642\u3082count\u304C\u5897\u3048\u308B\u306E\u3067\
    \u6CE8\u610F\n    int Unite(int x, int y){\n        x = Find(x, MOD + 1);\n  \
    \      y = Find(y, MOD + 1);\n        ++count;\n        if(x == y)\n         \
    \   return 0;\n        if(par[x] > par[y])\n            swap(x, y);\n        par[x]\
    \ += par[y];\n        par[y] = x;\n        time[y] = count;\n        return count;\n\
    \    }\n};\n\n"
  code: "struct UnionFind{\n    vector<int> par, time;\n    int count;\n    UnionFind(int\
    \ n) : par(n, -1), time(n, MOD), count(0){}\n    // [0, t]\u306E\u9593\u306B\u4F75\
    \u5408\u3055\u308C\u305F\u304B\u3069\u3046\u304B\n    int Find(int x, int t){return\
    \ par[x] < 0 || time[x] > t ? x : Find(par[x], t);}\n    int Size(int x){return\
    \ par[x] < 0 ? -par[x] : Size(par[x]);}\n    // \u73FE\u5728\u306Ecount+1\u306E\
    \u30BF\u30A4\u30DF\u30F3\u30B0\u3067\u4F75\u5408\u3055\u308C\u305F\u4E8B\u306B\
    \u3059\u308B\n    // Unite\u5931\u6557\u6642\u3082count\u304C\u5897\u3048\u308B\
    \u306E\u3067\u6CE8\u610F\n    int Unite(int x, int y){\n        x = Find(x, MOD\
    \ + 1);\n        y = Find(y, MOD + 1);\n        ++count;\n        if(x == y)\n\
    \            return 0;\n        if(par[x] > par[y])\n            swap(x, y);\n\
    \        par[x] += par[y];\n        par[y] = x;\n        time[y] = count;\n  \
    \      return count;\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/persistentunionfind.cpp
  requiredBy: []
  timestamp: '2020-02-24 09:13:36+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/persistentunionfind.test.cpp
documentation_of: lib/classes/persistentunionfind.cpp
layout: document
redirect_from:
- /library/lib/classes/persistentunionfind.cpp
- /library/lib/classes/persistentunionfind.cpp.html
title: lib/classes/persistentunionfind.cpp
---
