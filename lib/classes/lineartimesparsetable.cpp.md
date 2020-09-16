---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/multi_str_matching.test.cpp
    title: verify/multi_str_matching.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string_seatch.test.cpp
    title: verify/string_seatch.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/lineartimesparsetable.cpp\"\ntemplate<typename\
    \ T>\nstruct LinearTimeSparseTable{\n    int n, m;\n    vector<T> a;\n    SparseTable<T>\
    \ b;\n    vector<vector<uint32_t>> c;\n    static constexpr uint32_t block = 32;\n\
    \    LinearTimeSparseTable(vector<T>& v) : n(v.size()), a(v), m((n + block - 1)\
    \ / block){\n        n = m * block;\n        v.resize(n, 0);\n        vector<T>\
    \ big_table(m);\n        for(int i = 0; i < n; ++i)\n            big_table[i /\
    \ block] = (i & (block - 1) ? min(big_table[i / block], v[i]) : v[i]);\n     \
    \   b = SparseTable<T>(big_table, [](auto x, auto y){return min(x, y);});\n  \
    \      c.assign(m, vector<uint32_t>(block, 0));\n        for(int i = 0; i < m;\
    \ ++i){\n            stack<pair<T, int>> st;\n            vector<int> g(block,\
    \ -1);\n            for(int j = 0; j < block; ++j){\n                T x = v[i\
    \ * block + j];\n                while(!st.empty() && x <= st.top().first)st.pop();\n\
    \                if(!st.empty())\n                    g[j] = st.top().second;\n\
    \                st.emplace(x, j);\n            }\n            for(int j = 0;\
    \ j < block; ++j){\n                c[i][j] = (g[j] == -1 ? 0 : c[i][g[j]] | (1u\
    \ << g[j]));\n            }\n        }\n    }\n    T get_small(int i, int j, int\
    \ k){\n        uint32_t w = c[k][j] & ~((1u << i) - 1);\n        if(w == 0)\n\
    \            return a[k * block + j];\n        return a[k * block + (__builtin_ffs(w)\
    \ - 1)];\n    }\n    T get(int l, int r){\n        --r;\n        int lb = l /\
    \ block;\n        int rb = r / block;\n        int lc = l & (block - 1);\n   \
    \     int rc = r & (block - 1);\n        if(lb == rb)\n            return get_small(lc,\
    \ rc, lb);\n        T l_res = get_small(lc, block - 1, lb);\n        T r_res =\
    \ get_small(0, rc, rb);\n        if(rb - lb == 1)\n            return min(l_res,\
    \ r_res);\n        return min({l_res, r_res, b.get(lb + 1, rb)});\n    }\n};\n\
    \n"
  code: "template<typename T>\nstruct LinearTimeSparseTable{\n    int n, m;\n    vector<T>\
    \ a;\n    SparseTable<T> b;\n    vector<vector<uint32_t>> c;\n    static constexpr\
    \ uint32_t block = 32;\n    LinearTimeSparseTable(vector<T>& v) : n(v.size()),\
    \ a(v), m((n + block - 1) / block){\n        n = m * block;\n        v.resize(n,\
    \ 0);\n        vector<T> big_table(m);\n        for(int i = 0; i < n; ++i)\n \
    \           big_table[i / block] = (i & (block - 1) ? min(big_table[i / block],\
    \ v[i]) : v[i]);\n        b = SparseTable<T>(big_table, [](auto x, auto y){return\
    \ min(x, y);});\n        c.assign(m, vector<uint32_t>(block, 0));\n        for(int\
    \ i = 0; i < m; ++i){\n            stack<pair<T, int>> st;\n            vector<int>\
    \ g(block, -1);\n            for(int j = 0; j < block; ++j){\n               \
    \ T x = v[i * block + j];\n                while(!st.empty() && x <= st.top().first)st.pop();\n\
    \                if(!st.empty())\n                    g[j] = st.top().second;\n\
    \                st.emplace(x, j);\n            }\n            for(int j = 0;\
    \ j < block; ++j){\n                c[i][j] = (g[j] == -1 ? 0 : c[i][g[j]] | (1u\
    \ << g[j]));\n            }\n        }\n    }\n    T get_small(int i, int j, int\
    \ k){\n        uint32_t w = c[k][j] & ~((1u << i) - 1);\n        if(w == 0)\n\
    \            return a[k * block + j];\n        return a[k * block + (__builtin_ffs(w)\
    \ - 1)];\n    }\n    T get(int l, int r){\n        --r;\n        int lb = l /\
    \ block;\n        int rb = r / block;\n        int lc = l & (block - 1);\n   \
    \     int rc = r & (block - 1);\n        if(lb == rb)\n            return get_small(lc,\
    \ rc, lb);\n        T l_res = get_small(lc, block - 1, lb);\n        T r_res =\
    \ get_small(0, rc, rb);\n        if(rb - lb == 1)\n            return min(l_res,\
    \ r_res);\n        return min({l_res, r_res, b.get(lb + 1, rb)});\n    }\n};\n\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/lineartimesparsetable.cpp
  requiredBy: []
  timestamp: '2020-05-31 22:09:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/multi_str_matching.test.cpp
  - verify/string_seatch.test.cpp
documentation_of: lib/classes/lineartimesparsetable.cpp
layout: document
redirect_from:
- /library/lib/classes/lineartimesparsetable.cpp
- /library/lib/classes/lineartimesparsetable.cpp.html
title: lib/classes/lineartimesparsetable.cpp
---
