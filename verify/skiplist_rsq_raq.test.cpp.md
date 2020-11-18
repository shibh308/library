---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/lazyskiplist.cpp
    title: lib/classes/lazyskiplist.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_G\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"../lib/classes/lazyskiplist.cpp\"\n\n\nsigned main(){\n    int\
    \ n, q;\n    cin >> n >> q;\n    SkipList<i64,i64> slist([](auto x, auto y){return\
    \ x + y;}, [](auto x, auto y, int z){return x + y * z;}, [](auto x, auto y){return\
    \ x + y;}, 0LL, 0LL);\n    for(int i = 0; i < n; ++i)\n        slist.insert_index(i,\
    \ 0);\n    for(int i = 0; i < q; ++i){\n        int t;\n        scanf(\"%d\",\
    \ &t);\n        if(t == 0){\n            int l, r, x;\n            scanf(\"%d%d%d\"\
    , &l, &r, &x);\n            slist.update(--l, r, x);\n        }else{\n       \
    \     int l, r;\n            scanf(\"%d%d\", &l, &r);\n            printf(\"%lld\\\
    n\", slist.get(--l, r));\n        }\n    }\n}\n\n\n"
  dependsOn:
  - lib/classes/lazyskiplist.cpp
  isVerificationFile: true
  path: verify/skiplist_rsq_raq.test.cpp
  requiredBy: []
  timestamp: '2020-04-06 15:54:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/skiplist_rsq_raq.test.cpp
layout: document
redirect_from:
- /verify/verify/skiplist_rsq_raq.test.cpp
- /verify/verify/skiplist_rsq_raq.test.cpp.html
title: verify/skiplist_rsq_raq.test.cpp
---
