---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/functions/modpow.cpp\"\nauto mpow = [](auto x, i64 y){\n\
    \tauto z = x;\n\tdecltype(x) val = y & 1 ? x : decltype(x)(1);\n\twhile(z *= z,\
    \ y >>= 1)\n\t\tif(y & 1)\n\t\t\tval *= z;\n\treturn val;\n};\n\n"
  code: "auto mpow = [](auto x, i64 y){\n\tauto z = x;\n\tdecltype(x) val = y & 1\
    \ ? x : decltype(x)(1);\n\twhile(z *= z, y >>= 1)\n\t\tif(y & 1)\n\t\t\tval *=\
    \ z;\n\treturn val;\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/modpow.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/functions/modpow.cpp
layout: document
redirect_from:
- /library/lib/functions/modpow.cpp
- /library/lib/functions/modpow.cpp.html
title: lib/functions/modpow.cpp
---
