---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/memorypool.cpp
    title: lib/classes/memorypool.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/twothreetree.cpp
    title: lib/classes/twothreetree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\n#include \"../lib/classes/memorypool.cpp\"\
    \n#include \"../lib/classes/twothreetree.cpp\"\n\nsigned main(){\n    TwoThreeTree<int>\
    \ bt;\n    int q;\n    cin >> q;\n    for(int i = 0; i < q; ++i){\n        int\
    \ t, x;\n        cin >> t >> x;\n\n        auto res = bt.lower_bound(x);\n\n \
    \       if(t == 0){\n            if(!(res.second && x == res.first))\n       \
    \         bt.insert(x);\n            printf(\"%d\\n\", bt.size());\n        }\n\
    \        else if(t == 1){\n            printf(\"%d\\n\", res.second && x == res.first);\n\
    \        }\n        else{\n            if(res.second && x == res.first){\n   \
    \             bt.erase(x);\n            }\n        }\n    }\n}"
  dependsOn:
  - lib/classes/memorypool.cpp
  - lib/classes/twothreetree.cpp
  isVerificationFile: true
  path: verify/twothreetree.test.cpp
  requiredBy: []
  timestamp: '2020-04-21 23:33:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/twothreetree.test.cpp
layout: document
redirect_from:
- /verify/verify/twothreetree.test.cpp
- /verify/verify/twothreetree.test.cpp.html
title: verify/twothreetree.test.cpp
---
