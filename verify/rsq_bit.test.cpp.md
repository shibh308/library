---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/binaryindexedtree.cpp
    title: lib/classes/binaryindexedtree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"verify/rsq_bit.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#line\
    \ 1 \"lib/classes/binaryindexedtree.cpp\"\ntemplate <typename T>\nstruct BIT{\n\
    \    vector<T> elm;\n    BIT(int n, T init = T()) : elm(n + 1, init){\n    }\n\
    \n    // [0, x)\n    T sum(int x){\n        T val = 0;\n        for(; x > 0; x\
    \ -= x & -x)\n            val += elm[x];\n        return val;\n    }\n\n    //\
    \ [l, r)\n    T sum(int l, int r){\n        return sum(r) - sum(l);\n    }\n\n\
    \    void add(int x, T val){\n        for(++x; x < elm.size(); x += x & -x)\n\
    \            elm[x] += val;\n    }\n};\n\n#line 8 \"verify/rsq_bit.test.cpp\"\n\
    \n\nsigned main() {\n\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n\n    BIT<i64>\
    \ b(n);\n    for(int i = 0; i < n; ++i){\n        int a;\n        cin >> a;\n\
    \        b.add(i, a);\n    }\n    for(int i = 0; i < q; ++i){\n        int t,\
    \ a, c;\n        cin >> t >> a >> c;\n        if(t == 0){\n            b.add(a,\
    \ c);\n        }\n        else{\n            cout << b.sum(a, c) << endl;\n  \
    \      }\n    }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#include\
    \ \"../lib/classes/binaryindexedtree.cpp\"\n\n\nsigned main() {\n\n    int n,\
    \ q;\n    scanf(\"%d%d\", &n, &q);\n\n    BIT<i64> b(n);\n    for(int i = 0; i\
    \ < n; ++i){\n        int a;\n        cin >> a;\n        b.add(i, a);\n    }\n\
    \    for(int i = 0; i < q; ++i){\n        int t, a, c;\n        cin >> t >> a\
    \ >> c;\n        if(t == 0){\n            b.add(a, c);\n        }\n        else{\n\
    \            cout << b.sum(a, c) << endl;\n        }\n    }\n}\n\n"
  dependsOn:
  - lib/classes/binaryindexedtree.cpp
  isVerificationFile: true
  path: verify/rsq_bit.test.cpp
  requiredBy: []
  timestamp: '2019-12-05 03:16:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/rsq_bit.test.cpp
layout: document
redirect_from:
- /verify/verify/rsq_bit.test.cpp
- /verify/verify/rsq_bit.test.cpp.html
title: verify/rsq_bit.test.cpp
---
