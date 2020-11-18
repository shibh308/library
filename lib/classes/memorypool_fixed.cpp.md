---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/memorypool_fixed.cpp\"\ntemplate <typename T,\
    \ int SIZE = 1000000>\nstruct MemoryPool{\n    int idx;\n    stack<int> st;\n\
    \    T pool[SIZE];\n    struct Index{\n        int idx;\n        friend bool operator==(const\
    \ Index& a, const Index& b){return a.idx == b.idx;}\n        friend bool operator!=(const\
    \ Index& a, const Index& b){return a.idx != b.idx;}\n    };\n    MemoryPool()\
    \ : idx(0){}\n    Index alloc(){\n        if(!st.empty()){\n            int res\
    \ = st.top();\n            st.pop();\n            return {res};\n        }\n \
    \       assert(++idx != SIZE);\n        return {idx};\n    }\n    void free(Index\
    \ x){st.push(x.idx);}\n    int used(){return idx - st.size();}\n\n    T& operator[](Index\
    \ x){return pool[x.idx];}\n};\n"
  code: "template <typename T, int SIZE = 1000000>\nstruct MemoryPool{\n    int idx;\n\
    \    stack<int> st;\n    T pool[SIZE];\n    struct Index{\n        int idx;\n\
    \        friend bool operator==(const Index& a, const Index& b){return a.idx ==\
    \ b.idx;}\n        friend bool operator!=(const Index& a, const Index& b){return\
    \ a.idx != b.idx;}\n    };\n    MemoryPool() : idx(0){}\n    Index alloc(){\n\
    \        if(!st.empty()){\n            int res = st.top();\n            st.pop();\n\
    \            return {res};\n        }\n        assert(++idx != SIZE);\n      \
    \  return {idx};\n    }\n    void free(Index x){st.push(x.idx);}\n    int used(){return\
    \ idx - st.size();}\n\n    T& operator[](Index x){return pool[x.idx];}\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/memorypool_fixed.cpp
  requiredBy: []
  timestamp: '2020-10-16 13:51:55+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/memorypool_fixed.cpp
layout: document
redirect_from:
- /library/lib/classes/memorypool_fixed.cpp
- /library/lib/classes/memorypool_fixed.cpp.html
title: lib/classes/memorypool_fixed.cpp
---
