---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/memorypool.cpp
    title: lib/classes/memorypool.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/zdd.cpp
    title: lib/classes/zdd.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_1_B\"\
    \n#include \"bits/stdc++.h\"\n\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \nconst i64 MOD = i64(1e9) + 7;\nconst i64 INF = i64(1e18) + 7;\n\n\n#include\
    \ \"../lib/classes/memorypool.cpp\"\n#include \"../lib/classes/zdd.cpp\"\n\n\n\
    signed main(){\n    int n, k;\n    cin >> n >> k;\n    vector<i64> v(n), w(n);\n\
    \    for(int i = 0; i < n; ++i)\n        cin >> v[i] >> w[i];\n    auto f = [&](int\
    \ p, int i, bool fl){\n        if(fl)\n            p += w[i];\n        if(p >\
    \ k)\n            return make_pair(0, 0);\n        if(i + 1 == n)\n          \
    \  return make_pair(0, int(p <= k));\n        return make_pair(p, -1);\n    };\n\
    \    ZDD zdd;\n    auto root = zdd.build<int>(f, 0);\n    cout << zdd.linear_func_max(root,\
    \ v) << endl;\n}\n\n"
  dependsOn:
  - lib/classes/memorypool.cpp
  - lib/classes/zdd.cpp
  isVerificationFile: true
  path: verify/zdd_knapsack.test.cpp
  requiredBy: []
  timestamp: '2020-04-29 13:59:55+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/zdd_knapsack.test.cpp
layout: document
redirect_from:
- /verify/verify/zdd_knapsack.test.cpp
- /verify/verify/zdd_knapsack.test.cpp.html
title: verify/zdd_knapsack.test.cpp
---
