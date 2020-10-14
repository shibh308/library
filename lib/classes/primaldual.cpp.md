---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/primaldual.cpp\"\ntemplate <typename T, typename\
    \ U>\nstruct PrimalDual{\n    struct Edge{\n        int to, rev;\n        U cap;\n\
    \        T cost;\n        Edge(int to, U cap, T cost, int rev) :\n           \
    \ to(to), rev(rev), cap(cap), cost(cost){}\n    };\n    vector<vector<Edge>> edges;\n\
    \    T _inf;\n    vector<T> potential, min_cost;\n    vector<int> prev_v, prev_e;\n\
    \n    PrimalDual(int n) : edges(n), _inf(numeric_limits<T>::max()){}\n\n    void\
    \ add(int from, int to, U cap, T cost){\n        edges[from].emplace_back(to,\
    \ cap, cost, static_cast<int>(edges[to].size()));\n        edges[to].emplace_back(from,\
    \ 0, -cost, static_cast<int>(edges[from].size()) - 1);\n    }\n\n    T solve(int\
    \ s, int t, U flow){\n        int n = edges.size();\n        T ret = 0;\n    \
    \    priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> que;\n\
    \        potential.assign(n, 0);\n        prev_v.assign(n, -1);\n        prev_e.assign(n,\
    \ -1);\n        while(flow > 0){\n            min_cost.assign(n, _inf);\n    \
    \        que.emplace(0, s);\n            min_cost[s] = 0;\n            while(!que.empty()){\n\
    \                T fl;\n                int pos;\n                tie(fl, pos)\
    \ = que.top();\n                que.pop();\n                if(min_cost[pos] !=\
    \ fl)\n                    continue;\n                for(int i = 0; i < edges[pos].size();\
    \ ++i){\n                    auto& ed = edges[pos][i];\n                    T\
    \ nex = fl + ed.cost + potential[pos] - potential[ed.to];\n                  \
    \  if(ed.cap > 0 && min_cost[ed.to] > nex){\n                        min_cost[ed.to]\
    \ = nex;\n                        prev_v[ed.to] = pos;\n                     \
    \   prev_e[ed.to] = i;\n                        que.emplace(min_cost[ed.to], ed.to);\n\
    \                    }\n                }\n            }\n            if(min_cost[t]\
    \ == _inf)\n                return -1;\n            for(int i = 0; i < n; ++i)\n\
    \                potential[i] += min_cost[i];\n            T add_flow = flow;\n\
    \            for(int x = t; x != s; x = prev_v[x])\n                add_flow =\
    \ min(add_flow, edges[prev_v[x]][prev_e[x]].cap);\n            flow -= add_flow;\n\
    \            ret += add_flow * potential[t];\n            for(int x = t; x !=\
    \ s; x = prev_v[x]){\n                auto& ed = edges[prev_v[x]][prev_e[x]];\n\
    \                ed.cap -= add_flow;\n                edges[x][ed.rev].cap +=\
    \ add_flow;\n            }\n        }\n        return ret;\n    }\n};\n\n"
  code: "template <typename T, typename U>\nstruct PrimalDual{\n    struct Edge{\n\
    \        int to, rev;\n        U cap;\n        T cost;\n        Edge(int to, U\
    \ cap, T cost, int rev) :\n            to(to), rev(rev), cap(cap), cost(cost){}\n\
    \    };\n    vector<vector<Edge>> edges;\n    T _inf;\n    vector<T> potential,\
    \ min_cost;\n    vector<int> prev_v, prev_e;\n\n    PrimalDual(int n) : edges(n),\
    \ _inf(numeric_limits<T>::max()){}\n\n    void add(int from, int to, U cap, T\
    \ cost){\n        edges[from].emplace_back(to, cap, cost, static_cast<int>(edges[to].size()));\n\
    \        edges[to].emplace_back(from, 0, -cost, static_cast<int>(edges[from].size())\
    \ - 1);\n    }\n\n    T solve(int s, int t, U flow){\n        int n = edges.size();\n\
    \        T ret = 0;\n        priority_queue<pair<T,int>, vector<pair<T,int>>,\
    \ greater<pair<T,int>>> que;\n        potential.assign(n, 0);\n        prev_v.assign(n,\
    \ -1);\n        prev_e.assign(n, -1);\n        while(flow > 0){\n            min_cost.assign(n,\
    \ _inf);\n            que.emplace(0, s);\n            min_cost[s] = 0;\n     \
    \       while(!que.empty()){\n                T fl;\n                int pos;\n\
    \                tie(fl, pos) = que.top();\n                que.pop();\n     \
    \           if(min_cost[pos] != fl)\n                    continue;\n         \
    \       for(int i = 0; i < edges[pos].size(); ++i){\n                    auto&\
    \ ed = edges[pos][i];\n                    T nex = fl + ed.cost + potential[pos]\
    \ - potential[ed.to];\n                    if(ed.cap > 0 && min_cost[ed.to] >\
    \ nex){\n                        min_cost[ed.to] = nex;\n                    \
    \    prev_v[ed.to] = pos;\n                        prev_e[ed.to] = i;\n      \
    \                  que.emplace(min_cost[ed.to], ed.to);\n                    }\n\
    \                }\n            }\n            if(min_cost[t] == _inf)\n     \
    \           return -1;\n            for(int i = 0; i < n; ++i)\n             \
    \   potential[i] += min_cost[i];\n            T add_flow = flow;\n           \
    \ for(int x = t; x != s; x = prev_v[x])\n                add_flow = min(add_flow,\
    \ edges[prev_v[x]][prev_e[x]].cap);\n            flow -= add_flow;\n         \
    \   ret += add_flow * potential[t];\n            for(int x = t; x != s; x = prev_v[x]){\n\
    \                auto& ed = edges[prev_v[x]][prev_e[x]];\n                ed.cap\
    \ -= add_flow;\n                edges[x][ed.rev].cap += add_flow;\n          \
    \  }\n        }\n        return ret;\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/primaldual.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/primaldual.cpp
layout: document
redirect_from:
- /library/lib/classes/primaldual.cpp
- /library/lib/classes/primaldual.cpp.html
title: lib/classes/primaldual.cpp
---
