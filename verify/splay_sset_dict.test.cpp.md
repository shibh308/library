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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\n#include \"../lib/classes/splaytree_sset.cpp\"\
    \n\nsigned main(){\n    ios_base::sync_with_stdio(false);\n    cin.tie(0);\n \
    \   int n;\n    cin >> n;\n    vector<int> type(n);\n    vector<int> v(n, 0);\n\
    \    string l = \"0ACGT\";\n    for(int i = 0; i < n; ++i){\n        string s,\
    \ t;\n        cin >> s >> t;\n        type[i] = (s == \"find\");\n        int\
    \ k = 1;\n        for(int j = 0; j < t.size(); ++j, k *= 5)\n            v[i]\
    \ += l.find(t[j]) * k;\n    }\n\n    SplayTree<int> sp;\n    auto root = sp.nil;\n\
    \n    for(int i = 0; i < n; ++i){\n        if(type[i] == 0){\n            root\
    \ = sp.insert(root, v[i]).first;\n        }\n        else{\n            bool fl;\n\
    \            SplayTree<int>::NodePtr ptr;\n            tie(ptr, fl) = sp.lower_bound(root,\
    \ v[i]);\n            if(fl)\n                root = ptr;\n            printf(fl\
    \ && root->val == v[i] ? \"yes\\n\" : \"no\\n\");\n        }\n    }\n}\n\n\n\n"
  dependsOn:
  - lib/classes/splaytree_sset.cpp
  isVerificationFile: true
  path: verify/splay_sset_dict.test.cpp
  requiredBy: []
  timestamp: '2020-04-10 23:19:58+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/splay_sset_dict.test.cpp
layout: document
redirect_from:
- /verify/verify/splay_sset_dict.test.cpp
- /verify/verify/splay_sset_dict.test.cpp.html
title: verify/splay_sset_dict.test.cpp
---
