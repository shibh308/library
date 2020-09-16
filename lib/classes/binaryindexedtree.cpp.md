---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/rsq_bit.test.cpp
    title: verify/rsq_bit.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/binaryindexedtree.cpp\"\ntemplate <typename\
    \ T>\nstruct BIT{\n    vector<T> elm;\n    BIT(int n, T init = T()) : elm(n +\
    \ 1, init){\n    }\n\n    // [0, x)\n    T sum(int x){\n        T val = 0;\n \
    \       for(; x > 0; x -= x & -x)\n            val += elm[x];\n        return\
    \ val;\n    }\n\n    // [l, r)\n    T sum(int l, int r){\n        return sum(r)\
    \ - sum(l);\n    }\n\n    void add(int x, T val){\n        for(++x; x < elm.size();\
    \ x += x & -x)\n            elm[x] += val;\n    }\n};\n\n"
  code: "template <typename T>\nstruct BIT{\n    vector<T> elm;\n    BIT(int n, T\
    \ init = T()) : elm(n + 1, init){\n    }\n\n    // [0, x)\n    T sum(int x){\n\
    \        T val = 0;\n        for(; x > 0; x -= x & -x)\n            val += elm[x];\n\
    \        return val;\n    }\n\n    // [l, r)\n    T sum(int l, int r){\n     \
    \   return sum(r) - sum(l);\n    }\n\n    void add(int x, T val){\n        for(++x;\
    \ x < elm.size(); x += x & -x)\n            elm[x] += val;\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/binaryindexedtree.cpp
  requiredBy: []
  timestamp: '2019-12-05 03:16:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/rsq_bit.test.cpp
documentation_of: lib/classes/binaryindexedtree.cpp
layout: document
redirect_from:
- /library/lib/classes/binaryindexedtree.cpp
- /library/lib/classes/binaryindexedtree.cpp.html
title: lib/classes/binaryindexedtree.cpp
---
