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
    PROBLEM: https://yukicoder.me/problems/1937
    links:
    - https://yukicoder.me/problems/1937
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/1937\"\n#include \"bits/stdc++.h\"\
    \n\nusing namespace std;\n\nusing i64 = long long;\n\n\n#include \"../lib/classes/bitvector.cpp\"\
    \n#include \"../lib/classes/waveletmatrix.cpp\"\n\n\nsigned main(){\n\n    int\
    \ n;\n    cin >> n;\n    vector<i64> a(n);\n    for(int i = 0; i < n; ++i){\n\
    \        cin >> a[i];\n        a[i] += 2000000000;\n    }\n    vector<i64> l(n),\
    \ r(n);\n    for(int i = 0; i < n; ++i){\n        cin >> l[i] >> r[i];\n     \
    \   l[i] = a[i] - l[i];\n        r[i] = a[i] + r[i];\n    }\n\n    WaveletMatrix<i64,\
    \ 35> l_wm(l);\n    WaveletMatrix<i64, 35> r_wm(r);\n\n    i64 ans = 0;\n    for(int\
    \ i = 0; i < n; ++i){\n        int l_idx = distance(a.begin(), lower_bound(a.begin(),\
    \ a.end(), l[i]));\n        int r_idx = distance(a.begin(), upper_bound(a.begin(),\
    \ a.end(), r[i])) - 1;\n        ans += r_wm.count_range(l_idx, i, a[i], (1LL <<\
    \ 34));\n        ans += l_wm.count_range(i + 1, r_idx + 1, 0, a[i] + 1);\n   \
    \ }\n    cout << (ans >> 1) << endl;\n\n}\n"
  dependsOn:
  - lib/classes/bitvector.cpp
  - lib/classes/waveletmatrix.cpp
  isVerificationFile: true
  path: verify/waveletmatrix_rangefreq.test.cpp
  requiredBy: []
  timestamp: '2020-04-15 15:25:38+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/waveletmatrix_rangefreq.test.cpp
layout: document
redirect_from:
- /verify/verify/waveletmatrix_rangefreq.test.cpp
- /verify/verify/waveletmatrix_rangefreq.test.cpp.html
title: verify/waveletmatrix_rangefreq.test.cpp
---
