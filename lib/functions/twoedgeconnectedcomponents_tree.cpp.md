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
    links: []
  bundledCode: "#line 1 \"lib/functions/twoedgeconnectedcomponents_tree.cpp\"\nstruct\
    \ Result{\n    int group_cnt;\n    vector<int> group;\n    vector<vector<int>>\
    \ group_elm_list;\n    // \u540C\u3058\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\
    \u306E\u8FBA\u3092\u30B0\u30EB\u30FC\u30D7\u3054\u3068\u306B\u5217\u6319\u3059\
    \u308B, \u7247\u65B9\u5411\u306E\u307F(\u8FBA\u6570\u500D\u5316\u3057\u306A\u3044\
    )\n    vector<vector<pair<int,int>>> same_group_edges;\n    // \u6A4B, \u7247\u65B9\
    \u5411\u306E\u307F\n    vector<pair<int,int>> bridges;\n    // \u95A2\u7BC0\u70B9\
    \n    vector<int> arts;\n    vector<vector<int>> tree_graph;\n    vector<int>\
    \ par;\n    vector<vector<int>> childs;\n};\n\nResult two_edge_connected_components_tree(vector<vector<int>>&\
    \ edges){\n    int n = edges.size();\n    LowLink ll(edges);\n    vector<vector<int>>\
    \ not_bridge_graph(n);\n    for(int i = 0; i < n; ++i)\n        for(auto j : edges[i]){\n\
    \            pair<int,int> min_max = minmax(i, j);\n            auto iter = lower_bound(ll.bridge.begin(),\
    \ ll.bridge.end(), min_max);\n            if(iter == ll.bridge.end() || *iter\
    \ != min_max)\n                not_bridge_graph[i].push_back(j);\n        }\n\n\
    \    vector<int> group(n, -1);\n    function<void(int)> group_dfs = [&](int x){\n\
    \        for(auto y : not_bridge_graph[x])\n            if(group[y] == -1){\n\
    \                group[y] = group[x];\n                group_dfs(y);\n       \
    \     }\n    };\n    int group_cnt = 0;\n    for(int i = 0; i < n; ++i)\n    \
    \    if(group[i] == -1){\n            group[i] = group_cnt++;\n            group_dfs(i);\n\
    \        }\n    vector<vector<int>> group_elm_list(group_cnt);\n    for(int i\
    \ = 0; i < n; ++i)\n        group_elm_list[group[i]].push_back(i);\n\n    vector<vector<pair<int,int>>>\
    \ same_group_edges(group_cnt);\n    vector<vector<int>> tree_edges(group_cnt);\n\
    \    vector<int> par(group_cnt, -1);\n    vector<vector<int>> childs(group_cnt);\n\
    \n    for(int i = 0; i < n; ++i)\n        for(auto j : edges[i])\n           \
    \ if(group[i] == group[j] && i < j)\n                same_group_edges[group[i]].emplace_back(i,\
    \ j);\n\n    for(auto& p : ll.bridge){\n        tree_edges[group[p.first]].push_back(group[p.second]);\n\
    \        tree_edges[group[p.second]].push_back(group[p.first]);\n    }\n    vector<bool>\
    \ flag(n, false);\n    function<void(int)> tree_dfs = [&](int x){\n        for(auto\
    \ y : tree_edges[x])\n            if(!flag[y]){\n                flag[y] = true;\n\
    \                par[y] = x;\n                childs[x].push_back(y);\n      \
    \          tree_dfs(y);\n            }\n    };\n    flag[0] = true;\n    tree_dfs(0);\n\
    \n    Result res;\n    res.group_cnt = group_cnt;\n    res.group_elm_list = move(group_elm_list);\n\
    \    res.same_group_edges = move(same_group_edges);\n    res.bridges = move(ll.bridge);\n\
    \    res.arts = move(ll.art);\n    res.group = move(group);\n    res.tree_graph\
    \ = move(tree_edges);\n    res.par = move(par);\n    res.childs = move(childs);\n\
    \    return res;\n}\n\n"
  code: "struct Result{\n    int group_cnt;\n    vector<int> group;\n    vector<vector<int>>\
    \ group_elm_list;\n    // \u540C\u3058\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\
    \u306E\u8FBA\u3092\u30B0\u30EB\u30FC\u30D7\u3054\u3068\u306B\u5217\u6319\u3059\
    \u308B, \u7247\u65B9\u5411\u306E\u307F(\u8FBA\u6570\u500D\u5316\u3057\u306A\u3044\
    )\n    vector<vector<pair<int,int>>> same_group_edges;\n    // \u6A4B, \u7247\u65B9\
    \u5411\u306E\u307F\n    vector<pair<int,int>> bridges;\n    // \u95A2\u7BC0\u70B9\
    \n    vector<int> arts;\n    vector<vector<int>> tree_graph;\n    vector<int>\
    \ par;\n    vector<vector<int>> childs;\n};\n\nResult two_edge_connected_components_tree(vector<vector<int>>&\
    \ edges){\n    int n = edges.size();\n    LowLink ll(edges);\n    vector<vector<int>>\
    \ not_bridge_graph(n);\n    for(int i = 0; i < n; ++i)\n        for(auto j : edges[i]){\n\
    \            pair<int,int> min_max = minmax(i, j);\n            auto iter = lower_bound(ll.bridge.begin(),\
    \ ll.bridge.end(), min_max);\n            if(iter == ll.bridge.end() || *iter\
    \ != min_max)\n                not_bridge_graph[i].push_back(j);\n        }\n\n\
    \    vector<int> group(n, -1);\n    function<void(int)> group_dfs = [&](int x){\n\
    \        for(auto y : not_bridge_graph[x])\n            if(group[y] == -1){\n\
    \                group[y] = group[x];\n                group_dfs(y);\n       \
    \     }\n    };\n    int group_cnt = 0;\n    for(int i = 0; i < n; ++i)\n    \
    \    if(group[i] == -1){\n            group[i] = group_cnt++;\n            group_dfs(i);\n\
    \        }\n    vector<vector<int>> group_elm_list(group_cnt);\n    for(int i\
    \ = 0; i < n; ++i)\n        group_elm_list[group[i]].push_back(i);\n\n    vector<vector<pair<int,int>>>\
    \ same_group_edges(group_cnt);\n    vector<vector<int>> tree_edges(group_cnt);\n\
    \    vector<int> par(group_cnt, -1);\n    vector<vector<int>> childs(group_cnt);\n\
    \n    for(int i = 0; i < n; ++i)\n        for(auto j : edges[i])\n           \
    \ if(group[i] == group[j] && i < j)\n                same_group_edges[group[i]].emplace_back(i,\
    \ j);\n\n    for(auto& p : ll.bridge){\n        tree_edges[group[p.first]].push_back(group[p.second]);\n\
    \        tree_edges[group[p.second]].push_back(group[p.first]);\n    }\n    vector<bool>\
    \ flag(n, false);\n    function<void(int)> tree_dfs = [&](int x){\n        for(auto\
    \ y : tree_edges[x])\n            if(!flag[y]){\n                flag[y] = true;\n\
    \                par[y] = x;\n                childs[x].push_back(y);\n      \
    \          tree_dfs(y);\n            }\n    };\n    flag[0] = true;\n    tree_dfs(0);\n\
    \n    Result res;\n    res.group_cnt = group_cnt;\n    res.group_elm_list = move(group_elm_list);\n\
    \    res.same_group_edges = move(same_group_edges);\n    res.bridges = move(ll.bridge);\n\
    \    res.arts = move(ll.art);\n    res.group = move(group);\n    res.tree_graph\
    \ = move(tree_edges);\n    res.par = move(par);\n    res.childs = move(childs);\n\
    \    return res;\n}\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/twoedgeconnectedcomponents_tree.cpp
  requiredBy: []
  timestamp: '2020-03-02 22:53:16+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/lowlink_tree.test.cpp
documentation_of: lib/functions/twoedgeconnectedcomponents_tree.cpp
layout: document
redirect_from:
- /library/lib/functions/twoedgeconnectedcomponents_tree.cpp
- /library/lib/functions/twoedgeconnectedcomponents_tree.cpp.html
title: lib/functions/twoedgeconnectedcomponents_tree.cpp
---
