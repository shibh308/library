---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/splay_sset_dict.test.cpp
    title: verify/splay_sset_dict.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/splay_sset_itp.test.cpp
    title: verify/splay_sset_itp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/yfastttrie2_itp.test.cpp
    title: verify/yfastttrie2_itp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/yfastttrie_itp.test.cpp
    title: verify/yfastttrie_itp.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/splaytree_sset.cpp\"\ntemplate <typename T>\n\
    struct SplayTree{\n    struct Node{\n        int size;\n        T val;\n     \
    \   Node* par;\n        Node* c[2];\n        Node(){}\n        Node(T val, Node*\
    \ nil) : val(val), size(1), par(nil){c[0] = nil; c[1] = nil;}\n    };\n    using\
    \ NodePtr = Node*;\n    NodePtr nil;\n\n    SplayTree(){\n        nil = new Node(T(),\
    \ nullptr);\n        nil->size = 0;\n        nil->par = nil->c[0] = nil->c[1]\
    \ = nil;\n    }\n\n    NodePtr make(T val){\n        return new Node(val, nil);\n\
    \    }\n\n    void _update(NodePtr x){\n        if(x == nil)\n            return;\n\
    \        assert(x != x->c[0]);\n        assert(x != x->c[1]);\n        assert(x->c[0]\
    \ == nil || x->c[0] != x->c[1]);\n        x->size = x->c[0]->size + x->c[1]->size\
    \ + 1;\n        assert(x->size > 0);\n    }\n\n    // idx\u5074\u306E\u5B50\u3092\
    \u4E0A\u306B\u6301\u3063\u3066\u3044\u304F\n    void rotate(NodePtr p, bool p_right){\n\
    \        NodePtr x = p->c[p_right];\n        NodePtr q = p->par;\n        // x\u306B\
    \u5143\u3005\u3064\u3044\u3066\u305F\u8FBA\u3092p\u306B\u5F35\u308A\u66FF\u3048\
    \n        assert(p->c[p_right] == x);\n        p->c[p_right] = x->c[p_right ^\
    \ 1];\n        if(x->c[p_right ^ 1] != nil){\n            p->c[p_right]->par =\
    \ p;\n            assert(p != p->c[p_right]);\n        }\n        // xp\u9593\u306E\
    \u8FBA\u306E\u5F35\u308A\u66FF\u3048\n        p->par = x;\n        x->c[p_right\
    \ ^ 1] = p;\n        // pq\u9593\u306E\u8FBA\u306E\u5F35\u308A\u66FF\u3048\n \
    \       x->par = q;\n        if(q != nil){\n            bool q_right = (q->c[1]\
    \ == p);\n            assert(q->c[q_right] == p);\n            q->c[q_right] =\
    \ x;\n        }\n        _update(p), _update(x), _update(q);\n    }\n\n    void\
    \ reroot(NodePtr x){\n        while(x->par != nil){\n            NodePtr p = x->par;\n\
    \            NodePtr q = p->par;\n            bool q_right = (q->c[1] == p);\n\
    \            bool p_right = (p->c[1] == x);\n            if(p->par == nil){\n\
    \                rotate(p, p_right);\n                break;\n            }\n\
    \            // \u540C\u3058\u5411\u304D\u306E\u4E8C\u56DE\u56DE\u8EE2\n     \
    \       if(q_right == p_right){\n                rotate(q, q_right), rotate(p,\
    \ p_right);\n            }\n            else{\n                rotate(p, p_right),\
    \ rotate(q, q_right);\n            }\n        }\n    }\n\n    pair<NodePtr, bool>\
    \ _lower_bound(NodePtr p, T key){\n        if(p == nil)\n            return make_pair(nil,\
    \ false);\n        if(p->val < key){\n            auto res = _lower_bound(p->c[1],\
    \ key);\n            return res.second ? res : make_pair(p, false);\n        }\n\
    \        else{\n            auto res = _lower_bound(p->c[0], key);\n         \
    \   return res.second ? res : make_pair(p, true);\n        }\n    }\n\n    pair<NodePtr,\
    \ bool> lower_bound(NodePtr p, T key){\n        if(p == nil)\n            return\
    \ make_pair(p, false);\n        auto res = _lower_bound(p, key);\n        reroot(res.first);\n\
    \        assert(res.first != nil);\n        return res;\n    }\n\n    NodePtr\
    \ access(NodePtr p, int idx){\n        if(p == nil)\n            return nil;\n\
    \        while(p->c[0]->size != idx){\n            if(p->c[0]->size < idx)\n \
    \               idx -= p->c[0]->size + 1, p = p->c[1];\n            else\n   \
    \             p = p->c[0];\n            if(p == nil)\n                return nil;\n\
    \        }\n        reroot(p);\n        return p;\n    }\n\n    NodePtr next(NodePtr\
    \ p){\n        reroot(p);\n        p = p->c[1];\n        while(p->c[0] != nil)\n\
    \            p = p->c[0];\n        if(p != nil)\n            reroot(p);\n    \
    \    return p;\n    }\n\n    NodePtr prev(NodePtr p){\n        reroot(p);\n  \
    \      p = p->c[0];\n        while(p->c[1] != nil)\n            p = p->c[1];\n\
    \        if(p != nil)\n            reroot(p);\n        return p;\n    }\n\n  \
    \  pair<NodePtr, bool> insert(NodePtr root, T key){\n        if(root == nil)\n\
    \            return make_pair(make(key), true);\n        NodePtr l, r, np;\n \
    \       bool exist;\n        // lower_bound\u306E\u7D50\u679C\u304B\u3089split\u3059\
    \u308B\u6642\u3001lower_bound\u306E\u7D50\u679C\u304Cnil\u3060\u3068\u30D0\u30B0\
    \u308B\u306E\u3067\u6CE8\u610F\n        tie(np, exist) = lower_bound(root, key);\n\
    \        if(exist){\n            if(np->val == key)\n                return make_pair(np,\
    \ false);\n            tie(l, r) = split(np);\n            return make_pair(merge(merge(l,\
    \ make(key)), r), true);\n        }\n        else{\n            return make_pair(merge(np,\
    \ make(key)), true);\n        }\n    }\n\n    pair<NodePtr, bool> erase(NodePtr\
    \ root, T key){\n        NodePtr p = lower_bound(root, key).first;\n        reroot(p);\n\
    \        if(p == nil || p->val != key)\n            return make_pair(p, false);\n\
    \        NodePtr l = p->c[0], r = p->c[1];\n        l->par = r->par = nil;\n \
    \       delete(p);\n        return make_pair(merge(l, r), true);\n    }\n\n  \
    \  // [0, p), [p, n)\u3067splist\n    pair<NodePtr, NodePtr> split(NodePtr p){\n\
    \        if(p == nil)\n            return make_pair(nil, nil);\n        reroot(p);\n\
    \        NodePtr l = p->c[0];\n        l->par = nil;\n        p->c[0] = nil;\n\
    \        _update(p);\n        return make_pair(l, p);\n    }\n\n    NodePtr merge(NodePtr\
    \ p, NodePtr q){\n        reroot(p);\n        reroot(q);\n        if(q == nil)\n\
    \            return p;\n        if(p == nil)\n            return q;\n        while(p->c[1]\
    \ != nil)\n            p = p->c[1];\n        reroot(p);\n        assert(p->c[1]\
    \ == nil);\n        p->c[1] = q;\n        q->par = p;\n        _update(p);\n \
    \       assert(p != nil);\n        return p;\n    }\n\n    void print(NodePtr\
    \ x, int p = 0){\n        if(x == nil)return;\n        if(p == 0)\n          \
    \  cout << \"----print----\" << endl;\n        print(x->c[0], p + 8);\n      \
    \  for(int i = 0; i < p; ++i)\n            cout << \" \";\n        cout << \"\
    val:\" << x->val << \" \";\n        cout << \"size:\" << x->size << endl;\n  \
    \      print(x->c[1], p + 8);\n        if(p == 0)\n            cout << \"-------------\"\
    \ << endl;\n    }\n};\n\n"
  code: "template <typename T>\nstruct SplayTree{\n    struct Node{\n        int size;\n\
    \        T val;\n        Node* par;\n        Node* c[2];\n        Node(){}\n \
    \       Node(T val, Node* nil) : val(val), size(1), par(nil){c[0] = nil; c[1]\
    \ = nil;}\n    };\n    using NodePtr = Node*;\n    NodePtr nil;\n\n    SplayTree(){\n\
    \        nil = new Node(T(), nullptr);\n        nil->size = 0;\n        nil->par\
    \ = nil->c[0] = nil->c[1] = nil;\n    }\n\n    NodePtr make(T val){\n        return\
    \ new Node(val, nil);\n    }\n\n    void _update(NodePtr x){\n        if(x ==\
    \ nil)\n            return;\n        assert(x != x->c[0]);\n        assert(x !=\
    \ x->c[1]);\n        assert(x->c[0] == nil || x->c[0] != x->c[1]);\n        x->size\
    \ = x->c[0]->size + x->c[1]->size + 1;\n        assert(x->size > 0);\n    }\n\n\
    \    // idx\u5074\u306E\u5B50\u3092\u4E0A\u306B\u6301\u3063\u3066\u3044\u304F\n\
    \    void rotate(NodePtr p, bool p_right){\n        NodePtr x = p->c[p_right];\n\
    \        NodePtr q = p->par;\n        // x\u306B\u5143\u3005\u3064\u3044\u3066\
    \u305F\u8FBA\u3092p\u306B\u5F35\u308A\u66FF\u3048\n        assert(p->c[p_right]\
    \ == x);\n        p->c[p_right] = x->c[p_right ^ 1];\n        if(x->c[p_right\
    \ ^ 1] != nil){\n            p->c[p_right]->par = p;\n            assert(p !=\
    \ p->c[p_right]);\n        }\n        // xp\u9593\u306E\u8FBA\u306E\u5F35\u308A\
    \u66FF\u3048\n        p->par = x;\n        x->c[p_right ^ 1] = p;\n        //\
    \ pq\u9593\u306E\u8FBA\u306E\u5F35\u308A\u66FF\u3048\n        x->par = q;\n  \
    \      if(q != nil){\n            bool q_right = (q->c[1] == p);\n           \
    \ assert(q->c[q_right] == p);\n            q->c[q_right] = x;\n        }\n   \
    \     _update(p), _update(x), _update(q);\n    }\n\n    void reroot(NodePtr x){\n\
    \        while(x->par != nil){\n            NodePtr p = x->par;\n            NodePtr\
    \ q = p->par;\n            bool q_right = (q->c[1] == p);\n            bool p_right\
    \ = (p->c[1] == x);\n            if(p->par == nil){\n                rotate(p,\
    \ p_right);\n                break;\n            }\n            // \u540C\u3058\
    \u5411\u304D\u306E\u4E8C\u56DE\u56DE\u8EE2\n            if(q_right == p_right){\n\
    \                rotate(q, q_right), rotate(p, p_right);\n            }\n    \
    \        else{\n                rotate(p, p_right), rotate(q, q_right);\n    \
    \        }\n        }\n    }\n\n    pair<NodePtr, bool> _lower_bound(NodePtr p,\
    \ T key){\n        if(p == nil)\n            return make_pair(nil, false);\n \
    \       if(p->val < key){\n            auto res = _lower_bound(p->c[1], key);\n\
    \            return res.second ? res : make_pair(p, false);\n        }\n     \
    \   else{\n            auto res = _lower_bound(p->c[0], key);\n            return\
    \ res.second ? res : make_pair(p, true);\n        }\n    }\n\n    pair<NodePtr,\
    \ bool> lower_bound(NodePtr p, T key){\n        if(p == nil)\n            return\
    \ make_pair(p, false);\n        auto res = _lower_bound(p, key);\n        reroot(res.first);\n\
    \        assert(res.first != nil);\n        return res;\n    }\n\n    NodePtr\
    \ access(NodePtr p, int idx){\n        if(p == nil)\n            return nil;\n\
    \        while(p->c[0]->size != idx){\n            if(p->c[0]->size < idx)\n \
    \               idx -= p->c[0]->size + 1, p = p->c[1];\n            else\n   \
    \             p = p->c[0];\n            if(p == nil)\n                return nil;\n\
    \        }\n        reroot(p);\n        return p;\n    }\n\n    NodePtr next(NodePtr\
    \ p){\n        reroot(p);\n        p = p->c[1];\n        while(p->c[0] != nil)\n\
    \            p = p->c[0];\n        if(p != nil)\n            reroot(p);\n    \
    \    return p;\n    }\n\n    NodePtr prev(NodePtr p){\n        reroot(p);\n  \
    \      p = p->c[0];\n        while(p->c[1] != nil)\n            p = p->c[1];\n\
    \        if(p != nil)\n            reroot(p);\n        return p;\n    }\n\n  \
    \  pair<NodePtr, bool> insert(NodePtr root, T key){\n        if(root == nil)\n\
    \            return make_pair(make(key), true);\n        NodePtr l, r, np;\n \
    \       bool exist;\n        // lower_bound\u306E\u7D50\u679C\u304B\u3089split\u3059\
    \u308B\u6642\u3001lower_bound\u306E\u7D50\u679C\u304Cnil\u3060\u3068\u30D0\u30B0\
    \u308B\u306E\u3067\u6CE8\u610F\n        tie(np, exist) = lower_bound(root, key);\n\
    \        if(exist){\n            if(np->val == key)\n                return make_pair(np,\
    \ false);\n            tie(l, r) = split(np);\n            return make_pair(merge(merge(l,\
    \ make(key)), r), true);\n        }\n        else{\n            return make_pair(merge(np,\
    \ make(key)), true);\n        }\n    }\n\n    pair<NodePtr, bool> erase(NodePtr\
    \ root, T key){\n        NodePtr p = lower_bound(root, key).first;\n        reroot(p);\n\
    \        if(p == nil || p->val != key)\n            return make_pair(p, false);\n\
    \        NodePtr l = p->c[0], r = p->c[1];\n        l->par = r->par = nil;\n \
    \       delete(p);\n        return make_pair(merge(l, r), true);\n    }\n\n  \
    \  // [0, p), [p, n)\u3067splist\n    pair<NodePtr, NodePtr> split(NodePtr p){\n\
    \        if(p == nil)\n            return make_pair(nil, nil);\n        reroot(p);\n\
    \        NodePtr l = p->c[0];\n        l->par = nil;\n        p->c[0] = nil;\n\
    \        _update(p);\n        return make_pair(l, p);\n    }\n\n    NodePtr merge(NodePtr\
    \ p, NodePtr q){\n        reroot(p);\n        reroot(q);\n        if(q == nil)\n\
    \            return p;\n        if(p == nil)\n            return q;\n        while(p->c[1]\
    \ != nil)\n            p = p->c[1];\n        reroot(p);\n        assert(p->c[1]\
    \ == nil);\n        p->c[1] = q;\n        q->par = p;\n        _update(p);\n \
    \       assert(p != nil);\n        return p;\n    }\n\n    void print(NodePtr\
    \ x, int p = 0){\n        if(x == nil)return;\n        if(p == 0)\n          \
    \  cout << \"----print----\" << endl;\n        print(x->c[0], p + 8);\n      \
    \  for(int i = 0; i < p; ++i)\n            cout << \" \";\n        cout << \"\
    val:\" << x->val << \" \";\n        cout << \"size:\" << x->size << endl;\n  \
    \      print(x->c[1], p + 8);\n        if(p == 0)\n            cout << \"-------------\"\
    \ << endl;\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/splaytree_sset.cpp
  requiredBy: []
  timestamp: '2020-04-10 23:19:58+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yfastttrie_itp.test.cpp
  - verify/yfastttrie2_itp.test.cpp
  - verify/splay_sset_dict.test.cpp
  - verify/splay_sset_itp.test.cpp
documentation_of: lib/classes/splaytree_sset.cpp
layout: document
redirect_from:
- /library/lib/classes/splaytree_sset.cpp
- /library/lib/classes/splaytree_sset.cpp.html
title: lib/classes/splaytree_sset.cpp
---
