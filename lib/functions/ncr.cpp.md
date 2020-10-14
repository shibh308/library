---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/functions/ncr.cpp\"\nauto ncr = [&fact, &inv](int n,\
    \ int r){\n\tif(n < 0 || r < 0 || n < r)\n\t\treturn mint(0);\n\treturn fact[n]\
    \ * inv[r] * inv[n - r];\n};\n\n"
  code: "auto ncr = [&fact, &inv](int n, int r){\n\tif(n < 0 || r < 0 || n < r)\n\t\
    \treturn mint(0);\n\treturn fact[n] * inv[r] * inv[n - r];\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/ncr.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/functions/ncr.cpp
layout: document
redirect_from:
- /library/lib/functions/ncr.cpp
- /library/lib/functions/ncr.cpp.html
title: lib/functions/ncr.cpp
---
