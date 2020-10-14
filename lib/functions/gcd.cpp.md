---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/functions/gcd.cpp\"\nauto gcd = [](i64 x, i64 y){\n\t\
    while(y){\n\t\ti64 z = x % y;\n\t\tx = y;\n\t\ty = z;\n\t}\n\treturn x;\n};\n\n"
  code: "auto gcd = [](i64 x, i64 y){\n\twhile(y){\n\t\ti64 z = x % y;\n\t\tx = y;\n\
    \t\ty = z;\n\t}\n\treturn x;\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/gcd.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/functions/gcd.cpp
layout: document
redirect_from:
- /library/lib/functions/gcd.cpp
- /library/lib/functions/gcd.cpp.html
title: lib/functions/gcd.cpp
---
