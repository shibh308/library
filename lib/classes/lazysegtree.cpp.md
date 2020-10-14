---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/rmq_raq.test.cpp
    title: verify/rmq_raq.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/lazysegtree.cpp\"\ntemplate<typename T, typename\
    \ U>\nstruct Segtree{\n    int n;\n    T op_t;\n    U op_u;\n    vector<T> elm;\n\
    \    vector<U> lazy;\n    vector<int> length;\n    function<T(T, T)> f;\n    function<T(T,\
    \ U, int)> g;\n    function<U(U, U)> h;\n\n    Segtree(int n, T init, function<T(T,\
    \ T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t = T(), U op_u =\
    \ U()) :\n        n(n),\n        op_t(op_t),\n        op_u(op_u),\n        elm(2\
    \ * n, init),\n        lazy(2 * n, op_u),\n        length(2 * n, 0),\n       \
    \ f(f),\n        g(g),\n        h(h)\n    {\n        for(int i = n - 1; i > 0;\
    \ --i){\n            elm[i] = f(elm[2 * i], elm[2 * i + 1]);\n            length[i]\
    \ = length[2 * i] + 1;\n        }\n    }\n\n    Segtree(int n, vector<T> init,\
    \ function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t =\
    \ T(), U op_u = U()) :\n        n(n),\n        op_t(op_t),\n        op_u(op_u),\n\
    \        elm(2 * n),\n        lazy(2 * n, op_u),\n        length(2 * n, 0),\n\
    \        f(f),\n        g(g),\n        h(h)\n    {\n        for(int i = 0; i <\
    \ n; ++i)\n            elm[i + n] = init[i];\n\n        for(int i = n - 1; i >\
    \ 0; --i){\n            elm[i] = f(elm[2 * i], elm[2 * i + 1]);\n            length[i]\
    \ = length[2 * i] + 1;\n        }\n    }\n\n    vector<int> get_list(int x, int\
    \ y){\n\n        vector<int> ret_list;\n        for(x += n, y += n - 1; x; x >>=\
    \ 1, y >>= 1){\n            ret_list.emplace_back(x);\n            if(x != y)\n\
    \                ret_list.emplace_back(y);\n        }\n\n        return ret_list;\n\
    \    }\n\n    void eval(int x){\n\n        elm[x] = g(elm[x], lazy[x], 1 << length[x]);\n\
    \        if(x < n){\n            lazy[2 * x] = h(lazy[2 * x], lazy[x]);\n    \
    \        lazy[2 * x + 1] = h(lazy[2 * x + 1], lazy[x]);\n        }\n        lazy[x]\
    \ = op_u;\n    }\n\n    void update(int x, int y, U val){\n\n        if(x == y)\n\
    \            return;\n        vector<int> index_list = get_list(x, y);\n     \
    \   for(int i = index_list.size() - 1; i >= 0; --i)\n            eval(index_list[i]);\n\
    \n        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){\n            if(x\
    \ & 1){\n                lazy[x] = h(lazy[x], val);\n                eval(x++);\n\
    \            }\n            if(!(y & 1)){\n                lazy[y] = h(lazy[y],\
    \ val);\n                eval(y--);\n            }\n        }\n\n        for(auto\
    \ index : index_list){\n            if(index < n){\n                eval(2 * index);\n\
    \                eval(2 * index + 1);\n                elm[index] = f(elm[2 *\
    \ index], elm[2 * index + 1]);\n            }\n        }\n    }\n\n    T get(int\
    \ x, int y){\n\n        vector<int> index_list = get_list(x, y);\n        for(int\
    \ i = index_list.size() - 1; i >= 0; --i)\n            eval(index_list[i]);\n\n\
    \        T l = op_t, r = op_t;\n        for(x += n, y += n - 1; x <= y; x >>=\
    \ 1, y >>= 1){\n            if(x & 1){\n                eval(x);\n           \
    \     l = f(l, elm[x++]);\n            }\n            if(!(y & 1)){\n        \
    \        eval(y);\n                r = f(elm[y--], r);\n            }\n      \
    \  }\n        return f(l, r);\n    }\n};\n\n"
  code: "template<typename T, typename U>\nstruct Segtree{\n    int n;\n    T op_t;\n\
    \    U op_u;\n    vector<T> elm;\n    vector<U> lazy;\n    vector<int> length;\n\
    \    function<T(T, T)> f;\n    function<T(T, U, int)> g;\n    function<U(U, U)>\
    \ h;\n\n    Segtree(int n, T init, function<T(T, T)> f, function<T(T, U, int)>\
    \ g, function<U(U, U)> h, T op_t = T(), U op_u = U()) :\n        n(n),\n     \
    \   op_t(op_t),\n        op_u(op_u),\n        elm(2 * n, init),\n        lazy(2\
    \ * n, op_u),\n        length(2 * n, 0),\n        f(f),\n        g(g),\n     \
    \   h(h)\n    {\n        for(int i = n - 1; i > 0; --i){\n            elm[i] =\
    \ f(elm[2 * i], elm[2 * i + 1]);\n            length[i] = length[2 * i] + 1;\n\
    \        }\n    }\n\n    Segtree(int n, vector<T> init, function<T(T, T)> f, function<T(T,\
    \ U, int)> g, function<U(U, U)> h, T op_t = T(), U op_u = U()) :\n        n(n),\n\
    \        op_t(op_t),\n        op_u(op_u),\n        elm(2 * n),\n        lazy(2\
    \ * n, op_u),\n        length(2 * n, 0),\n        f(f),\n        g(g),\n     \
    \   h(h)\n    {\n        for(int i = 0; i < n; ++i)\n            elm[i + n] =\
    \ init[i];\n\n        for(int i = n - 1; i > 0; --i){\n            elm[i] = f(elm[2\
    \ * i], elm[2 * i + 1]);\n            length[i] = length[2 * i] + 1;\n       \
    \ }\n    }\n\n    vector<int> get_list(int x, int y){\n\n        vector<int> ret_list;\n\
    \        for(x += n, y += n - 1; x; x >>= 1, y >>= 1){\n            ret_list.emplace_back(x);\n\
    \            if(x != y)\n                ret_list.emplace_back(y);\n        }\n\
    \n        return ret_list;\n    }\n\n    void eval(int x){\n\n        elm[x] =\
    \ g(elm[x], lazy[x], 1 << length[x]);\n        if(x < n){\n            lazy[2\
    \ * x] = h(lazy[2 * x], lazy[x]);\n            lazy[2 * x + 1] = h(lazy[2 * x\
    \ + 1], lazy[x]);\n        }\n        lazy[x] = op_u;\n    }\n\n    void update(int\
    \ x, int y, U val){\n\n        if(x == y)\n            return;\n        vector<int>\
    \ index_list = get_list(x, y);\n        for(int i = index_list.size() - 1; i >=\
    \ 0; --i)\n            eval(index_list[i]);\n\n        for(x += n, y += n - 1;\
    \ x <= y; x >>= 1, y >>= 1){\n            if(x & 1){\n                lazy[x]\
    \ = h(lazy[x], val);\n                eval(x++);\n            }\n            if(!(y\
    \ & 1)){\n                lazy[y] = h(lazy[y], val);\n                eval(y--);\n\
    \            }\n        }\n\n        for(auto index : index_list){\n         \
    \   if(index < n){\n                eval(2 * index);\n                eval(2 *\
    \ index + 1);\n                elm[index] = f(elm[2 * index], elm[2 * index +\
    \ 1]);\n            }\n        }\n    }\n\n    T get(int x, int y){\n\n      \
    \  vector<int> index_list = get_list(x, y);\n        for(int i = index_list.size()\
    \ - 1; i >= 0; --i)\n            eval(index_list[i]);\n\n        T l = op_t, r\
    \ = op_t;\n        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){\n      \
    \      if(x & 1){\n                eval(x);\n                l = f(l, elm[x++]);\n\
    \            }\n            if(!(y & 1)){\n                eval(y);\n        \
    \        r = f(elm[y--], r);\n            }\n        }\n        return f(l, r);\n\
    \    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/lazysegtree.cpp
  requiredBy: []
  timestamp: '2020-03-03 20:41:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/rmq_raq.test.cpp
documentation_of: lib/classes/lazysegtree.cpp
layout: document
redirect_from:
- /library/lib/classes/lazysegtree.cpp
- /library/lib/classes/lazysegtree.cpp.html
title: lib/classes/lazysegtree.cpp
---
