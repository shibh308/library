---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/sparsetable.cpp
    title: lib/classes/sparsetable.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/lineartimesparsetable.cpp
    title: lib/classes/lineartimesparsetable.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/substrmatching.cpp
    title: lib/classes/substrmatching.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\n\n#include \"../lib/classes/sparsetable.cpp\"\
    \n#include \"../lib/classes/lineartimesparsetable.cpp\"\n#include \"../lib/classes/substrmatching.cpp\"\
    \n\n\nsigned main(){\n    string s, t;\n    cin >> s;\n    SubstrMatching p(s);\n\
    \    int q;\n    cin >> q;\n    for(int i = 0; i < q; ++i){\n        cin >> t;\n\
    \        printf(\"%d\\n\", p.contains(t));\n    }\n}\n\n"
  dependsOn:
  - lib/classes/sparsetable.cpp
  - lib/classes/lineartimesparsetable.cpp
  - lib/classes/substrmatching.cpp
  isVerificationFile: true
  path: verify/multi_str_matching.test.cpp
  requiredBy: []
  timestamp: '2020-06-02 15:59:15+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/multi_str_matching.test.cpp
layout: document
redirect_from:
- /verify/verify/multi_str_matching.test.cpp
- /verify/verify/multi_str_matching.test.cpp.html
title: verify/multi_str_matching.test.cpp
---
