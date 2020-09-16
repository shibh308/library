---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/binarylifting.cpp
    title: lib/classes/binarylifting.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/lca
    links:
    - https://judge.yosupo.jp/problem/lca
  bundledCode: "#line 1 \"verify/lca_binarylifting.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/lca\"\n#include <bits/stdc++.h>\n\nusing namespace\
    \ std;\n\nusing i64 = long long;\n\n#line 1 \"lib/classes/binarylifting.cpp\"\n\
    struct BinaryLifting{\n    int n;\n    vector<vector<int>> next;\n    vector<int>\
    \ par;\n    vector<vector<int>> childs;\n    vector<int> depth;\n\n    BinaryLifting(vector<vector<int>>&\
    \ edges, int root = 0) : n(edges.size()), depth(n, -1), par(n, -1), childs(n){\n\
    \        function<void(int)> dfs = [&](int x){\n            for(auto y : edges[x])\n\
    \                if(depth[y] == -1){\n                    depth[y] = depth[x]\
    \ + 1;\n                    par[y] = x;\n                    childs[x].push_back(y);\n\
    \                    dfs(y);\n                }\n        };\n        depth[root]\
    \ = 0;\n        dfs(root);\n\n        next.push_back(par);\n        for(int k\
    \ = 0;; ++k){\n            bool fl = false;\n            next.emplace_back(n,\
    \ -1);\n            for(int i = 0; i < n; ++i){\n                next[k + 1][i]\
    \ = (next[k][i] == -1 ? -1 : next[k][next[k][i]]);\n                if(next[k\
    \ + 1][i] != -1)\n                    fl = true;\n            }\n            if(!fl)\n\
    \                break;\n        }\n    }\n    // kth_next(x, 0) => x\n    int\
    \ kth_next(int x, int k){\n        for(int i = 0; i < next.size() && k; ++i){\n\
    \            if(k & (1 << i)){\n                x = next[i][x];\n            \
    \    if(x == -1)\n                    break;\n            }\n        }\n     \
    \   return x;\n    }\n\n    int lca(int x, int y){\n        int min_depth = min(depth[x],\
    \ depth[y]);\n        x = kth_next(x, depth[x] - min_depth);\n        y = kth_next(y,\
    \ depth[y] - min_depth);\n        if(x == y)\n            return x;\n        for(int\
    \ i = next.size() - 1; i >= 0; --i)\n            if(next[i][x] != next[i][y]){\n\
    \                x = next[i][x];\n                y = next[i][y];\n          \
    \  }\n        return next[0][x];\n    }\n};\n\n#line 9 \"verify/lca_binarylifting.test.cpp\"\
    \n\nsigned main() {\n    int n, q;\n    cin >> n >> q;\n    vector<vector<int>>\
    \ edges(n);\n    for(int i = 1; i < n; ++i){\n        int j;\n        cin >> j;\n\
    \        edges[i].emplace_back(j);\n        edges[j].emplace_back(i);\n    }\n\
    \    BinaryLifting tree(edges);\n    for(int i = 0; i < q; ++i){\n        int\
    \ u, v;\n        cin >> u >> v;\n        cout << tree.lca(u, v) << endl;\n   \
    \ }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/lca\"\n#include <bits/stdc++.h>\n\
    \nusing namespace std;\n\nusing i64 = long long;\n\n#include \"../lib/classes/binarylifting.cpp\"\
    \n\nsigned main() {\n    int n, q;\n    cin >> n >> q;\n    vector<vector<int>>\
    \ edges(n);\n    for(int i = 1; i < n; ++i){\n        int j;\n        cin >> j;\n\
    \        edges[i].emplace_back(j);\n        edges[j].emplace_back(i);\n    }\n\
    \    BinaryLifting tree(edges);\n    for(int i = 0; i < q; ++i){\n        int\
    \ u, v;\n        cin >> u >> v;\n        cout << tree.lca(u, v) << endl;\n   \
    \ }\n}\n\n"
  dependsOn:
  - lib/classes/binarylifting.cpp
  isVerificationFile: true
  path: verify/lca_binarylifting.test.cpp
  requiredBy: []
  timestamp: '2020-03-20 18:12:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/lca_binarylifting.test.cpp
layout: document
redirect_from:
- /verify/verify/lca_binarylifting.test.cpp
- /verify/verify/lca_binarylifting.test.cpp.html
title: verify/lca_binarylifting.test.cpp
---
