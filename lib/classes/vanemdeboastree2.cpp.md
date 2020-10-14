---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/veb2_set.test.cpp
    title: verify/veb2_set.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/vanemdeboastree2.cpp\"\n// \u5FC5\u8981\u306A\
    \u6240\u3060\u3051\u4F5C\u308BvEB\u6728\ntemplate <uint32_t W, uint64_t NULL_FLAG\
    \ = ~0uLL>\nstruct VanEmdeBoasTree{\n\n    struct Node{\n        uint64_t u, ma,\
    \ mi;\n        Node* aux;\n        HashMap<int, Node*> c;\n        Node(int u)\
    \ : u(u), mi(NULL_FLAG), ma(0){\n            if(u)\n                aux = new\
    \ Node(u - 1);\n        }\n    };\n    Node* root;\n    VanEmdeBoasTree(){\n \
    \       root = new Node(64 - __builtin_clzll(W - 1));\n        insert((1uLL <<\
    \ W) - 1, root);\n    }\n\n    Node* child(Node* ptr, uint64_t idx){\n       \
    \ assert(ptr->u > 0);\n        auto res = ptr->c.find(idx);\n        if(res.second)\n\
    \            return res.first;\n        ptr->c.add(idx, new Node(ptr->u - 1));\n\
    \        return ptr->c.find(idx).first;\n    }\n\n    bool insert(uint64_t key,\
    \ Node* ptr = nullptr){\n        if(ptr == nullptr)\n            ptr = root;\n\
    \        if(ptr->u == 0){\n            bool fl = (ptr->ma < key) || (key < ptr->mi);\n\
    \            ptr->ma = max(ptr->ma, key);\n            ptr->mi = min(ptr->mi,\
    \ key);\n            return fl;\n        }\n        if(ptr->mi > ptr->ma){\n \
    \           ptr->mi = ptr->ma = key;\n            return true;\n        }\n  \
    \      if(key < ptr->mi){\n            swap(key, ptr->mi);\n        }\n      \
    \  else if(ptr->mi == key)\n            return false;\n        if(ptr->ma < key)\n\
    \            ptr->ma = key;\n\n        int shift_cnt = 1 << (ptr->u - 1);\n  \
    \      uint64_t idx = key >> shift_cnt;\n        uint64_t next_key = key & ((1uLL\
    \ << shift_cnt) - 1);\n\n        if(child(ptr, idx)->mi > child(ptr, idx)->ma)\n\
    \            insert(idx, ptr->aux);\n        return insert(next_key, child(ptr,\
    \ idx));\n    }\n\n    bool erase(uint64_t key, Node* ptr = nullptr){\n      \
    \  if(ptr == nullptr)\n            ptr = root;\n        if(ptr->mi > ptr->ma)\n\
    \            return false;\n        if(ptr->mi == ptr->ma){\n            if(ptr->mi\
    \ == key){\n                ptr->mi = NULL_FLAG;\n                ptr->ma = 0;\n\
    \                return true;\n            }\n            return false;\n    \
    \    }\n        if(ptr->u == 0){\n            // 2\u8981\u7D20\u3042\u308B\u3046\
    \u3061\u306E1\u8981\u7D20\u304C\u6B8B\u308B\n            assert(ptr->mi == key\
    \ || ptr->ma == key);\n            uint64_t x = ptr->mi == key ? ptr->ma : ptr->mi;\n\
    \            ptr->mi = ptr->ma = x;\n            return true;\n        }\n   \
    \     int shift_cnt = 1 << (ptr->u - 1);\n        if(ptr->mi == key)\n       \
    \     ptr->mi = key = ((ptr->aux->mi << shift_cnt) | child(ptr, ptr->aux->mi)->mi);\n\
    \n        uint64_t idx = uint64_t(key) >> shift_cnt;\n        uint64_t next_key\
    \ = key & ((1uLL << shift_cnt) - 1);\n        auto nex = child(ptr, idx);\n  \
    \      if(erase(next_key, nex)){\n            if(nex->mi > nex->ma)\n        \
    \        erase(idx, ptr->aux);\n            if(ptr->ma == key){\n            \
    \    if(ptr->aux->mi > ptr->aux->ma)\n                    ptr->ma = ptr->mi;\n\
    \                else\n                    ptr->ma = ((ptr->aux->ma << shift_cnt)\
    \ | child(ptr, ptr->aux->ma)->ma);\n            }\n            return true;\n\
    \        }\n        else\n            return false;\n    }\n\n    uint32_t lower_bound(uint64_t\
    \ key, Node* ptr = nullptr){\n        if(ptr == nullptr)\n            ptr = root;\n\
    \        if(ptr->u == 0){\n            assert(key <= ptr->ma);\n            return\
    \ key <= ptr->mi ? ptr->mi : ptr->ma;\n        }\n        if(key <= ptr->mi){\n\
    \            assert(ptr->mi != NULL_FLAG);\n            return ptr->mi;\n    \
    \    }\n        int shift_cnt = 1 << (ptr->u - 1);\n        uint64_t idx = uint64_t(key)\
    \ >> shift_cnt;\n        uint64_t next_key = key & ((1uLL << shift_cnt) - 1);\n\
    \n        auto nex = child(ptr, idx);\n        if(nex->mi != NULL_FLAG && next_key\
    \ <= nex->ma){\n            return (idx << shift_cnt) | lower_bound(next_key,\
    \ nex);\n        }\n\n        uint64_t i = lower_bound(idx + 1, ptr->aux);\n \
    \       return (i << shift_cnt) | child(ptr, i)->mi;\n    }\n};\n\n"
  code: "// \u5FC5\u8981\u306A\u6240\u3060\u3051\u4F5C\u308BvEB\u6728\ntemplate <uint32_t\
    \ W, uint64_t NULL_FLAG = ~0uLL>\nstruct VanEmdeBoasTree{\n\n    struct Node{\n\
    \        uint64_t u, ma, mi;\n        Node* aux;\n        HashMap<int, Node*>\
    \ c;\n        Node(int u) : u(u), mi(NULL_FLAG), ma(0){\n            if(u)\n \
    \               aux = new Node(u - 1);\n        }\n    };\n    Node* root;\n \
    \   VanEmdeBoasTree(){\n        root = new Node(64 - __builtin_clzll(W - 1));\n\
    \        insert((1uLL << W) - 1, root);\n    }\n\n    Node* child(Node* ptr, uint64_t\
    \ idx){\n        assert(ptr->u > 0);\n        auto res = ptr->c.find(idx);\n \
    \       if(res.second)\n            return res.first;\n        ptr->c.add(idx,\
    \ new Node(ptr->u - 1));\n        return ptr->c.find(idx).first;\n    }\n\n  \
    \  bool insert(uint64_t key, Node* ptr = nullptr){\n        if(ptr == nullptr)\n\
    \            ptr = root;\n        if(ptr->u == 0){\n            bool fl = (ptr->ma\
    \ < key) || (key < ptr->mi);\n            ptr->ma = max(ptr->ma, key);\n     \
    \       ptr->mi = min(ptr->mi, key);\n            return fl;\n        }\n    \
    \    if(ptr->mi > ptr->ma){\n            ptr->mi = ptr->ma = key;\n          \
    \  return true;\n        }\n        if(key < ptr->mi){\n            swap(key,\
    \ ptr->mi);\n        }\n        else if(ptr->mi == key)\n            return false;\n\
    \        if(ptr->ma < key)\n            ptr->ma = key;\n\n        int shift_cnt\
    \ = 1 << (ptr->u - 1);\n        uint64_t idx = key >> shift_cnt;\n        uint64_t\
    \ next_key = key & ((1uLL << shift_cnt) - 1);\n\n        if(child(ptr, idx)->mi\
    \ > child(ptr, idx)->ma)\n            insert(idx, ptr->aux);\n        return insert(next_key,\
    \ child(ptr, idx));\n    }\n\n    bool erase(uint64_t key, Node* ptr = nullptr){\n\
    \        if(ptr == nullptr)\n            ptr = root;\n        if(ptr->mi > ptr->ma)\n\
    \            return false;\n        if(ptr->mi == ptr->ma){\n            if(ptr->mi\
    \ == key){\n                ptr->mi = NULL_FLAG;\n                ptr->ma = 0;\n\
    \                return true;\n            }\n            return false;\n    \
    \    }\n        if(ptr->u == 0){\n            // 2\u8981\u7D20\u3042\u308B\u3046\
    \u3061\u306E1\u8981\u7D20\u304C\u6B8B\u308B\n            assert(ptr->mi == key\
    \ || ptr->ma == key);\n            uint64_t x = ptr->mi == key ? ptr->ma : ptr->mi;\n\
    \            ptr->mi = ptr->ma = x;\n            return true;\n        }\n   \
    \     int shift_cnt = 1 << (ptr->u - 1);\n        if(ptr->mi == key)\n       \
    \     ptr->mi = key = ((ptr->aux->mi << shift_cnt) | child(ptr, ptr->aux->mi)->mi);\n\
    \n        uint64_t idx = uint64_t(key) >> shift_cnt;\n        uint64_t next_key\
    \ = key & ((1uLL << shift_cnt) - 1);\n        auto nex = child(ptr, idx);\n  \
    \      if(erase(next_key, nex)){\n            if(nex->mi > nex->ma)\n        \
    \        erase(idx, ptr->aux);\n            if(ptr->ma == key){\n            \
    \    if(ptr->aux->mi > ptr->aux->ma)\n                    ptr->ma = ptr->mi;\n\
    \                else\n                    ptr->ma = ((ptr->aux->ma << shift_cnt)\
    \ | child(ptr, ptr->aux->ma)->ma);\n            }\n            return true;\n\
    \        }\n        else\n            return false;\n    }\n\n    uint32_t lower_bound(uint64_t\
    \ key, Node* ptr = nullptr){\n        if(ptr == nullptr)\n            ptr = root;\n\
    \        if(ptr->u == 0){\n            assert(key <= ptr->ma);\n            return\
    \ key <= ptr->mi ? ptr->mi : ptr->ma;\n        }\n        if(key <= ptr->mi){\n\
    \            assert(ptr->mi != NULL_FLAG);\n            return ptr->mi;\n    \
    \    }\n        int shift_cnt = 1 << (ptr->u - 1);\n        uint64_t idx = uint64_t(key)\
    \ >> shift_cnt;\n        uint64_t next_key = key & ((1uLL << shift_cnt) - 1);\n\
    \n        auto nex = child(ptr, idx);\n        if(nex->mi != NULL_FLAG && next_key\
    \ <= nex->ma){\n            return (idx << shift_cnt) | lower_bound(next_key,\
    \ nex);\n        }\n\n        uint64_t i = lower_bound(idx + 1, ptr->aux);\n \
    \       return (i << shift_cnt) | child(ptr, i)->mi;\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/vanemdeboastree2.cpp
  requiredBy: []
  timestamp: '2020-04-13 20:50:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/veb2_set.test.cpp
documentation_of: lib/classes/vanemdeboastree2.cpp
layout: document
redirect_from:
- /library/lib/classes/vanemdeboastree2.cpp
- /library/lib/classes/vanemdeboastree2.cpp.html
title: lib/classes/vanemdeboastree2.cpp
---
