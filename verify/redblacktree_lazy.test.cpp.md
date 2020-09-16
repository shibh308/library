---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/memorypool.cpp
    title: lib/classes/memorypool.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/redblacktree_lazy.cpp
    title: lib/classes/redblacktree_lazy.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_I\"\
    \n#include \"bits/stdc++.h\"\n\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"../lib/classes/memorypool.cpp\"\n#include \"../lib/classes/redblacktree_lazy.cpp\"\
    \n\n\n\n\nsigned main(){\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    RedBlackTree<int,\
    \ int> s([](auto x, auto y){return x + y;}, [](auto x, auto y, int z){return y\
    \ == 100000 ? x : y * z;}, [](auto x, auto y){return y == 100000 ? x : y;}, 0,\
    \ 100000);\n    auto root = s.nil;\n    for(int i = 0; i < n; ++i)\n        root\
    \ = s.insert(root, i, 0);\n    for(int i = 0; i < q; ++i){\n        int t;\n \
    \       scanf(\"%d\", &t);\n        if(t == 0){\n            int l, r, x;\n  \
    \          scanf(\"%d%d%d\", &l, &r, &x);\n            root = s.range_update(root,\
    \ l, r + 1, x);\n        }\n        else{\n            int l, r;\n           \
    \ scanf(\"%d%d\", &l, &r);\n            auto res = s.range_get(root, l, r + 1);\n\
    \            root = res.second;\n            printf(\"%d\\n\", res.first);\n \
    \       }\n    }\n}\n"
  dependsOn:
  - lib/classes/memorypool.cpp
  - lib/classes/redblacktree_lazy.cpp
  isVerificationFile: true
  path: verify/redblacktree_lazy.test.cpp
  requiredBy: []
  timestamp: '2020-04-22 14:31:46+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/redblacktree_lazy.test.cpp
layout: document
redirect_from:
- /verify/verify/redblacktree_lazy.test.cpp
- /verify/verify/redblacktree_lazy.test.cpp.html
title: verify/redblacktree_lazy.test.cpp
---
