---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/rmq_raq_persistent.test.cpp
    title: verify/rmq_raq_persistent.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/persistentdynamiclazysegmenttree.cpp\"\ntemplate<typename\
    \ T, typename U>\nstruct Segtree{\n\n    struct SegNode{\n        T val;\n   \
    \     U lazy;\n\n        shared_ptr<SegNode> l;\n        shared_ptr<SegNode> r;\n\
    \        SegNode(T val, U lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr){}\n\
    \    };\n\n    i64 n;\n    shared_ptr<SegNode> nil;\n    function<T(T, T)> f;\n\
    \    function<T(T, U, int)> g;\n    function<U(U, U)> h;\n    T op_t;\n    U op_u;\n\
    \n    shared_ptr<SegNode> root;\n\n    Segtree(int n_, function<T(T, T)> f, function<T(T,\
    \ U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t),\
    \ op_u(op_u){\n        for(n = 1; n < n_; n <<= 1);\n        root = make_shared<SegNode>(op_t,\
    \ op_u);\n    }\n\n    void eval(shared_ptr<SegNode> node, i64 len, bool make\
    \ = true){\n        node->val = g(node->val, node->lazy, len);\n        if(make){\n\
    \            node->l = node->l ? make_shared<SegNode>(*node->l) : make_shared<SegNode>(op_t,\
    \ op_u);\n            node->r = node->r ? make_shared<SegNode>(*node->r) : make_shared<SegNode>(op_t,\
    \ op_u);\n        }\n        node->l->lazy = h(node->l->lazy, node->lazy);\n \
    \       node->r->lazy = h(node->r->lazy, node->lazy);\n        node->lazy = op_u;\n\
    \    }\n\n    // if root -> make new node      -> eval(make child)\n    void update(i64\
    \ x, i64 y, U val, shared_ptr<SegNode> node = nullptr, i64 l = -1, i64 r = -1){\n\
    \        bool root_flag = (node == nullptr);\n        if(root_flag){\n       \
    \     root = make_shared<SegNode>(*root);\n            node = root;\n        }\n\
    \        if(l == -1){\n            l = 0;\n            r = n;\n        }\n   \
    \     eval(node, r - l);\n        if(r <= x || y <= l)\n            return ;\n\
    \        if(x <= l && r <= y){\n            node->lazy = h(node->lazy, val);\n\
    \            eval(node, r - l, false);\n        }else{\n            eval(node,\
    \ r - l);\n            i64 mid = (l + r) >> 1;\n            update(x, y, val,\
    \ node->l, l, mid);\n            update(x, y, val, node->r, mid, r);\n       \
    \     node->val = f(node->l->val, node->r->val);\n        }\n        return ;\n\
    \    }\n\n    T get(i64 x, i64 y, shared_ptr<SegNode> node = nullptr, i64 l =\
    \ -1, i64 r = -1){\n        bool root_flag = (node == nullptr);\n        if(root_flag){\n\
    \            root = make_shared<SegNode>(*root);\n            node = root;\n \
    \       }\n        if(l == -1){\n            l = 0;\n            r = n;\n    \
    \    }\n\n        if(r <= x || y <= l)\n            return op_t;\n        eval(node,\
    \ r - l);\n        if(x <= l && r <= y)\n            return node->val;\n\n   \
    \     i64 val_l = op_t, val_r = op_t;\n        i64 mid = (l + r) >> 1;\n\n   \
    \     if(node->l)\n            val_l = get(x, y, node->l, l, mid);\n        if(node->r)\n\
    \            val_r = get(x, y, node->r, mid, r);\n\n        return f(val_l, val_r);\n\
    \    }\n\n};\n\n\n"
  code: "template<typename T, typename U>\nstruct Segtree{\n\n    struct SegNode{\n\
    \        T val;\n        U lazy;\n\n        shared_ptr<SegNode> l;\n        shared_ptr<SegNode>\
    \ r;\n        SegNode(T val, U lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr){}\n\
    \    };\n\n    i64 n;\n    shared_ptr<SegNode> nil;\n    function<T(T, T)> f;\n\
    \    function<T(T, U, int)> g;\n    function<U(U, U)> h;\n    T op_t;\n    U op_u;\n\
    \n    shared_ptr<SegNode> root;\n\n    Segtree(int n_, function<T(T, T)> f, function<T(T,\
    \ U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t),\
    \ op_u(op_u){\n        for(n = 1; n < n_; n <<= 1);\n        root = make_shared<SegNode>(op_t,\
    \ op_u);\n    }\n\n    void eval(shared_ptr<SegNode> node, i64 len, bool make\
    \ = true){\n        node->val = g(node->val, node->lazy, len);\n        if(make){\n\
    \            node->l = node->l ? make_shared<SegNode>(*node->l) : make_shared<SegNode>(op_t,\
    \ op_u);\n            node->r = node->r ? make_shared<SegNode>(*node->r) : make_shared<SegNode>(op_t,\
    \ op_u);\n        }\n        node->l->lazy = h(node->l->lazy, node->lazy);\n \
    \       node->r->lazy = h(node->r->lazy, node->lazy);\n        node->lazy = op_u;\n\
    \    }\n\n    // if root -> make new node      -> eval(make child)\n    void update(i64\
    \ x, i64 y, U val, shared_ptr<SegNode> node = nullptr, i64 l = -1, i64 r = -1){\n\
    \        bool root_flag = (node == nullptr);\n        if(root_flag){\n       \
    \     root = make_shared<SegNode>(*root);\n            node = root;\n        }\n\
    \        if(l == -1){\n            l = 0;\n            r = n;\n        }\n   \
    \     eval(node, r - l);\n        if(r <= x || y <= l)\n            return ;\n\
    \        if(x <= l && r <= y){\n            node->lazy = h(node->lazy, val);\n\
    \            eval(node, r - l, false);\n        }else{\n            eval(node,\
    \ r - l);\n            i64 mid = (l + r) >> 1;\n            update(x, y, val,\
    \ node->l, l, mid);\n            update(x, y, val, node->r, mid, r);\n       \
    \     node->val = f(node->l->val, node->r->val);\n        }\n        return ;\n\
    \    }\n\n    T get(i64 x, i64 y, shared_ptr<SegNode> node = nullptr, i64 l =\
    \ -1, i64 r = -1){\n        bool root_flag = (node == nullptr);\n        if(root_flag){\n\
    \            root = make_shared<SegNode>(*root);\n            node = root;\n \
    \       }\n        if(l == -1){\n            l = 0;\n            r = n;\n    \
    \    }\n\n        if(r <= x || y <= l)\n            return op_t;\n        eval(node,\
    \ r - l);\n        if(x <= l && r <= y)\n            return node->val;\n\n   \
    \     i64 val_l = op_t, val_r = op_t;\n        i64 mid = (l + r) >> 1;\n\n   \
    \     if(node->l)\n            val_l = get(x, y, node->l, l, mid);\n        if(node->r)\n\
    \            val_r = get(x, y, node->r, mid, r);\n\n        return f(val_l, val_r);\n\
    \    }\n\n};\n\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/persistentdynamiclazysegmenttree.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/rmq_raq_persistent.test.cpp
documentation_of: lib/classes/persistentdynamiclazysegmenttree.cpp
layout: document
redirect_from:
- /library/lib/classes/persistentdynamiclazysegmenttree.cpp
- /library/lib/classes/persistentdynamiclazysegmenttree.cpp.html
title: lib/classes/persistentdynamiclazysegmenttree.cpp
---
