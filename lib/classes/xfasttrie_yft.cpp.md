---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
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
  bundledCode: "#line 1 \"lib/classes/xfasttrie_yft.cpp\"\n// y-fast trie\u7528\u306E\
    x-fast trie\ntemplate <typename T, int W = 31, T HASHMAP_NULL = (1LL << W) - 1,\
    \ T HASHMAP_DEL = (1LL << W) - 2>\nstruct XFastTrie_yft{\n    using SplayNode\
    \ = typename SplayTree<T>::NodePtr;\n    struct Node{\n        T val;\n      \
    \  int exist;\n        Node* c[2];\n        SplayNode node;\n        Node(T val)\
    \ : val(val), exist(0), node(nullptr){\n            // \u5B50\u304C\u5B58\u5728\
    \u3059\u308B\u306A\u3089\u5B50\u3078\u306E\u30DD\u30A4\u30F3\u30BF\u3092\u6301\
    \u3064\n            // \u8449\u306A\u3089\u5DE6\u53F3\u306F\u305D\u308C\u305E\u308C\
    prev,next\n            // \u5DE6\u306E\u5B50\u304C\u5B58\u5728\u3057\u306A\u3044\
    \u306A\u3089\u5DE6\u306Fprev\u3078\u306E\u30B7\u30E7\u30FC\u30C8\u30AB\u30C3\u30C8\
    \n            // \u53F3\u306E\u304C\u5B58\u5728\u3057\u306A\u3044\u306A\u3089\u53F3\
    \u306Fnext\u3078\u306E\u30B7\u30E7\u30FC\u30C8\u30AB\u30C3\u30C8\n           \
    \ c[0] = nullptr;\n            c[1] = nullptr;\n        }\n    };\n    int n;\n\
    \    Node* root;\n    Node* front;\n    Node* back;\n    array<HashMap<T, Node*,\
    \ HASHMAP_NULL, HASHMAP_DEL>, W> hashmap;\n\n    XFastTrie_yft() : n(0), hashmap(){\n\
    \        root = new Node(0);\n        front = new Node(0);\n        back = new\
    \ Node(0);\n        front->exist = 2;\n        front->c[1] = back;\n        back->exist\
    \ = 1;\n        back->c[0] = front;\n        root->c[0] = back;\n        root->c[1]\
    \ = front;\n    }\n\n    Node* insert(SplayNode node){\n        T key = node->val;\n\
    \        // \u5B58\u5728\u3057\u3066\u3044\u308B\u30CE\u30FC\u30C9\u306F\u5168\
    \u90E8\u8449\u304C\u3042\u308B\u3068\u4EEE\u5B9A\u3059\u308B\n        T val =\
    \ 0;\n        Node* ptr = root;\n        Node* nex = nullptr;\n        Node* pre\
    \ = nullptr;\n        bool make_flag = false;\n        for(int i = W - 1; i >=\
    \ 0; --i){\n            bool fl = (key >> i) & 1;\n            bool exist = (ptr->exist\
    \ >> fl) & 1;\n            if(fl)\n                val += (1LL << i);\n      \
    \      if(!exist){\n                if(!nex){\n                    if(fl){\n \
    \                       pre = ptr->c[1];\n                        nex = pre->c[1];\n\
    \                    }\n                    else{\n                        nex\
    \ = ptr->c[0];\n                        pre = nex->c[0];\n                   \
    \ }\n                }\n                make_flag = true;\n                ptr->exist\
    \ |= (1 << fl);\n                ptr->c[fl] = new Node(val);\n               \
    \ hashmap[i].add(val, ptr->c[fl]);\n                ptr->c[fl]->c[0] = back;\n\
    \                ptr->c[fl]->c[1] = front;\n            }\n            ptr = ptr->c[fl];\n\
    \        }\n        if(!make_flag)\n            return nullptr;\n        ++n;\n\
    \        assert(nex == back || key < nex->val);\n        assert(pre == front ||\
    \ pre->val < key);\n\n        ptr->node = node;\n        pre->c[1] = ptr;\n  \
    \      ptr->c[1] = nex;\n        nex->c[0] = ptr;\n        ptr->c[0] = pre;\n\
    \        assert(val == key && ptr->val == key);\n\n        Node* new_node = ptr;\n\
    \        ptr = root;\n        for(int i = W - 1; i >= 0; --i){\n            if(!(ptr->exist\
    \ & 1) && (ptr->c[0] == back || key < ptr->c[0]->val)){\n                ptr->c[0]\
    \ = new_node;\n            }\n            if(!(ptr->exist & 2) && (ptr->c[1] ==\
    \ front || ptr->c[1]->val < key)){\n                ptr->c[1] = new_node;\n  \
    \          }\n            ptr = ptr->c[(key >> i) & 1];\n        }\n        return\
    \ new_node;\n    }\n\n    bool erase(T key){\n        Node* ptr = root;\n    \
    \    Node* cut_ptr = nullptr;\n        bool cut_fl = false;\n        stack<Node*>\
    \ node_stack;\n        for(int i = W - 1; i >= 0; --i){\n            bool fl =\
    \ (key >> i) & 1;\n            if(!((ptr->exist >> fl) & 1))\n               \
    \ return false;\n            if((ptr->exist >> (!fl)) & 1){\n                while(!node_stack.empty())node_stack.pop();\n\
    \                cut_ptr = ptr;\n                cut_fl = fl;\n            }\n\
    \            else if(i != W - 1)\n                node_stack.push(ptr);\n    \
    \        ptr = ptr->c[fl];\n        }\n        Node* target = ptr;\n        Node*\
    \ pre = target->c[0];\n        Node* nex = target->c[1];\n        pre->c[1] =\
    \ nex;\n        nex->c[0] = pre;\n        int h = 0;\n        for(int i = 0; !node_stack.empty();\
    \ ++i){\n            Node* node = node_stack.top();\n            hashmap[i + 1].erase(node->val);\n\
    \            node_stack.pop();\n            assert(node != target);\n        }\n\
    \        hashmap[0].erase(key);\n        if(!cut_ptr){\n            *this = XFastTrie_yft();\n\
    \            return true;\n        }\n        cut_ptr->c[cut_fl] = cut_fl ? pre\
    \ : nex;\n        cut_ptr->exist &= ~(1 << cut_fl);\n        ptr = root;\n   \
    \     if(target->val != key)\n            return false;\n        for(int i = W\
    \ - 1; i >= 0; --i){\n            bool fl = (key >> i) & 1;\n            if(ptr->c[0]\
    \ == target){\n                ptr->c[0] = nex;\n            }\n            if(ptr->c[1]\
    \ == target){\n                ptr->c[1] = pre;\n            }\n            if(!(ptr->exist\
    \ & (1 << fl)))\n                break;\n            ptr = ptr->c[fl];\n     \
    \   }\n        --n;\n        delete(target);\n        return true;\n    }\n\n\
    \    Node* lower_bound(T key){\n        Node* ptr = root;\n        int lb = W,\
    \ rb = -1;\n        while(lb - rb > 1){\n            int mid = (lb + rb) >> 1;\n\
    \            bool fl;\n            Node* res;\n            tie(res, fl) = hashmap[mid].find(key\
    \ & ~((1LL << mid) - 1));\n            if(fl)\n                ptr = res;\n  \
    \          (fl ? lb : rb) = mid;\n        }\n        if(!lb)return ptr;\n    \
    \    int fl = (key >> rb) & 1;\n        return fl ? ptr->c[fl]->c[1] : ptr->c[fl];\n\
    \    }\n};\n\n"
  code: "// y-fast trie\u7528\u306Ex-fast trie\ntemplate <typename T, int W = 31,\
    \ T HASHMAP_NULL = (1LL << W) - 1, T HASHMAP_DEL = (1LL << W) - 2>\nstruct XFastTrie_yft{\n\
    \    using SplayNode = typename SplayTree<T>::NodePtr;\n    struct Node{\n   \
    \     T val;\n        int exist;\n        Node* c[2];\n        SplayNode node;\n\
    \        Node(T val) : val(val), exist(0), node(nullptr){\n            // \u5B50\
    \u304C\u5B58\u5728\u3059\u308B\u306A\u3089\u5B50\u3078\u306E\u30DD\u30A4\u30F3\
    \u30BF\u3092\u6301\u3064\n            // \u8449\u306A\u3089\u5DE6\u53F3\u306F\u305D\
    \u308C\u305E\u308Cprev,next\n            // \u5DE6\u306E\u5B50\u304C\u5B58\u5728\
    \u3057\u306A\u3044\u306A\u3089\u5DE6\u306Fprev\u3078\u306E\u30B7\u30E7\u30FC\u30C8\
    \u30AB\u30C3\u30C8\n            // \u53F3\u306E\u304C\u5B58\u5728\u3057\u306A\u3044\
    \u306A\u3089\u53F3\u306Fnext\u3078\u306E\u30B7\u30E7\u30FC\u30C8\u30AB\u30C3\u30C8\
    \n            c[0] = nullptr;\n            c[1] = nullptr;\n        }\n    };\n\
    \    int n;\n    Node* root;\n    Node* front;\n    Node* back;\n    array<HashMap<T,\
    \ Node*, HASHMAP_NULL, HASHMAP_DEL>, W> hashmap;\n\n    XFastTrie_yft() : n(0),\
    \ hashmap(){\n        root = new Node(0);\n        front = new Node(0);\n    \
    \    back = new Node(0);\n        front->exist = 2;\n        front->c[1] = back;\n\
    \        back->exist = 1;\n        back->c[0] = front;\n        root->c[0] = back;\n\
    \        root->c[1] = front;\n    }\n\n    Node* insert(SplayNode node){\n   \
    \     T key = node->val;\n        // \u5B58\u5728\u3057\u3066\u3044\u308B\u30CE\
    \u30FC\u30C9\u306F\u5168\u90E8\u8449\u304C\u3042\u308B\u3068\u4EEE\u5B9A\u3059\
    \u308B\n        T val = 0;\n        Node* ptr = root;\n        Node* nex = nullptr;\n\
    \        Node* pre = nullptr;\n        bool make_flag = false;\n        for(int\
    \ i = W - 1; i >= 0; --i){\n            bool fl = (key >> i) & 1;\n          \
    \  bool exist = (ptr->exist >> fl) & 1;\n            if(fl)\n                val\
    \ += (1LL << i);\n            if(!exist){\n                if(!nex){\n       \
    \             if(fl){\n                        pre = ptr->c[1];\n            \
    \            nex = pre->c[1];\n                    }\n                    else{\n\
    \                        nex = ptr->c[0];\n                        pre = nex->c[0];\n\
    \                    }\n                }\n                make_flag = true;\n\
    \                ptr->exist |= (1 << fl);\n                ptr->c[fl] = new Node(val);\n\
    \                hashmap[i].add(val, ptr->c[fl]);\n                ptr->c[fl]->c[0]\
    \ = back;\n                ptr->c[fl]->c[1] = front;\n            }\n        \
    \    ptr = ptr->c[fl];\n        }\n        if(!make_flag)\n            return\
    \ nullptr;\n        ++n;\n        assert(nex == back || key < nex->val);\n   \
    \     assert(pre == front || pre->val < key);\n\n        ptr->node = node;\n \
    \       pre->c[1] = ptr;\n        ptr->c[1] = nex;\n        nex->c[0] = ptr;\n\
    \        ptr->c[0] = pre;\n        assert(val == key && ptr->val == key);\n\n\
    \        Node* new_node = ptr;\n        ptr = root;\n        for(int i = W - 1;\
    \ i >= 0; --i){\n            if(!(ptr->exist & 1) && (ptr->c[0] == back || key\
    \ < ptr->c[0]->val)){\n                ptr->c[0] = new_node;\n            }\n\
    \            if(!(ptr->exist & 2) && (ptr->c[1] == front || ptr->c[1]->val < key)){\n\
    \                ptr->c[1] = new_node;\n            }\n            ptr = ptr->c[(key\
    \ >> i) & 1];\n        }\n        return new_node;\n    }\n\n    bool erase(T\
    \ key){\n        Node* ptr = root;\n        Node* cut_ptr = nullptr;\n       \
    \ bool cut_fl = false;\n        stack<Node*> node_stack;\n        for(int i =\
    \ W - 1; i >= 0; --i){\n            bool fl = (key >> i) & 1;\n            if(!((ptr->exist\
    \ >> fl) & 1))\n                return false;\n            if((ptr->exist >> (!fl))\
    \ & 1){\n                while(!node_stack.empty())node_stack.pop();\n       \
    \         cut_ptr = ptr;\n                cut_fl = fl;\n            }\n      \
    \      else if(i != W - 1)\n                node_stack.push(ptr);\n          \
    \  ptr = ptr->c[fl];\n        }\n        Node* target = ptr;\n        Node* pre\
    \ = target->c[0];\n        Node* nex = target->c[1];\n        pre->c[1] = nex;\n\
    \        nex->c[0] = pre;\n        int h = 0;\n        for(int i = 0; !node_stack.empty();\
    \ ++i){\n            Node* node = node_stack.top();\n            hashmap[i + 1].erase(node->val);\n\
    \            node_stack.pop();\n            assert(node != target);\n        }\n\
    \        hashmap[0].erase(key);\n        if(!cut_ptr){\n            *this = XFastTrie_yft();\n\
    \            return true;\n        }\n        cut_ptr->c[cut_fl] = cut_fl ? pre\
    \ : nex;\n        cut_ptr->exist &= ~(1 << cut_fl);\n        ptr = root;\n   \
    \     if(target->val != key)\n            return false;\n        for(int i = W\
    \ - 1; i >= 0; --i){\n            bool fl = (key >> i) & 1;\n            if(ptr->c[0]\
    \ == target){\n                ptr->c[0] = nex;\n            }\n            if(ptr->c[1]\
    \ == target){\n                ptr->c[1] = pre;\n            }\n            if(!(ptr->exist\
    \ & (1 << fl)))\n                break;\n            ptr = ptr->c[fl];\n     \
    \   }\n        --n;\n        delete(target);\n        return true;\n    }\n\n\
    \    Node* lower_bound(T key){\n        Node* ptr = root;\n        int lb = W,\
    \ rb = -1;\n        while(lb - rb > 1){\n            int mid = (lb + rb) >> 1;\n\
    \            bool fl;\n            Node* res;\n            tie(res, fl) = hashmap[mid].find(key\
    \ & ~((1LL << mid) - 1));\n            if(fl)\n                ptr = res;\n  \
    \          (fl ? lb : rb) = mid;\n        }\n        if(!lb)return ptr;\n    \
    \    int fl = (key >> rb) & 1;\n        return fl ? ptr->c[fl]->c[1] : ptr->c[fl];\n\
    \    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/xfasttrie_yft.cpp
  requiredBy: []
  timestamp: '2020-04-11 13:43:20+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yfastttrie_itp.test.cpp
  - verify/yfastttrie2_itp.test.cpp
documentation_of: lib/classes/xfasttrie_yft.cpp
layout: document
redirect_from:
- /library/lib/classes/xfasttrie_yft.cpp
- /library/lib/classes/xfasttrie_yft.cpp.html
title: lib/classes/xfasttrie_yft.cpp
---
