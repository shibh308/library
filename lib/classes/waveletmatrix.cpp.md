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
  bundledCode: "#line 1 \"lib/classes/waveletmatrix.cpp\"\ntemplate <typename T, int\
    \ W>\nstruct WaveletMatrix{\n\n    array<BitVector, W> bv;\n    array<int, W>\
    \ zero_cnt;\n\n    WaveletMatrix(vector<T>& a){\n        int n = a.size();\n \
    \       vector<T> v(a);\n        for(int i = W - 1; i >= 0; --i){\n          \
    \  vector<uint64_t> b((n >> 6) + 1, 0);\n            vector<T> v1, v2;\n     \
    \       for(int j = 0; j < n; ++j){\n                ((v[j] >> i) & 1 ? v2 : v1).push_back(v[j]);\n\
    \                b[j >> 6] |= uint64_t((v[j] >> i) & 1) << (j & 63);\n       \
    \     }\n            for(int j = 0; j < v.size(); ++j)\n                v[j] =\
    \ (j < v1.size() ? v1[j] : v2[j - v1.size()]);\n            bv[i].v = move(b);\n\
    \            bv[i].build();\n            zero_cnt[i] = bv[i].rank(n, 0);\n   \
    \     }\n    }\n\n    // [l, r)\u5185\u306Ex\u306E\u6570\n    int count(int l,\
    \ int r, T x){\n        for(int i = W - 1; i >= 0; --i){\n            bool fl\
    \ = (x >> i) & 1;\n            int st = bv[i].rank(l, fl);\n            int en\
    \ = bv[i].rank(r, fl);\n            l = (fl ? zero_cnt[i] : 0) + st;\n       \
    \     r = (fl ? zero_cnt[i] : 0) + en;\n        }\n        return r - l;\n   \
    \ }\n\n    // [l, r)\u5185\u3067[0, x)\u3092\u6E80\u305F\u3059\u5024\u306E\u6570\
    \n    int count_lower(int l, int r, T x){\n        int cnt = 0;\n        for(int\
    \ i = W - 1; i >= 0; --i){\n            bool fl = (x >> i) & 1;\n            int\
    \ st = bv[i].rank(l, fl);\n            int en = bv[i].rank(r, fl);\n         \
    \   if(fl){\n                st += zero_cnt[i];\n                en += zero_cnt[i];\n\
    \                cnt += (bv[i].rank(r, 0) - bv[i].rank(l, 0));\n            }\n\
    \            l = st, r = en;\n        }\n        return cnt;\n    }\n\n    //\
    \ [l, r)\u5185\u3067[x, y)\u3092\u6E80\u305F\u3059\u5024\u306E\u6570\n    int\
    \ count_range(int l, int r, T x, T y){\n        return count_lower(l, r, y) -\
    \ count_lower(l, r, x);\n    }\n\n    // 0-indexed\u3067k\u756A\u76EE\u306B\u5C0F\
    \u3055\u3044\u3082\u306E\u3092\u8FD4\u3059\n    T kth_min(int l, int r, int k){\n\
    \        T ans = 0;\n        for(int i = W - 1; i >= 0; --i){\n            int\
    \ st = bv[i].rank(l, 0);\n            int en = bv[i].rank(r, 0);\n           \
    \ if(en - st <= k){\n                k -= en - st;\n                l = zero_cnt[i]\
    \ + bv[i].rank(l, 1);\n                r = zero_cnt[i] + bv[i].rank(r, 1);\n \
    \               ans |= (1uLL << i);\n            }\n            else{\n      \
    \          l = st, r = en;\n            }\n        }\n        return ans;\n  \
    \  }\n\n    // [l, r)\u3067\u306Ex\u4EE5\u4E0A\u6700\u5C0F\u5024\n    pair<T,\
    \ bool> predecessor(int l, int r, T x){\n        int idx = count_lower(l, r, x);\n\
    \        if(idx == r - l){\n            return make_pair((1uLL << W) - 1, false);\n\
    \        }\n        return make_pair(kth_min(l, r, idx), true);\n    }\n\n   \
    \ // [l, r)\u3067\u306Ex\u4EE5\u4E0B\u6700\u5927\u5024\n    pair<T, bool> successor(int\
    \ l, int r, T x){\n        int idx = count_lower(l, r, x + 1);\n        if(idx\
    \ == 0)\n            return make_pair(0, false);\n        return make_pair(kth_min(l,\
    \ r, idx - 1), true);\n    }\n};\n\n"
  code: "template <typename T, int W>\nstruct WaveletMatrix{\n\n    array<BitVector,\
    \ W> bv;\n    array<int, W> zero_cnt;\n\n    WaveletMatrix(vector<T>& a){\n  \
    \      int n = a.size();\n        vector<T> v(a);\n        for(int i = W - 1;\
    \ i >= 0; --i){\n            vector<uint64_t> b((n >> 6) + 1, 0);\n          \
    \  vector<T> v1, v2;\n            for(int j = 0; j < n; ++j){\n              \
    \  ((v[j] >> i) & 1 ? v2 : v1).push_back(v[j]);\n                b[j >> 6] |=\
    \ uint64_t((v[j] >> i) & 1) << (j & 63);\n            }\n            for(int j\
    \ = 0; j < v.size(); ++j)\n                v[j] = (j < v1.size() ? v1[j] : v2[j\
    \ - v1.size()]);\n            bv[i].v = move(b);\n            bv[i].build();\n\
    \            zero_cnt[i] = bv[i].rank(n, 0);\n        }\n    }\n\n    // [l, r)\u5185\
    \u306Ex\u306E\u6570\n    int count(int l, int r, T x){\n        for(int i = W\
    \ - 1; i >= 0; --i){\n            bool fl = (x >> i) & 1;\n            int st\
    \ = bv[i].rank(l, fl);\n            int en = bv[i].rank(r, fl);\n            l\
    \ = (fl ? zero_cnt[i] : 0) + st;\n            r = (fl ? zero_cnt[i] : 0) + en;\n\
    \        }\n        return r - l;\n    }\n\n    // [l, r)\u5185\u3067[0, x)\u3092\
    \u6E80\u305F\u3059\u5024\u306E\u6570\n    int count_lower(int l, int r, T x){\n\
    \        int cnt = 0;\n        for(int i = W - 1; i >= 0; --i){\n            bool\
    \ fl = (x >> i) & 1;\n            int st = bv[i].rank(l, fl);\n            int\
    \ en = bv[i].rank(r, fl);\n            if(fl){\n                st += zero_cnt[i];\n\
    \                en += zero_cnt[i];\n                cnt += (bv[i].rank(r, 0)\
    \ - bv[i].rank(l, 0));\n            }\n            l = st, r = en;\n        }\n\
    \        return cnt;\n    }\n\n    // [l, r)\u5185\u3067[x, y)\u3092\u6E80\u305F\
    \u3059\u5024\u306E\u6570\n    int count_range(int l, int r, T x, T y){\n     \
    \   return count_lower(l, r, y) - count_lower(l, r, x);\n    }\n\n    // 0-indexed\u3067\
    k\u756A\u76EE\u306B\u5C0F\u3055\u3044\u3082\u306E\u3092\u8FD4\u3059\n    T kth_min(int\
    \ l, int r, int k){\n        T ans = 0;\n        for(int i = W - 1; i >= 0; --i){\n\
    \            int st = bv[i].rank(l, 0);\n            int en = bv[i].rank(r, 0);\n\
    \            if(en - st <= k){\n                k -= en - st;\n              \
    \  l = zero_cnt[i] + bv[i].rank(l, 1);\n                r = zero_cnt[i] + bv[i].rank(r,\
    \ 1);\n                ans |= (1uLL << i);\n            }\n            else{\n\
    \                l = st, r = en;\n            }\n        }\n        return ans;\n\
    \    }\n\n    // [l, r)\u3067\u306Ex\u4EE5\u4E0A\u6700\u5C0F\u5024\n    pair<T,\
    \ bool> predecessor(int l, int r, T x){\n        int idx = count_lower(l, r, x);\n\
    \        if(idx == r - l){\n            return make_pair((1uLL << W) - 1, false);\n\
    \        }\n        return make_pair(kth_min(l, r, idx), true);\n    }\n\n   \
    \ // [l, r)\u3067\u306Ex\u4EE5\u4E0B\u6700\u5927\u5024\n    pair<T, bool> successor(int\
    \ l, int r, T x){\n        int idx = count_lower(l, r, x + 1);\n        if(idx\
    \ == 0)\n            return make_pair(0, false);\n        return make_pair(kth_min(l,\
    \ r, idx - 1), true);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/waveletmatrix.cpp
  requiredBy: []
  timestamp: '2020-04-15 15:25:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/static_rmq_wm.test.cpp
  - verify/waveletmatrix_rangefreq.test.cpp
  - verify/waveletmatrix_kthmin.test.cpp
  - verify/waveletmatrix_lowerbound.test.cpp
documentation_of: lib/classes/waveletmatrix.cpp
layout: document
redirect_from:
- /library/lib/classes/waveletmatrix.cpp
- /library/lib/classes/waveletmatrix.cpp.html
title: lib/classes/waveletmatrix.cpp
---
