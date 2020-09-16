---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/dinic.cpp
    title: lib/classes/dinic.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "#line 1 \"verify/bipartitematching.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/bipartitematching\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing i64 = long;\n\n#line 1 \"lib/classes/dinic.cpp\"\n\
    template <typename T>\nstruct Dinic{\n    struct Edge{\n        int to, rev;\n\
    \        T cap;\n        Edge(int to, T cap, int rev) : to(to), rev(rev), cap(cap){}\n\
    \    };\n\n    vector<vector<Edge>> edges;\n    T _inf;\n    vector<T> min_cost;\n\
    \    vector<int> cnt;\n\n    Dinic(int n) : edges(n), _inf(numeric_limits<T>::max()){}\n\
    \n    void add(int from, int to, T cap){\n        edges[from].emplace_back(to,\
    \ cap, static_cast<int>(edges[to].size()));\n        edges[to].emplace_back(from,\
    \ 0, static_cast<int>(edges[from].size()) - 1);\n    }\n\n    bool bfs(int s,\
    \ int t){\n        min_cost.assign(edges.size(), -1);\n        queue<int> que;\n\
    \        min_cost[s] = 0;\n        que.emplace(s);\n        while(!que.empty()\
    \ && min_cost[t] == -1){\n            int x = que.front();\n            que.pop();\n\
    \            for(auto& ed : edges[x])\n                if(ed.cap > 0 && min_cost[ed.to]\
    \ == -1){\n                    min_cost[ed.to] = min_cost[x] + 1;\n          \
    \          que.emplace(ed.to);\n                }\n        }\n        return min_cost[t]\
    \ != -1;\n    }\n\n    T dfs(int idx, int t, T flow){\n        if(idx == t)\n\
    \            return flow;\n        T ret = 0;\n        while(cnt[idx] < edges[idx].size()){\n\
    \            auto& ed = edges[idx][cnt[idx]];\n            if(ed.cap > 0 && min_cost[idx]\
    \ < min_cost[ed.to]){\n                T d = dfs(ed.to, t, min(flow, ed.cap));\n\
    \                ed.cap -= d;\n                edges[ed.to][ed.rev].cap += d;\n\
    \                ret += d;\n                flow -= d;\n                if(flow\
    \ == 0)\n                    break;\n            }\n            ++cnt[idx];\n\
    \        }\n        return ret;\n    }\n\n    T solve(int s, int t){\n       \
    \ T flow = 0;\n        while(bfs(s, t)){\n            cnt.assign(edges.size(),\
    \ 0);\n            T f = 0;\n            while((f = dfs(s, t, _inf)) > 0)\n  \
    \              flow += f;\n        }\n        return flow;\n    }\n\n};\n\n#line\
    \ 8 \"verify/bipartitematching.test.cpp\"\n\n\nsigned main() {\n\n    int l, r,\
    \ m;\n    cin >> l >> r >> m;\n    Dinic<int> d(l + r + 2);\n    for(int i = 0;\
    \ i < m; ++i){\n        int a, b;\n        cin >> a >> b;\n        d.add(a, l\
    \ + b, 1);\n    }\n    for(int i = 0; i < l; ++i)\n        d.add(l + r, i, 1);\n\
    \    for(int i = 0; i < r; ++i)\n        d.add(l + i, l + r + 1, 1);\n    cout\
    \ << d.solve(l + r, l + r + 1) << endl;\n    for(int i = 0; i < l + r; ++i)\n\
    \        for(auto& e : d.edges[i]){\n            if(e.to >= l + r || i >= e.to)\n\
    \                continue;\n            if(e.cap == 0)\n                cout <<\
    \ i << \" \" << e.to - l << endl;\n        }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\n\n\
    #include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#include\
    \ \"../lib/classes/dinic.cpp\"\n\n\nsigned main() {\n\n    int l, r, m;\n    cin\
    \ >> l >> r >> m;\n    Dinic<int> d(l + r + 2);\n    for(int i = 0; i < m; ++i){\n\
    \        int a, b;\n        cin >> a >> b;\n        d.add(a, l + b, 1);\n    }\n\
    \    for(int i = 0; i < l; ++i)\n        d.add(l + r, i, 1);\n    for(int i =\
    \ 0; i < r; ++i)\n        d.add(l + i, l + r + 1, 1);\n    cout << d.solve(l +\
    \ r, l + r + 1) << endl;\n    for(int i = 0; i < l + r; ++i)\n        for(auto&\
    \ e : d.edges[i]){\n            if(e.to >= l + r || i >= e.to)\n             \
    \   continue;\n            if(e.cap == 0)\n                cout << i << \" \"\
    \ << e.to - l << endl;\n        }\n}\n\n"
  dependsOn:
  - lib/classes/dinic.cpp
  isVerificationFile: true
  path: verify/bipartitematching.test.cpp
  requiredBy: []
  timestamp: '2019-12-04 00:43:23+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/bipartitematching.test.cpp
layout: document
redirect_from:
- /verify/verify/bipartitematching.test.cpp
- /verify/verify/bipartitematching.test.cpp.html
title: verify/bipartitematching.test.cpp
---
