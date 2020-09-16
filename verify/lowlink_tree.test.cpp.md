---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/lowlink.cpp
    title: lib/classes/lowlink.cpp
  - icon: ':heavy_check_mark:'
    path: lib/functions/twoedgeconnectedcomponents_tree.cpp
    title: lib/functions/twoedgeconnectedcomponents_tree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415
  bundledCode: "#line 1 \"verify/lowlink_tree.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\ntemplate <typename T>\n\
    bool chmax(T& x, T y){\n    if(x < y){\n        x = y;\n        return true;\n\
    \    }\n    return false;\n}\n\n\n#line 1 \"lib/classes/lowlink.cpp\"\nstruct\
    \ LowLink{\n    vector<vector<int>>& edges;\n    // \u95A2\u7BC0\u70B9\n    vector<int>\
    \ art;\n    vector<pair<int,int>> bridge;\n\n    vector<int> used, ord, low;\n\
    \    int k;\n\n    void dfs(int idx, int par){\n        ord[idx] = k++;\n    \
    \    low[idx] = ord[idx];\n        bool is_art = false;\n        int cnt = 0;\n\
    \        for(auto& to : edges[idx]){\n            if(ord[to] == -1){\n       \
    \         ++cnt;\n                dfs(to, idx);\n                low[idx] = min(low[idx],\
    \ low[to]);\n                is_art |= par != -1 && low[to] >= ord[idx];\n   \
    \             if(ord[idx] < low[to])\n                    bridge.emplace_back(idx,\
    \ to);\n            }else if(to != par)\n                low[idx] = min(low[idx],\
    \ ord[to]);\n        }\n        is_art |= (par == -1 && cnt > 1);\n        if(is_art)\n\
    \            art.emplace_back(idx);\n    }\n\n    LowLink(vector<vector<int>>&\
    \ edges) :\n        edges(edges),\n        ord(edges.size(), -1),\n        low(edges.size(),\
    \ 0),\n        k(0)\n    {\n        for(int i = 0; i < edges.size(); ++i)\n  \
    \          if(ord[i] == -1)\n                dfs(i, -1);\n        for(auto& b\
    \ : bridge)\n            b = make_pair(min(b.first, b.second), max(b.first, b.second));\n\
    \        sort(art.begin(), art.end());\n        sort(bridge.begin(), bridge.end());\n\
    \    }\n};\n\n#line 1 \"lib/functions/twoedgeconnectedcomponents_tree.cpp\"\n\
    struct Result{\n    int group_cnt;\n    vector<int> group;\n    vector<vector<int>>\
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
    \    return res;\n}\n\n#line 18 \"verify/lowlink_tree.test.cpp\"\n\nsigned main(){\n\
    \    int n, m;\n    cin >> n >> m;\n    vector<int> a(n);\n    vector<int> u(m),\
    \ v(m);\n    for(int i = 0; i < n; ++i)\n        cin >> a[i];\n    vector<vector<int>>\
    \ edges(n);\n    for(int i = 0; i < m; ++i){\n        cin >> u[i] >> v[i];\n \
    \       --u[i], --v[i];\n        edges[u[i]].push_back(v[i]);\n        edges[v[i]].push_back(u[i]);\n\
    \    }\n    auto res = two_edge_connected_components_tree(edges);\n    int k =\
    \ res.group_cnt;\n    vector<int> values(k, 0);\n    for(int i = 0; i < n; ++i)\n\
    \        values[res.group[i]] += a[i];\n\n    auto& par = res.par;\n    auto&\
    \ childs = res.childs;\n    vector<int> dp(k, 0);\n    vector<unordered_map<int,\
    \ int>> dp2(k);\n    function<void(int)> f = [&](int x){\n        int val = 0;\n\
    \        for(auto y : childs[x]){\n            f(y);\n            chmax(val, dp[y]);\n\
    \        }\n        dp[x] = values[x] + val;\n    };\n    f(0);\n\n    int ans\
    \ = 0;\n    function<void(int)> g = [&](int x){\n        multiset<int> v{0, 0};\n\
    \        for(auto y : childs[x]){\n            v.insert(dp[y]);\n            v.erase(v.begin());\n\
    \            g(y);\n        }\n        chmax(ans, values[x] + *prev(v.end()) +\
    \ *prev(v.end(), 2));\n    };\n    g(0);\n    cout << ans << endl;\n\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\ntemplate <typename T>\n\
    bool chmax(T& x, T y){\n    if(x < y){\n        x = y;\n        return true;\n\
    \    }\n    return false;\n}\n\n\n#include \"../lib/classes/lowlink.cpp\"\n#include\
    \ \"../lib/functions/twoedgeconnectedcomponents_tree.cpp\"\n\nsigned main(){\n\
    \    int n, m;\n    cin >> n >> m;\n    vector<int> a(n);\n    vector<int> u(m),\
    \ v(m);\n    for(int i = 0; i < n; ++i)\n        cin >> a[i];\n    vector<vector<int>>\
    \ edges(n);\n    for(int i = 0; i < m; ++i){\n        cin >> u[i] >> v[i];\n \
    \       --u[i], --v[i];\n        edges[u[i]].push_back(v[i]);\n        edges[v[i]].push_back(u[i]);\n\
    \    }\n    auto res = two_edge_connected_components_tree(edges);\n    int k =\
    \ res.group_cnt;\n    vector<int> values(k, 0);\n    for(int i = 0; i < n; ++i)\n\
    \        values[res.group[i]] += a[i];\n\n    auto& par = res.par;\n    auto&\
    \ childs = res.childs;\n    vector<int> dp(k, 0);\n    vector<unordered_map<int,\
    \ int>> dp2(k);\n    function<void(int)> f = [&](int x){\n        int val = 0;\n\
    \        for(auto y : childs[x]){\n            f(y);\n            chmax(val, dp[y]);\n\
    \        }\n        dp[x] = values[x] + val;\n    };\n    f(0);\n\n    int ans\
    \ = 0;\n    function<void(int)> g = [&](int x){\n        multiset<int> v{0, 0};\n\
    \        for(auto y : childs[x]){\n            v.insert(dp[y]);\n            v.erase(v.begin());\n\
    \            g(y);\n        }\n        chmax(ans, values[x] + *prev(v.end()) +\
    \ *prev(v.end(), 2));\n    };\n    g(0);\n    cout << ans << endl;\n\n    return\
    \ 0;\n}\n"
  dependsOn:
  - lib/classes/lowlink.cpp
  - lib/functions/twoedgeconnectedcomponents_tree.cpp
  isVerificationFile: true
  path: verify/lowlink_tree.test.cpp
  requiredBy: []
  timestamp: '2020-03-03 11:11:00+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/lowlink_tree.test.cpp
layout: document
redirect_from:
- /verify/verify/lowlink_tree.test.cpp
- /verify/verify/lowlink_tree.test.cpp.html
title: verify/lowlink_tree.test.cpp
---
