---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/dynamicwaveletmatrix_kthmin.test.cpp
    title: verify/dynamicwaveletmatrix_kthmin.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/dynamicwaveletmatrix_rmq.test.cpp
    title: verify/dynamicwaveletmatrix_rmq.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/dynamicwaveletmatrix.cpp\"\ntemplate <typename\
    \ T, int W>\nstruct WaveletMatrix{\n\n    array<DynamicBitVector, W> bv;\n\n \
    \   WaveletMatrix(vector<T>& a){\n        int n = a.size();\n        vector<T>\
    \ v(a);\n        for(int i = W - 1; i >= 0; --i){\n            vector<uint64_t>\
    \ b((n + 31) >> 5, 0);\n            vector<int> length(b.size(), 0);\n       \
    \     vector<T> v1, v2;\n            for(int j = 0; j < n; ++j){\n           \
    \     bool fl = ((v[j] >> i) & 1);\n                (fl ? v2 : v1).push_back(v[j]);\n\
    \                b[j >> 5] |= uint64_t(fl) << (j & 31);\n                ++length[j\
    \ >> 5];\n            }\n            for(int j = 0; j < v.size(); ++j)\n     \
    \           v[j] = (j < v1.size() ? v1[j] : v2[j - v1.size()]);\n\n          \
    \  if(b.size() >= 2 && !(n & 31)){\n                b[b.size() - 2] |= b[b.size()\
    \ - 1] << 32;\n                b.pop_back();\n            }\n            bv[i].build(n,\
    \ b);\n        }\n    }\n\n    void insert(int k, T x){\n        for(int i = W\
    \ - 1; i >= 0; --i){\n            bool fl = (x >> i) & 1;\n            bv[i].insert(k,\
    \ fl);\n            k = (fl ? bv[i].rank_val : k - bv[i].rank_val) + (fl ? bv[i].zero_cnt()\
    \ : 0);\n        }\n    }\n\n    void erase(int k){\n        for(int i = W - 1;\
    \ i >= 0; --i){\n            int zero_cnt = bv[i].zero_cnt();\n            bv[i].erase(k);\n\
    \            bool fl = bv[i].erase_fl;\n            int rank = (fl ? bv[i].rank_val\
    \ : k - bv[i].rank_val);\n            k = rank + (fl ? zero_cnt : 0);\n      \
    \  }\n    }\n\n    // [l, r)\u5185\u306Ex\u306E\u6570\n    int count(int l, int\
    \ r, T x){\n        for(int i = W - 1; i >= 0; --i){\n            bool fl = (x\
    \ >> i) & 1;\n            int st = bv[i].rank(l, fl);\n            int en = bv[i].rank(r,\
    \ fl);\n            l = (fl ? bv[i].zero_cnt() : 0) + st;\n            r = (fl\
    \ ? bv[i].zero_cnt() : 0) + en;\n        }\n        return r - l;\n    }\n\n \
    \   // [l, r)\u5185\u3067[0, x)\u3092\u6E80\u305F\u3059\u5024\u306E\u6570\n  \
    \  int count_lower(int l, int r, T x){\n        int cnt = 0;\n        for(int\
    \ i = W - 1; i >= 0; --i){\n            bool fl = (x >> i) & 1;\n            int\
    \ st = bv[i].rank(l, fl);\n            int en = bv[i].rank(r, fl);\n         \
    \   if(fl){\n                st += bv[i].zero_cnt();\n                en += bv[i].zero_cnt();\n\
    \                cnt += (bv[i].rank(r, 0) - bv[i].rank(l, 0));\n            }\n\
    \            l = st, r = en;\n        }\n        return cnt;\n    }\n\n    //\
    \ [l, r)\u5185\u3067[x, y)\u3092\u6E80\u305F\u3059\u5024\u306E\u6570\n    int\
    \ count_range(int l, int r, T x, T y){\n        return count_lower(l, r, y) -\
    \ count_lower(l, r, x);\n    }\n\n    // 0-indexed\u3067k\u756A\u76EE\u306B\u5C0F\
    \u3055\u3044\u3082\u306E\u3092\u8FD4\u3059\n    T kth_min(int l, int r, int k){\n\
    \        T ans = 0;\n        for(int i = W - 1; i >= 0; --i){\n            int\
    \ st = bv[i].rank(l, 0);\n            int en = bv[i].rank(r, 0);\n           \
    \ if(en - st <= k){\n                k -= en - st;\n                l = bv[i].zero_cnt()\
    \ + (l - st);\n                r = bv[i].zero_cnt() + (r - en);\n            \
    \    ans |= (1uLL << i);\n            }\n            else{\n                l\
    \ = st, r = en;\n            }\n        }\n        return ans;\n    }\n\n    //\
    \ [l, r)\u3067\u306Ex\u4EE5\u4E0A\u6700\u5C0F\u5024\n    pair<T, bool> predecessor(int\
    \ l, int r, T x){\n        int idx = count_lower(l, r, x);\n        if(idx ==\
    \ r - l){\n            return make_pair((1uLL << W) - 1, false);\n        }\n\
    \        return make_pair(kth_min(l, r, idx), true);\n    }\n\n    // [l, r)\u3067\
    \u306Ex\u4EE5\u4E0B\u6700\u5927\u5024\n    pair<T, bool> successor(int l, int\
    \ r, T x){\n        int idx = count_lower(l, r, x + 1);\n        if(idx == 0)\n\
    \            return make_pair(0, false);\n        return make_pair(kth_min(l,\
    \ r, idx - 1), true);\n    }\n};\n\n"
  code: "template <typename T, int W>\nstruct WaveletMatrix{\n\n    array<DynamicBitVector,\
    \ W> bv;\n\n    WaveletMatrix(vector<T>& a){\n        int n = a.size();\n    \
    \    vector<T> v(a);\n        for(int i = W - 1; i >= 0; --i){\n            vector<uint64_t>\
    \ b((n + 31) >> 5, 0);\n            vector<int> length(b.size(), 0);\n       \
    \     vector<T> v1, v2;\n            for(int j = 0; j < n; ++j){\n           \
    \     bool fl = ((v[j] >> i) & 1);\n                (fl ? v2 : v1).push_back(v[j]);\n\
    \                b[j >> 5] |= uint64_t(fl) << (j & 31);\n                ++length[j\
    \ >> 5];\n            }\n            for(int j = 0; j < v.size(); ++j)\n     \
    \           v[j] = (j < v1.size() ? v1[j] : v2[j - v1.size()]);\n\n          \
    \  if(b.size() >= 2 && !(n & 31)){\n                b[b.size() - 2] |= b[b.size()\
    \ - 1] << 32;\n                b.pop_back();\n            }\n            bv[i].build(n,\
    \ b);\n        }\n    }\n\n    void insert(int k, T x){\n        for(int i = W\
    \ - 1; i >= 0; --i){\n            bool fl = (x >> i) & 1;\n            bv[i].insert(k,\
    \ fl);\n            k = (fl ? bv[i].rank_val : k - bv[i].rank_val) + (fl ? bv[i].zero_cnt()\
    \ : 0);\n        }\n    }\n\n    void erase(int k){\n        for(int i = W - 1;\
    \ i >= 0; --i){\n            int zero_cnt = bv[i].zero_cnt();\n            bv[i].erase(k);\n\
    \            bool fl = bv[i].erase_fl;\n            int rank = (fl ? bv[i].rank_val\
    \ : k - bv[i].rank_val);\n            k = rank + (fl ? zero_cnt : 0);\n      \
    \  }\n    }\n\n    // [l, r)\u5185\u306Ex\u306E\u6570\n    int count(int l, int\
    \ r, T x){\n        for(int i = W - 1; i >= 0; --i){\n            bool fl = (x\
    \ >> i) & 1;\n            int st = bv[i].rank(l, fl);\n            int en = bv[i].rank(r,\
    \ fl);\n            l = (fl ? bv[i].zero_cnt() : 0) + st;\n            r = (fl\
    \ ? bv[i].zero_cnt() : 0) + en;\n        }\n        return r - l;\n    }\n\n \
    \   // [l, r)\u5185\u3067[0, x)\u3092\u6E80\u305F\u3059\u5024\u306E\u6570\n  \
    \  int count_lower(int l, int r, T x){\n        int cnt = 0;\n        for(int\
    \ i = W - 1; i >= 0; --i){\n            bool fl = (x >> i) & 1;\n            int\
    \ st = bv[i].rank(l, fl);\n            int en = bv[i].rank(r, fl);\n         \
    \   if(fl){\n                st += bv[i].zero_cnt();\n                en += bv[i].zero_cnt();\n\
    \                cnt += (bv[i].rank(r, 0) - bv[i].rank(l, 0));\n            }\n\
    \            l = st, r = en;\n        }\n        return cnt;\n    }\n\n    //\
    \ [l, r)\u5185\u3067[x, y)\u3092\u6E80\u305F\u3059\u5024\u306E\u6570\n    int\
    \ count_range(int l, int r, T x, T y){\n        return count_lower(l, r, y) -\
    \ count_lower(l, r, x);\n    }\n\n    // 0-indexed\u3067k\u756A\u76EE\u306B\u5C0F\
    \u3055\u3044\u3082\u306E\u3092\u8FD4\u3059\n    T kth_min(int l, int r, int k){\n\
    \        T ans = 0;\n        for(int i = W - 1; i >= 0; --i){\n            int\
    \ st = bv[i].rank(l, 0);\n            int en = bv[i].rank(r, 0);\n           \
    \ if(en - st <= k){\n                k -= en - st;\n                l = bv[i].zero_cnt()\
    \ + (l - st);\n                r = bv[i].zero_cnt() + (r - en);\n            \
    \    ans |= (1uLL << i);\n            }\n            else{\n                l\
    \ = st, r = en;\n            }\n        }\n        return ans;\n    }\n\n    //\
    \ [l, r)\u3067\u306Ex\u4EE5\u4E0A\u6700\u5C0F\u5024\n    pair<T, bool> predecessor(int\
    \ l, int r, T x){\n        int idx = count_lower(l, r, x);\n        if(idx ==\
    \ r - l){\n            return make_pair((1uLL << W) - 1, false);\n        }\n\
    \        return make_pair(kth_min(l, r, idx), true);\n    }\n\n    // [l, r)\u3067\
    \u306Ex\u4EE5\u4E0B\u6700\u5927\u5024\n    pair<T, bool> successor(int l, int\
    \ r, T x){\n        int idx = count_lower(l, r, x + 1);\n        if(idx == 0)\n\
    \            return make_pair(0, false);\n        return make_pair(kth_min(l,\
    \ r, idx - 1), true);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/dynamicwaveletmatrix.cpp
  requiredBy: []
  timestamp: '2020-04-25 21:27:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/dynamicwaveletmatrix_rmq.test.cpp
  - verify/dynamicwaveletmatrix_kthmin.test.cpp
documentation_of: lib/classes/dynamicwaveletmatrix.cpp
layout: document
redirect_from:
- /library/lib/classes/dynamicwaveletmatrix.cpp
- /library/lib/classes/dynamicwaveletmatrix.cpp.html
title: lib/classes/dynamicwaveletmatrix.cpp
---
