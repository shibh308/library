---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/functions/simple_graph.cpp\"\ntemplate <typename T =\
    \ pair<int,int>>\nvector<vector<int>> simple_graph(vector<vector<T>>& edges, function<int(T)>\
    \ f = [](auto x){return x.first;}){\n    vector<vector<int>> simple_edges(edges.size());\n\
    \    for(int i = 0; i < edges.size(); ++i)\n        for(auto& x : edges[i])\n\
    \            simple_edges[i].push_back(f(x));\n    return simple_edges;\n}\n\n"
  code: "template <typename T = pair<int,int>>\nvector<vector<int>> simple_graph(vector<vector<T>>&\
    \ edges, function<int(T)> f = [](auto x){return x.first;}){\n    vector<vector<int>>\
    \ simple_edges(edges.size());\n    for(int i = 0; i < edges.size(); ++i)\n   \
    \     for(auto& x : edges[i])\n            simple_edges[i].push_back(f(x));\n\
    \    return simple_edges;\n}\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/simple_graph.cpp
  requiredBy: []
  timestamp: '2020-03-04 14:48:14+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/functions/simple_graph.cpp
layout: document
redirect_from:
- /library/lib/functions/simple_graph.cpp
- /library/lib/functions/simple_graph.cpp.html
title: lib/functions/simple_graph.cpp
---
