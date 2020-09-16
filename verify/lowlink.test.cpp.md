---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 70, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir).decode()\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 191, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.8.5/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: bits/stdc++.h:\
    \ line -1: no such header\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0415\"\
    \n#include \"bits/stdc++.h\"\nusing namespace std;\nusing i64 = long long;\nconst\
    \ i64 MOD = 1e9+7;\nconst i64 INF = 1e18+7;\n\n\ntemplate <typename T>\nbool chmin(T&\
    \ x, T y){\n    if(x > y){\n        x = y;\n        return true;\n    }\n    return\
    \ false;\n}\n\ntemplate <typename T>\nbool chmax(T& x, T y){\n    if(x < y){\n\
    \        x = y;\n        return true;\n    }\n    return false;\n}\n\nstruct UnionFind{\n\
    \    vector<i64> par;\n    i64 count;\n    UnionFind(i64 n) : par(n, -1), count(0){}\n\
    \    i64 Find(i64 x){return par[x] < 0 ? x : Find(par[x]);}\n    i64 Size(i64\
    \ x){return par[x] < 0 ? -par[x] : Size(par[x]);}\n    bool Unite(i64 x, i64 y){\n\
    \        x = Find(x);\n        y = Find(y);\n        if(x == y)\n            return\
    \ false;\n        if(par[x] > par[y])\n            swap(x, y);\n        par[x]\
    \ += par[y];\n        par[y] = x;\n        return ++count;\n    }\n};\n\n\nstruct\
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
    \    }\n};\n\n\n\nsigned main(){\n    i64 n, m;\n    cin >> n >> m;\n    vector<i64>\
    \ v(n);\n    for(auto& x : v)\n        cin >> x;\n    vector<i64> s(m), t(m);\n\
    \    vector<vector<int>> graph_edges(n);\n    for(i64 i = 0; i < m; ++i){\n  \
    \      cin >> s[i] >> t[i];\n        --s[i], --t[i];\n        graph_edges[s[i]].emplace_back(t[i]);\n\
    \        graph_edges[t[i]].emplace_back(s[i]);\n    }\n    LowLink ll(graph_edges);\n\
    \    auto is_bridge = [&](int i, int j){\n        if(i > j)\n            swap(i,\
    \ j);\n        auto iter = lower_bound(ll.bridge.begin(), ll.bridge.end(), make_pair(i,\
    \ j));\n        if(iter != ll.bridge.end() && *iter == make_pair(i, j))\n    \
    \        return true;\n        return false;\n    };\n\n    vector<i64> flag(n,\
    \ false);\n    vector<vector<i64>> ori_childs(n);\n\n    function<void(i64)> f\
    \ = [&](i64 x){\n        for(auto& y : graph_edges[x]){\n            if(flag[y])\n\
    \                continue;\n            flag[y] = true;\n            if(is_bridge(x,\
    \ y))\n                ori_childs[x].emplace_back(y);\n            f(y);\n   \
    \     }\n    };\n\n    flag[0] = true;\n    f(0);\n\n    UnionFind uf(n);\n  \
    \  for(int i = 0; i < m; ++i)\n        if(!is_bridge(s[i], t[i]))\n          \
    \  uf.Unite(s[i], t[i]);\n\n    vector<i64> union_par;\n    for(i64 i = 0; i <\
    \ n; ++i)\n        if(uf.Find(i) == i)\n            union_par.emplace_back(i);\n\
    \    i64 k = union_par.size();\n    auto getidx = [&](int i){\n        int id\
    \ = uf.Find(i);\n        return distance(union_par.begin(), lower_bound(union_par.begin(),\
    \ union_par.end(), id));\n    };\n    vector<i64> val(k, 0);\n    for(i64 i =\
    \ 0; i < n; ++i)\n        val[getidx(i)] += v[i];\n\n    vector<vector<i64>> childs(k);\n\
    \    for(i64 x = 0; x < n; ++x)\n        for(auto& y : ori_childs[x])\n      \
    \      childs[getidx(x)].emplace_back(getidx(y));\n\n    i64 ans = 0;\n    function<i64(i64)>\
    \ g = [&](i64 x){\n        vector<i64> values;\n        for(auto& y : childs[x])\n\
    \            values.emplace_back(g(y));\n        sort(values.begin(), values.end(),\
    \ greater<i64>());\n        i64 res = val[x];\n        for(i64 i = 0; i < min(2LL,\
    \ i64(values.size())); ++i)\n            res += values[i];\n        chmax(ans,\
    \ res);\n        return (values.size() ? values[0] : 0) + val[x];\n    };\n  \
    \  g(0);\n    cout << ans << endl;\n}\n\n"
  dependsOn: []
  isVerificationFile: true
  path: verify/lowlink.test.cpp
  requiredBy: []
  timestamp: '2020-02-24 09:29:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/lowlink.test.cpp
layout: document
redirect_from:
- /verify/verify/lowlink.test.cpp
- /verify/verify/lowlink.test.cpp.html
title: verify/lowlink.test.cpp
---
