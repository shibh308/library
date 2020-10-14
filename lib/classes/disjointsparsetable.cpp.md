---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/static_rmq.test.cpp
    title: verify/static_rmq.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/disjointsparsetable.cpp\"\ntemplate <typename\
    \ T>\nstruct DisjointSparseTable{\n    function<T(T, T)> f;\n    vector<vector<T>>\
    \ v;\n\n    DisjointSparseTable(vector<T>& inp, function<T(T, T)> f) : f(f){\n\
    \        int n = inp.size();\n        int b;\n        for(b = 0; (1 << b) <= inp.size();\
    \ ++b);\n        v.assign(b, vector<T>(n));\n        for(int i = 0; i < n; ++i)\n\
    \            v[0][i] = inp[i];\n        for(int i = 1; i < b; ++i){\n        \
    \    int siz = 1 << i;\n            for(int j = 0; j < n; j += siz << 1){\n  \
    \              int t = min(j + siz, n);\n                v[i][t - 1] = inp[t -\
    \ 1];\n                for(int k = t - 2; k >= j; --k)\n                    v[i][k]\
    \ = f(inp[k], v[i][k + 1]);\n                if(t >= n)\n                    break;\n\
    \                v[i][t] = inp[t];\n                int r = min(t + siz, n);\n\
    \                for(int k = t + 1; k < r; ++k)\n                    v[i][k] =\
    \ f(v[i][k - 1], inp[k]);\n            }\n        }\n    }\n\n    T get(int l,\
    \ int r){\n        if(l >= --r)\n            return v[0][l];\n        int p =\
    \ 31 - __builtin_clz(l ^ r);\n        return f(v[p][l], v[p][r]);\n    }\n};\n\
    \n"
  code: "template <typename T>\nstruct DisjointSparseTable{\n    function<T(T, T)>\
    \ f;\n    vector<vector<T>> v;\n\n    DisjointSparseTable(vector<T>& inp, function<T(T,\
    \ T)> f) : f(f){\n        int n = inp.size();\n        int b;\n        for(b =\
    \ 0; (1 << b) <= inp.size(); ++b);\n        v.assign(b, vector<T>(n));\n     \
    \   for(int i = 0; i < n; ++i)\n            v[0][i] = inp[i];\n        for(int\
    \ i = 1; i < b; ++i){\n            int siz = 1 << i;\n            for(int j =\
    \ 0; j < n; j += siz << 1){\n                int t = min(j + siz, n);\n      \
    \          v[i][t - 1] = inp[t - 1];\n                for(int k = t - 2; k >=\
    \ j; --k)\n                    v[i][k] = f(inp[k], v[i][k + 1]);\n           \
    \     if(t >= n)\n                    break;\n                v[i][t] = inp[t];\n\
    \                int r = min(t + siz, n);\n                for(int k = t + 1;\
    \ k < r; ++k)\n                    v[i][k] = f(v[i][k - 1], inp[k]);\n       \
    \     }\n        }\n    }\n\n    T get(int l, int r){\n        if(l >= --r)\n\
    \            return v[0][l];\n        int p = 31 - __builtin_clz(l ^ r);\n   \
    \     return f(v[p][l], v[p][r]);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/disjointsparsetable.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/static_rmq.test.cpp
documentation_of: lib/classes/disjointsparsetable.cpp
layout: document
redirect_from:
- /library/lib/classes/disjointsparsetable.cpp
- /library/lib/classes/disjointsparsetable.cpp.html
title: lib/classes/disjointsparsetable.cpp
---
