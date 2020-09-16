---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/functions/rerooting.cpp
    title: lib/functions/rerooting.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_5_A\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"../lib/functions/rerooting.cpp\"\n\n\nsigned main(){\n    int n;\n\
    \    cin >> n;\n    vector<int> a(n - 1), b(n - 1), c(n - 1);\n    vector<vector<int>>\
    \ edges(2 * n - 1);\n    vector<int> v(2 * n - 1, 0);\n    for(int i = 0; i <\
    \ n - 1; ++i){\n        cin >> a[i] >> b[i] >> c[i];\n        edges[a[i]].emplace_back(n\
    \ + i);\n        edges[n + i].emplace_back(b[i]);\n        edges[b[i]].emplace_back(n\
    \ + i);\n        edges[n + i].emplace_back(a[i]);\n        v[i + n] = c[i];\n\
    \    }\n\n    function<int(int,int)> f = [&](int x, int y){return max(x, y);};\n\
    \    function<int(int,int)> g = [&](int x, int idx){return x + v[idx];};\n\n \
    \   auto res = rerooting(edges, v, f, g, 0);\n    cout << *max_element(res.begin(),\
    \ next(res.begin(), n)) << endl;\n}"
  dependsOn:
  - lib/functions/rerooting.cpp
  isVerificationFile: true
  path: verify/rerooting_diameter.test.cpp
  requiredBy: []
  timestamp: '2020-04-29 14:02:11+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/rerooting_diameter.test.cpp
layout: document
redirect_from:
- /verify/verify/rerooting_diameter.test.cpp
- /verify/verify/rerooting_diameter.test.cpp.html
title: verify/rerooting_diameter.test.cpp
---
