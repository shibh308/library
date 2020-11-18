---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/dynamicwaveletmatrix_kthmin.test.cpp
    title: verify/dynamicwaveletmatrix_kthmin.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/dynamicwaveletmatrix_rmq.test.cpp
    title: verify/dynamicwaveletmatrix_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/redblacktree_lazy.test.cpp
    title: verify/redblacktree_lazy.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/redblacktree_rsq.test.cpp
    title: verify/redblacktree_rsq.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/redblacktree_sset.test.cpp
    title: verify/redblacktree_sset.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/twothreetree.test.cpp
    title: verify/twothreetree.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/zdd_knapsack.test.cpp
    title: verify/zdd_knapsack.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/memorypool.cpp\"\ntemplate <typename T>\nstruct\
    \ MemoryPool{\n    int siz, idx;\n    stack<int> st;\n    vector<T*> pool;\n \
    \   struct Index{\n        int idx;\n        friend bool operator==(const Index&\
    \ a, const Index& b){return a.idx == b.idx;}\n        friend bool operator!=(const\
    \ Index& a, const Index& b){return a.idx != b.idx;}\n    };\n    MemoryPool()\
    \ : siz(1), idx(0){}\n    void resize(){\n        pool.emplace_back(new T[siz]);\n\
    \        siz <<= 1;\n    }\n    Index alloc(){\n        if(!st.empty()){\n   \
    \         int res = st.top();\n            st.pop();\n            return {res};\n\
    \        }\n        if(++idx == siz)\n            resize();\n        return {idx};\n\
    \    }\n    void free(Index x){st.push(x.idx);}\n    int used(){return idx - st.size();}\n\
    \n    T& operator[](Index x){return pool[31 - __builtin_clz(x.idx)][x.idx & ~(1\
    \ << (31 - __builtin_clz(x.idx)))];}\n};\n\n"
  code: "template <typename T>\nstruct MemoryPool{\n    int siz, idx;\n    stack<int>\
    \ st;\n    vector<T*> pool;\n    struct Index{\n        int idx;\n        friend\
    \ bool operator==(const Index& a, const Index& b){return a.idx == b.idx;}\n  \
    \      friend bool operator!=(const Index& a, const Index& b){return a.idx !=\
    \ b.idx;}\n    };\n    MemoryPool() : siz(1), idx(0){}\n    void resize(){\n \
    \       pool.emplace_back(new T[siz]);\n        siz <<= 1;\n    }\n    Index alloc(){\n\
    \        if(!st.empty()){\n            int res = st.top();\n            st.pop();\n\
    \            return {res};\n        }\n        if(++idx == siz)\n            resize();\n\
    \        return {idx};\n    }\n    void free(Index x){st.push(x.idx);}\n    int\
    \ used(){return idx - st.size();}\n\n    T& operator[](Index x){return pool[31\
    \ - __builtin_clz(x.idx)][x.idx & ~(1 << (31 - __builtin_clz(x.idx)))];}\n};\n\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/memorypool.cpp
  requiredBy: []
  timestamp: '2020-04-21 23:33:35+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/twothreetree.test.cpp
  - verify/redblacktree_sset.test.cpp
  - verify/redblacktree_rsq.test.cpp
  - verify/dynamicwaveletmatrix_rmq.test.cpp
  - verify/redblacktree_lazy.test.cpp
  - verify/dynamicwaveletmatrix_kthmin.test.cpp
  - verify/zdd_knapsack.test.cpp
documentation_of: lib/classes/memorypool.cpp
layout: document
redirect_from:
- /library/lib/classes/memorypool.cpp
- /library/lib/classes/memorypool.cpp.html
title: lib/classes/memorypool.cpp
---
