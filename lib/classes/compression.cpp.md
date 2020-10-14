---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/compression.cpp\"\ntemplate<typename T>\nstruct\
    \ Compression{\n    vector<T> compvec;\n    Compression(vector<T>& inp){//\u5727\
    \u7E2E\u3059\u308B\n        compvec = inp;\n        sort(compvec.begin(), compvec.end());\n\
    \        compvec.erase(unique(compvec.begin(), compvec.end()), compvec.end());\n\
    \    }\n    int Index(T val){//\u5727\u7E2E\u3092\u5143\u306B\u5BFE\u5FDC\u3059\
    \u308B\u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u3092\u8FD4\u3059\n        auto it\
    \ = lower_bound(compvec.begin(), compvec.end(), val);\n        return distance(compvec.begin(),\
    \ it);\n    }\n    vector<T>& operator*(){\n        return compvec;\n    }\n};\n\
    \n"
  code: "template<typename T>\nstruct Compression{\n    vector<T> compvec;\n    Compression(vector<T>&\
    \ inp){//\u5727\u7E2E\u3059\u308B\n        compvec = inp;\n        sort(compvec.begin(),\
    \ compvec.end());\n        compvec.erase(unique(compvec.begin(), compvec.end()),\
    \ compvec.end());\n    }\n    int Index(T val){//\u5727\u7E2E\u3092\u5143\u306B\
    \u5BFE\u5FDC\u3059\u308B\u30A4\u30F3\u30C7\u30C3\u30AF\u30B9\u3092\u8FD4\u3059\
    \n        auto it = lower_bound(compvec.begin(), compvec.end(), val);\n      \
    \  return distance(compvec.begin(), it);\n    }\n    vector<T>& operator*(){\n\
    \        return compvec;\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/compression.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/compression.cpp
layout: document
redirect_from:
- /library/lib/classes/compression.cpp
- /library/lib/classes/compression.cpp.html
title: lib/classes/compression.cpp
---
