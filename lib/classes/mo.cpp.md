---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/mo.test.cpp
    title: verify/mo.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/mo_query.test.cpp
    title: verify/mo_query.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/mo.cpp\"\nstruct Mo{\n    int l, r;\n    function<void(int)>\
    \ left_add, left_erase, right_add, right_erase;\n    Mo(function<void(int)> left_add,\
    \ function<void(int)> left_erase,\n       function<void(int)> right_add, function<void(int)>\
    \ right_erase,\n       int sl = 0, int sr = 0) :\n       l(sl), r(sr), left_add(left_add),\
    \ left_erase(left_erase), right_add(right_add), right_erase(right_erase){}\n \
    \   void move(int next_l, int next_r){\n        for(int i = l; i < next_l; ++i)\n\
    \            left_erase(i);\n        for(int i = l - 1; i >= next_l; --i)\n  \
    \          left_add(i);\n        for(int i = r; i < next_r; ++i)\n           \
    \ right_add(i);\n        for(int i = r - 1; i >= next_r; --i)\n            right_erase(i);\n\
    \        l = next_l, r = next_r;\n    }\n};\n\n"
  code: "struct Mo{\n    int l, r;\n    function<void(int)> left_add, left_erase,\
    \ right_add, right_erase;\n    Mo(function<void(int)> left_add, function<void(int)>\
    \ left_erase,\n       function<void(int)> right_add, function<void(int)> right_erase,\n\
    \       int sl = 0, int sr = 0) :\n       l(sl), r(sr), left_add(left_add), left_erase(left_erase),\
    \ right_add(right_add), right_erase(right_erase){}\n    void move(int next_l,\
    \ int next_r){\n        for(int i = l; i < next_l; ++i)\n            left_erase(i);\n\
    \        for(int i = l - 1; i >= next_l; --i)\n            left_add(i);\n    \
    \    for(int i = r; i < next_r; ++i)\n            right_add(i);\n        for(int\
    \ i = r - 1; i >= next_r; --i)\n            right_erase(i);\n        l = next_l,\
    \ r = next_r;\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/mo.cpp
  requiredBy: []
  timestamp: '2020-03-03 14:01:09+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/mo.test.cpp
  - verify/mo_query.test.cpp
documentation_of: lib/classes/mo.cpp
layout: document
redirect_from:
- /library/lib/classes/mo.cpp
- /library/lib/classes/mo.cpp.html
title: lib/classes/mo.cpp
---
