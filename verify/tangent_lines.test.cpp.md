---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/geometry.cpp
    title: lib/geometry.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2201
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2201
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2201\"\
    \n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \ntemplate <typename T>\nbool chmax(T& x, T y){\n    if(x < y){\n        x = y;\n\
    \        return true;\n    }\n    return false;\n}\n\n\n#include \"../lib/geometry.cpp\"\
    \n\nbool solve(){\n    int n;\n    cin >> n;\n    if(!n)\n        return false;\n\
    \    vector<int> x(n);\n    vector<int> y(n);\n    vector<int> r(n);\n    vector<int>\
    \ m(n);\n    for(int i = 0; i < n; ++i)\n        cin >> x[i] >> y[i] >> r[i] >>\
    \ m[i];\n    if(n == 1){\n        cout << 1 << endl;\n        return true;\n \
    \   }\n    using namespace geometry;\n    vector<C> circles, power;\n    for(int\
    \ i = 0; i < n; ++i){\n        circles.emplace_back(x[i], y[i], r[i]);\n     \
    \   power.emplace_back(x[i], y[i], r[i] + m[i]);\n    }\n\n    vector<pair<P,P>>\
    \ vs;\n    for(int i = 0; i < n; ++i){\n        for(int j = i + 1; j < n; ++j){\n\
    \            auto res = tangent_lines(circles[i], circles[j]);\n            for(auto\
    \ p : res)\n                vs.push_back(p);\n            res = tangent_lines(circles[i],\
    \ power[j]);\n            for(auto p : res)\n                vs.push_back(p);\n\
    \            res = tangent_lines(power[i], circles[j]);\n            for(auto\
    \ p : res)\n                vs.push_back(p);\n            res = tangent_lines(power[i],\
    \ power[j]);\n            for(auto p : res)\n                vs.push_back(p);\n\
    \        }\n    }\n    int ans = 0;\n    for(auto& p : vs){\n        P p1, p2;\n\
    \        tie(p1, p2) = p;\n        int cnt = 0;\n        for(int i = 0; i < n;\
    \ ++i){\n            D d = dist(p1, p2, circles[i]);\n            if(r[i] < d\
    \ + eps && d < r[i] + m[i] + eps)\n                ++cnt;\n        }\n       \
    \ chmax(ans, cnt);\n    }\n    cout << ans << endl;\n    return true;\n}\n\nsigned\
    \ main(){\n    while(solve());\n}\n"
  dependsOn:
  - lib/geometry.cpp
  isVerificationFile: true
  path: verify/tangent_lines.test.cpp
  requiredBy: []
  timestamp: '2020-02-25 16:29:27+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/tangent_lines.test.cpp
layout: document
redirect_from:
- /verify/verify/tangent_lines.test.cpp
- /verify/verify/tangent_lines.test.cpp.html
title: verify/tangent_lines.test.cpp
---
