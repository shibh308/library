---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/multi_str_matching.test.cpp
    title: verify/multi_str_matching.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string_seatch.test.cpp
    title: verify/string_seatch.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/sparsetable.cpp\"\ntemplate <typename T>\nstruct\
    \ SparseTable{\n    vector<int> len;\n    vector<vector<T>> v;\n    function<T(T,\
    \ T)> f;\n    SparseTable(){}\n    SparseTable(vector<T>& a, function<T(T, T)>\
    \ f) : len(a.size() + 1, 0), v(1, a), f(f){\n        int n = a.size();\n     \
    \   for(int j = 0; (1 << j) < n; ++j){\n            v.emplace_back(n);\n     \
    \       for(int i = 0; i < n; ++i)\n                v[j + 1][i] = (i + (1 << j)\
    \ < n ? f(v[j][i], v[j][i + (1 << j)]) : v[j][i]);\n        }\n        for(int\
    \ i = 2; i <= n; ++i){\n            len[i] = len[i >> 1] + 1;\n        }\n   \
    \ }\n    T get(int l, int r){\n        int siz = r - l;\n        return f(v[len[siz]][l],\
    \ v[len[siz]][r - (1 << len[siz])]);\n    }\n};\n\n"
  code: "template <typename T>\nstruct SparseTable{\n    vector<int> len;\n    vector<vector<T>>\
    \ v;\n    function<T(T, T)> f;\n    SparseTable(){}\n    SparseTable(vector<T>&\
    \ a, function<T(T, T)> f) : len(a.size() + 1, 0), v(1, a), f(f){\n        int\
    \ n = a.size();\n        for(int j = 0; (1 << j) < n; ++j){\n            v.emplace_back(n);\n\
    \            for(int i = 0; i < n; ++i)\n                v[j + 1][i] = (i + (1\
    \ << j) < n ? f(v[j][i], v[j][i + (1 << j)]) : v[j][i]);\n        }\n        for(int\
    \ i = 2; i <= n; ++i){\n            len[i] = len[i >> 1] + 1;\n        }\n   \
    \ }\n    T get(int l, int r){\n        int siz = r - l;\n        return f(v[len[siz]][l],\
    \ v[len[siz]][r - (1 << len[siz])]);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/sparsetable.cpp
  requiredBy: []
  timestamp: '2020-05-31 19:48:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/multi_str_matching.test.cpp
  - verify/string_seatch.test.cpp
documentation_of: lib/classes/sparsetable.cpp
layout: document
redirect_from:
- /library/lib/classes/sparsetable.cpp
- /library/lib/classes/sparsetable.cpp.html
title: lib/classes/sparsetable.cpp
---
