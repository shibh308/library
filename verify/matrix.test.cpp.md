---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/matrix.cpp
    title: lib/classes/matrix.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1327
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1327
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1327\"\
    \n\n#include \"bits/stdc++.h\"\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \nstruct ModInt{\n    static i64 mod;\n    i64 p;\n\n    ModInt() : p(0){}\n \
    \   ModInt(i64 x){p = x >= 0 ? x % mod : x + (-x + mod - 1) / mod * mod;}\n\n\
    \    ModInt& operator+=(const ModInt& y){p = p + *y - ((p + *y) >= mod ? mod :\
    \ 0); return *this;}\n    ModInt& operator-=(const ModInt& y){p = p - *y + (p\
    \ - *y < 0 ? mod : 0); return *this;}\n    ModInt& operator*=(const ModInt& y){p\
    \ = (p * *y) % mod; return *this;}\n\n    ModInt operator+(const ModInt& y) const{ModInt\
    \ x = *this; return x += y;}\n    ModInt operator-(const ModInt& y) const{ModInt\
    \ x = *this; return x -= y;}\n    ModInt operator*(const ModInt& y) const{ModInt\
    \ x = *this; return x *= y;}\n\n    ModInt& operator++(){p = (p + 1) % mod; return\
    \ *this;}\n    ModInt& operator--(){p = (p - 1 + mod) % mod; return *this;}\n\n\
    \    bool operator==(const ModInt& y) const{return p == *y;}\n    bool operator!=(const\
    \ ModInt& y) const{return p != *y;}\n\n    const i64& operator*() const{return\
    \ p;}\n    i64& operator*(){return p;}\n\n};\n\nusing mint = ModInt;\ni64 mint::mod\
    \ = 0;\n\n\n#include \"../lib/classes/matrix.cpp\"\n\nbool solve(){\n    int n,\
    \ m, a, b, c, t;\n    cin >> n >> m >> a >> b >> c >> t;\n    if(!n)\n       \
    \ return false;\n\n    mint::mod = m;\n\n    Matrix<mint> mat(n, n);\n    for(int\
    \ i = 0; i < n; ++i){\n        if(i)\n            mat.at(i - 1, i) = a;\n    \
    \    mat.at(i, i) = b;\n        if(i != n - 1)\n            mat.at(i + 1, i) =\
    \ c;\n    }\n    Matrix<mint> st(1, n);\n    for(int i = 0; i < n; ++i){\n   \
    \     int s;\n        cin >> s;\n        st.at(0, i) = s;\n    }\n    auto res\
    \ = st * mat.pow(t);\n    for(int i = 0; i < n; ++i){\n        cout << *res.at(0,\
    \ i) << \" \\n\"[i == n - 1];\n    }\n\n    return true;\n}\n\nsigned main(){\n\
    \    while(solve());\n}\n"
  dependsOn:
  - lib/classes/matrix.cpp
  isVerificationFile: true
  path: verify/matrix.test.cpp
  requiredBy: []
  timestamp: '2020-02-25 08:21:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/matrix.test.cpp
layout: document
redirect_from:
- /verify/verify/matrix.test.cpp
- /verify/verify/matrix.test.cpp.html
title: verify/matrix.test.cpp
---
