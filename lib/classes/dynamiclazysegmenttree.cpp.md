---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/rmq_raq_dynamic.test.cpp
    title: verify/rmq_raq_dynamic.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/dynamiclazysegmenttree.cpp\"\ntemplate<typename\
    \ T, typename U>\nstruct Segtree{\n\n    struct SegNode{\n        T val;\n   \
    \     U lazy;\n\n        SegNode* l;\n        SegNode* r;\n        SegNode(T val,\
    \ U lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr){}\n    };\n\n    i64\
    \ n;\n    function<T(T, T)> f;\n    function<T(T, U, int)> g;\n    function<U(U,\
    \ U)> h;\n    T op_t;\n    U op_u;\n\n    SegNode* root;\n\n    Segtree(int n_,\
    \ function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t,\
    \ U op_u) : f(f), g(g), h(h), op_t(op_t), op_u(op_u){\n        for(n = 1; n <\
    \ n_; n <<= 1);\n        root = new SegNode(op_t, op_u);\n    }\n\n    SegNode*\
    \ getl(SegNode* node){\n        return node->l ? node->l : node->l = new SegNode(op_t,\
    \ op_u);\n    }\n\n    SegNode* getr(SegNode* node){\n        return node->r ?\
    \ node->r : node->r = new SegNode(op_t, op_u);\n    }\n\n    void eval(SegNode*\
    \ node, i64 len){\n        node->val = g(node->val, node->lazy, len);\n      \
    \  getl(node);\n        node->l->lazy = h(node->l->lazy, node->lazy);\n      \
    \  getr(node);\n        node->r->lazy = h(node->r->lazy, node->lazy);\n      \
    \  node->lazy = op_u;\n    }\n\n    void update(i64 x, i64 y, U val, SegNode*\
    \ node = nullptr, i64 l = 0, i64 r = 0){\n        if(node == nullptr){\n     \
    \       node = root;\n            r = n;\n        }\n        eval(node, r - l);\n\
    \        if(r <= x || y <= l)\n            return ;\n        if(x <= l && r <=\
    \ y){\n            node->lazy = h(node->lazy, val);\n            eval(node, r\
    \ - l);\n        }else{\n            i64 mid = (l + r) >> 1;\n            update(x,\
    \ y, val, getl(node), l, mid);\n            update(x, y, val, getr(node), mid,\
    \ r);\n            node->val = f(node->l->val, node->r->val);\n        }\n   \
    \ }\n\n    T get(i64 x, i64 y, SegNode* node = nullptr, i64 l = 0, i64 r = 0){\n\
    \        if(node\t== nullptr){\n            node = root;\n            r = n;\n\
    \        }\n\n        if(r <= x || y <= l)\n            return op_t;\n       \
    \ eval(node, r - l);\n        if(x <= l && r <= y)\n            return node->val;\n\
    \n        i64 val_l = op_t, val_r = op_t;\n        i64 mid = (l + r) >> 1;\n\n\
    \        if(node->l)\n            val_l = get(x, y, node->l, l, mid);\n      \
    \  if(node->r)\n            val_r = get(x, y, node->r, mid, r);\n        return\
    \ f(val_l, val_r);\n    }\n\n};\n\n"
  code: "template<typename T, typename U>\nstruct Segtree{\n\n    struct SegNode{\n\
    \        T val;\n        U lazy;\n\n        SegNode* l;\n        SegNode* r;\n\
    \        SegNode(T val, U lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr){}\n\
    \    };\n\n    i64 n;\n    function<T(T, T)> f;\n    function<T(T, U, int)> g;\n\
    \    function<U(U, U)> h;\n    T op_t;\n    U op_u;\n\n    SegNode* root;\n\n\
    \    Segtree(int n_, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U,\
    \ U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t), op_u(op_u){\n       \
    \ for(n = 1; n < n_; n <<= 1);\n        root = new SegNode(op_t, op_u);\n    }\n\
    \n    SegNode* getl(SegNode* node){\n        return node->l ? node->l : node->l\
    \ = new SegNode(op_t, op_u);\n    }\n\n    SegNode* getr(SegNode* node){\n   \
    \     return node->r ? node->r : node->r = new SegNode(op_t, op_u);\n    }\n\n\
    \    void eval(SegNode* node, i64 len){\n        node->val = g(node->val, node->lazy,\
    \ len);\n        getl(node);\n        node->l->lazy = h(node->l->lazy, node->lazy);\n\
    \        getr(node);\n        node->r->lazy = h(node->r->lazy, node->lazy);\n\
    \        node->lazy = op_u;\n    }\n\n    void update(i64 x, i64 y, U val, SegNode*\
    \ node = nullptr, i64 l = 0, i64 r = 0){\n        if(node == nullptr){\n     \
    \       node = root;\n            r = n;\n        }\n        eval(node, r - l);\n\
    \        if(r <= x || y <= l)\n            return ;\n        if(x <= l && r <=\
    \ y){\n            node->lazy = h(node->lazy, val);\n            eval(node, r\
    \ - l);\n        }else{\n            i64 mid = (l + r) >> 1;\n            update(x,\
    \ y, val, getl(node), l, mid);\n            update(x, y, val, getr(node), mid,\
    \ r);\n            node->val = f(node->l->val, node->r->val);\n        }\n   \
    \ }\n\n    T get(i64 x, i64 y, SegNode* node = nullptr, i64 l = 0, i64 r = 0){\n\
    \        if(node\t== nullptr){\n            node = root;\n            r = n;\n\
    \        }\n\n        if(r <= x || y <= l)\n            return op_t;\n       \
    \ eval(node, r - l);\n        if(x <= l && r <= y)\n            return node->val;\n\
    \n        i64 val_l = op_t, val_r = op_t;\n        i64 mid = (l + r) >> 1;\n\n\
    \        if(node->l)\n            val_l = get(x, y, node->l, l, mid);\n      \
    \  if(node->r)\n            val_r = get(x, y, node->r, mid, r);\n        return\
    \ f(val_l, val_r);\n    }\n\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/dynamiclazysegmenttree.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/rmq_raq_dynamic.test.cpp
documentation_of: lib/classes/dynamiclazysegmenttree.cpp
layout: document
redirect_from:
- /library/lib/classes/dynamiclazysegmenttree.cpp
- /library/lib/classes/dynamiclazysegmenttree.cpp.html
title: lib/classes/dynamiclazysegmenttree.cpp
---
