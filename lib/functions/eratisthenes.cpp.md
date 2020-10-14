---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/functions/eratisthenes.cpp\"\nauto eratosthenes = []{\n\
    \tconstexpr int N = 2e6;\n\tbitset<N> not_prime(3);\n\tfor(int i = 2; i < N; ++i)\n\
    \t\tif(!not_prime[i])\n\t\t\tfor(int j = 2 * i; j < N; j += i)\n\t\t\t\tnot_prime.set(j);\n\
    \treturn not_prime;\n};\n\n"
  code: "auto eratosthenes = []{\n\tconstexpr int N = 2e6;\n\tbitset<N> not_prime(3);\n\
    \tfor(int i = 2; i < N; ++i)\n\t\tif(!not_prime[i])\n\t\t\tfor(int j = 2 * i;\
    \ j < N; j += i)\n\t\t\t\tnot_prime.set(j);\n\treturn not_prime;\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/eratisthenes.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/functions/eratisthenes.cpp
layout: document
redirect_from:
- /library/lib/functions/eratisthenes.cpp
- /library/lib/functions/eratisthenes.cpp.html
title: lib/functions/eratisthenes.cpp
---
