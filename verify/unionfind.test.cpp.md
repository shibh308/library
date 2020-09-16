---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/unionfind.cpp
    title: lib/classes/unionfind.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/unionfind
    links:
    - https://judge.yosupo.jp/problem/unionfind
  bundledCode: "#line 1 \"verify/unionfind.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#line\
    \ 1 \"lib/classes/unionfind.cpp\"\nstruct UnionFind{\n    vector<int> par;\n \
    \   int count;\n    UnionFind(int n) : par(n, -1), count(0){}\n    int Find(int\
    \ x){return par[x] < 0 ? x : Find(par[x]);}\n    int Size(int x){return par[x]\
    \ < 0 ? -par[x] : Size(par[x]);}\n    bool Unite(int x, int y){\n        x = Find(x);\n\
    \        y = Find(y);\n        if(x == y)\n            return false;\n       \
    \ if(par[x] > par[y])\n            swap(x, y);\n        par[x] += par[y];\n  \
    \      par[y] = x;\n        return ++count;\n    }\n};\n\n#line 8 \"verify/unionfind.test.cpp\"\
    \n\n\nsigned main() {\n\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    vector<int>\
    \ t(q), u(q), v(q);\n    for(int i = 0; i < q; ++i)\n        cin >> t[i] >> u[i]\
    \ >> v[i];\n\n    UnionFind uf(n);\n    for(int i = 0; i < q; ++i){\n        if(t[i]\
    \ == 0)\n            uf.Unite(u[i], v[i]);\n        else\n            cout <<\
    \ (uf.Find(u[i]) == uf.Find(v[i])) << endl;\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#include \"../lib/classes/unionfind.cpp\"\
    \n\n\nsigned main() {\n\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    vector<int>\
    \ t(q), u(q), v(q);\n    for(int i = 0; i < q; ++i)\n        cin >> t[i] >> u[i]\
    \ >> v[i];\n\n    UnionFind uf(n);\n    for(int i = 0; i < q; ++i){\n        if(t[i]\
    \ == 0)\n            uf.Unite(u[i], v[i]);\n        else\n            cout <<\
    \ (uf.Find(u[i]) == uf.Find(v[i])) << endl;\n    }\n}\n"
  dependsOn:
  - lib/classes/unionfind.cpp
  isVerificationFile: true
  path: verify/unionfind.test.cpp
  requiredBy: []
  timestamp: '2019-12-04 00:43:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/unionfind.test.cpp
layout: document
redirect_from:
- /verify/verify/unionfind.test.cpp
- /verify/verify/unionfind.test.cpp.html
title: verify/unionfind.test.cpp
---
