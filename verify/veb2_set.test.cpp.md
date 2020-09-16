---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/hashmap.cpp
    title: lib/classes/hashmap.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/vanemdeboastree2.cpp
    title: lib/classes/vanemdeboastree2.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B
  bundledCode: "#line 1 \"verify/veb2_set.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n#line 1 \"lib/classes/hashmap.cpp\"\ntemplate <typename T, typename U, T del\
    \ = numeric_limits<T>::max(), T null = numeric_limits<T>::max() - 1>\nstruct HashMap{\n\
    \    static constexpr __int128_t z = 0xf332ac987401cba5;\n    uint64_t n, q, d;\n\
    \n    vector<pair<T, U>> v;\n\n    HashMap() : n(0), q(0), d(1),  v(2, make_pair(null,\
    \ U())){\n    }\n\n    inline uint64_t hash(T key){return uint64_t((z * __int128_t(key))\
    \ >> (64 - d)) & ((1LL << d) - 1);}\n\n    pair<U, bool> find(T x){\n        for(uint64_t\
    \ i = hash(x); v[i].first != null; i = (i + 1) & ((1 << d) - 1))\n           \
    \ if(v[i].first == x)\n                return make_pair(v[i].second, true);\n\
    \        return make_pair(U(), false);\n    }\n\n    bool add(T x, U val){\n \
    \       if(find(x).second)\n            return false;\n        if(((q + 1) <<\
    \ 1) > (1 << d) || (1 << d) < 3 * n)\n            resize();\n        uint64_t\
    \ i = hash(x);\n        for(; v[i].first != null && v[i].first != del; i = (i\
    \ + 1) & ((1 << d) - 1));\n        q += (v[i].first == null);\n        ++n;\n\
    \        v[i] = make_pair(x, val);\n        return true;\n    }\n\n    bool erase(T\
    \ x){\n        uint64_t i = hash(x);\n        for(; v[i].first != null && v[i].first\
    \ != x; i = (i + 1) & ((1 << d) - 1));\n        if(v[i].first == null)\n     \
    \       return false;\n        --n;\n        v[i] = make_pair(del, U());\n   \
    \     return true;\n    }\n\n    void resize(){\n        ++d;\n        vector<pair<T,\
    \ U>> old_table;\n        q = n;\n        swap(old_table, v);\n        v.assign(1\
    \ << d, make_pair(null, U()));\n        n = 0;\n        for(int i = 0; i < old_table.size();\
    \ ++i)\n            if(old_table[i].first != null && old_table[i].first != del)\n\
    \                add(old_table[i].first, old_table[i].second);\n    }\n};\n\n\
    #line 1 \"lib/classes/vanemdeboastree2.cpp\"\n// \u5FC5\u8981\u306A\u6240\u3060\
    \u3051\u4F5C\u308BvEB\u6728\ntemplate <uint32_t W, uint64_t NULL_FLAG = ~0uLL>\n\
    struct VanEmdeBoasTree{\n\n    struct Node{\n        uint64_t u, ma, mi;\n   \
    \     Node* aux;\n        HashMap<int, Node*> c;\n        Node(int u) : u(u),\
    \ mi(NULL_FLAG), ma(0){\n            if(u)\n                aux = new Node(u -\
    \ 1);\n        }\n    };\n    Node* root;\n    VanEmdeBoasTree(){\n        root\
    \ = new Node(64 - __builtin_clzll(W - 1));\n        insert((1uLL << W) - 1, root);\n\
    \    }\n\n    Node* child(Node* ptr, uint64_t idx){\n        assert(ptr->u > 0);\n\
    \        auto res = ptr->c.find(idx);\n        if(res.second)\n            return\
    \ res.first;\n        ptr->c.add(idx, new Node(ptr->u - 1));\n        return ptr->c.find(idx).first;\n\
    \    }\n\n    bool insert(uint64_t key, Node* ptr = nullptr){\n        if(ptr\
    \ == nullptr)\n            ptr = root;\n        if(ptr->u == 0){\n           \
    \ bool fl = (ptr->ma < key) || (key < ptr->mi);\n            ptr->ma = max(ptr->ma,\
    \ key);\n            ptr->mi = min(ptr->mi, key);\n            return fl;\n  \
    \      }\n        if(ptr->mi > ptr->ma){\n            ptr->mi = ptr->ma = key;\n\
    \            return true;\n        }\n        if(key < ptr->mi){\n           \
    \ swap(key, ptr->mi);\n        }\n        else if(ptr->mi == key)\n          \
    \  return false;\n        if(ptr->ma < key)\n            ptr->ma = key;\n\n  \
    \      int shift_cnt = 1 << (ptr->u - 1);\n        uint64_t idx = key >> shift_cnt;\n\
    \        uint64_t next_key = key & ((1uLL << shift_cnt) - 1);\n\n        if(child(ptr,\
    \ idx)->mi > child(ptr, idx)->ma)\n            insert(idx, ptr->aux);\n      \
    \  return insert(next_key, child(ptr, idx));\n    }\n\n    bool erase(uint64_t\
    \ key, Node* ptr = nullptr){\n        if(ptr == nullptr)\n            ptr = root;\n\
    \        if(ptr->mi > ptr->ma)\n            return false;\n        if(ptr->mi\
    \ == ptr->ma){\n            if(ptr->mi == key){\n                ptr->mi = NULL_FLAG;\n\
    \                ptr->ma = 0;\n                return true;\n            }\n \
    \           return false;\n        }\n        if(ptr->u == 0){\n            //\
    \ 2\u8981\u7D20\u3042\u308B\u3046\u3061\u306E1\u8981\u7D20\u304C\u6B8B\u308B\n\
    \            assert(ptr->mi == key || ptr->ma == key);\n            uint64_t x\
    \ = ptr->mi == key ? ptr->ma : ptr->mi;\n            ptr->mi = ptr->ma = x;\n\
    \            return true;\n        }\n        int shift_cnt = 1 << (ptr->u - 1);\n\
    \        if(ptr->mi == key)\n            ptr->mi = key = ((ptr->aux->mi << shift_cnt)\
    \ | child(ptr, ptr->aux->mi)->mi);\n\n        uint64_t idx = uint64_t(key) >>\
    \ shift_cnt;\n        uint64_t next_key = key & ((1uLL << shift_cnt) - 1);\n \
    \       auto nex = child(ptr, idx);\n        if(erase(next_key, nex)){\n     \
    \       if(nex->mi > nex->ma)\n                erase(idx, ptr->aux);\n       \
    \     if(ptr->ma == key){\n                if(ptr->aux->mi > ptr->aux->ma)\n \
    \                   ptr->ma = ptr->mi;\n                else\n               \
    \     ptr->ma = ((ptr->aux->ma << shift_cnt) | child(ptr, ptr->aux->ma)->ma);\n\
    \            }\n            return true;\n        }\n        else\n          \
    \  return false;\n    }\n\n    uint32_t lower_bound(uint64_t key, Node* ptr =\
    \ nullptr){\n        if(ptr == nullptr)\n            ptr = root;\n        if(ptr->u\
    \ == 0){\n            assert(key <= ptr->ma);\n            return key <= ptr->mi\
    \ ? ptr->mi : ptr->ma;\n        }\n        if(key <= ptr->mi){\n            assert(ptr->mi\
    \ != NULL_FLAG);\n            return ptr->mi;\n        }\n        int shift_cnt\
    \ = 1 << (ptr->u - 1);\n        uint64_t idx = uint64_t(key) >> shift_cnt;\n \
    \       uint64_t next_key = key & ((1uLL << shift_cnt) - 1);\n\n        auto nex\
    \ = child(ptr, idx);\n        if(nex->mi != NULL_FLAG && next_key <= nex->ma){\n\
    \            return (idx << shift_cnt) | lower_bound(next_key, nex);\n       \
    \ }\n\n        uint64_t i = lower_bound(idx + 1, ptr->aux);\n        return (i\
    \ << shift_cnt) | child(ptr, i)->mi;\n    }\n};\n\n#line 10 \"verify/veb2_set.test.cpp\"\
    \n\nsigned main(){\n    int n;\n    cin >> n;\n    VanEmdeBoasTree<32> b;\n  \
    \  vector<int> type(n);\n    vector<int> v(n, 0);\n    for(int i = 0; i < n; ++i)\n\
    \        scanf(\"%d%d\", &type[i], &v[i]);\n\n    int m = 0;\n\n    for(int i\
    \ = 0; i < n; ++i){\n        int x = v[i];\n        if(type[i] == 0){\n      \
    \      m += b.insert(x);\n            printf(\"%d\\n\", m);\n        }\n     \
    \   else if(type[i] == 1){\n            printf(\"%d\\n\", b.lower_bound(x) ==\
    \ x);\n        }\n        else if(type[i] == 2){\n            m -= b.erase(x);\n\
    \        }\n    }\n}\n\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n#include \"../lib/classes/hashmap.cpp\"\n#include \"../lib/classes/vanemdeboastree2.cpp\"\
    \n\nsigned main(){\n    int n;\n    cin >> n;\n    VanEmdeBoasTree<32> b;\n  \
    \  vector<int> type(n);\n    vector<int> v(n, 0);\n    for(int i = 0; i < n; ++i)\n\
    \        scanf(\"%d%d\", &type[i], &v[i]);\n\n    int m = 0;\n\n    for(int i\
    \ = 0; i < n; ++i){\n        int x = v[i];\n        if(type[i] == 0){\n      \
    \      m += b.insert(x);\n            printf(\"%d\\n\", m);\n        }\n     \
    \   else if(type[i] == 1){\n            printf(\"%d\\n\", b.lower_bound(x) ==\
    \ x);\n        }\n        else if(type[i] == 2){\n            m -= b.erase(x);\n\
    \        }\n    }\n}\n\n"
  dependsOn:
  - lib/classes/hashmap.cpp
  - lib/classes/vanemdeboastree2.cpp
  isVerificationFile: true
  path: verify/veb2_set.test.cpp
  requiredBy: []
  timestamp: '2020-04-13 20:50:20+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/veb2_set.test.cpp
layout: document
redirect_from:
- /verify/verify/veb2_set.test.cpp
- /verify/verify/veb2_set.test.cpp.html
title: verify/veb2_set.test.cpp
---
