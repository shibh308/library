---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/functions/scc.cpp
    title: lib/functions/scc.cpp
  - icon: ':heavy_check_mark:'
    path: lib/functions/scc_dag.cpp
    title: lib/functions/scc_dag.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3075
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3075
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.6/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3075\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\nusing i64 = long long;\n\
    \nconst i64 MOD = 1e9 + 7;\n\n#include \"../lib/functions/scc.cpp\"\n#include\
    \ \"../lib/functions/scc_dag.cpp\"\n\n\ntemplate <typename T>\nbool chmax(T& x,\
    \ T y){\n    if(x < y){\n        x = y;\n        return true;\n    }\n    return\
    \ false;\n}\n\n\nsigned main(){\n    int n, m;\n    cin >> n >> m;\n    vector<int>\
    \ x(n), y(n), z(n);\n    vector<vector<int>> v(n, vector<int>(8, 0));\n    for(int\
    \ i = 0; i < n; ++i){\n        cin >> x[i] >> y[i] >> z[i];\n        for(int j\
    \ = 0; j < 8; ++j){\n            v[i][j] += x[i] * (j & 1 ? -1 : 1);\n       \
    \     v[i][j] += y[i] * (j & 2 ? -1 : 1);\n            v[i][j] += z[i] * (j &\
    \ 4 ? -1 : 1);\n        }\n    }\n    vector<vector<int>> edges(n);\n    for(int\
    \ i = 0; i < m; ++i){\n        int p, q;\n        cin >> p >> q;\n        --p,\
    \ --q;\n        edges[q].push_back(p);\n    }\n    Result res = scc_dag(edges);\n\
    \    int k = res.dag_size;\n    vector<vector<int>> dp(k, vector<int>(8, -MOD));\n\
    \    for(int i = 0; i < n; ++i)\n        for(int j = 0; j < 8; ++j)\n        \
    \    chmax(dp[res.elements[i]][j], v[i][j]);\n\n    for(auto i : res.tps_order){\n\
    \        for(int j = 0; j < 8; ++j){\n            for(auto nex : res.dag_graph[i]){\n\
    \                chmax(dp[nex][j], dp[i][j]);\n            }\n        }\n    }\n\
    \n    for(int i = 0; i < n; ++i){\n        int dist = 0;\n        for(int j =\
    \ 0; j < 8; ++j){\n            chmax(dist, dp[res.elements[i]][j] - v[i][j]);\n\
    \        }\n        cout << dist << endl;\n    }\n}\n"
  dependsOn:
  - lib/functions/scc.cpp
  - lib/functions/scc_dag.cpp
  isVerificationFile: true
  path: verify/scc_dag.test.cpp
  requiredBy: []
  timestamp: '2020-02-25 06:59:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/scc_dag.test.cpp
layout: document
redirect_from:
- /verify/verify/scc_dag.test.cpp
- /verify/verify/scc_dag.test.cpp.html
title: verify/scc_dag.test.cpp
---
