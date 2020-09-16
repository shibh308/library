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
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\
    #include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"../lib/classes/bitvector.cpp\"\n#include \"../lib/classes/waveletmatrix.cpp\"\
    \n\n\nsigned main(){\n    int n, q;\n    cin >> n >> q;\n    vector<int> a(n);\n\
    \    for(int i = 0; i < n; ++i)\n        cin >> a[i];\n    WaveletMatrix<int,\
    \ 31> wm(a);\n    for(int i = 0; i < q; ++i){\n        int l, r, k;\n        cin\
    \ >> l >> r >> k;\n        cout << wm.kth_min(l, r, k) << endl;\n    }\n}\n\n"
  dependsOn:
  - lib/classes/bitvector.cpp
  - lib/classes/waveletmatrix.cpp
  isVerificationFile: true
  path: verify/waveletmatrix_kthmin.test.cpp
  requiredBy: []
  timestamp: '2020-04-15 15:25:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/waveletmatrix_kthmin.test.cpp
layout: document
redirect_from:
- /verify/verify/waveletmatrix_kthmin.test.cpp
- /verify/verify/waveletmatrix_kthmin.test.cpp.html
title: verify/waveletmatrix_kthmin.test.cpp
---
