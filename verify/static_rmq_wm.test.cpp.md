---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/bitvector.cpp
    title: lib/classes/bitvector.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/waveletmatrix.cpp
    title: lib/classes/waveletmatrix.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"verify/static_rmq_wm.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#line\
    \ 1 \"lib/classes/bitvector.cpp\"\nstruct BitVector{\n    vector<uint64_t> v;\n\
    \    vector<int> r;\n    BitVector(){}\n    void build(){\n        r.assign(v.size()\
    \ + 1, 0);\n        for(int i = 0; i < v.size(); ++i)\n            r[i + 1] =\
    \ r[i] + __builtin_popcountll(v[i]);\n    }\n    bool access(int x){\n       \
    \ return (v[x >> 6] >> (x & 63)) & 1;\n    }\n    // [0, x)\u306E1\u306E\u51FA\
    \u73FE\u56DE\u6570\n    int rank(int x){\n        return r[x >> 6] + __builtin_popcountll(v[x\
    \ >> 6] & ((1uLL << (x & 63)) - 1));\n    }\n    int rank(int x, bool fl){\n \
    \       return fl ? rank(x) : x - rank(x);\n    }\n};\n\n#line 1 \"lib/classes/waveletmatrix.cpp\"\
    \ntemplate <typename T, int W>\nstruct WaveletMatrix{\n\n    array<BitVector,\
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
    \ r, idx - 1), true);\n    }\n};\n\n#line 9 \"verify/static_rmq_wm.test.cpp\"\n\
    \n\nsigned main() {\n\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    vector<int>\
    \ a(n);\n    for(auto& x : a)\n        cin >> x;\n    WaveletMatrix<int, 31> wm(a);\n\
    \    for(int i = 0; i < q; ++i){\n        int l, r;\n        cin >> l >> r;\n\
    \        cout << wm.kth_min(l, r, 0) << endl;\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#include \"../lib/classes/bitvector.cpp\"\
    \n#include \"../lib/classes/waveletmatrix.cpp\"\n\n\nsigned main() {\n\n    int\
    \ n, q;\n    scanf(\"%d%d\", &n, &q);\n    vector<int> a(n);\n    for(auto& x\
    \ : a)\n        cin >> x;\n    WaveletMatrix<int, 31> wm(a);\n    for(int i =\
    \ 0; i < q; ++i){\n        int l, r;\n        cin >> l >> r;\n        cout <<\
    \ wm.kth_min(l, r, 0) << endl;\n    }\n}\n"
  dependsOn:
  - lib/classes/bitvector.cpp
  - lib/classes/waveletmatrix.cpp
  isVerificationFile: true
  path: verify/static_rmq_wm.test.cpp
  requiredBy: []
  timestamp: '2020-04-15 15:28:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/static_rmq_wm.test.cpp
layout: document
redirect_from:
- /verify/verify/static_rmq_wm.test.cpp
- /verify/verify/static_rmq_wm.test.cpp.html
title: verify/static_rmq_wm.test.cpp
---
