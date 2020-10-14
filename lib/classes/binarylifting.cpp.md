---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/lca_binarylifting.test.cpp
    title: verify/lca_binarylifting.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/binarylifting.cpp\"\nstruct BinaryLifting{\n\
    \    int n;\n    vector<vector<int>> next;\n    vector<int> par;\n    vector<vector<int>>\
    \ childs;\n    vector<int> depth;\n\n    BinaryLifting(vector<vector<int>>& edges,\
    \ int root = 0) : n(edges.size()), depth(n, -1), par(n, -1), childs(n){\n    \
    \    function<void(int)> dfs = [&](int x){\n            for(auto y : edges[x])\n\
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
    \  }\n        return next[0][x];\n    }\n};\n\n"
  code: "struct BinaryLifting{\n    int n;\n    vector<vector<int>> next;\n    vector<int>\
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
    \  }\n        return next[0][x];\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/binarylifting.cpp
  requiredBy: []
  timestamp: '2020-03-20 18:12:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/lca_binarylifting.test.cpp
documentation_of: lib/classes/binarylifting.cpp
layout: document
redirect_from:
- /library/lib/classes/binarylifting.cpp
- /library/lib/classes/binarylifting.cpp.html
title: lib/classes/binarylifting.cpp
---
