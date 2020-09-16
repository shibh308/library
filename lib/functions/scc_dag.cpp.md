---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/scc_dag.test.cpp
    title: verify/scc_dag.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/functions/scc_dag.cpp\"\nstruct Result{\n    int dag_size;\n\
    \    vector<vector<int>> dag_graph;\n    // \u5143\u306E\u30B0\u30E9\u30D5\u3067\
    i\u756A\u76EE\u306E\u9802\u70B9\u304C\u4F55\u756A\u76EE\u306E\u5F37\u9023\u7D50\
    \u6210\u5206\u306B\u542B\u307E\u308C\u308B\u304B\n    vector<int> elements;\n\
    \    // i\u756A\u76EE\u306E\u5F37\u9023\u7D50\u6210\u5206\u306B\u542B\u307E\u308C\
    \u308B\u9802\u70B9\u306E\u30EA\u30B9\u30C8\n    vector<vector<int>> tps_list;\n\
    \    // \u30C8\u30DD\u30BD\u3057\u3066i\u756A\u76EE\u306B\u304F\u308B\u9802\u70B9\
    \u306Eindex\n    vector<int> tps_order;\n    // DAG\u306Ei\u756A\u76EE\u306E\u9802\
    \u70B9\u3092\u30C8\u30DD\u30BD\u3057\u305F\u6642\u306E\u756A\u53F7\n    vector<int>\
    \ tps_index;\n};\n\nResult scc_dag(vector<vector<int>>& edges){\n    int n = edges.size();\n\
    \    vector<int> scc_vec = scc(edges);\n    int m = *max_element(scc_vec.begin(),\
    \ scc_vec.end()) + 1;\n    vector<vector<int>> dag_graph(m);\n\n    queue<int>\
    \ tps_que;\n    vector<int> in_count(m, 0);\n    vector<int> tps(m, -1);\n   \
    \ vector<int> tps_idx(m);\n    for(int i = 0; i < n; ++i){\n        for(auto j\
    \ : edges[i]){\n            if(scc_vec[i] == scc_vec[j])\n                continue;\n\
    \            dag_graph[scc_vec[i]].push_back(scc_vec[j]);\n            ++in_count[scc_vec[j]];\n\
    \        }\n    }\n    for(int i = 0; i < m; ++i)\n        if(in_count[i] == 0)\n\
    \            tps_que.push(i);\n    int cnt = 0;\n    while(!tps_que.empty()){\n\
    \        int x = tps_que.front();\n        tps_idx[x] = cnt;\n        tps[cnt++]\
    \ = x;\n        tps_que.pop();\n        for(auto y : dag_graph[x])\n         \
    \   if(--in_count[y] == 0)\n                tps_que.push(y);\n    }\n    assert(cnt\
    \ == m);\n\n    vector<vector<int>> tps_list(m);\n    for(int i = 0; i < n; ++i)\n\
    \        tps_list[scc_vec[i]].push_back(i);\n\n    Result res;\n    res.dag_size\
    \ = m;\n    res.elements = move(scc_vec);\n    res.tps_index = move(tps_idx);\n\
    \    res.tps_order = move(tps);\n    res.tps_list = move(tps_list);\n    res.dag_graph\
    \ = move(dag_graph);\n    return res;\n}\n\n"
  code: "struct Result{\n    int dag_size;\n    vector<vector<int>> dag_graph;\n \
    \   // \u5143\u306E\u30B0\u30E9\u30D5\u3067i\u756A\u76EE\u306E\u9802\u70B9\u304C\
    \u4F55\u756A\u76EE\u306E\u5F37\u9023\u7D50\u6210\u5206\u306B\u542B\u307E\u308C\
    \u308B\u304B\n    vector<int> elements;\n    // i\u756A\u76EE\u306E\u5F37\u9023\
    \u7D50\u6210\u5206\u306B\u542B\u307E\u308C\u308B\u9802\u70B9\u306E\u30EA\u30B9\
    \u30C8\n    vector<vector<int>> tps_list;\n    // \u30C8\u30DD\u30BD\u3057\u3066\
    i\u756A\u76EE\u306B\u304F\u308B\u9802\u70B9\u306Eindex\n    vector<int> tps_order;\n\
    \    // DAG\u306Ei\u756A\u76EE\u306E\u9802\u70B9\u3092\u30C8\u30DD\u30BD\u3057\
    \u305F\u6642\u306E\u756A\u53F7\n    vector<int> tps_index;\n};\n\nResult scc_dag(vector<vector<int>>&\
    \ edges){\n    int n = edges.size();\n    vector<int> scc_vec = scc(edges);\n\
    \    int m = *max_element(scc_vec.begin(), scc_vec.end()) + 1;\n    vector<vector<int>>\
    \ dag_graph(m);\n\n    queue<int> tps_que;\n    vector<int> in_count(m, 0);\n\
    \    vector<int> tps(m, -1);\n    vector<int> tps_idx(m);\n    for(int i = 0;\
    \ i < n; ++i){\n        for(auto j : edges[i]){\n            if(scc_vec[i] ==\
    \ scc_vec[j])\n                continue;\n            dag_graph[scc_vec[i]].push_back(scc_vec[j]);\n\
    \            ++in_count[scc_vec[j]];\n        }\n    }\n    for(int i = 0; i <\
    \ m; ++i)\n        if(in_count[i] == 0)\n            tps_que.push(i);\n    int\
    \ cnt = 0;\n    while(!tps_que.empty()){\n        int x = tps_que.front();\n \
    \       tps_idx[x] = cnt;\n        tps[cnt++] = x;\n        tps_que.pop();\n \
    \       for(auto y : dag_graph[x])\n            if(--in_count[y] == 0)\n     \
    \           tps_que.push(y);\n    }\n    assert(cnt == m);\n\n    vector<vector<int>>\
    \ tps_list(m);\n    for(int i = 0; i < n; ++i)\n        tps_list[scc_vec[i]].push_back(i);\n\
    \n    Result res;\n    res.dag_size = m;\n    res.elements = move(scc_vec);\n\
    \    res.tps_index = move(tps_idx);\n    res.tps_order = move(tps);\n    res.tps_list\
    \ = move(tps_list);\n    res.dag_graph = move(dag_graph);\n    return res;\n}\n\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/scc_dag.cpp
  requiredBy: []
  timestamp: '2020-02-24 19:52:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/scc_dag.test.cpp
documentation_of: lib/functions/scc_dag.cpp
layout: document
redirect_from:
- /library/lib/functions/scc_dag.cpp
- /library/lib/functions/scc_dag.cpp.html
title: lib/functions/scc_dag.cpp
---
