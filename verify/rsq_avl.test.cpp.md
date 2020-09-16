---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/avl.cpp
    title: lib/classes/avl.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    #include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n#include \"../lib/classes/avl.cpp\"\n\n\nsigned main() {\n\n    int n, q;\n\
    \    scanf(\"%d%d\", &n, &q);\n\n    AVL<i64> avl([](auto x, auto y){return x\
    \ + y;}, 0);\n    auto root = avl.nil;\n    for(int i = 0; i < n; ++i){\n    \
    \    int a;\n        cin >> a;\n        root = avl.insert(root, i, a);\n    }\n\
    \n    for(int i = 0; i < q; ++i){\n        int t, a, c;\n        cin >> t >> a\
    \ >> c;\n        if(t == 0){\n            avl.update(root, a, c);\n        }\n\
    \        else{\n            cout << avl.get(root, a, c) << endl;\n        }\n\
    \    }\n\n}\n\n"
  dependsOn:
  - lib/classes/avl.cpp
  isVerificationFile: true
  path: verify/rsq_avl.test.cpp
  requiredBy: []
  timestamp: '2020-02-26 07:59:33+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/rsq_avl.test.cpp
layout: document
redirect_from:
- /verify/verify/rsq_avl.test.cpp
- /verify/verify/rsq_avl.test.cpp.html
title: verify/rsq_avl.test.cpp
---
