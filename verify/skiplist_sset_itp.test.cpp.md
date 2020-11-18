---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/skiplist_sset.cpp
    title: lib/classes/skiplist_sset.cpp
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
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"../lib/classes/skiplist_sset.cpp\"\n\n\nsigned main(){\n    int\
    \ q;\n    scanf(\"%d\", &q);\n    SSet<int> s;\n    for(int i = 0; i < q; ++i){\n\
    \        int t, x;\n        scanf(\"%d%d\", &t, &x);\n        if(t == 0){\n  \
    \          auto ptr = s.lower_bound(x);\n            if(ptr == s.back || ptr->val\
    \ != x)\n                s.insert(x);\n            printf(\"%d\\n\", s.size());\n\
    \        }\n        else if(t == 2){\n            s.erase_key(x);\n        }\n\
    \        else{\n            auto ptr = s.lower_bound(x);\n            printf(\"\
    %d\\n\", ptr != s.back && ptr->val == x);\n        }\n    }\n}\n"
  dependsOn:
  - lib/classes/skiplist_sset.cpp
  isVerificationFile: true
  path: verify/skiplist_sset_itp.test.cpp
  requiredBy: []
  timestamp: '2020-04-10 22:58:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/skiplist_sset_itp.test.cpp
layout: document
redirect_from:
- /verify/verify/skiplist_sset_itp.test.cpp
- /verify/verify/skiplist_sset_itp.test.cpp.html
title: verify/skiplist_sset_itp.test.cpp
---
