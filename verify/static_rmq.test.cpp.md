---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/disjointsparsetable.cpp
    title: lib/classes/disjointsparsetable.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"verify/static_rmq.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#line\
    \ 1 \"lib/classes/disjointsparsetable.cpp\"\ntemplate <typename T>\nstruct DisjointSparseTable{\n\
    \    function<T(T, T)> f;\n    vector<vector<T>> v;\n\n    DisjointSparseTable(vector<T>&\
    \ inp, function<T(T, T)> f) : f(f){\n        int n = inp.size();\n        int\
    \ b;\n        for(b = 0; (1 << b) <= inp.size(); ++b);\n        v.assign(b, vector<T>(n));\n\
    \        for(int i = 0; i < n; ++i)\n            v[0][i] = inp[i];\n        for(int\
    \ i = 1; i < b; ++i){\n            int siz = 1 << i;\n            for(int j =\
    \ 0; j < n; j += siz << 1){\n                int t = min(j + siz, n);\n      \
    \          v[i][t - 1] = inp[t - 1];\n                for(int k = t - 2; k >=\
    \ j; --k)\n                    v[i][k] = f(inp[k], v[i][k + 1]);\n           \
    \     if(t >= n)\n                    break;\n                v[i][t] = inp[t];\n\
    \                int r = min(t + siz, n);\n                for(int k = t + 1;\
    \ k < r; ++k)\n                    v[i][k] = f(v[i][k - 1], inp[k]);\n       \
    \     }\n        }\n    }\n\n    T get(int l, int r){\n        if(l >= --r)\n\
    \            return v[0][l];\n        int p = 31 - __builtin_clz(l ^ r);\n   \
    \     return f(v[p][l], v[p][r]);\n    }\n};\n\n#line 8 \"verify/static_rmq.test.cpp\"\
    \n\n\nsigned main() {\n\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    vector<int>\
    \ a(n);\n    for(auto& x : a)\n        cin >> x;\n    DisjointSparseTable<int>\
    \ d(a, [](auto x, auto y){return min(x, y);});\n    for(int i = 0; i < q; ++i){\n\
    \        int l, r;\n        cin >> l >> r;\n        cout << d.get(l, r) << endl;\n\
    \    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#include \"../lib/classes/disjointsparsetable.cpp\"\
    \n\n\nsigned main() {\n\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n    vector<int>\
    \ a(n);\n    for(auto& x : a)\n        cin >> x;\n    DisjointSparseTable<int>\
    \ d(a, [](auto x, auto y){return min(x, y);});\n    for(int i = 0; i < q; ++i){\n\
    \        int l, r;\n        cin >> l >> r;\n        cout << d.get(l, r) << endl;\n\
    \    }\n}\n"
  dependsOn:
  - lib/classes/disjointsparsetable.cpp
  isVerificationFile: true
  path: verify/static_rmq.test.cpp
  requiredBy: []
  timestamp: '2019-12-04 00:43:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/static_rmq.test.cpp
layout: document
redirect_from:
- /verify/verify/static_rmq.test.cpp
- /verify/verify/static_rmq.test.cpp.html
title: verify/static_rmq.test.cpp
---
