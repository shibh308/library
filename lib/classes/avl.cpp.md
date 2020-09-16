---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/rsq_avl_erase.test.cpp
    title: verify/rsq_avl_erase.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/rsq_avl.test.cpp
    title: verify/rsq_avl.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/avl.cpp\"\ntemplate <typename T>\nstruct AVL{\n\
    \    template <typename U>\n    struct Node{\n        int size, height;\n    \
    \    U val, sum;\n        Node(U val, Node<U>* nil) : val(val), sum(val), size(1),\
    \ height(1){c[0] = nil; c[1] = nil;}\n        Node<U>* c[2];\n    };\n\n    using\
    \ NodePtr = Node<T>*;\n    function<T(T, T)> f = [](auto x, auto y){return x +\
    \ y;};\n    T op;\n    NodePtr nil;\n\n    AVL(function<T(T, T)> f, T op) : f(f),\
    \ op(op){\n        nil = new Node<T>(op, nullptr);\n        nil->size = 0;\n \
    \       nil->height = 0;\n        nil->c[0] = nil;\n        nil->c[1] = nil;\n\
    \    }\n\n    template <bool inv>\n    int balance_factor(NodePtr x){return (x->c[0]->height\
    \ - x->c[1]->height) * (inv ? -1 : 1);}\n    void _update(NodePtr x){\n      \
    \  if(x == nil)\n            return;\n        x->size = x->c[0]->size + x->c[1]->size\
    \ + 1;\n        x->height = max(x->c[0]->height, x->c[1]->height) + 1;\n     \
    \   x->sum = f(f(x->c[0]->sum, x->val), x->c[1]->sum);\n    }\n    template <bool\
    \ is_right>\n    NodePtr rotate(NodePtr x){\n        NodePtr new_root = x->c[1\
    \ ^ is_right];\n        x->c[1 ^ is_right] = new_root->c[0 ^ is_right];\n    \
    \    new_root->c[0 ^ is_right] = x;\n        _update(x);\n        _update(new_root);\n\
    \        return new_root;\n    }\n    template <bool inv>\n    NodePtr _balance(NodePtr\
    \ x){\n        if(balance_factor<inv>(x) == 2){\n            if(balance_factor<inv>(x->c[0\
    \ ^ inv]) < 0)\n                x->c[0 ^ inv] = rotate<inv>(x->c[0 ^ inv]);\n\
    \            x = rotate<1 ^ inv>(x);\n        }\n        return x;\n    }\n  \
    \  NodePtr balance(NodePtr x){\n        x = _balance<false>(x);\n        x = _balance<true>(x);\n\
    \        _update(x);\n        return x;\n    }\n    NodePtr insert(NodePtr x,\
    \ int idx, T val){\n        if(x == nil)\n            return new Node<T>(val,\
    \ nil);\n        int left_size = x->c[0]->size;\n        if(idx <= left_size)\n\
    \            x->c[0] = insert(x->c[0], idx, val);\n        else\n            x->c[1]\
    \ = insert(x->c[1], idx - left_size - 1, val);\n        x = balance(x);\n    \
    \    return x;\n    }\n\n    // \u5B50\u304C\u7247\u65B9\u3057\u304B\u306A\u3044\
    \u6642\u306B\u30CE\u30FC\u30C9\u3092\u524A\u9664\u3059\u308B\n    NodePtr _erase_top(NodePtr\
    \ x, bool del){\n        for(int i = 0; i < 2; ++i){\n            if(x->c[i] ==\
    \ nil){\n                NodePtr new_node = x->c[i ^ 1];\n                if(del)\n\
    \                    delete(x);\n                return new_node;\n          \
    \  }\n        }\n    }\n    // \u6700\u5C0F\u306E\u8981\u7D20\u3092dst\u306B\u30B3\
    \u30D4\u30FC\u3057\u3066\u304B\u3089\u524A\u9664\u3059\u308B\n    NodePtr _copy_erase(NodePtr\
    \ x, NodePtr dst, bool del){\n        if(x->c[0] == nil){\n            dst->val\
    \ = x->val;\n            return _erase_top(x, del);\n        }\n        x->c[0]\
    \ = _copy_erase(x->c[0], dst, del);\n        x = balance(x);\n        return x;\n\
    \    }\n    NodePtr erase(NodePtr x, int idx, bool del = true){\n        int left_size\
    \ = x->c[0]->size;\n        if(idx < left_size)\n            x->c[0] = erase(x->c[0],\
    \ idx, del);\n        else if(left_size < idx)\n            x->c[1] = erase(x->c[1],\
    \ idx - left_size - 1, del);\n        else{\n            if(x->c[0] == nil ||\
    \ x->c[1] == nil)\n                return _erase_top(x, del);\n            x->c[1]\
    \ = _copy_erase(x->c[1], x, del);\n        }\n        x = balance(x);\n      \
    \  return x;\n    }\n    NodePtr getNode(NodePtr x, int idx){\n        int left_size\
    \ = x->c[0]->size;\n        if(idx < left_size)\n            return getNode(x->c[0],\
    \ idx);\n        else if(left_size < idx)\n            return getNode(x->c[1],\
    \ idx - left_size - 1);\n        else\n            return x;\n    }\n    T get(NodePtr\
    \ x, int l, int r){\n        if(l <= 0 && x->size <= r)\n            return x->sum;\n\
    \        int left_size = x->c[0]->size;\n        T res = op;\n        if(l <=\
    \ left_size && left_size < r)\n            res = x->val;\n        if(l < left_size)\n\
    \            res = f(get(x->c[0], l, r), res);\n        if(left_size + 1 < r)\n\
    \            res = f(res, get(x->c[1], l - left_size - 1, r - left_size - 1));\n\
    \        return res;\n    }\n    NodePtr update(NodePtr x, int idx, T val, function<T(T,\
    \ T)> g = [](auto x, auto y){return x + y;}){\n        int left_size = x->c[0]->size;\n\
    \        if(idx < left_size)\n            x->c[0] = update(x->c[0], idx, val,\
    \ g);\n        else if(left_size < idx)\n            x->c[1] = update(x->c[1],\
    \ idx - left_size - 1, val, g);\n        else\n            x->val = g(x->val,\
    \ val);\n        _update(x);\n\n        return x;\n    }\n    NodePtr set(NodePtr\
    \ x, int idx, T val){\n        int left_size = x->c[0]->size;\n        if(idx\
    \ < left_size)\n            x->c[0] = set(x->c[0], idx, val);\n        else if(left_size\
    \ < idx)\n            x->c[1] = set(x->c[1], idx - left_size - 1, val);\n    \
    \    else\n            x->val = val;\n        _update(x);\n        return x;\n\
    \    }\n\n    void print(NodePtr x, int p = 0){\n        if(x == nil)return;\n\
    \        if(p == 0)\n            cout << \"----print----\" << endl;\n        print(x->c[0],\
    \ p + 12);\n        for(int i = 0; i < p; ++i)\n            cout << \" \";\n \
    \       cout << \"val:\" << x->val << \" \";\n        cout << \"sum:\" << x->sum\
    \ << \" \";\n        cout << \"size:\" << x->size << \" \";\n        cout << \"\
    height:\" << x->height << endl;\n        print(x->c[1], p + 12);\n        if(p\
    \ == 0)\n            cout << \"-------------\" << endl;\n    }\n};\n\n"
  code: "template <typename T>\nstruct AVL{\n    template <typename U>\n    struct\
    \ Node{\n        int size, height;\n        U val, sum;\n        Node(U val, Node<U>*\
    \ nil) : val(val), sum(val), size(1), height(1){c[0] = nil; c[1] = nil;}\n   \
    \     Node<U>* c[2];\n    };\n\n    using NodePtr = Node<T>*;\n    function<T(T,\
    \ T)> f = [](auto x, auto y){return x + y;};\n    T op;\n    NodePtr nil;\n\n\
    \    AVL(function<T(T, T)> f, T op) : f(f), op(op){\n        nil = new Node<T>(op,\
    \ nullptr);\n        nil->size = 0;\n        nil->height = 0;\n        nil->c[0]\
    \ = nil;\n        nil->c[1] = nil;\n    }\n\n    template <bool inv>\n    int\
    \ balance_factor(NodePtr x){return (x->c[0]->height - x->c[1]->height) * (inv\
    \ ? -1 : 1);}\n    void _update(NodePtr x){\n        if(x == nil)\n          \
    \  return;\n        x->size = x->c[0]->size + x->c[1]->size + 1;\n        x->height\
    \ = max(x->c[0]->height, x->c[1]->height) + 1;\n        x->sum = f(f(x->c[0]->sum,\
    \ x->val), x->c[1]->sum);\n    }\n    template <bool is_right>\n    NodePtr rotate(NodePtr\
    \ x){\n        NodePtr new_root = x->c[1 ^ is_right];\n        x->c[1 ^ is_right]\
    \ = new_root->c[0 ^ is_right];\n        new_root->c[0 ^ is_right] = x;\n     \
    \   _update(x);\n        _update(new_root);\n        return new_root;\n    }\n\
    \    template <bool inv>\n    NodePtr _balance(NodePtr x){\n        if(balance_factor<inv>(x)\
    \ == 2){\n            if(balance_factor<inv>(x->c[0 ^ inv]) < 0)\n           \
    \     x->c[0 ^ inv] = rotate<inv>(x->c[0 ^ inv]);\n            x = rotate<1 ^\
    \ inv>(x);\n        }\n        return x;\n    }\n    NodePtr balance(NodePtr x){\n\
    \        x = _balance<false>(x);\n        x = _balance<true>(x);\n        _update(x);\n\
    \        return x;\n    }\n    NodePtr insert(NodePtr x, int idx, T val){\n  \
    \      if(x == nil)\n            return new Node<T>(val, nil);\n        int left_size\
    \ = x->c[0]->size;\n        if(idx <= left_size)\n            x->c[0] = insert(x->c[0],\
    \ idx, val);\n        else\n            x->c[1] = insert(x->c[1], idx - left_size\
    \ - 1, val);\n        x = balance(x);\n        return x;\n    }\n\n    // \u5B50\
    \u304C\u7247\u65B9\u3057\u304B\u306A\u3044\u6642\u306B\u30CE\u30FC\u30C9\u3092\
    \u524A\u9664\u3059\u308B\n    NodePtr _erase_top(NodePtr x, bool del){\n     \
    \   for(int i = 0; i < 2; ++i){\n            if(x->c[i] == nil){\n           \
    \     NodePtr new_node = x->c[i ^ 1];\n                if(del)\n             \
    \       delete(x);\n                return new_node;\n            }\n        }\n\
    \    }\n    // \u6700\u5C0F\u306E\u8981\u7D20\u3092dst\u306B\u30B3\u30D4\u30FC\
    \u3057\u3066\u304B\u3089\u524A\u9664\u3059\u308B\n    NodePtr _copy_erase(NodePtr\
    \ x, NodePtr dst, bool del){\n        if(x->c[0] == nil){\n            dst->val\
    \ = x->val;\n            return _erase_top(x, del);\n        }\n        x->c[0]\
    \ = _copy_erase(x->c[0], dst, del);\n        x = balance(x);\n        return x;\n\
    \    }\n    NodePtr erase(NodePtr x, int idx, bool del = true){\n        int left_size\
    \ = x->c[0]->size;\n        if(idx < left_size)\n            x->c[0] = erase(x->c[0],\
    \ idx, del);\n        else if(left_size < idx)\n            x->c[1] = erase(x->c[1],\
    \ idx - left_size - 1, del);\n        else{\n            if(x->c[0] == nil ||\
    \ x->c[1] == nil)\n                return _erase_top(x, del);\n            x->c[1]\
    \ = _copy_erase(x->c[1], x, del);\n        }\n        x = balance(x);\n      \
    \  return x;\n    }\n    NodePtr getNode(NodePtr x, int idx){\n        int left_size\
    \ = x->c[0]->size;\n        if(idx < left_size)\n            return getNode(x->c[0],\
    \ idx);\n        else if(left_size < idx)\n            return getNode(x->c[1],\
    \ idx - left_size - 1);\n        else\n            return x;\n    }\n    T get(NodePtr\
    \ x, int l, int r){\n        if(l <= 0 && x->size <= r)\n            return x->sum;\n\
    \        int left_size = x->c[0]->size;\n        T res = op;\n        if(l <=\
    \ left_size && left_size < r)\n            res = x->val;\n        if(l < left_size)\n\
    \            res = f(get(x->c[0], l, r), res);\n        if(left_size + 1 < r)\n\
    \            res = f(res, get(x->c[1], l - left_size - 1, r - left_size - 1));\n\
    \        return res;\n    }\n    NodePtr update(NodePtr x, int idx, T val, function<T(T,\
    \ T)> g = [](auto x, auto y){return x + y;}){\n        int left_size = x->c[0]->size;\n\
    \        if(idx < left_size)\n            x->c[0] = update(x->c[0], idx, val,\
    \ g);\n        else if(left_size < idx)\n            x->c[1] = update(x->c[1],\
    \ idx - left_size - 1, val, g);\n        else\n            x->val = g(x->val,\
    \ val);\n        _update(x);\n\n        return x;\n    }\n    NodePtr set(NodePtr\
    \ x, int idx, T val){\n        int left_size = x->c[0]->size;\n        if(idx\
    \ < left_size)\n            x->c[0] = set(x->c[0], idx, val);\n        else if(left_size\
    \ < idx)\n            x->c[1] = set(x->c[1], idx - left_size - 1, val);\n    \
    \    else\n            x->val = val;\n        _update(x);\n        return x;\n\
    \    }\n\n    void print(NodePtr x, int p = 0){\n        if(x == nil)return;\n\
    \        if(p == 0)\n            cout << \"----print----\" << endl;\n        print(x->c[0],\
    \ p + 12);\n        for(int i = 0; i < p; ++i)\n            cout << \" \";\n \
    \       cout << \"val:\" << x->val << \" \";\n        cout << \"sum:\" << x->sum\
    \ << \" \";\n        cout << \"size:\" << x->size << \" \";\n        cout << \"\
    height:\" << x->height << endl;\n        print(x->c[1], p + 12);\n        if(p\
    \ == 0)\n            cout << \"-------------\" << endl;\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/avl.cpp
  requiredBy: []
  timestamp: '2020-02-26 07:59:33+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/rsq_avl_erase.test.cpp
  - verify/rsq_avl.test.cpp
documentation_of: lib/classes/avl.cpp
layout: document
redirect_from:
- /library/lib/classes/avl.cpp
- /library/lib/classes/avl.cpp.html
title: lib/classes/avl.cpp
---
