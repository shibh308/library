---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/yfastttrie2_itp.test.cpp
    title: verify/yfastttrie2_itp.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/yfasttrie2.cpp\"\n// \u30B5\u30A4\u30BA\u3092\
    \u4FDD\u3064\u3088\u3046\u306Bsplit/merge\u3092\u3059\u308By-fast trie\ntemplate\
    \ <typename T, int W = 31, T HASHMAP_NULL = (1LL << W) - 1, T HASHMAP_DEL = (1LL\
    \ << W) - 2>\nstruct YFastTrie2{\n\n    using SplayNode = typename SplayTree<T>::NodePtr;\n\
    \    int n;\n    XFastTrie_yft<T, W, HASHMAP_NULL, HASHMAP_DEL> xft;\n    SplayTree<T>\
    \ splay;\n\n    YFastTrie2() : n(1), xft(), splay(){\n        SplayNode node =\
    \ splay.make((1LL << W) - 1);\n        xft.insert(node);\n    }\n\n    SplayNode\
    \ lower_bound(T key){\n        auto xft_ptr = xft.lower_bound(key);\n        assert(xft_ptr\
    \ != xft.back);\n        auto res = splay.lower_bound(xft_ptr->node, key);\n \
    \       xft_ptr->node = res.first;\n        if(!res.second){\n            xft_ptr\
    \ = xft_ptr->c[1];\n            xft_ptr->node = splay.access(xft_ptr->node, 0);\n\
    \        }\n        return xft_ptr->node;\n    }\n\n    bool insert(T key){\n\
    \        auto xft_ptr = xft.lower_bound(key);\n        auto res = splay.insert(xft_ptr->node,\
    \ key);\n        xft_ptr->node = res.first;\n        n += res.second;\n      \
    \  split(xft_ptr);\n        return res.second;\n    }\n\n    bool erase(T key){\n\
    \        auto xft_ptr = xft.lower_bound(key);\n        auto res = splay.erase(xft_ptr->node,\
    \ key);\n        assert(res.first != splay.nil);\n        xft_ptr->node = res.first;\n\
    \        n -= res.second;\n        merge(xft_ptr);\n        return res.second;\n\
    \    }\n\n    void split(typename XFastTrie_yft<T, W>::Node* xft_node){\n    \
    \    if(xft_node->node->size <= (W << 1))\n            return;\n        SplayNode\
    \ l, r;\n        tie(l, r) = splay.split(splay.access(xft_node->node, xft_node->node->size\
    \ >> 1));\n        xft_node->node = r;\n        l = splay.access(l, l->size -\
    \ 1);\n        xft.insert(l);\n    }\n\n    void merge(typename XFastTrie_yft<T,\
    \ W>::Node* xft_ptr){\n        if(xft_ptr->node->size >= (W >> 2))\n         \
    \   return;\n        if(xft_ptr->c[0] != xft.front)\n            merge(xft_ptr->c[0],\
    \ xft_ptr);\n        else if(xft_ptr->c[1] != xft.back)\n            merge(xft_ptr,\
    \ xft_ptr->c[1]);\n    }\n\n    void merge(typename XFastTrie_yft<T, W>::Node*\
    \ xft_l, typename XFastTrie_yft<T, W>::Node* xft_r){\n        xft_r->node = splay.merge(xft_l->node,\
    \ xft_r->node);\n        xft_l->node = nullptr;\n        xft.erase(xft_l->val);\n\
    \        split(xft_r);\n    }\n};\n"
  code: "// \u30B5\u30A4\u30BA\u3092\u4FDD\u3064\u3088\u3046\u306Bsplit/merge\u3092\
    \u3059\u308By-fast trie\ntemplate <typename T, int W = 31, T HASHMAP_NULL = (1LL\
    \ << W) - 1, T HASHMAP_DEL = (1LL << W) - 2>\nstruct YFastTrie2{\n\n    using\
    \ SplayNode = typename SplayTree<T>::NodePtr;\n    int n;\n    XFastTrie_yft<T,\
    \ W, HASHMAP_NULL, HASHMAP_DEL> xft;\n    SplayTree<T> splay;\n\n    YFastTrie2()\
    \ : n(1), xft(), splay(){\n        SplayNode node = splay.make((1LL << W) - 1);\n\
    \        xft.insert(node);\n    }\n\n    SplayNode lower_bound(T key){\n     \
    \   auto xft_ptr = xft.lower_bound(key);\n        assert(xft_ptr != xft.back);\n\
    \        auto res = splay.lower_bound(xft_ptr->node, key);\n        xft_ptr->node\
    \ = res.first;\n        if(!res.second){\n            xft_ptr = xft_ptr->c[1];\n\
    \            xft_ptr->node = splay.access(xft_ptr->node, 0);\n        }\n    \
    \    return xft_ptr->node;\n    }\n\n    bool insert(T key){\n        auto xft_ptr\
    \ = xft.lower_bound(key);\n        auto res = splay.insert(xft_ptr->node, key);\n\
    \        xft_ptr->node = res.first;\n        n += res.second;\n        split(xft_ptr);\n\
    \        return res.second;\n    }\n\n    bool erase(T key){\n        auto xft_ptr\
    \ = xft.lower_bound(key);\n        auto res = splay.erase(xft_ptr->node, key);\n\
    \        assert(res.first != splay.nil);\n        xft_ptr->node = res.first;\n\
    \        n -= res.second;\n        merge(xft_ptr);\n        return res.second;\n\
    \    }\n\n    void split(typename XFastTrie_yft<T, W>::Node* xft_node){\n    \
    \    if(xft_node->node->size <= (W << 1))\n            return;\n        SplayNode\
    \ l, r;\n        tie(l, r) = splay.split(splay.access(xft_node->node, xft_node->node->size\
    \ >> 1));\n        xft_node->node = r;\n        l = splay.access(l, l->size -\
    \ 1);\n        xft.insert(l);\n    }\n\n    void merge(typename XFastTrie_yft<T,\
    \ W>::Node* xft_ptr){\n        if(xft_ptr->node->size >= (W >> 2))\n         \
    \   return;\n        if(xft_ptr->c[0] != xft.front)\n            merge(xft_ptr->c[0],\
    \ xft_ptr);\n        else if(xft_ptr->c[1] != xft.back)\n            merge(xft_ptr,\
    \ xft_ptr->c[1]);\n    }\n\n    void merge(typename XFastTrie_yft<T, W>::Node*\
    \ xft_l, typename XFastTrie_yft<T, W>::Node* xft_r){\n        xft_r->node = splay.merge(xft_l->node,\
    \ xft_r->node);\n        xft_l->node = nullptr;\n        xft.erase(xft_l->val);\n\
    \        split(xft_r);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/yfasttrie2.cpp
  requiredBy: []
  timestamp: '2020-04-10 22:13:43+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yfastttrie2_itp.test.cpp
documentation_of: lib/classes/yfasttrie2.cpp
layout: document
redirect_from:
- /library/lib/classes/yfasttrie2.cpp
- /library/lib/classes/yfasttrie2.cpp.html
title: lib/classes/yfasttrie2.cpp
---
