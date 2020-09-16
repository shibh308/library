---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/eulertour.test.cpp
    title: verify/eulertour.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/eulertour.cpp\"\nstruct EulerTour{\n    int\
    \ n;\n    vector<int> in, out;\n    EulerTour(vector<vector<int>>& edges, int\
    \ par = 0) : n(edges.size()), in(n, -1), out(n, -1){\n        int cnt = 0;\n \
    \       function<void(int)> f = [&](int x){\n            in[x] = cnt++;\n    \
    \        for(auto y : edges[x]){\n                if(in[y] == -1)\n          \
    \          f(y);\n            }\n            out[x] = cnt;\n        };\n     \
    \   f(par);\n    }\n    int get_pos(int x){\n        return in[x];\n    }\n  \
    \  // \u81EA\u8EAB\u3092\u542B\u307F\u305F\u304F\u306A\u3044\u5834\u5408\u306F\
    (in[x] + 1, out[x])\n    pair<int,int> get_subtree(int x){\n        return make_pair(in[x],\
    \ out[x]);\n    }\n};\n\n"
  code: "struct EulerTour{\n    int n;\n    vector<int> in, out;\n    EulerTour(vector<vector<int>>&\
    \ edges, int par = 0) : n(edges.size()), in(n, -1), out(n, -1){\n        int cnt\
    \ = 0;\n        function<void(int)> f = [&](int x){\n            in[x] = cnt++;\n\
    \            for(auto y : edges[x]){\n                if(in[y] == -1)\n      \
    \              f(y);\n            }\n            out[x] = cnt;\n        };\n \
    \       f(par);\n    }\n    int get_pos(int x){\n        return in[x];\n    }\n\
    \    // \u81EA\u8EAB\u3092\u542B\u307F\u305F\u304F\u306A\u3044\u5834\u5408\u306F\
    (in[x] + 1, out[x])\n    pair<int,int> get_subtree(int x){\n        return make_pair(in[x],\
    \ out[x]);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/eulertour.cpp
  requiredBy: []
  timestamp: '2020-03-06 18:23:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/eulertour.test.cpp
documentation_of: lib/classes/eulertour.cpp
layout: document
redirect_from:
- /library/lib/classes/eulertour.cpp
- /library/lib/classes/eulertour.cpp.html
title: lib/classes/eulertour.cpp
---
