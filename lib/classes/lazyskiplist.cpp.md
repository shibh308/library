---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/skiplist_rmq_raq.test.cpp
    title: verify/skiplist_rmq_raq.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/skiplist_rsq_raq.test.cpp
    title: verify/skiplist_rsq_raq.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/lazyskiplist.cpp\"\ntemplate <typename T, typename\
    \ U>\nstruct SkipList{\n\n    static uint32_t rnd(){\n        static uint32_t\
    \ x = 123456789, y = 362436069, z = 521288629, w = 0; // time(0);\n        uint32_t\
    \ t = x ^ (x << 11);\n        x = y, y = z, z = w;\n        w = (w ^ (w >> 19))\
    \ ^ (t ^ (t >> 8));\n        return w;\n    }\n\n    struct Node{\n        int\
    \ height;\n        vector<Node*> next, prev;\n        vector<T> sum;\n       \
    \ vector<U> lazy;\n        vector<int> size;\n        Node(T val, int height,\
    \ U op_u) : height(height), next(height, nullptr), prev(height, nullptr), sum(height,\
    \ val), lazy(height, op_u), size(height, 1){}\n    };\n\n    using NodePtr = Node*;\n\
    \    int max_height;\n    NodePtr front, back;\n    function<T(T, T)> f;\n   \
    \ function<T(T, U, int)> g;\n    function<U(U, U)> h;\n    T op_t;\n    U op_u;\n\
    \n    SkipList(function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)>\
    \ h, T op_t, U op_u) : max_height(0), f(f), g(g), h(h), op_t(op_t), op_u(op_u){\n\
    \        front = new Node(op_t, 21, op_u);\n        back = new Node(op_t, 21,\
    \ op_u);\n        front->next[0] = back;\n        back->prev[0] = front;\n   \
    \ }\n\n    int size(){\n        return front->size[max_height] - 1;\n    }\n\n\
    \    T get_val(NodePtr ptr, int height){\n        return ptr->lazy[height] ==\
    \ op_u ? ptr->sum[height] : g(ptr->sum[height], ptr->lazy[height], ptr->size[height]);\n\
    \    }\n\n    NodePtr insert_next(NodePtr pre, T key){\n        uint32_t r = max(rnd(),\
    \ uint32_t(1));\n        int height = min(__builtin_ffs(r), 20);\n        while(max_height\
    \ < height){\n            ++max_height;\n            front->size[max_height] =\
    \ front->size[max_height - 1];\n            front->next[max_height] = back;\n\
    \            back->prev[max_height] = front;\n            front->sum[max_height]\
    \ = front->sum[max_height - 1];\n            front->lazy[max_height] = front->lazy[max_height\
    \ - 1];\n            front->lazy[max_height - 1] = op_u;\n        }\n        NodePtr\
    \ node = new Node(key, height, op_u);\n        vector<pair<NodePtr, int>> node_list\
    \ = get_list(pre);\n        for(int i = node_list.size() - 1; i >= 0; --i)\n \
    \           eval(node_list[i].first, node_list[i].second);\n        int pre_size\
    \ = 1;\n        T pre_sum = pre->sum[0];\n        T nex_sum = key;\n        NodePtr\
    \ nex = pre->next[0];\n        for(int i = 0; i <= max_height; ++i){\n       \
    \     ++pre->size[i];\n            if(i < height){\n                pre->next[i]\
    \ = node;\n                node->next[i] = nex;\n                nex->prev[i]\
    \ = node;\n                node->prev[i] = pre;\n                int range_size\
    \ = pre->size[i];\n                pre->size[i] = pre_size;\n                pre->sum[i]\
    \ = pre_sum;\n                node->size[i] = range_size - pre_size;\n       \
    \         node->sum[i] = nex_sum;\n            }\n            else{\n        \
    \        pre->sum[i] = f(pre_sum, nex_sum);\n            }\n            for(;\
    \ pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i]){\n    \
    \            pre_sum = f(get_val(pre->prev[i], i), pre_sum);\n               \
    \ pre_size += pre->prev[i]->size[i];\n            }\n            for(; nex->height\
    \ == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]){\n                nex_sum\
    \ = f(nex_sum, get_val(nex, i));\n            }\n        }\n\t\treturn node;\n\
    \    }\n\n    // idx\u756A\u76EE(idx=0\u306A\u3089\u5148\u982D)\u306B\u633F\u5165\
    \u3059\u308B\n    NodePtr insert_index(int idx, T key){\n        NodePtr pre =\
    \ access(idx - 1);\n        return insert_next(pre, key);\n    }\n\n    NodePtr\
    \ insert_key(T key){\n        NodePtr pre = lower_bound(key)->prev[0];\n     \
    \   return insert_next(pre, key);\n    }\n\n    NodePtr erase(NodePtr target){\n\
    \        // \u30E1\u30E2\u30EA\u89E3\u653E\u306F\u3057\u306A\u3044(\u3057\u3066\
    \u3082\u3044\u3044\u3051\u3069)\n        int height = target->height;\n      \
    \  NodePtr pre = target->prev[0];\n        NodePtr nex = target->next[0];\n\t\t\
    NodePtr ret = nex;\n        vector<pair<NodePtr, int>> node_list = get_list(pre,\
    \ target);\n        for(int i = node_list.size() - 1; i >= 0; --i)\n         \
    \   eval(node_list[i].first, node_list[i].second);\n        T sum = pre->sum[0];\n\
    \        for(int i = 0; i <= max_height; ++i){\n            pre->sum[i] = sum;\n\
    \            --pre->size[i];\n            if(i < height){\n                pre->next[i]\
    \ = nex;\n                nex->prev[i] = pre;\n                pre->size[i] +=\
    \ target->size[i];\n            }\n            for(; pre->height == i + 1 && pre->prev[i]\
    \ != nullptr; pre = pre->prev[i])\n                sum = f(get_val(pre->prev[i],\
    \ i), sum);\n            for(; nex->height == i + 1 && nex->next[i] != nullptr;\
    \ nex = nex->next[i])\n                sum = f(sum, get_val(nex, i));\n      \
    \  }\n\t\treturn ret;\n    }\n\n    NodePtr erase_index(int idx){\n        NodePtr\
    \ target = access(idx);\n        return erase(target);\n    }\n\n    NodePtr erase_key(T\
    \ key){\n        NodePtr target = lower_bound(key);\n        if(target == back\
    \ || target->sum[0] != key)\n            return target;\n        return erase(target);\n\
    \    }\n\n    NodePtr lower_bound(T key){\n        NodePtr pre = front;\n    \
    \    for(int i = max_height; i >= 0; --i)\n            for(; i < pre->next.size()\
    \ && pre->next[i] != back && pre->next[i]->sum[0] < key; pre = pre->next[i]);\n\
    \        return pre->next[0];\n    }\n\n    NodePtr upper_bound(T key){\n    \
    \    NodePtr pre = front;\n        for(int i = max_height; i >= 0; --i)\n    \
    \        for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->sum[0]\
    \ <= key; pre = pre->next[i]);\n        return pre->next[0];\n    }\n\n    bool\
    \ contains(T key){\n        NodePtr ptr = lower_bound(key);\n        return ptr\
    \ != back && ptr->key == key;\n    }\n\n    // (k\u500B\u5148\u306E\u30CE\u30FC\
    \u30C9, [ptr, ptr + k)\u3092\u8986\u3046\u533A\u9593\u306E\u30EA\u30B9\u30C8)\u3092\
    \u8FD4\u3059\n    pair<NodePtr, vector<pair<NodePtr, int>>> kth_next(NodePtr ptr,\
    \ int k){\n        vector<pair<NodePtr, int>> node_list;\n        for(; ptr->size[ptr->height\
    \ - 1] <= k; ptr = ptr->next[ptr->height - 1]){\n            k -= ptr->size[ptr->height\
    \ - 1];\n            node_list.emplace_back(ptr, ptr->height - 1);\n        }\n\
    \        for(int i = ptr->height - 2; k; --i)\n            for(; ptr->size[i]\
    \ <= k; ptr = ptr->next[i]){\n                k -= ptr->size[i];\n           \
    \     node_list.emplace_back(ptr, i);\n            }\n        return make_pair(ptr,\
    \ node_list);\n    }\n\n    // 0-indexed\u3067\u30A2\u30AF\u30BB\u30B9\u3059\u308B\
    \n    NodePtr access(int idx){\n        ++idx;\n        assert(0 <= idx && idx\
    \ <= size());\n        NodePtr ptr = front;\n        for(int i = max_height; i\
    \ >= 0; --i)\n            for(; i < ptr->next.size() && ptr->next[i] != back &&\
    \ ptr->size[i] <= idx; idx -= ptr->size[i], ptr = ptr->next[i]);\n        return\
    \ ptr;\n    }\n\n    vector<pair<NodePtr, int>> get_list(NodePtr ptr){\n     \
    \   vector<pair<NodePtr, int>> node_list;\n        for(int i = 0; i <= max_height;\
    \ ++i){\n            node_list.emplace_back(ptr, i);\n            for(; ptr->height\
    \ == i + 1 && ptr->prev[i] != nullptr; ptr = ptr->prev[i]);\n        }\n     \
    \   return node_list;\n    }\n\n    vector<pair<NodePtr, int>> get_list(NodePtr\
    \ l_ptr, NodePtr r_ptr){\n        NodePtr ptr = l_ptr;\n        vector<pair<NodePtr,\
    \ int>> ptr_list;\n        for(int i = 0; i <= max_height; ++i){\n           \
    \ ptr_list.emplace_back(l_ptr, i);\n            if(l_ptr != r_ptr)\n         \
    \       ptr_list.emplace_back(r_ptr, i);\n            for(; l_ptr->height == i\
    \ + 1 && l_ptr->prev[i] != nullptr; l_ptr = l_ptr->prev[i]);\n            for(;\
    \ r_ptr->height == i + 1 && r_ptr->prev[i] != nullptr; r_ptr = r_ptr->prev[i]);\n\
    \        }\n        return ptr_list;\n    }\n\n    vector<NodePtr> get_child(NodePtr\
    \ ptr, int height){\n        vector<NodePtr> node_vec;\n        if(height == 0)\n\
    \            return node_vec;\n        int diff = ptr->size[height];\n       \
    \ for(; diff; ptr = ptr->next[height - 1]){\n            diff -= ptr->size[height\
    \ - 1];\n            node_vec.emplace_back(ptr);\n        }\n        return node_vec;\n\
    \    }\n\n    void eval(NodePtr ptr, int height){\n        U lazy = ptr->lazy[height];\n\
    \        if(lazy == op_u)\n            return;\n        ptr->sum[height] = get_val(ptr,\
    \ height);\n        vector<NodePtr> child_list = get_child(ptr, height);\n   \
    \     for(auto child : child_list)\n            child->lazy[height - 1] = h(child->lazy[height\
    \ - 1], lazy);\n        ptr->lazy[height] = op_u;\n    }\n\n    T get(int idx){\n\
    \        NodePtr ptr = access(idx);\n        vector<pair<NodePtr, int>> node_list\
    \ = get_list(ptr);\n        T sum = node_list[0].first->sum[0];\n        for(int\
    \ i = node_list.size() - 1; i >= 0; --i){\n            NodePtr node = node_list[i].first;\n\
    \            int height = node_list[i].second;\n            sum = g(sum, node->lazy[height],\
    \ node->size[height]);\n        }\n        return sum;\n    }\n\n    T get(int\
    \ l, int r){\n        NodePtr l_ptr = access(l);\n        NodePtr r_ptr;\n   \
    \     vector<pair<NodePtr, int>> segment_list;\n        tie(r_ptr, segment_list)\
    \ = kth_next(l_ptr, r - l);\n        r_ptr = r_ptr->prev[0];\n        vector<pair<NodePtr,\
    \ int>> ptr_list = get_list(l_ptr, r_ptr);\n        for(int i = ptr_list.size()\
    \ - 1; i >= 0; --i)\n            eval(ptr_list[i].first, ptr_list[i].second);\n\
    \        T sum = op_t;\n        for(auto p : segment_list){\n            NodePtr\
    \ ptr = p.first;\n            int height = p.second;\n            sum = f(sum,\
    \ get_val(ptr, height));\n        }\n        return sum;\n    }\n\n    void update(int\
    \ l, int r, U val){\n        NodePtr l_ptr = access(l);\n        NodePtr r_ptr;\n\
    \        vector<pair<NodePtr, int>> segment_list;\n        tie(r_ptr, segment_list)\
    \ = kth_next(l_ptr, r - l);\n        r_ptr = r_ptr->prev[0];\n        vector<pair<NodePtr,\
    \ int>> ptr_list = get_list(l_ptr, r_ptr);\n        for(int i = ptr_list.size()\
    \ - 1; i >= 0; --i)\n            eval(ptr_list[i].first, ptr_list[i].second);\n\
    \        for(auto p : segment_list){\n            int height = p.second;\n   \
    \         NodePtr ptr = p.first;\n            ptr->lazy[height] = h(ptr->lazy[height],\
    \ val);\n        }\n        for(auto p : ptr_list){\n            NodePtr node\
    \ = p.first;\n            int height = p.second;\n            if(!height)\n  \
    \              continue;\n            vector<NodePtr> child_list = get_child(node,\
    \ height);\n            T sum = op_t;\n            for(auto child : child_list)\n\
    \                sum = f(sum, get_val(child, height - 1));\n            node->sum[height]\
    \ = sum;\n        }\n    }\n\n    void print(bool eval_flag = false){\n      \
    \  int idx = -1;\n        for(NodePtr node = front; node != nullptr; node = node->next[0],\
    \ ++idx){\n            if(node == front || node == back)\n                printf(\"\
    \  null: \");\n            else\n                printf(\"%6d: \", eval_flag ?\
    \ get(idx) : node->sum[0]);\n            for(int i = 0; i < node->height; ++i)\n\
    \                printf(\"%2d: \", eval_flag ? get_val(node, i) : node->sum[i]);\n\
    \                // cout << node->size[i] << \" \";\n            cout << endl;\n\
    \        }\n        cout << endl;\n    }\n};\n"
  code: "template <typename T, typename U>\nstruct SkipList{\n\n    static uint32_t\
    \ rnd(){\n        static uint32_t x = 123456789, y = 362436069, z = 521288629,\
    \ w = 0; // time(0);\n        uint32_t t = x ^ (x << 11);\n        x = y, y =\
    \ z, z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return w;\n\
    \    }\n\n    struct Node{\n        int height;\n        vector<Node*> next, prev;\n\
    \        vector<T> sum;\n        vector<U> lazy;\n        vector<int> size;\n\
    \        Node(T val, int height, U op_u) : height(height), next(height, nullptr),\
    \ prev(height, nullptr), sum(height, val), lazy(height, op_u), size(height, 1){}\n\
    \    };\n\n    using NodePtr = Node*;\n    int max_height;\n    NodePtr front,\
    \ back;\n    function<T(T, T)> f;\n    function<T(T, U, int)> g;\n    function<U(U,\
    \ U)> h;\n    T op_t;\n    U op_u;\n\n    SkipList(function<T(T, T)> f, function<T(T,\
    \ U, int)> g, function<U(U, U)> h, T op_t, U op_u) : max_height(0), f(f), g(g),\
    \ h(h), op_t(op_t), op_u(op_u){\n        front = new Node(op_t, 21, op_u);\n \
    \       back = new Node(op_t, 21, op_u);\n        front->next[0] = back;\n   \
    \     back->prev[0] = front;\n    }\n\n    int size(){\n        return front->size[max_height]\
    \ - 1;\n    }\n\n    T get_val(NodePtr ptr, int height){\n        return ptr->lazy[height]\
    \ == op_u ? ptr->sum[height] : g(ptr->sum[height], ptr->lazy[height], ptr->size[height]);\n\
    \    }\n\n    NodePtr insert_next(NodePtr pre, T key){\n        uint32_t r = max(rnd(),\
    \ uint32_t(1));\n        int height = min(__builtin_ffs(r), 20);\n        while(max_height\
    \ < height){\n            ++max_height;\n            front->size[max_height] =\
    \ front->size[max_height - 1];\n            front->next[max_height] = back;\n\
    \            back->prev[max_height] = front;\n            front->sum[max_height]\
    \ = front->sum[max_height - 1];\n            front->lazy[max_height] = front->lazy[max_height\
    \ - 1];\n            front->lazy[max_height - 1] = op_u;\n        }\n        NodePtr\
    \ node = new Node(key, height, op_u);\n        vector<pair<NodePtr, int>> node_list\
    \ = get_list(pre);\n        for(int i = node_list.size() - 1; i >= 0; --i)\n \
    \           eval(node_list[i].first, node_list[i].second);\n        int pre_size\
    \ = 1;\n        T pre_sum = pre->sum[0];\n        T nex_sum = key;\n        NodePtr\
    \ nex = pre->next[0];\n        for(int i = 0; i <= max_height; ++i){\n       \
    \     ++pre->size[i];\n            if(i < height){\n                pre->next[i]\
    \ = node;\n                node->next[i] = nex;\n                nex->prev[i]\
    \ = node;\n                node->prev[i] = pre;\n                int range_size\
    \ = pre->size[i];\n                pre->size[i] = pre_size;\n                pre->sum[i]\
    \ = pre_sum;\n                node->size[i] = range_size - pre_size;\n       \
    \         node->sum[i] = nex_sum;\n            }\n            else{\n        \
    \        pre->sum[i] = f(pre_sum, nex_sum);\n            }\n            for(;\
    \ pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i]){\n    \
    \            pre_sum = f(get_val(pre->prev[i], i), pre_sum);\n               \
    \ pre_size += pre->prev[i]->size[i];\n            }\n            for(; nex->height\
    \ == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]){\n                nex_sum\
    \ = f(nex_sum, get_val(nex, i));\n            }\n        }\n\t\treturn node;\n\
    \    }\n\n    // idx\u756A\u76EE(idx=0\u306A\u3089\u5148\u982D)\u306B\u633F\u5165\
    \u3059\u308B\n    NodePtr insert_index(int idx, T key){\n        NodePtr pre =\
    \ access(idx - 1);\n        return insert_next(pre, key);\n    }\n\n    NodePtr\
    \ insert_key(T key){\n        NodePtr pre = lower_bound(key)->prev[0];\n     \
    \   return insert_next(pre, key);\n    }\n\n    NodePtr erase(NodePtr target){\n\
    \        // \u30E1\u30E2\u30EA\u89E3\u653E\u306F\u3057\u306A\u3044(\u3057\u3066\
    \u3082\u3044\u3044\u3051\u3069)\n        int height = target->height;\n      \
    \  NodePtr pre = target->prev[0];\n        NodePtr nex = target->next[0];\n\t\t\
    NodePtr ret = nex;\n        vector<pair<NodePtr, int>> node_list = get_list(pre,\
    \ target);\n        for(int i = node_list.size() - 1; i >= 0; --i)\n         \
    \   eval(node_list[i].first, node_list[i].second);\n        T sum = pre->sum[0];\n\
    \        for(int i = 0; i <= max_height; ++i){\n            pre->sum[i] = sum;\n\
    \            --pre->size[i];\n            if(i < height){\n                pre->next[i]\
    \ = nex;\n                nex->prev[i] = pre;\n                pre->size[i] +=\
    \ target->size[i];\n            }\n            for(; pre->height == i + 1 && pre->prev[i]\
    \ != nullptr; pre = pre->prev[i])\n                sum = f(get_val(pre->prev[i],\
    \ i), sum);\n            for(; nex->height == i + 1 && nex->next[i] != nullptr;\
    \ nex = nex->next[i])\n                sum = f(sum, get_val(nex, i));\n      \
    \  }\n\t\treturn ret;\n    }\n\n    NodePtr erase_index(int idx){\n        NodePtr\
    \ target = access(idx);\n        return erase(target);\n    }\n\n    NodePtr erase_key(T\
    \ key){\n        NodePtr target = lower_bound(key);\n        if(target == back\
    \ || target->sum[0] != key)\n            return target;\n        return erase(target);\n\
    \    }\n\n    NodePtr lower_bound(T key){\n        NodePtr pre = front;\n    \
    \    for(int i = max_height; i >= 0; --i)\n            for(; i < pre->next.size()\
    \ && pre->next[i] != back && pre->next[i]->sum[0] < key; pre = pre->next[i]);\n\
    \        return pre->next[0];\n    }\n\n    NodePtr upper_bound(T key){\n    \
    \    NodePtr pre = front;\n        for(int i = max_height; i >= 0; --i)\n    \
    \        for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->sum[0]\
    \ <= key; pre = pre->next[i]);\n        return pre->next[0];\n    }\n\n    bool\
    \ contains(T key){\n        NodePtr ptr = lower_bound(key);\n        return ptr\
    \ != back && ptr->key == key;\n    }\n\n    // (k\u500B\u5148\u306E\u30CE\u30FC\
    \u30C9, [ptr, ptr + k)\u3092\u8986\u3046\u533A\u9593\u306E\u30EA\u30B9\u30C8)\u3092\
    \u8FD4\u3059\n    pair<NodePtr, vector<pair<NodePtr, int>>> kth_next(NodePtr ptr,\
    \ int k){\n        vector<pair<NodePtr, int>> node_list;\n        for(; ptr->size[ptr->height\
    \ - 1] <= k; ptr = ptr->next[ptr->height - 1]){\n            k -= ptr->size[ptr->height\
    \ - 1];\n            node_list.emplace_back(ptr, ptr->height - 1);\n        }\n\
    \        for(int i = ptr->height - 2; k; --i)\n            for(; ptr->size[i]\
    \ <= k; ptr = ptr->next[i]){\n                k -= ptr->size[i];\n           \
    \     node_list.emplace_back(ptr, i);\n            }\n        return make_pair(ptr,\
    \ node_list);\n    }\n\n    // 0-indexed\u3067\u30A2\u30AF\u30BB\u30B9\u3059\u308B\
    \n    NodePtr access(int idx){\n        ++idx;\n        assert(0 <= idx && idx\
    \ <= size());\n        NodePtr ptr = front;\n        for(int i = max_height; i\
    \ >= 0; --i)\n            for(; i < ptr->next.size() && ptr->next[i] != back &&\
    \ ptr->size[i] <= idx; idx -= ptr->size[i], ptr = ptr->next[i]);\n        return\
    \ ptr;\n    }\n\n    vector<pair<NodePtr, int>> get_list(NodePtr ptr){\n     \
    \   vector<pair<NodePtr, int>> node_list;\n        for(int i = 0; i <= max_height;\
    \ ++i){\n            node_list.emplace_back(ptr, i);\n            for(; ptr->height\
    \ == i + 1 && ptr->prev[i] != nullptr; ptr = ptr->prev[i]);\n        }\n     \
    \   return node_list;\n    }\n\n    vector<pair<NodePtr, int>> get_list(NodePtr\
    \ l_ptr, NodePtr r_ptr){\n        NodePtr ptr = l_ptr;\n        vector<pair<NodePtr,\
    \ int>> ptr_list;\n        for(int i = 0; i <= max_height; ++i){\n           \
    \ ptr_list.emplace_back(l_ptr, i);\n            if(l_ptr != r_ptr)\n         \
    \       ptr_list.emplace_back(r_ptr, i);\n            for(; l_ptr->height == i\
    \ + 1 && l_ptr->prev[i] != nullptr; l_ptr = l_ptr->prev[i]);\n            for(;\
    \ r_ptr->height == i + 1 && r_ptr->prev[i] != nullptr; r_ptr = r_ptr->prev[i]);\n\
    \        }\n        return ptr_list;\n    }\n\n    vector<NodePtr> get_child(NodePtr\
    \ ptr, int height){\n        vector<NodePtr> node_vec;\n        if(height == 0)\n\
    \            return node_vec;\n        int diff = ptr->size[height];\n       \
    \ for(; diff; ptr = ptr->next[height - 1]){\n            diff -= ptr->size[height\
    \ - 1];\n            node_vec.emplace_back(ptr);\n        }\n        return node_vec;\n\
    \    }\n\n    void eval(NodePtr ptr, int height){\n        U lazy = ptr->lazy[height];\n\
    \        if(lazy == op_u)\n            return;\n        ptr->sum[height] = get_val(ptr,\
    \ height);\n        vector<NodePtr> child_list = get_child(ptr, height);\n   \
    \     for(auto child : child_list)\n            child->lazy[height - 1] = h(child->lazy[height\
    \ - 1], lazy);\n        ptr->lazy[height] = op_u;\n    }\n\n    T get(int idx){\n\
    \        NodePtr ptr = access(idx);\n        vector<pair<NodePtr, int>> node_list\
    \ = get_list(ptr);\n        T sum = node_list[0].first->sum[0];\n        for(int\
    \ i = node_list.size() - 1; i >= 0; --i){\n            NodePtr node = node_list[i].first;\n\
    \            int height = node_list[i].second;\n            sum = g(sum, node->lazy[height],\
    \ node->size[height]);\n        }\n        return sum;\n    }\n\n    T get(int\
    \ l, int r){\n        NodePtr l_ptr = access(l);\n        NodePtr r_ptr;\n   \
    \     vector<pair<NodePtr, int>> segment_list;\n        tie(r_ptr, segment_list)\
    \ = kth_next(l_ptr, r - l);\n        r_ptr = r_ptr->prev[0];\n        vector<pair<NodePtr,\
    \ int>> ptr_list = get_list(l_ptr, r_ptr);\n        for(int i = ptr_list.size()\
    \ - 1; i >= 0; --i)\n            eval(ptr_list[i].first, ptr_list[i].second);\n\
    \        T sum = op_t;\n        for(auto p : segment_list){\n            NodePtr\
    \ ptr = p.first;\n            int height = p.second;\n            sum = f(sum,\
    \ get_val(ptr, height));\n        }\n        return sum;\n    }\n\n    void update(int\
    \ l, int r, U val){\n        NodePtr l_ptr = access(l);\n        NodePtr r_ptr;\n\
    \        vector<pair<NodePtr, int>> segment_list;\n        tie(r_ptr, segment_list)\
    \ = kth_next(l_ptr, r - l);\n        r_ptr = r_ptr->prev[0];\n        vector<pair<NodePtr,\
    \ int>> ptr_list = get_list(l_ptr, r_ptr);\n        for(int i = ptr_list.size()\
    \ - 1; i >= 0; --i)\n            eval(ptr_list[i].first, ptr_list[i].second);\n\
    \        for(auto p : segment_list){\n            int height = p.second;\n   \
    \         NodePtr ptr = p.first;\n            ptr->lazy[height] = h(ptr->lazy[height],\
    \ val);\n        }\n        for(auto p : ptr_list){\n            NodePtr node\
    \ = p.first;\n            int height = p.second;\n            if(!height)\n  \
    \              continue;\n            vector<NodePtr> child_list = get_child(node,\
    \ height);\n            T sum = op_t;\n            for(auto child : child_list)\n\
    \                sum = f(sum, get_val(child, height - 1));\n            node->sum[height]\
    \ = sum;\n        }\n    }\n\n    void print(bool eval_flag = false){\n      \
    \  int idx = -1;\n        for(NodePtr node = front; node != nullptr; node = node->next[0],\
    \ ++idx){\n            if(node == front || node == back)\n                printf(\"\
    \  null: \");\n            else\n                printf(\"%6d: \", eval_flag ?\
    \ get(idx) : node->sum[0]);\n            for(int i = 0; i < node->height; ++i)\n\
    \                printf(\"%2d: \", eval_flag ? get_val(node, i) : node->sum[i]);\n\
    \                // cout << node->size[i] << \" \";\n            cout << endl;\n\
    \        }\n        cout << endl;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/lazyskiplist.cpp
  requiredBy: []
  timestamp: '2020-04-06 15:54:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/skiplist_rsq_raq.test.cpp
  - verify/skiplist_rmq_raq.test.cpp
documentation_of: lib/classes/lazyskiplist.cpp
layout: document
redirect_from:
- /library/lib/classes/lazyskiplist.cpp
- /library/lib/classes/lazyskiplist.cpp.html
title: lib/classes/lazyskiplist.cpp
---
