---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/yfastttrie_itp.test.cpp
    title: verify/yfastttrie_itp.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/yfasttrie.cpp\"\n// \u4E71\u629E\u3067\u633F\
    \u5165\u5148\u3092\u6C7A\u3081\u308By-fast trie\ntemplate <typename T, int W =\
    \ 31, T HASHMAP_NULL = (1LL << W) - 1, T HASHMAP_DEL = (1LL << W) - 2>\nstruct\
    \ YFastTrie{\n\n    static uint32_t rnd(){\n        static uint32_t x = 123456789,\
    \ y = 362436069, z = 521288629, w = 0; // time(0);\n        uint32_t t = x ^ (x\
    \ << 11);\n        x = y, y = z, z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t\
    \ >> 8));\n        return w;\n    }\n\n    using SplayNode = typename SplayTree<T>::NodePtr;\n\
    \    int n;\n    XFastTrie_yft<T, W, HASHMAP_NULL, HASHMAP_DEL> xft;\n    SplayTree<T>\
    \ splay;\n\n    YFastTrie() : n(1), xft(), splay(){\n        SplayNode node =\
    \ splay.make((1LL << W) - 1);\n        xft.insert(node);\n    }\n\n    SplayNode\
    \ lower_bound(T key){\n        auto xft_ptr = xft.lower_bound(key);\n        assert(xft_ptr\
    \ != xft.back);\n        return xft_ptr->node = splay.lower_bound(xft_ptr->node,\
    \ key).first;\n    }\n\n    bool insert(T key){\n        auto xft_ptr = xft.lower_bound(key);\n\
    \         pair<SplayNode , bool> res;\n        if(xft_ptr->val == key)\n     \
    \       return false;\n        if(rnd() % W == 0){\n            res = splay.lower_bound(xft_ptr->node,\
    \ key);\n            assert(res.second);\n            SplayNode l;\n         \
    \   tie(l, xft_ptr->node) = splay.split(res.first);\n            assert(xft_ptr->node\
    \ != splay.nil);\n            res = splay.insert(l, key);\n            n += res.second;\n\
    \            assert(res.first != splay.nil);\n            xft.insert(splay.access(res.first,\
    \ res.first->size - 1));\n        }\n        else{\n            res = splay.insert(xft_ptr->node,\
    \ key);\n            n += res.second;\n            xft_ptr->node = res.first;\n\
    \        }\n        return res.second;\n    }\n\n    bool erase(T key){\n    \
    \    pair<SplayNode, bool> res;\n        auto xft_ptr = xft.lower_bound(key);\n\
    \        if(xft_ptr->val == key){\n            auto r = xft_ptr->c[1];\n     \
    \       r->node = splay.merge(xft_ptr->node, r->node);\n            res = splay.erase(r->node,\
    \ key);\n            r->node = res.first;\n            if(res.second){\n     \
    \           xft_ptr->node = nullptr;\n                xft.erase(xft_ptr->val);\n\
    \            }\n        }\n        else{\n            res = splay.erase(xft_ptr->node,\
    \ key);\n            xft_ptr->node = res.first;\n        }\n        n -= res.second;\n\
    \        return res.second;\n    }\n};\n"
  code: "// \u4E71\u629E\u3067\u633F\u5165\u5148\u3092\u6C7A\u3081\u308By-fast trie\n\
    template <typename T, int W = 31, T HASHMAP_NULL = (1LL << W) - 1, T HASHMAP_DEL\
    \ = (1LL << W) - 2>\nstruct YFastTrie{\n\n    static uint32_t rnd(){\n       \
    \ static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 0; // time(0);\n\
    \        uint32_t t = x ^ (x << 11);\n        x = y, y = z, z = w;\n        w\
    \ = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n    }\n\n    using SplayNode\
    \ = typename SplayTree<T>::NodePtr;\n    int n;\n    XFastTrie_yft<T, W, HASHMAP_NULL,\
    \ HASHMAP_DEL> xft;\n    SplayTree<T> splay;\n\n    YFastTrie() : n(1), xft(),\
    \ splay(){\n        SplayNode node = splay.make((1LL << W) - 1);\n        xft.insert(node);\n\
    \    }\n\n    SplayNode lower_bound(T key){\n        auto xft_ptr = xft.lower_bound(key);\n\
    \        assert(xft_ptr != xft.back);\n        return xft_ptr->node = splay.lower_bound(xft_ptr->node,\
    \ key).first;\n    }\n\n    bool insert(T key){\n        auto xft_ptr = xft.lower_bound(key);\n\
    \         pair<SplayNode , bool> res;\n        if(xft_ptr->val == key)\n     \
    \       return false;\n        if(rnd() % W == 0){\n            res = splay.lower_bound(xft_ptr->node,\
    \ key);\n            assert(res.second);\n            SplayNode l;\n         \
    \   tie(l, xft_ptr->node) = splay.split(res.first);\n            assert(xft_ptr->node\
    \ != splay.nil);\n            res = splay.insert(l, key);\n            n += res.second;\n\
    \            assert(res.first != splay.nil);\n            xft.insert(splay.access(res.first,\
    \ res.first->size - 1));\n        }\n        else{\n            res = splay.insert(xft_ptr->node,\
    \ key);\n            n += res.second;\n            xft_ptr->node = res.first;\n\
    \        }\n        return res.second;\n    }\n\n    bool erase(T key){\n    \
    \    pair<SplayNode, bool> res;\n        auto xft_ptr = xft.lower_bound(key);\n\
    \        if(xft_ptr->val == key){\n            auto r = xft_ptr->c[1];\n     \
    \       r->node = splay.merge(xft_ptr->node, r->node);\n            res = splay.erase(r->node,\
    \ key);\n            r->node = res.first;\n            if(res.second){\n     \
    \           xft_ptr->node = nullptr;\n                xft.erase(xft_ptr->val);\n\
    \            }\n        }\n        else{\n            res = splay.erase(xft_ptr->node,\
    \ key);\n            xft_ptr->node = res.first;\n        }\n        n -= res.second;\n\
    \        return res.second;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/yfasttrie.cpp
  requiredBy: []
  timestamp: '2020-04-11 13:43:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yfastttrie_itp.test.cpp
documentation_of: lib/classes/yfasttrie.cpp
layout: document
redirect_from:
- /library/lib/classes/yfasttrie.cpp
- /library/lib/classes/yfasttrie.cpp.html
title: lib/classes/yfasttrie.cpp
---
