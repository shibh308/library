---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/bipartitematching.test.cpp
    title: verify/bipartitematching.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/dinic.cpp\"\ntemplate <typename T>\nstruct Dinic{\n\
    \    struct Edge{\n        int to, rev;\n        T cap;\n        Edge(int to,\
    \ T cap, int rev) : to(to), rev(rev), cap(cap){}\n    };\n\n    vector<vector<Edge>>\
    \ edges;\n    T _inf;\n    vector<T> min_cost;\n    vector<int> cnt;\n\n    Dinic(int\
    \ n) : edges(n), _inf(numeric_limits<T>::max()){}\n\n    void add(int from, int\
    \ to, T cap){\n        edges[from].emplace_back(to, cap, static_cast<int>(edges[to].size()));\n\
    \        edges[to].emplace_back(from, 0, static_cast<int>(edges[from].size())\
    \ - 1);\n    }\n\n    bool bfs(int s, int t){\n        min_cost.assign(edges.size(),\
    \ -1);\n        queue<int> que;\n        min_cost[s] = 0;\n        que.emplace(s);\n\
    \        while(!que.empty() && min_cost[t] == -1){\n            int x = que.front();\n\
    \            que.pop();\n            for(auto& ed : edges[x])\n              \
    \  if(ed.cap > 0 && min_cost[ed.to] == -1){\n                    min_cost[ed.to]\
    \ = min_cost[x] + 1;\n                    que.emplace(ed.to);\n              \
    \  }\n        }\n        return min_cost[t] != -1;\n    }\n\n    T dfs(int idx,\
    \ int t, T flow){\n        if(idx == t)\n            return flow;\n        T ret\
    \ = 0;\n        while(cnt[idx] < edges[idx].size()){\n            auto& ed = edges[idx][cnt[idx]];\n\
    \            if(ed.cap > 0 && min_cost[idx] < min_cost[ed.to]){\n            \
    \    T d = dfs(ed.to, t, min(flow, ed.cap));\n                ed.cap -= d;\n \
    \               edges[ed.to][ed.rev].cap += d;\n                ret += d;\n  \
    \              flow -= d;\n                if(flow == 0)\n                   \
    \ break;\n            }\n            ++cnt[idx];\n        }\n        return ret;\n\
    \    }\n\n    T solve(int s, int t){\n        T flow = 0;\n        while(bfs(s,\
    \ t)){\n            cnt.assign(edges.size(), 0);\n            T f = 0;\n     \
    \       while((f = dfs(s, t, _inf)) > 0)\n                flow += f;\n       \
    \ }\n        return flow;\n    }\n\n};\n\n"
  code: "template <typename T>\nstruct Dinic{\n    struct Edge{\n        int to, rev;\n\
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
    \              flow += f;\n        }\n        return flow;\n    }\n\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/dinic.cpp
  requiredBy: []
  timestamp: '2019-12-04 00:09:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/bipartitematching.test.cpp
documentation_of: lib/classes/dinic.cpp
layout: document
redirect_from:
- /library/lib/classes/dinic.cpp
- /library/lib/classes/dinic.cpp.html
title: lib/classes/dinic.cpp
---
