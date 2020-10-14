---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/skiplist_sset_dict.test.cpp
    title: verify/skiplist_sset_dict.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/skiplist_sset_itp.test.cpp
    title: verify/skiplist_sset_itp.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/skiplist_sset.cpp\"\ntemplate <typename T>\n\
    struct SSet{\n\n    static uint32_t rnd(){\n        static uint32_t x = 123456789,\
    \ y = 362436069, z = 521288629, w = time(0);\n        uint32_t t = x ^(x << 11);\n\
    \        x = y, y = z, z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n\
    \        return w;\n    }\n\n    struct Node{\n        int height;\n        T\
    \ val;\n        vector<Node *> next, prev;\n        vector<int> size;\n      \
    \  Node(T val, int height) : val(val), height(height), next(height, nullptr),\
    \ prev(height, nullptr), size(height, 1){}\n    };\n\n    using NodePtr = Node*;\n\
    \    int max_height;\n    NodePtr front, back;\n\n    SSet(Node* fr = nullptr,\
    \ Node* ba = nullptr) : max_height(0), front(fr), back(ba){\n        if(front\
    \ == nullptr){\n            front = new Node(T(), 21);\n            back = new\
    \ Node(T(), 21);\n            front->next[0] = back;\n            back->prev[0]\
    \ = front;\n        }\n    }\n\n    int size(){\n        return front->size[max_height]\
    \ - 1;\n    }\n\n    void insert_next(NodePtr pre, T key, int height = -1){\n\
    \        if(height == -1){\n            uint32_t r = max(rnd(), uint32_t(1));\n\
    \            height = min(20, __builtin_ffs(r));\n        }\n        while(max_height\
    \ < height){\n            ++max_height;\n            front->size[max_height] =\
    \ front->size[max_height - 1];\n            front->next[max_height] = back;\n\
    \            back->prev[max_height] = front;\n        }\n        NodePtr node\
    \ = new Node(key, height);\n\n        int pre_size = 1;\n        NodePtr nex =\
    \ pre->next[0];\n        for(int i = 0; i <= max_height; ++i){\n            ++pre->size[i];\n\
    \            if(i < height){\n                pre->next[i] = node;\n         \
    \       node->next[i] = nex;\n                nex->prev[i] = node;\n         \
    \       node->prev[i] = pre;\n                int range_size = pre->size[i];\n\
    \                pre->size[i] = pre_size;\n                node->size[i] = range_size\
    \ - pre_size;\n            }\n            for(; pre->height == i + 1 && pre->prev[i]\
    \ != nullptr; pre = pre->prev[i])\n                pre_size += pre->prev[i]->size[i];\n\
    \            for(; nex->height == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]);\n\
    \        }\n    }\n\n    void insert(T key){\n        NodePtr pre = lower_bound(key)->prev[0];\n\
    \        insert_next(pre, key);\n    }\n\n    void erase(NodePtr target){\n  \
    \      // \u30E1\u30E2\u30EA\u89E3\u653E\u306F\u3057\u306A\u3044(\u3057\u3066\u3082\
    \u3044\u3044\u3051\u3069)\n        int height = target->height;\n        NodePtr\
    \ pre = target->prev[0];\n        NodePtr nex = target->next[0];\n        for(int\
    \ i = 0; i <= max_height; ++i){\n            --pre->size[i];\n            if(i\
    \ < height){\n                pre->next[i] = nex;\n                nex->prev[i]\
    \ = pre;\n                pre->size[i] += target->size[i];\n            }\n  \
    \          for(; pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i]);\n\
    \            for(; nex->height == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]);\n\
    \        }\n    }\n\n    void erase_index(int idx){\n        NodePtr target =\
    \ access(idx);\n        erase(target);\n    }\n\n    void erase_key(T key){\n\
    \        NodePtr target = lower_bound(key);\n        if(target == back || target->val\
    \ != key)\n            return;\n        erase(target);\n    }\n\n    NodePtr lower_bound(T\
    \ key){\n        NodePtr pre = front;\n        for(int i = max_height; i >= 0;\
    \ --i)\n            for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->val\
    \ < key; pre = pre->next[i]);\n        return pre->next[0];\n    }\n\n    // 0-indexed\u3067\
    \u30A2\u30AF\u30BB\u30B9\u3059\u308B\n    NodePtr access(int idx){\n        ++idx;\n\
    \        assert(0 <= idx && idx <= size());\n        NodePtr ptr = front;\n  \
    \      for(int i = max_height; i >= 0; --i)\n            for(; i < ptr->next.size()\
    \ && ptr->next[i] != back && ptr->size[i] <= idx; idx -= ptr->size[i], ptr = ptr->next[i]);\n\
    \        return ptr;\n    }\n\n    // [0, k), [k, n)\u3067\u5206\u5272\u3057\u3001\
    [k, n)\u3092\u8FD4\u3059\n    SSet<T> split(int k){\n        int max_h = max_height;\n\
    \        NodePtr pre = access(k - 1);\n        insert_next(pre, T(), 21);\n  \
    \      NodePtr l_back = pre->next[0];\n        insert_next(l_back, T(), 21);\n\
    \        NodePtr r_front = l_back->next[0];\n        NodePtr l_front = front,\
    \ r_back = back;\n        for(int i = 0; i < l_back->height; ++i){\n         \
    \   l_back->next[i] = nullptr;\n            r_front->prev[i] = nullptr;\n    \
    \        l_back->size[i] = 1;\n        }\n        max_height = max_h;\n      \
    \  NodePtr ptr = l_back;\n        int size = 1;\n        for(int i = 0; i <= max_height;\
    \ ++i){\n            ptr->size[i] = size;\n            for(; ptr->height == i\
    \ + 1 && ptr->prev[i] != nullptr; ptr = ptr->prev[i])\n                size +=\
    \ ptr->prev[i]->size[i];\n        }\n        back = l_back;\n        SSet<T> sset(r_front,\
    \ r_back);\n        sset.max_height = max_h;\n        return sset;\n    }\n\n\
    \    // this\u306E\u672B\u5C3E\u306Bslist\u3092\u7D50\u5408\u3059\u308B\n    void\
    \ merge(SSet<T>& slist){\n        while(max_height < slist.max_height){\n    \
    \        ++max_height;\n            front->size[max_height] = front->size[max_height\
    \ - 1];\n            front->next[max_height] = back;\n            back->prev[max_height]\
    \ = front;\n        }\n        while(slist.max_height < max_height){\n       \
    \     ++slist.max_height;\n            slist.front->size[slist.max_height] = slist.front->size[slist.max_height\
    \ - 1];\n            slist.front->next[slist.max_height] = slist.back;\n     \
    \       slist.back->prev[slist.max_height] = slist.front;\n        }\n       \
    \ NodePtr a = back, b = slist.front;\n        for(int i = 0; i < back->height;\
    \ ++i){\n            a->next[i] = b;\n            b->prev[i] = a;\n        }\n\
    \        back = slist.back;\n        erase(a);\n        erase(b);\n    }\n};\n\
    \n"
  code: "template <typename T>\nstruct SSet{\n\n    static uint32_t rnd(){\n     \
    \   static uint32_t x = 123456789, y = 362436069, z = 521288629, w = time(0);\n\
    \        uint32_t t = x ^(x << 11);\n        x = y, y = z, z = w;\n        w =\
    \ (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n    }\n\n    struct Node{\n\
    \        int height;\n        T val;\n        vector<Node *> next, prev;\n   \
    \     vector<int> size;\n        Node(T val, int height) : val(val), height(height),\
    \ next(height, nullptr), prev(height, nullptr), size(height, 1){}\n    };\n\n\
    \    using NodePtr = Node*;\n    int max_height;\n    NodePtr front, back;\n\n\
    \    SSet(Node* fr = nullptr, Node* ba = nullptr) : max_height(0), front(fr),\
    \ back(ba){\n        if(front == nullptr){\n            front = new Node(T(),\
    \ 21);\n            back = new Node(T(), 21);\n            front->next[0] = back;\n\
    \            back->prev[0] = front;\n        }\n    }\n\n    int size(){\n   \
    \     return front->size[max_height] - 1;\n    }\n\n    void insert_next(NodePtr\
    \ pre, T key, int height = -1){\n        if(height == -1){\n            uint32_t\
    \ r = max(rnd(), uint32_t(1));\n            height = min(20, __builtin_ffs(r));\n\
    \        }\n        while(max_height < height){\n            ++max_height;\n \
    \           front->size[max_height] = front->size[max_height - 1];\n         \
    \   front->next[max_height] = back;\n            back->prev[max_height] = front;\n\
    \        }\n        NodePtr node = new Node(key, height);\n\n        int pre_size\
    \ = 1;\n        NodePtr nex = pre->next[0];\n        for(int i = 0; i <= max_height;\
    \ ++i){\n            ++pre->size[i];\n            if(i < height){\n          \
    \      pre->next[i] = node;\n                node->next[i] = nex;\n          \
    \      nex->prev[i] = node;\n                node->prev[i] = pre;\n          \
    \      int range_size = pre->size[i];\n                pre->size[i] = pre_size;\n\
    \                node->size[i] = range_size - pre_size;\n            }\n     \
    \       for(; pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i])\n\
    \                pre_size += pre->prev[i]->size[i];\n            for(; nex->height\
    \ == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]);\n        }\n    }\n\
    \n    void insert(T key){\n        NodePtr pre = lower_bound(key)->prev[0];\n\
    \        insert_next(pre, key);\n    }\n\n    void erase(NodePtr target){\n  \
    \      // \u30E1\u30E2\u30EA\u89E3\u653E\u306F\u3057\u306A\u3044(\u3057\u3066\u3082\
    \u3044\u3044\u3051\u3069)\n        int height = target->height;\n        NodePtr\
    \ pre = target->prev[0];\n        NodePtr nex = target->next[0];\n        for(int\
    \ i = 0; i <= max_height; ++i){\n            --pre->size[i];\n            if(i\
    \ < height){\n                pre->next[i] = nex;\n                nex->prev[i]\
    \ = pre;\n                pre->size[i] += target->size[i];\n            }\n  \
    \          for(; pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i]);\n\
    \            for(; nex->height == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]);\n\
    \        }\n    }\n\n    void erase_index(int idx){\n        NodePtr target =\
    \ access(idx);\n        erase(target);\n    }\n\n    void erase_key(T key){\n\
    \        NodePtr target = lower_bound(key);\n        if(target == back || target->val\
    \ != key)\n            return;\n        erase(target);\n    }\n\n    NodePtr lower_bound(T\
    \ key){\n        NodePtr pre = front;\n        for(int i = max_height; i >= 0;\
    \ --i)\n            for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->val\
    \ < key; pre = pre->next[i]);\n        return pre->next[0];\n    }\n\n    // 0-indexed\u3067\
    \u30A2\u30AF\u30BB\u30B9\u3059\u308B\n    NodePtr access(int idx){\n        ++idx;\n\
    \        assert(0 <= idx && idx <= size());\n        NodePtr ptr = front;\n  \
    \      for(int i = max_height; i >= 0; --i)\n            for(; i < ptr->next.size()\
    \ && ptr->next[i] != back && ptr->size[i] <= idx; idx -= ptr->size[i], ptr = ptr->next[i]);\n\
    \        return ptr;\n    }\n\n    // [0, k), [k, n)\u3067\u5206\u5272\u3057\u3001\
    [k, n)\u3092\u8FD4\u3059\n    SSet<T> split(int k){\n        int max_h = max_height;\n\
    \        NodePtr pre = access(k - 1);\n        insert_next(pre, T(), 21);\n  \
    \      NodePtr l_back = pre->next[0];\n        insert_next(l_back, T(), 21);\n\
    \        NodePtr r_front = l_back->next[0];\n        NodePtr l_front = front,\
    \ r_back = back;\n        for(int i = 0; i < l_back->height; ++i){\n         \
    \   l_back->next[i] = nullptr;\n            r_front->prev[i] = nullptr;\n    \
    \        l_back->size[i] = 1;\n        }\n        max_height = max_h;\n      \
    \  NodePtr ptr = l_back;\n        int size = 1;\n        for(int i = 0; i <= max_height;\
    \ ++i){\n            ptr->size[i] = size;\n            for(; ptr->height == i\
    \ + 1 && ptr->prev[i] != nullptr; ptr = ptr->prev[i])\n                size +=\
    \ ptr->prev[i]->size[i];\n        }\n        back = l_back;\n        SSet<T> sset(r_front,\
    \ r_back);\n        sset.max_height = max_h;\n        return sset;\n    }\n\n\
    \    // this\u306E\u672B\u5C3E\u306Bslist\u3092\u7D50\u5408\u3059\u308B\n    void\
    \ merge(SSet<T>& slist){\n        while(max_height < slist.max_height){\n    \
    \        ++max_height;\n            front->size[max_height] = front->size[max_height\
    \ - 1];\n            front->next[max_height] = back;\n            back->prev[max_height]\
    \ = front;\n        }\n        while(slist.max_height < max_height){\n       \
    \     ++slist.max_height;\n            slist.front->size[slist.max_height] = slist.front->size[slist.max_height\
    \ - 1];\n            slist.front->next[slist.max_height] = slist.back;\n     \
    \       slist.back->prev[slist.max_height] = slist.front;\n        }\n       \
    \ NodePtr a = back, b = slist.front;\n        for(int i = 0; i < back->height;\
    \ ++i){\n            a->next[i] = b;\n            b->prev[i] = a;\n        }\n\
    \        back = slist.back;\n        erase(a);\n        erase(b);\n    }\n};\n\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/skiplist_sset.cpp
  requiredBy: []
  timestamp: '2020-04-09 14:57:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/skiplist_sset_itp.test.cpp
  - verify/skiplist_sset_dict.test.cpp
documentation_of: lib/classes/skiplist_sset.cpp
layout: document
redirect_from:
- /library/lib/classes/skiplist_sset.cpp
- /library/lib/classes/skiplist_sset.cpp.html
title: lib/classes/skiplist_sset.cpp
---
