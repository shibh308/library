---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/veb_set.test.cpp
    title: verify/veb_set.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/vanemdeboastree.cpp\"\ntemplate <uint32_t W,\
    \ uint32_t NULL_FLAG = ~0u>\nstruct VanEmdeBoasTree{\n\n    // \u30B5\u30A4\u30BA\
    2^(2^U)\u306E\u30CE\u30FC\u30C9\n    // U=0\u304B\u3089\u3067\u30B5\u30A4\u30BA\
    \u304C2, 4, 16, 256, 65536, \u3068\u306A\u308B\n    struct Node{\n        uint32_t\
    \ u, ma, mi;\n        Node* aux;\n        vector<Node*> c;\n        Node(int u,\
    \ int n) : u(u), mi(NULL_FLAG), ma(0){\n            if(u){\n                while(n){\n\
    \                    int d = min(1 << (1 << (u - 1)), n);\n                  \
    \  Node *node = new Node(u - 1, d);\n                    c.push_back(node);\n\
    \                    n -= d;\n                }\n                aux = new Node(u\
    \ - 1, c.size());\n            }\n        }\n    };\n    Node* root;\n    VanEmdeBoasTree(){\n\
    \        root = new Node(32 - __builtin_clz(W - 1), 1 << W);\n        insert((1\
    \ << W) - 1, root);\n    }\n\n    bool insert(uint32_t key, Node* ptr = nullptr){\n\
    \        if(ptr == nullptr)\n            ptr = root;\n        if(ptr->u == 0){\n\
    \            bool fl = (ptr->ma < key) || (key < ptr->mi);\n            ptr->ma\
    \ = max(ptr->ma, key);\n            ptr->mi = min(ptr->mi, key);\n           \
    \ return fl;\n        }\n        if(ptr->mi > ptr->ma){\n            ptr->mi =\
    \ ptr->ma = key;\n            return true;\n        }\n        if(key < ptr->mi){\n\
    \            swap(key, ptr->mi);\n        }\n        else if(ptr->mi == key)\n\
    \            return false;\n        if(ptr->ma < key)\n            ptr->ma = key;\n\
    \n        int shift_cnt = 1 << (ptr->u - 1);\n        uint32_t idx = uint64_t(key)\
    \ >> shift_cnt;\n        uint32_t next_key = key & ((1uLL << shift_cnt) - 1u);\n\
    \n        assert(idx < ptr->c.size());\n\n        if(ptr->c[idx]->mi > ptr->c[idx]->ma){\n\
    \            insert(idx, ptr->aux);\n        }\n        return insert(next_key,\
    \ ptr->c[idx]);\n    }\n\n    bool erase(uint32_t key, Node* ptr = nullptr){\n\
    \        if(ptr == nullptr)\n            ptr = root;\n        if(ptr->mi > ptr->ma){\n\
    \            return false;\n        }\n        if(ptr->mi == ptr->ma){\n     \
    \       if(ptr->mi == key){\n                ptr->mi = NULL_FLAG;\n          \
    \      ptr->ma = 0;\n                return true;\n            }\n           \
    \ return false;\n        }\n        if(ptr->u == 0){\n            // 2\u8981\u7D20\
    \u3042\u308B\u3046\u3061\u306E1\u8981\u7D20\u304C\u6B8B\u308B\n            assert(ptr->mi\
    \ == key || ptr->ma == key);\n            i64 x = ptr->mi == key ? ptr->ma : ptr->mi;\n\
    \            ptr->mi = ptr->ma = x;\n            return true;\n        }\n   \
    \     int shift_cnt = 1 << (ptr->u - 1);\n        if(ptr->mi == key)\n       \
    \     ptr->mi = key = ((ptr->aux->mi << shift_cnt) | ptr->c[ptr->aux->mi]->mi);\n\
    \n        uint32_t idx = uint64_t(key) >> shift_cnt;\n        uint32_t next_key\
    \ = key & ((1uLL << shift_cnt) - 1u);\n        auto nex = ptr->c[idx];\n     \
    \   if(erase(next_key, nex)){\n            if(nex->mi > nex->ma)\n           \
    \     erase(idx, ptr->aux);\n            if(ptr->ma == key){\n               \
    \ if(ptr->aux->mi > ptr->aux->ma)\n                    ptr->ma = ptr->mi;\n  \
    \              else\n                    ptr->ma = ((ptr->aux->ma << shift_cnt)\
    \ | ptr->c[ptr->aux->ma]->ma);\n            }\n            return true;\n    \
    \    }\n        else\n            return false;\n    }\n\n    uint32_t lower_bound(uint32_t\
    \ key, Node* ptr = nullptr){\n        if(ptr == nullptr)\n            ptr = root;\n\
    \        if(ptr->u == 0){\n            assert(key <= ptr->ma);\n            return\
    \ key <= ptr->mi ? ptr->mi : ptr->ma;\n        }\n        if(key <= ptr->mi){\n\
    \            assert(ptr->mi != NULL_FLAG);\n            return ptr->mi;\n    \
    \    }\n        int shift_cnt = 1 << (ptr->u - 1);\n        uint32_t idx = uint64_t(key)\
    \ >> shift_cnt;\n        uint32_t next_key = key & ((1uLL << shift_cnt) - 1u);\n\
    \        assert(idx < ptr->c.size());\n\n        auto nex = ptr->c[idx];\n   \
    \     if(nex->mi != NULL_FLAG && next_key <= nex->ma){\n            return (idx\
    \ << shift_cnt) | lower_bound(next_key, nex);\n        }\n\n        uint64_t i\
    \ = lower_bound(idx + 1, ptr->aux);\n        return (i << shift_cnt) | ptr->c[i]->mi;\n\
    \    }\n};\n\n"
  code: "template <uint32_t W, uint32_t NULL_FLAG = ~0u>\nstruct VanEmdeBoasTree{\n\
    \n    // \u30B5\u30A4\u30BA2^(2^U)\u306E\u30CE\u30FC\u30C9\n    // U=0\u304B\u3089\
    \u3067\u30B5\u30A4\u30BA\u304C2, 4, 16, 256, 65536, \u3068\u306A\u308B\n    struct\
    \ Node{\n        uint32_t u, ma, mi;\n        Node* aux;\n        vector<Node*>\
    \ c;\n        Node(int u, int n) : u(u), mi(NULL_FLAG), ma(0){\n            if(u){\n\
    \                while(n){\n                    int d = min(1 << (1 << (u - 1)),\
    \ n);\n                    Node *node = new Node(u - 1, d);\n                \
    \    c.push_back(node);\n                    n -= d;\n                }\n    \
    \            aux = new Node(u - 1, c.size());\n            }\n        }\n    };\n\
    \    Node* root;\n    VanEmdeBoasTree(){\n        root = new Node(32 - __builtin_clz(W\
    \ - 1), 1 << W);\n        insert((1 << W) - 1, root);\n    }\n\n    bool insert(uint32_t\
    \ key, Node* ptr = nullptr){\n        if(ptr == nullptr)\n            ptr = root;\n\
    \        if(ptr->u == 0){\n            bool fl = (ptr->ma < key) || (key < ptr->mi);\n\
    \            ptr->ma = max(ptr->ma, key);\n            ptr->mi = min(ptr->mi,\
    \ key);\n            return fl;\n        }\n        if(ptr->mi > ptr->ma){\n \
    \           ptr->mi = ptr->ma = key;\n            return true;\n        }\n  \
    \      if(key < ptr->mi){\n            swap(key, ptr->mi);\n        }\n      \
    \  else if(ptr->mi == key)\n            return false;\n        if(ptr->ma < key)\n\
    \            ptr->ma = key;\n\n        int shift_cnt = 1 << (ptr->u - 1);\n  \
    \      uint32_t idx = uint64_t(key) >> shift_cnt;\n        uint32_t next_key =\
    \ key & ((1uLL << shift_cnt) - 1u);\n\n        assert(idx < ptr->c.size());\n\n\
    \        if(ptr->c[idx]->mi > ptr->c[idx]->ma){\n            insert(idx, ptr->aux);\n\
    \        }\n        return insert(next_key, ptr->c[idx]);\n    }\n\n    bool erase(uint32_t\
    \ key, Node* ptr = nullptr){\n        if(ptr == nullptr)\n            ptr = root;\n\
    \        if(ptr->mi > ptr->ma){\n            return false;\n        }\n      \
    \  if(ptr->mi == ptr->ma){\n            if(ptr->mi == key){\n                ptr->mi\
    \ = NULL_FLAG;\n                ptr->ma = 0;\n                return true;\n \
    \           }\n            return false;\n        }\n        if(ptr->u == 0){\n\
    \            // 2\u8981\u7D20\u3042\u308B\u3046\u3061\u306E1\u8981\u7D20\u304C\
    \u6B8B\u308B\n            assert(ptr->mi == key || ptr->ma == key);\n        \
    \    i64 x = ptr->mi == key ? ptr->ma : ptr->mi;\n            ptr->mi = ptr->ma\
    \ = x;\n            return true;\n        }\n        int shift_cnt = 1 << (ptr->u\
    \ - 1);\n        if(ptr->mi == key)\n            ptr->mi = key = ((ptr->aux->mi\
    \ << shift_cnt) | ptr->c[ptr->aux->mi]->mi);\n\n        uint32_t idx = uint64_t(key)\
    \ >> shift_cnt;\n        uint32_t next_key = key & ((1uLL << shift_cnt) - 1u);\n\
    \        auto nex = ptr->c[idx];\n        if(erase(next_key, nex)){\n        \
    \    if(nex->mi > nex->ma)\n                erase(idx, ptr->aux);\n          \
    \  if(ptr->ma == key){\n                if(ptr->aux->mi > ptr->aux->ma)\n    \
    \                ptr->ma = ptr->mi;\n                else\n                  \
    \  ptr->ma = ((ptr->aux->ma << shift_cnt) | ptr->c[ptr->aux->ma]->ma);\n     \
    \       }\n            return true;\n        }\n        else\n            return\
    \ false;\n    }\n\n    uint32_t lower_bound(uint32_t key, Node* ptr = nullptr){\n\
    \        if(ptr == nullptr)\n            ptr = root;\n        if(ptr->u == 0){\n\
    \            assert(key <= ptr->ma);\n            return key <= ptr->mi ? ptr->mi\
    \ : ptr->ma;\n        }\n        if(key <= ptr->mi){\n            assert(ptr->mi\
    \ != NULL_FLAG);\n            return ptr->mi;\n        }\n        int shift_cnt\
    \ = 1 << (ptr->u - 1);\n        uint32_t idx = uint64_t(key) >> shift_cnt;\n \
    \       uint32_t next_key = key & ((1uLL << shift_cnt) - 1u);\n        assert(idx\
    \ < ptr->c.size());\n\n        auto nex = ptr->c[idx];\n        if(nex->mi !=\
    \ NULL_FLAG && next_key <= nex->ma){\n            return (idx << shift_cnt) |\
    \ lower_bound(next_key, nex);\n        }\n\n        uint64_t i = lower_bound(idx\
    \ + 1, ptr->aux);\n        return (i << shift_cnt) | ptr->c[i]->mi;\n    }\n};\n\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/vanemdeboastree.cpp
  requiredBy: []
  timestamp: '2020-04-13 20:19:50+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/veb_set.test.cpp
documentation_of: lib/classes/vanemdeboastree.cpp
layout: document
redirect_from:
- /library/lib/classes/vanemdeboastree.cpp
- /library/lib/classes/vanemdeboastree.cpp.html
title: lib/classes/vanemdeboastree.cpp
---
