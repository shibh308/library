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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1549
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1549
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1549\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"../lib/classes/bitvector.cpp\"\n#include \"../lib/classes/waveletmatrix.cpp\"\
    \n\n\nsigned main(){\n\n    int n, q;\n    cin >> n;\n    vector<int> a(n);\n\
    \    for(int i = 0; i < n; ++i)\n        cin >> a[i];\n    cin >> q;\n    WaveletMatrix<int,\
    \ 31> wm(a);\n    for(int i = 0; i < q; ++i){\n        int l, r, k;\n        cin\
    \ >> l >> r >> k;\n        auto res = wm.predecessor(l, r + 1, k);\n        auto\
    \ res2 = wm.successor(l, r + 1, k);\n        cout << min(res.second ? res.first\
    \ - k : INT_MAX, res2.second ? k - res2.first : INT_MAX) << endl;\n    }\n}\n\n"
  dependsOn:
  - lib/classes/bitvector.cpp
  - lib/classes/waveletmatrix.cpp
  isVerificationFile: true
  path: verify/waveletmatrix_lowerbound.test.cpp
  requiredBy: []
  timestamp: '2020-04-15 15:25:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/waveletmatrix_lowerbound.test.cpp
layout: document
redirect_from:
- /verify/verify/waveletmatrix_lowerbound.test.cpp
- /verify/verify/waveletmatrix_lowerbound.test.cpp.html
title: verify/waveletmatrix_lowerbound.test.cpp
---
