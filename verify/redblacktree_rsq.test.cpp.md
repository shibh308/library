---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/memorypool.cpp
    title: lib/classes/memorypool.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/redblacktree.cpp
    title: lib/classes/redblacktree.cpp
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
    \n\n#include \"../lib/classes/memorypool.cpp\"\n#include \"../lib/classes/redblacktree.cpp\"\
    \n\n\nsigned main(){\n    RedBlackTree<i64> rb;\n    int n, q;\n    cin >> n >>\
    \ q;\n    auto root = rb.nil;\n    vector<i64> a(n);\n    for(int i = 0; i < n;\
    \ ++i)\n        cin >> a[i];\n    root = rb.build(a);\n    for(int i = 0; i <\
    \ q; ++i){\n        int t, k, x;\n        cin >> t >> k >> x;\n        if(t ==\
    \ 0){\n            rb.set(root, k, x, [](auto x, auto y){return x + y;});\n  \
    \      }\n        else{\n            auto res = rb.range_get(root, k, x);\n  \
    \          root = res.second;\n            printf(\"%lld\\n\", res.first);\n \
    \       }\n    }\n}"
  dependsOn:
  - lib/classes/memorypool.cpp
  - lib/classes/redblacktree.cpp
  isVerificationFile: true
  path: verify/redblacktree_rsq.test.cpp
  requiredBy: []
  timestamp: '2020-04-22 12:46:51+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/redblacktree_rsq.test.cpp
layout: document
redirect_from:
- /verify/verify/redblacktree_rsq.test.cpp
- /verify/verify/redblacktree_rsq.test.cpp.html
title: verify/redblacktree_rsq.test.cpp
---
