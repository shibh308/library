---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/splaytree_sset.cpp
    title: lib/classes/splaytree_sset.cpp
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
    \n\n#include \"../lib/classes/splaytree_sset.cpp\"\n\n\nsigned main(){\n    int\
    \ q;\n    scanf(\"%d\", &q);\n    SplayTree<int> s;\n    auto root = s.nil;\n\
    \    for(int i = 0; i < q; ++i){\n        int t, x;\n        scanf(\"%d%d\", &t,\
    \ &x);\n        if(t == 0){\n            root = s.lower_bound(root, x).first;\n\
    \            if(root == s.nil || root->val != x)\n                root = s.insert(root,\
    \ x).first;\n            printf(\"%d\\n\", root->size);\n        }\n        else\
    \ if(t == 2){\n            root = s.erase(root, x).first;\n        }\n       \
    \ else{\n            auto res = s.lower_bound(root, x);\n            root = res.first;\n\
    \            printf(\"%d\\n\", res.second && root->val == x);\n        }\n   \
    \ }\n}\n"
  dependsOn:
  - lib/classes/splaytree_sset.cpp
  isVerificationFile: true
  path: verify/splay_sset_itp.test.cpp
  requiredBy: []
  timestamp: '2020-04-10 23:19:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/splay_sset_itp.test.cpp
layout: document
redirect_from:
- /verify/verify/splay_sset_itp.test.cpp
- /verify/verify/splay_sset_itp.test.cpp.html
title: verify/splay_sset_itp.test.cpp
---
