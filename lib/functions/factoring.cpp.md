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
  bundledCode: "#line 1 \"lib/functions/factoring.cpp\"\nauto factoring = [](i64 x){\n\
    \tint sq = sqrt(x) + 1;\n\tvector<int> ret;\n\tif(x == 1){\n\t\tret.emplace_back(1);\n\
    \t\treturn ret;\n\t}\n\tfor(i64 i = 2; i < sq; ++i)\n\t\twhile(x % i == 0){\n\t\
    \t\tret.emplace_back(i);\n\t\t\tx /= i;\n\t\t}\n\tif(x != 1)\n\t\tret.emplace_back(x);\n\
    \treturn ret;\n};\n\n"
  code: "auto factoring = [](i64 x){\n\tint sq = sqrt(x) + 1;\n\tvector<int> ret;\n\
    \tif(x == 1){\n\t\tret.emplace_back(1);\n\t\treturn ret;\n\t}\n\tfor(i64 i = 2;\
    \ i < sq; ++i)\n\t\twhile(x % i == 0){\n\t\t\tret.emplace_back(i);\n\t\t\tx /=\
    \ i;\n\t\t}\n\tif(x != 1)\n\t\tret.emplace_back(x);\n\treturn ret;\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/factoring.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/functions/factoring.cpp
layout: document
redirect_from:
- /library/lib/functions/factoring.cpp
- /library/lib/functions/factoring.cpp.html
title: lib/functions/factoring.cpp
---
