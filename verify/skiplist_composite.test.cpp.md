---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/skiplist.cpp
    title: lib/classes/skiplist.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_set_range_composite
    links:
    - https://judge.yosupo.jp/problem/point_set_range_composite
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_set_range_composite\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \nconst i64 MOD = 998244353;\n\n\n#include \"../lib/classes/skiplist.cpp\"\n\n\
    \nsigned main(){\n    int n, q;\n    cin >> n >> q;\n    vector<i64> a(n), b(n);\n\
    \    for(int i = 0; i < n; ++i)\n        scanf(\"%lld%lld\", &a[i], &b[i]);\n\
    \    auto f = [&](auto p1, auto p2){\n        i64 a = p1.first;\n        i64 b\
    \ = p1.second;\n        i64 c = p2.first;\n        i64 d = p2.second;\n      \
    \  return make_pair((c * a) % MOD, (c * b + d) % MOD);\n    };\n    SkipList<pair<i64,i64>>\
    \ slist(f, make_pair(1LL, 0LL));\n\n    for(int i = 0; i < n; ++i)\n        slist.insert_index(i,\
    \ make_pair(a[i], b[i]));\n    for(int i = 0; i < q; ++i){\n        int t;\n \
    \       scanf(\"%d\", &t);\n        if(t == 0){\n            int p;\n        \
    \    i64 c, d;\n            scanf(\"%d%lld%lld\", &p, &c, &d);\n            slist.erase_index(p);\n\
    \            slist.insert_index(p, make_pair(c, d));\n        }\n        else{\n\
    \            int l, r;\n            i64 x;\n            scanf(\"%d%d%lld\", &l,\
    \ &r, &x);\n            auto p = slist.get(l, r);\n            printf(\"%lld\\\
    n\", (p.first * x + p.second) % MOD);\n        }\n    }\n}\n\n"
  dependsOn:
  - lib/classes/skiplist.cpp
  isVerificationFile: true
  path: verify/skiplist_composite.test.cpp
  requiredBy: []
  timestamp: '2020-04-09 14:56:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/skiplist_composite.test.cpp
layout: document
redirect_from:
- /verify/verify/skiplist_composite.test.cpp
- /verify/verify/skiplist_composite.test.cpp.html
title: verify/skiplist_composite.test.cpp
---
