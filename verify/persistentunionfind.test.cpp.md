---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/persistentunionfind.cpp
    title: lib/classes/persistentunionfind.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575
  bundledCode: "#line 1 \"verify/persistentunionfind.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing i64 = long;\n\nconst i64 MOD = 1e9 + 7;\n\n#line 1\
    \ \"lib/classes/persistentunionfind.cpp\"\nstruct UnionFind{\n    vector<int>\
    \ par, time;\n    int count;\n    UnionFind(int n) : par(n, -1), time(n, MOD),\
    \ count(0){}\n    // [0, t]\u306E\u9593\u306B\u4F75\u5408\u3055\u308C\u305F\u304B\
    \u3069\u3046\u304B\n    int Find(int x, int t){return par[x] < 0 || time[x] >\
    \ t ? x : Find(par[x], t);}\n    int Size(int x){return par[x] < 0 ? -par[x] :\
    \ Size(par[x]);}\n    // \u73FE\u5728\u306Ecount+1\u306E\u30BF\u30A4\u30DF\u30F3\
    \u30B0\u3067\u4F75\u5408\u3055\u308C\u305F\u4E8B\u306B\u3059\u308B\n    // Unite\u5931\
    \u6557\u6642\u3082count\u304C\u5897\u3048\u308B\u306E\u3067\u6CE8\u610F\n    int\
    \ Unite(int x, int y){\n        x = Find(x, MOD + 1);\n        y = Find(y, MOD\
    \ + 1);\n        ++count;\n        if(x == y)\n            return 0;\n       \
    \ if(par[x] > par[y])\n            swap(x, y);\n        par[x] += par[y];\n  \
    \      par[y] = x;\n        time[y] = count;\n        return count;\n    }\n};\n\
    \n#line 10 \"verify/persistentunionfind.test.cpp\"\n\n\ntemplate <typename T>\n\
    bool chmin(T& x, T y){\n    if(x > y){\n        x = y;\n        return true;\n\
    \    }\n    return false;\n}\n\n\nsigned main(){\n    int n, m, k, q;\n    cin\
    \ >> n >> m >> k >> q;\n    vector<vector<pair<int,int>>> edges(n);\n    vector<int>\
    \ a(m), b(m), l(m);\n    for(int i = 0; i < m; ++i){\n        cin >> a[i] >> b[i]\
    \ >> l[i];\n        --a[i], --b[i];\n        edges[a[i]].emplace_back(b[i], l[i]);\n\
    \        edges[b[i]].emplace_back(a[i], l[i]);\n    }\n    vector<int> v(k);\n\
    \    unordered_set<int> vs;\n    for(int i = 0; i < k; ++i){\n        cin >> v[i];\n\
    \        --v[i];\n        vs.insert(v[i]);\n    }\n    priority_queue<pair<int,int>,\
    \ vector<pair<int,int>>, greater<pair<int,int>>> que;\n    vector<int> range(n,\
    \ MOD);\n    for(int i = 0; i < k; ++i){\n        range[v[i]] = 0;\n        que.emplace(0,\
    \ v[i]);\n    }\n    while(!que.empty()){\n        int dist, x;\n        tie(dist,\
    \ x) = que.top();\n        que.pop();\n        if(range[x] != dist)\n        \
    \    continue;\n        for(auto& ed : edges[x]){\n            if(chmin(range[ed.first],\
    \ dist + ed.second))\n                que.emplace(range[ed.first], ed.first);\n\
    \        }\n    }\n    vector<pair<int,int>> w;\n    for(int i = 0; i < m; ++i){\n\
    \        int dist_a = range[a[i]];\n        int dist_b = range[b[i]];\n      \
    \  w.emplace_back(min(dist_a, dist_b), i);\n    }\n    sort(w.begin(), w.end(),\
    \ greater<>());\n\n    UnionFind uf(n);\n\n    vector<int> query_time(m);\n  \
    \  for(int i = 0; i < m; ++i)\n        query_time[i] = w[i].first;\n\n    for(int\
    \ i = 0; i < m; ++i)\n        uf.Unite(a[w[i].second], b[w[i].second]);\n\n  \
    \  for(int i = 0; i < q; ++i){\n        int s, t;\n        cin >> s >> t;\n  \
    \      --s, --t;\n        // [0, t]\u306E\u9593\u306B\u4F75\u5408\u3055\u308C\u305F\
    \u304B\u3069\u3046\u304B\n        // \u73FE\u5728\u306Ecount+1\u306E\u30BF\u30A4\
    \u30DF\u30F3\u30B0\u3067\u4F75\u5408\u3055\u308C\u305F\u4E8B\u306B\u3059\u308B\
    \n        int ok = MOD, ng = 0;\n        while(abs(ng - ok) > 1){\n          \
    \  int mid = (ok + ng) / 2;\n            (uf.Find(s, mid) == uf.Find(t, mid) ?\
    \ ok : ng) = mid;\n        }\n        if(ok >= m){\n            cout << 0 << endl;\n\
    \            continue;\n        }\n        cout << query_time[ng] << endl;\n \
    \   }\n\n\n}\n\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0575\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\nconst\
    \ i64 MOD = 1e9 + 7;\n\n#include \"../lib/classes/persistentunionfind.cpp\"\n\n\
    \ntemplate <typename T>\nbool chmin(T& x, T y){\n    if(x > y){\n        x = y;\n\
    \        return true;\n    }\n    return false;\n}\n\n\nsigned main(){\n    int\
    \ n, m, k, q;\n    cin >> n >> m >> k >> q;\n    vector<vector<pair<int,int>>>\
    \ edges(n);\n    vector<int> a(m), b(m), l(m);\n    for(int i = 0; i < m; ++i){\n\
    \        cin >> a[i] >> b[i] >> l[i];\n        --a[i], --b[i];\n        edges[a[i]].emplace_back(b[i],\
    \ l[i]);\n        edges[b[i]].emplace_back(a[i], l[i]);\n    }\n    vector<int>\
    \ v(k);\n    unordered_set<int> vs;\n    for(int i = 0; i < k; ++i){\n       \
    \ cin >> v[i];\n        --v[i];\n        vs.insert(v[i]);\n    }\n    priority_queue<pair<int,int>,\
    \ vector<pair<int,int>>, greater<pair<int,int>>> que;\n    vector<int> range(n,\
    \ MOD);\n    for(int i = 0; i < k; ++i){\n        range[v[i]] = 0;\n        que.emplace(0,\
    \ v[i]);\n    }\n    while(!que.empty()){\n        int dist, x;\n        tie(dist,\
    \ x) = que.top();\n        que.pop();\n        if(range[x] != dist)\n        \
    \    continue;\n        for(auto& ed : edges[x]){\n            if(chmin(range[ed.first],\
    \ dist + ed.second))\n                que.emplace(range[ed.first], ed.first);\n\
    \        }\n    }\n    vector<pair<int,int>> w;\n    for(int i = 0; i < m; ++i){\n\
    \        int dist_a = range[a[i]];\n        int dist_b = range[b[i]];\n      \
    \  w.emplace_back(min(dist_a, dist_b), i);\n    }\n    sort(w.begin(), w.end(),\
    \ greater<>());\n\n    UnionFind uf(n);\n\n    vector<int> query_time(m);\n  \
    \  for(int i = 0; i < m; ++i)\n        query_time[i] = w[i].first;\n\n    for(int\
    \ i = 0; i < m; ++i)\n        uf.Unite(a[w[i].second], b[w[i].second]);\n\n  \
    \  for(int i = 0; i < q; ++i){\n        int s, t;\n        cin >> s >> t;\n  \
    \      --s, --t;\n        // [0, t]\u306E\u9593\u306B\u4F75\u5408\u3055\u308C\u305F\
    \u304B\u3069\u3046\u304B\n        // \u73FE\u5728\u306Ecount+1\u306E\u30BF\u30A4\
    \u30DF\u30F3\u30B0\u3067\u4F75\u5408\u3055\u308C\u305F\u4E8B\u306B\u3059\u308B\
    \n        int ok = MOD, ng = 0;\n        while(abs(ng - ok) > 1){\n          \
    \  int mid = (ok + ng) / 2;\n            (uf.Find(s, mid) == uf.Find(t, mid) ?\
    \ ok : ng) = mid;\n        }\n        if(ok >= m){\n            cout << 0 << endl;\n\
    \            continue;\n        }\n        cout << query_time[ng] << endl;\n \
    \   }\n\n\n}\n\n"
  dependsOn:
  - lib/classes/persistentunionfind.cpp
  isVerificationFile: true
  path: verify/persistentunionfind.test.cpp
  requiredBy: []
  timestamp: '2020-02-24 09:29:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/persistentunionfind.test.cpp
layout: document
redirect_from:
- /verify/verify/persistentunionfind.test.cpp
- /verify/verify/persistentunionfind.test.cpp.html
title: verify/persistentunionfind.test.cpp
---
