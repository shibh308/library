---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/static_rmq_wm.test.cpp
    title: verify/static_rmq_wm.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/waveletmatrix_kthmin.test.cpp
    title: verify/waveletmatrix_kthmin.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/waveletmatrix_lowerbound.test.cpp
    title: verify/waveletmatrix_lowerbound.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/waveletmatrix_rangefreq.test.cpp
    title: verify/waveletmatrix_rangefreq.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/bitvector.cpp\"\nstruct BitVector{\n    vector<uint64_t>\
    \ v;\n    vector<int> r;\n    BitVector(){}\n    void build(){\n        r.assign(v.size()\
    \ + 1, 0);\n        for(int i = 0; i < v.size(); ++i)\n            r[i + 1] =\
    \ r[i] + __builtin_popcountll(v[i]);\n    }\n    bool access(int x){\n       \
    \ return (v[x >> 6] >> (x & 63)) & 1;\n    }\n    // [0, x)\u306E1\u306E\u51FA\
    \u73FE\u56DE\u6570\n    int rank(int x){\n        return r[x >> 6] + __builtin_popcountll(v[x\
    \ >> 6] & ((1uLL << (x & 63)) - 1));\n    }\n    int rank(int x, bool fl){\n \
    \       return fl ? rank(x) : x - rank(x);\n    }\n};\n\n"
  code: "struct BitVector{\n    vector<uint64_t> v;\n    vector<int> r;\n    BitVector(){}\n\
    \    void build(){\n        r.assign(v.size() + 1, 0);\n        for(int i = 0;\
    \ i < v.size(); ++i)\n            r[i + 1] = r[i] + __builtin_popcountll(v[i]);\n\
    \    }\n    bool access(int x){\n        return (v[x >> 6] >> (x & 63)) & 1;\n\
    \    }\n    // [0, x)\u306E1\u306E\u51FA\u73FE\u56DE\u6570\n    int rank(int x){\n\
    \        return r[x >> 6] + __builtin_popcountll(v[x >> 6] & ((1uLL << (x & 63))\
    \ - 1));\n    }\n    int rank(int x, bool fl){\n        return fl ? rank(x) :\
    \ x - rank(x);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/bitvector.cpp
  requiredBy: []
  timestamp: '2020-04-15 14:51:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/static_rmq_wm.test.cpp
  - verify/waveletmatrix_rangefreq.test.cpp
  - verify/waveletmatrix_kthmin.test.cpp
  - verify/waveletmatrix_lowerbound.test.cpp
documentation_of: lib/classes/bitvector.cpp
layout: document
redirect_from:
- /library/lib/classes/bitvector.cpp
- /library/lib/classes/bitvector.cpp.html
title: lib/classes/bitvector.cpp
---
