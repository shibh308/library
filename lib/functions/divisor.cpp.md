---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/functions/divisor.cpp\"\nauto divisor = [](i64 x){\n\
    \tint sq = sqrt(x) + 1;\n\tvector<int> ret;\n\tfor(i64 i = 1; i < sq; ++i)\n\t\
    \tif(!(x % i)){\n\t\t\tret.emplace_back(i);\n\t\t\tif(i * i != x)\n\t\t\t\tret.emplace_back(x\
    \ / i);\n\t\t}\n\tsort(ret.begin(), ret.end());\n\treturn ret;\n};\n\n"
  code: "auto divisor = [](i64 x){\n\tint sq = sqrt(x) + 1;\n\tvector<int> ret;\n\t\
    for(i64 i = 1; i < sq; ++i)\n\t\tif(!(x % i)){\n\t\t\tret.emplace_back(i);\n\t\
    \t\tif(i * i != x)\n\t\t\t\tret.emplace_back(x / i);\n\t\t}\n\tsort(ret.begin(),\
    \ ret.end());\n\treturn ret;\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/divisor.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/functions/divisor.cpp
layout: document
redirect_from:
- /library/lib/functions/divisor.cpp
- /library/lib/functions/divisor.cpp.html
title: lib/functions/divisor.cpp
---
