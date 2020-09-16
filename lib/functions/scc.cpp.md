---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/scc_dag.test.cpp
    title: verify/scc_dag.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/2-sat.test.cpp
    title: verify/2-sat.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/functions/scc.cpp\"\nvector<int> scc(vector<vector<int>>&\
    \ edges){\n    int n = edges.size();\n    vector<vector<int>> rev(n);\n\n    for(int\
    \ i = 0; i < n; ++i)\n        for(auto& x : edges[i])\n            rev[x].emplace_back(i);\n\
    \n    vector<i64> dfs_num(n, -1);\n    vector<i64> flag(n, 0);\n    int num =\
    \ 0;\n    function<void(int)> dfs = [&](int pos){\n        flag[pos] = 1;\n  \
    \      for(auto& xx : edges[pos])\n            if(!flag[xx]){\n              \
    \  dfs(xx);\n        }\n        dfs_num[pos] = num++;\n    };\n\n    for(int i\
    \ = 0; i < n; ++i)\n        if(!flag[i])\n            dfs(i);\n\n    vector<int>\
    \ dfs_inv(n);\n    for(int i = 0; i < n; ++i)\n        dfs_inv[n - 1 - dfs_num[i]]\
    \ = i;\n\n    num = 0;\n\n    vector<int> scc_vec(n, -1);\n\n    function<void(int)>\
    \ rdfs = [&](int pos){\n        scc_vec[pos] = num;\n        for(auto t : rev[pos])\n\
    \            if(scc_vec[t] == -1)\n                rdfs(t);\n    };\n\n    for(int\
    \ i = 0; i < n; ++i)\n        if(scc_vec[dfs_inv[i]] == -1){\n            rdfs(dfs_inv[i]);\n\
    \            ++num;\n        }\n\n    return scc_vec;\n}\n"
  code: "vector<int> scc(vector<vector<int>>& edges){\n    int n = edges.size();\n\
    \    vector<vector<int>> rev(n);\n\n    for(int i = 0; i < n; ++i)\n        for(auto&\
    \ x : edges[i])\n            rev[x].emplace_back(i);\n\n    vector<i64> dfs_num(n,\
    \ -1);\n    vector<i64> flag(n, 0);\n    int num = 0;\n    function<void(int)>\
    \ dfs = [&](int pos){\n        flag[pos] = 1;\n        for(auto& xx : edges[pos])\n\
    \            if(!flag[xx]){\n                dfs(xx);\n        }\n        dfs_num[pos]\
    \ = num++;\n    };\n\n    for(int i = 0; i < n; ++i)\n        if(!flag[i])\n \
    \           dfs(i);\n\n    vector<int> dfs_inv(n);\n    for(int i = 0; i < n;\
    \ ++i)\n        dfs_inv[n - 1 - dfs_num[i]] = i;\n\n    num = 0;\n\n    vector<int>\
    \ scc_vec(n, -1);\n\n    function<void(int)> rdfs = [&](int pos){\n        scc_vec[pos]\
    \ = num;\n        for(auto t : rev[pos])\n            if(scc_vec[t] == -1)\n \
    \               rdfs(t);\n    };\n\n    for(int i = 0; i < n; ++i)\n        if(scc_vec[dfs_inv[i]]\
    \ == -1){\n            rdfs(dfs_inv[i]);\n            ++num;\n        }\n\n  \
    \  return scc_vec;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/scc.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/scc_dag.test.cpp
  - verify/2-sat.test.cpp
documentation_of: lib/functions/scc.cpp
layout: document
redirect_from:
- /library/lib/functions/scc.cpp
- /library/lib/functions/scc.cpp.html
title: lib/functions/scc.cpp
---
