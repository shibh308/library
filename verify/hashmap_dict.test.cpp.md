---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/hashmap.cpp
    title: lib/classes/hashmap.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_4_C\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n#include \"../lib/classes/hashmap.cpp\"\n\n\nsigned main(){\n    ios_base::sync_with_stdio(false);\n\
    \    cin.tie(0);\n    int n;\n    cin >> n;\n    vector<int> type(n);\n    vector<int>\
    \ v(n, 0);\n    string l = \"0ACGT\";\n    for(int i = 0; i < n; ++i){\n     \
    \   string s, t;\n        cin >> s >> t;\n        type[i] = (s == \"find\");\n\
    \        int k = 1;\n        for(int j = 0; j < t.size(); ++j, k *= 5)\n     \
    \       v[i] += l.find(t[j]) * k;\n    }\n\n    HashMap<int, int> h;\n\n    for(int\
    \ i = 0; i < n; ++i){\n        if(type[i] == 0){\n            h.add(v[i], 1);\n\
    \        }\n        else{\n            printf(h.find(v[i]).second ? \"yes\\n\"\
    \ : \"no\\n\");\n        }\n    }\n}\n\n\n"
  dependsOn:
  - lib/classes/hashmap.cpp
  isVerificationFile: true
  path: verify/hashmap_dict.test.cpp
  requiredBy: []
  timestamp: '2020-04-11 13:18:14+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/hashmap_dict.test.cpp
layout: document
redirect_from:
- /verify/verify/hashmap_dict.test.cpp
- /verify/verify/hashmap_dict.test.cpp.html
title: verify/hashmap_dict.test.cpp
---
