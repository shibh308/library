---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/mo_query.test.cpp
    title: verify/mo_query.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/functions/mo_query.cpp\"\ntemplate <typename ResultType>\n\
    vector<ResultType> mo_query(Mo& mo, vector<pair<int,int>>& queries, function<ResultType(int)>\
    \ get_func, int packet=512){\n    int q = queries.size();\n    vector<tuple<int,int,int>>\
    \ sort_queries;\n    for(int i = 0; i < q; ++i)\n        sort_queries.emplace_back(queries[i].first\
    \ / packet, queries[i].second, i);\n    sort(sort_queries.begin(), sort_queries.end());\n\
    \    vector<ResultType> ans(q);\n    for(auto& query : sort_queries){\n      \
    \  int idx = get<2>(query);\n        mo.move(queries[idx].first, queries[idx].second);\n\
    \        ans[idx] = get_func(idx);\n    }\n    return ans;\n}\n\n"
  code: "template <typename ResultType>\nvector<ResultType> mo_query(Mo& mo, vector<pair<int,int>>&\
    \ queries, function<ResultType(int)> get_func, int packet=512){\n    int q = queries.size();\n\
    \    vector<tuple<int,int,int>> sort_queries;\n    for(int i = 0; i < q; ++i)\n\
    \        sort_queries.emplace_back(queries[i].first / packet, queries[i].second,\
    \ i);\n    sort(sort_queries.begin(), sort_queries.end());\n    vector<ResultType>\
    \ ans(q);\n    for(auto& query : sort_queries){\n        int idx = get<2>(query);\n\
    \        mo.move(queries[idx].first, queries[idx].second);\n        ans[idx] =\
    \ get_func(idx);\n    }\n    return ans;\n}\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/mo_query.cpp
  requiredBy: []
  timestamp: '2020-03-03 20:05:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/mo_query.test.cpp
documentation_of: lib/functions/mo_query.cpp
layout: document
redirect_from:
- /library/lib/functions/mo_query.cpp
- /library/lib/functions/mo_query.cpp.html
title: lib/functions/mo_query.cpp
---
