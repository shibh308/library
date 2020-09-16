---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/lowlink_tree.test.cpp
    title: verify/lowlink_tree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/lowlink.cpp\"\nstruct LowLink{\n    vector<vector<int>>&\
    \ edges;\n    // \u95A2\u7BC0\u70B9\n    vector<int> art;\n    vector<pair<int,int>>\
    \ bridge;\n\n    vector<int> used, ord, low;\n    int k;\n\n    void dfs(int idx,\
    \ int par){\n        ord[idx] = k++;\n        low[idx] = ord[idx];\n        bool\
    \ is_art = false;\n        int cnt = 0;\n        for(auto& to : edges[idx]){\n\
    \            if(ord[to] == -1){\n                ++cnt;\n                dfs(to,\
    \ idx);\n                low[idx] = min(low[idx], low[to]);\n                is_art\
    \ |= par != -1 && low[to] >= ord[idx];\n                if(ord[idx] < low[to])\n\
    \                    bridge.emplace_back(idx, to);\n            }else if(to !=\
    \ par)\n                low[idx] = min(low[idx], ord[to]);\n        }\n      \
    \  is_art |= (par == -1 && cnt > 1);\n        if(is_art)\n            art.emplace_back(idx);\n\
    \    }\n\n    LowLink(vector<vector<int>>& edges) :\n        edges(edges),\n \
    \       ord(edges.size(), -1),\n        low(edges.size(), 0),\n        k(0)\n\
    \    {\n        for(int i = 0; i < edges.size(); ++i)\n            if(ord[i] ==\
    \ -1)\n                dfs(i, -1);\n        for(auto& b : bridge)\n          \
    \  b = make_pair(min(b.first, b.second), max(b.first, b.second));\n        sort(art.begin(),\
    \ art.end());\n        sort(bridge.begin(), bridge.end());\n    }\n};\n\n"
  code: "struct LowLink{\n    vector<vector<int>>& edges;\n    // \u95A2\u7BC0\u70B9\
    \n    vector<int> art;\n    vector<pair<int,int>> bridge;\n\n    vector<int> used,\
    \ ord, low;\n    int k;\n\n    void dfs(int idx, int par){\n        ord[idx] =\
    \ k++;\n        low[idx] = ord[idx];\n        bool is_art = false;\n        int\
    \ cnt = 0;\n        for(auto& to : edges[idx]){\n            if(ord[to] == -1){\n\
    \                ++cnt;\n                dfs(to, idx);\n                low[idx]\
    \ = min(low[idx], low[to]);\n                is_art |= par != -1 && low[to] >=\
    \ ord[idx];\n                if(ord[idx] < low[to])\n                    bridge.emplace_back(idx,\
    \ to);\n            }else if(to != par)\n                low[idx] = min(low[idx],\
    \ ord[to]);\n        }\n        is_art |= (par == -1 && cnt > 1);\n        if(is_art)\n\
    \            art.emplace_back(idx);\n    }\n\n    LowLink(vector<vector<int>>&\
    \ edges) :\n        edges(edges),\n        ord(edges.size(), -1),\n        low(edges.size(),\
    \ 0),\n        k(0)\n    {\n        for(int i = 0; i < edges.size(); ++i)\n  \
    \          if(ord[i] == -1)\n                dfs(i, -1);\n        for(auto& b\
    \ : bridge)\n            b = make_pair(min(b.first, b.second), max(b.first, b.second));\n\
    \        sort(art.begin(), art.end());\n        sort(bridge.begin(), bridge.end());\n\
    \    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/lowlink.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/lowlink_tree.test.cpp
documentation_of: lib/classes/lowlink.cpp
layout: document
redirect_from:
- /library/lib/classes/lowlink.cpp
- /library/lib/classes/lowlink.cpp.html
title: lib/classes/lowlink.cpp
---
