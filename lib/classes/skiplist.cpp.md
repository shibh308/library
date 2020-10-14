---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/skiplist_composite.test.cpp
    title: verify/skiplist_composite.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/skiplist.cpp\"\ntemplate <typename T>\nstruct\
    \ SkipList{\n\n    static uint32_t rnd(){\n        static uint32_t x = 123456789,\
    \ y = 362436069, z = 521288629, w = time(0);\n        uint32_t t = x ^ (x << 11);\n\
    \        x = y, y = z, z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n\
    \        return w;\n    }\n\n    struct Node{\n        int height;\n        T\
    \ val;\n        vector<Node*> next, prev;\n        vector<T> sum;\n        vector<int>\
    \ size;\n        Node(T val, int height) : val(val), height(height), next(height,\
    \ nullptr), prev(height, nullptr), sum(height, val), size(height, 1){}\n    };\n\
    \n    using NodePtr = Node*;\n    int max_height;\n    NodePtr front, back;\n\
    \    function<T(T, T)> f;\n    T op;\n\n    SkipList(function<T(T, T)> f = [](auto\
    \ x, auto y){return x;}, T op = T()) : max_height(0), f(f), op(op){\n        front\
    \ = new Node(op, 32);\n        back = new Node(op, 32);\n        front->next[0]\
    \ = back;\n        back->prev[0] = front;\n    }\n\n    int size(){\n        return\
    \ front->size[max_height] - 1;\n    }\n\n    void insert_next(NodePtr pre, T key){\n\
    \        uint32_t r = max(rnd(), uint32_t(1));\n        int height = __builtin_ffs(r);\n\
    \        while(max_height < height){\n            ++max_height;\n            front->size[max_height]\
    \ = front->size[max_height - 1];\n            front->next[max_height] = back;\n\
    \            back->prev[max_height] = front;\n            front->sum[max_height]\
    \ = front->sum[max_height - 1];\n        }\n        NodePtr node = new Node(key,\
    \ height);\n\n        int pre_size = 1;\n        T pre_sum = pre->val;\n     \
    \   T nex_sum = key;\n        NodePtr nex = pre->next[0];\n        for(int i =\
    \ 0; i <= max_height; ++i){\n            ++pre->size[i];\n            if(i < height){\n\
    \                pre->next[i] = node;\n                node->next[i] = nex;\n\
    \                nex->prev[i] = node;\n                node->prev[i] = pre;\n\
    \                int range_size = pre->size[i];\n                pre->size[i]\
    \ = pre_size;\n                pre->sum[i] = pre_sum;\n                node->size[i]\
    \ = range_size - pre_size;\n                node->sum[i] = nex_sum;\n        \
    \    }\n            else{\n                pre->sum[i] = f(pre_sum, nex_sum);\n\
    \            }\n            for(; pre->height == i + 1 && pre->prev[i] != nullptr;\
    \ pre = pre->prev[i]){\n                pre_sum = f(pre->prev[i]->sum[i], pre_sum);\n\
    \                pre_size += pre->prev[i]->size[i];\n            }\n         \
    \   for(; nex->height == i + 1  && nex->next[i] != nullptr; nex = nex->next[i]){\n\
    \                nex_sum = f(nex_sum, nex->sum[i]);\n            }\n        }\n\
    \    }\n\n    // idx\u756A\u76EE(idx=0\u306A\u3089\u5148\u982D)\u306B\u633F\u5165\
    \u3059\u308B\n    void insert_index(int idx, T key){\n        NodePtr pre = access(idx\
    \ - 1);\n        insert_next(pre, key);\n    }\n\n    void insert_key(T key){\n\
    \        NodePtr pre = lower_bound(key)->prev[0];\n        insert_next(pre, key);\n\
    \    }\n\n    void erase(NodePtr target){\n        // \u30E1\u30E2\u30EA\u89E3\
    \u653E\u306F\u3057\u306A\u3044(\u3057\u3066\u3082\u3044\u3044\u3051\u3069)\n \
    \       int height = target->height;\n        NodePtr pre = target->prev[0];\n\
    \        NodePtr nex = target->next[0];\n        T sum = pre->val;\n        for(int\
    \ i = 0; i <= max_height; ++i){\n            pre->sum[i] = sum;\n            --pre->size[i];\n\
    \            if(i < height){\n                pre->next[i] = nex;\n          \
    \      nex->prev[i] = pre;\n                pre->size[i] += target->size[i];\n\
    \            }\n            for(; pre->height == i + 1 && pre->prev[i] != nullptr;\
    \ pre = pre->prev[i])\n                sum = f(pre->prev[i]->sum[i], sum);\n \
    \           for(; nex->height == i + 1 && nex->next[i] != nullptr; nex = nex->next[i])\n\
    \                sum = f(sum, nex->sum[i]);\n        }\n    }\n\n    void erase_index(int\
    \ idx){\n        NodePtr target = access(idx);\n        erase(target);\n    }\n\
    \    void erase_key(T key){\n        NodePtr target = lower_bound(key);\n    \
    \    if(target == back || target->val != key)\n            return;\n        erase(target);\n\
    \    }\n\n    NodePtr lower_bound(T key){\n        NodePtr pre = front;\n    \
    \    for(int i = max_height; i >= 0; --i)\n            for(; i < pre->next.size()\
    \ && pre->next[i] != back && pre->next[i]->val < key; pre = pre->next[i]);\n \
    \       return pre->next[0];\n    }\n\n    NodePtr upper_bound(T key){\n     \
    \   NodePtr pre = front;\n        for(int i = max_height; i >= 0; --i)\n     \
    \       for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->val\
    \ <= key; pre = pre->next[i]);\n        return pre->next[0];\n    }\n\n    bool\
    \ contains(T key){\n        NodePtr ptr = lower_bound(key);\n        return ptr\
    \ != back && ptr->key == key;\n    }\n\n    // 0-indexed\u3067\u30A2\u30AF\u30BB\
    \u30B9\u3059\u308B\n    NodePtr access(int idx){\n        ++idx;\n        assert(0\
    \ <= idx && idx <= size());\n        NodePtr ptr = front;\n        for(int i =\
    \ max_height; i >= 0; --i)\n            for(; i < ptr->next.size() && ptr->next[i]\
    \ != back && ptr->size[i] <= idx; idx -= ptr->size[i], ptr = ptr->next[i]);\n\
    \        return ptr;\n    }\n\n    T get(int l, int r){\n        NodePtr ptr =\
    \ access(l);\n        T sum = op;\n        int diff = r - l;\n        int height_bound\
    \ = 32;\n        for(; ptr->size[ptr->height - 1] <= diff; ptr = ptr->next[ptr->height\
    \ - 1]){\n            diff -= ptr->size[ptr->height - 1];\n            sum = f(sum,\
    \ ptr->sum[ptr->height - 1]);\n        }\n        for(int i = ptr->height - 2;\
    \ diff; --i)\n            for(; ptr->size[i] <= diff; ptr = ptr->next[i]){\n \
    \               diff -= ptr->size[i];\n                sum = f(sum, ptr->sum[i]);\n\
    \            }\n        return sum;\n    }\n\n    void print(){\n        for(NodePtr\
    \ node = front; node != nullptr; node = node->next[0]){\n            if(node ==\
    \ front || node == back)\n                printf(\"  null: \");\n            else\n\
    \                printf(\"%6lld: \", node->val);\n            for(int i = 0; i\
    \ < node->height; ++i)\n                printf(\"%2d \", node->sum[i]);\n    \
    \            // cout << node->size[i] << \" \";\n            cout << endl;\n \
    \       }\n        cout << endl;\n    }\n};\n"
  code: "template <typename T>\nstruct SkipList{\n\n    static uint32_t rnd(){\n \
    \       static uint32_t x = 123456789, y = 362436069, z = 521288629, w = time(0);\n\
    \        uint32_t t = x ^ (x << 11);\n        x = y, y = z, z = w;\n        w\
    \ = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n    }\n\n    struct\
    \ Node{\n        int height;\n        T val;\n        vector<Node*> next, prev;\n\
    \        vector<T> sum;\n        vector<int> size;\n        Node(T val, int height)\
    \ : val(val), height(height), next(height, nullptr), prev(height, nullptr), sum(height,\
    \ val), size(height, 1){}\n    };\n\n    using NodePtr = Node*;\n    int max_height;\n\
    \    NodePtr front, back;\n    function<T(T, T)> f;\n    T op;\n\n    SkipList(function<T(T,\
    \ T)> f = [](auto x, auto y){return x;}, T op = T()) : max_height(0), f(f), op(op){\n\
    \        front = new Node(op, 32);\n        back = new Node(op, 32);\n       \
    \ front->next[0] = back;\n        back->prev[0] = front;\n    }\n\n    int size(){\n\
    \        return front->size[max_height] - 1;\n    }\n\n    void insert_next(NodePtr\
    \ pre, T key){\n        uint32_t r = max(rnd(), uint32_t(1));\n        int height\
    \ = __builtin_ffs(r);\n        while(max_height < height){\n            ++max_height;\n\
    \            front->size[max_height] = front->size[max_height - 1];\n        \
    \    front->next[max_height] = back;\n            back->prev[max_height] = front;\n\
    \            front->sum[max_height] = front->sum[max_height - 1];\n        }\n\
    \        NodePtr node = new Node(key, height);\n\n        int pre_size = 1;\n\
    \        T pre_sum = pre->val;\n        T nex_sum = key;\n        NodePtr nex\
    \ = pre->next[0];\n        for(int i = 0; i <= max_height; ++i){\n           \
    \ ++pre->size[i];\n            if(i < height){\n                pre->next[i] =\
    \ node;\n                node->next[i] = nex;\n                nex->prev[i] =\
    \ node;\n                node->prev[i] = pre;\n                int range_size\
    \ = pre->size[i];\n                pre->size[i] = pre_size;\n                pre->sum[i]\
    \ = pre_sum;\n                node->size[i] = range_size - pre_size;\n       \
    \         node->sum[i] = nex_sum;\n            }\n            else{\n        \
    \        pre->sum[i] = f(pre_sum, nex_sum);\n            }\n            for(;\
    \ pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i]){\n    \
    \            pre_sum = f(pre->prev[i]->sum[i], pre_sum);\n                pre_size\
    \ += pre->prev[i]->size[i];\n            }\n            for(; nex->height == i\
    \ + 1  && nex->next[i] != nullptr; nex = nex->next[i]){\n                nex_sum\
    \ = f(nex_sum, nex->sum[i]);\n            }\n        }\n    }\n\n    // idx\u756A\
    \u76EE(idx=0\u306A\u3089\u5148\u982D)\u306B\u633F\u5165\u3059\u308B\n    void\
    \ insert_index(int idx, T key){\n        NodePtr pre = access(idx - 1);\n    \
    \    insert_next(pre, key);\n    }\n\n    void insert_key(T key){\n        NodePtr\
    \ pre = lower_bound(key)->prev[0];\n        insert_next(pre, key);\n    }\n\n\
    \    void erase(NodePtr target){\n        // \u30E1\u30E2\u30EA\u89E3\u653E\u306F\
    \u3057\u306A\u3044(\u3057\u3066\u3082\u3044\u3044\u3051\u3069)\n        int height\
    \ = target->height;\n        NodePtr pre = target->prev[0];\n        NodePtr nex\
    \ = target->next[0];\n        T sum = pre->val;\n        for(int i = 0; i <= max_height;\
    \ ++i){\n            pre->sum[i] = sum;\n            --pre->size[i];\n       \
    \     if(i < height){\n                pre->next[i] = nex;\n                nex->prev[i]\
    \ = pre;\n                pre->size[i] += target->size[i];\n            }\n  \
    \          for(; pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i])\n\
    \                sum = f(pre->prev[i]->sum[i], sum);\n            for(; nex->height\
    \ == i + 1 && nex->next[i] != nullptr; nex = nex->next[i])\n                sum\
    \ = f(sum, nex->sum[i]);\n        }\n    }\n\n    void erase_index(int idx){\n\
    \        NodePtr target = access(idx);\n        erase(target);\n    }\n    void\
    \ erase_key(T key){\n        NodePtr target = lower_bound(key);\n        if(target\
    \ == back || target->val != key)\n            return;\n        erase(target);\n\
    \    }\n\n    NodePtr lower_bound(T key){\n        NodePtr pre = front;\n    \
    \    for(int i = max_height; i >= 0; --i)\n            for(; i < pre->next.size()\
    \ && pre->next[i] != back && pre->next[i]->val < key; pre = pre->next[i]);\n \
    \       return pre->next[0];\n    }\n\n    NodePtr upper_bound(T key){\n     \
    \   NodePtr pre = front;\n        for(int i = max_height; i >= 0; --i)\n     \
    \       for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->val\
    \ <= key; pre = pre->next[i]);\n        return pre->next[0];\n    }\n\n    bool\
    \ contains(T key){\n        NodePtr ptr = lower_bound(key);\n        return ptr\
    \ != back && ptr->key == key;\n    }\n\n    // 0-indexed\u3067\u30A2\u30AF\u30BB\
    \u30B9\u3059\u308B\n    NodePtr access(int idx){\n        ++idx;\n        assert(0\
    \ <= idx && idx <= size());\n        NodePtr ptr = front;\n        for(int i =\
    \ max_height; i >= 0; --i)\n            for(; i < ptr->next.size() && ptr->next[i]\
    \ != back && ptr->size[i] <= idx; idx -= ptr->size[i], ptr = ptr->next[i]);\n\
    \        return ptr;\n    }\n\n    T get(int l, int r){\n        NodePtr ptr =\
    \ access(l);\n        T sum = op;\n        int diff = r - l;\n        int height_bound\
    \ = 32;\n        for(; ptr->size[ptr->height - 1] <= diff; ptr = ptr->next[ptr->height\
    \ - 1]){\n            diff -= ptr->size[ptr->height - 1];\n            sum = f(sum,\
    \ ptr->sum[ptr->height - 1]);\n        }\n        for(int i = ptr->height - 2;\
    \ diff; --i)\n            for(; ptr->size[i] <= diff; ptr = ptr->next[i]){\n \
    \               diff -= ptr->size[i];\n                sum = f(sum, ptr->sum[i]);\n\
    \            }\n        return sum;\n    }\n\n    void print(){\n        for(NodePtr\
    \ node = front; node != nullptr; node = node->next[0]){\n            if(node ==\
    \ front || node == back)\n                printf(\"  null: \");\n            else\n\
    \                printf(\"%6lld: \", node->val);\n            for(int i = 0; i\
    \ < node->height; ++i)\n                printf(\"%2d \", node->sum[i]);\n    \
    \            // cout << node->size[i] << \" \";\n            cout << endl;\n \
    \       }\n        cout << endl;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/skiplist.cpp
  requiredBy: []
  timestamp: '2020-04-09 14:56:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/skiplist_composite.test.cpp
documentation_of: lib/classes/skiplist.cpp
layout: document
redirect_from:
- /library/lib/classes/skiplist.cpp
- /library/lib/classes/skiplist.cpp.html
title: lib/classes/skiplist.cpp
---
