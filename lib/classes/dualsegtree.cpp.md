---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/dualsegtree.cpp\"\ntemplate<typename T>\nstruct\
    \ Segtree{\n    int n;\n    T op;\n    vector<T> elm;\n    function<T(T, T)> f;\n\
    \n    Segtree(int n, T init, function<T(T, T)> f, T op = T()) :\n        n(n),\n\
    \        op(op),\n        elm(2 * n, op),\n        f(f)\n    {\n        for(int\
    \ i = 0; i < n; ++i)\n            elm[i + n] = init;\n    }\n\n    Segtree(int\
    \ n, vector<T> init, function<T(T, T)> f, T op = T()) :\n        n(n),\n     \
    \   op(op),\n        elm(2 * n, op),\n        f(f)\n    {\n        for(int i =\
    \ 0; i < n; ++i)\n            elm[i + n] = init[i];\n    }\n\n    void update(int\
    \ x, int y, T val){\n        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){\n\
    \            if(x & 1){\n                elm[x] = f(elm[x], val);\n          \
    \      x++;\n            }\n            if(!(y & 1)){\n                elm[y]\
    \ = f(elm[y], val);\n                y--;\n            }\n        }\n    }\n\n\
    \    void update(int x, T val){\n        x += n;\n        elm[x + n] = f(elm[x\
    \ + n], val);\n    }\n\n    T get(int x){\n        x += n;\n        T val = elm[x];\n\
    \        while(x >>= 1)\n            val = f(val, elm[x]);\n        return val;\n\
    \    }\n};\n"
  code: "template<typename T>\nstruct Segtree{\n    int n;\n    T op;\n    vector<T>\
    \ elm;\n    function<T(T, T)> f;\n\n    Segtree(int n, T init, function<T(T, T)>\
    \ f, T op = T()) :\n        n(n),\n        op(op),\n        elm(2 * n, op),\n\
    \        f(f)\n    {\n        for(int i = 0; i < n; ++i)\n            elm[i +\
    \ n] = init;\n    }\n\n    Segtree(int n, vector<T> init, function<T(T, T)> f,\
    \ T op = T()) :\n        n(n),\n        op(op),\n        elm(2 * n, op),\n   \
    \     f(f)\n    {\n        for(int i = 0; i < n; ++i)\n            elm[i + n]\
    \ = init[i];\n    }\n\n    void update(int x, int y, T val){\n        for(x +=\
    \ n, y += n - 1; x <= y; x >>= 1, y >>= 1){\n            if(x & 1){\n        \
    \        elm[x] = f(elm[x], val);\n                x++;\n            }\n     \
    \       if(!(y & 1)){\n                elm[y] = f(elm[y], val);\n            \
    \    y--;\n            }\n        }\n    }\n\n    void update(int x, T val){\n\
    \        x += n;\n        elm[x + n] = f(elm[x + n], val);\n    }\n\n    T get(int\
    \ x){\n        x += n;\n        T val = elm[x];\n        while(x >>= 1)\n    \
    \        val = f(val, elm[x]);\n        return val;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/dualsegtree.cpp
  requiredBy: []
  timestamp: '2020-10-14 21:55:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/dualsegtree.cpp
layout: document
redirect_from:
- /library/lib/classes/dualsegtree.cpp
- /library/lib/classes/dualsegtree.cpp.html
title: lib/classes/dualsegtree.cpp
---
