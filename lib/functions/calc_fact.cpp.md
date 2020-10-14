---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/functions/calc_fact.cpp\"\nauto calc_fact = [mpow]{\n\
    \tconstexpr int N = 2e6;\n\tvector<mint> fact(N + 1, 1);\n\tvector<mint> inv(N\
    \ + 1, 1);\n\tfor(int i = 1; i < N; ++i){\n\t\tfact[i + 1] = fact[i] * (i + 1);\n\
    \t\tinv[i + 1] = mpow(fact[i + 1], MOD - 2);\n\t}\n\treturn make_pair(fact, inv);\n\
    };\nvector<mint> fact, inv;\ntie(fact, inv) = calc_fact();\n\n"
  code: "auto calc_fact = [mpow]{\n\tconstexpr int N = 2e6;\n\tvector<mint> fact(N\
    \ + 1, 1);\n\tvector<mint> inv(N + 1, 1);\n\tfor(int i = 1; i < N; ++i){\n\t\t\
    fact[i + 1] = fact[i] * (i + 1);\n\t\tinv[i + 1] = mpow(fact[i + 1], MOD - 2);\n\
    \t}\n\treturn make_pair(fact, inv);\n};\nvector<mint> fact, inv;\ntie(fact, inv)\
    \ = calc_fact();\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/calc_fact.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/functions/calc_fact.cpp
layout: document
redirect_from:
- /library/lib/functions/calc_fact.cpp
- /library/lib/functions/calc_fact.cpp.html
title: lib/functions/calc_fact.cpp
---
