---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/hashmap.cpp
    title: lib/classes/hashmap.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/splaytree_sset.cpp
    title: lib/classes/splaytree_sset.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/xfasttrie_yft.cpp
    title: lib/classes/xfasttrie_yft.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/yfasttrie.cpp
    title: lib/classes/yfasttrie.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"../lib/classes/hashmap.cpp\"\n#include \"../lib/classes/splaytree_sset.cpp\"\
    \n#include \"../lib/classes/xfasttrie_yft.cpp\"\n#include \"../lib/classes/yfasttrie.cpp\"\
    \n\n\nsigned main(){\n    int q;\n    scanf(\"%d\", &q);\n    YFastTrie<int, 31>\
    \ s;\n    for(int i = 0; i < q; ++i){\n        int t, x;\n        scanf(\"%d%d\"\
    , &t, &x);\n        if(t == 0){\n            auto ptr = s.lower_bound(x);\n  \
    \          if(ptr == s.splay.nil || ptr->val != x)\n                s.insert(x);\n\
    \            printf(\"%d\\n\", s.n - 1);\n        }\n        else if(t == 2){\n\
    \            s.erase(x);\n        }\n        else{\n            auto ptr = s.lower_bound(x);\n\
    \            printf(\"%d\\n\", ptr != s.splay.nil && ptr->val == x);\n       \
    \ }\n    }\n}\n"
  dependsOn:
  - lib/classes/hashmap.cpp
  - lib/classes/splaytree_sset.cpp
  - lib/classes/xfasttrie_yft.cpp
  - lib/classes/yfasttrie.cpp
  isVerificationFile: true
  path: verify/yfastttrie_itp.test.cpp
  requiredBy: []
  timestamp: '2020-04-11 13:43:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/yfastttrie_itp.test.cpp
layout: document
redirect_from:
- /verify/verify/yfastttrie_itp.test.cpp
- /verify/verify/yfastttrie_itp.test.cpp.html
title: verify/yfastttrie_itp.test.cpp
---
