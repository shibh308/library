---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/dynamicbitvector.cpp
    title: lib/classes/dynamicbitvector.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/dynamicwaveletmatrix.cpp
    title: lib/classes/dynamicwaveletmatrix.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/memorypool.cpp
    title: lib/classes/memorypool.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A\"\
    \n#include \"bits/stdc++.h\"\n\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"./lib/classes/memorypool.cpp\"\n#include \"./lib/classes/dynamicbitvector.cpp\"\
    \n#include \"./lib/classes/dynamicwaveletmatrix.cpp\"\n\n\nsigned main(){\n\n\
    \    int n, q;\n    cin >> n >> q;\n\n    vector<uint64_t> a(n, (1uLL << 31) -\
    \ 1);\n    WaveletMatrix<uint64_t, 33> wm(a);\n    for(int i = 0; i < q; ++i){\n\
    \        int t, x, y;\n        scanf(\"%d%d%d\", &t, &x, &y);\n        if(t ==\
    \ 0){\n            wm.erase(x);\n            wm.insert(x, y);\n        }\n   \
    \     else{\n            printf(\"%lu\\n\", wm.kth_min(x, ++y, 0));\n        }\n\
    \    }\n}\n\n"
  dependsOn:
  - lib/classes/memorypool.cpp
  - lib/classes/dynamicbitvector.cpp
  - lib/classes/dynamicwaveletmatrix.cpp
  isVerificationFile: true
  path: verify/dynamicwaveletmatrix_rmq.test.cpp
  requiredBy: []
  timestamp: '2020-04-25 21:27:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/dynamicwaveletmatrix_rmq.test.cpp
layout: document
redirect_from:
- /verify/verify/dynamicwaveletmatrix_rmq.test.cpp
- /verify/verify/dynamicwaveletmatrix_rmq.test.cpp.html
title: verify/dynamicwaveletmatrix_rmq.test.cpp
---
