---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/yfastttrie2_itp.test.cpp
    title: verify/yfastttrie2_itp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/hashmap_dict.test.cpp
    title: verify/hashmap_dict.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/hashmap_itp.test.cpp
    title: verify/hashmap_itp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/veb2_set.test.cpp
    title: verify/veb2_set.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/xfastttrie_itp.test.cpp
    title: verify/xfastttrie_itp.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/yfastttrie_itp.test.cpp
    title: verify/yfastttrie_itp.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/hashmap.cpp\"\ntemplate <typename T, typename\
    \ U, T del = numeric_limits<T>::max(), T null = numeric_limits<T>::max() - 1>\n\
    struct HashMap{\n    static constexpr __int128_t z = 0xf332ac987401cba5;\n   \
    \ uint64_t n, q, d;\n\n    vector<pair<T, U>> v;\n\n    HashMap() : n(0), q(0),\
    \ d(1),  v(2, make_pair(null, U())){\n    }\n\n    inline uint64_t hash(T key){return\
    \ uint64_t((z * __int128_t(key)) >> (64 - d)) & ((1LL << d) - 1);}\n\n    pair<U,\
    \ bool> find(T x){\n        for(uint64_t i = hash(x); v[i].first != null; i =\
    \ (i + 1) & ((1 << d) - 1))\n            if(v[i].first == x)\n               \
    \ return make_pair(v[i].second, true);\n        return make_pair(U(), false);\n\
    \    }\n\n    bool add(T x, U val){\n        if(find(x).second)\n            return\
    \ false;\n        if(((q + 1) << 1) > (1 << d) || (1 << d) < 3 * n)\n        \
    \    resize();\n        uint64_t i = hash(x);\n        for(; v[i].first != null\
    \ && v[i].first != del; i = (i + 1) & ((1 << d) - 1));\n        q += (v[i].first\
    \ == null);\n        ++n;\n        v[i] = make_pair(x, val);\n        return true;\n\
    \    }\n\n    bool erase(T x){\n        uint64_t i = hash(x);\n        for(; v[i].first\
    \ != null && v[i].first != x; i = (i + 1) & ((1 << d) - 1));\n        if(v[i].first\
    \ == null)\n            return false;\n        --n;\n        v[i] = make_pair(del,\
    \ U());\n        return true;\n    }\n\n    void resize(){\n        ++d;\n   \
    \     vector<pair<T, U>> old_table;\n        q = n;\n        swap(old_table, v);\n\
    \        v.assign(1 << d, make_pair(null, U()));\n        n = 0;\n        for(int\
    \ i = 0; i < old_table.size(); ++i)\n            if(old_table[i].first != null\
    \ && old_table[i].first != del)\n                add(old_table[i].first, old_table[i].second);\n\
    \    }\n};\n\n"
  code: "template <typename T, typename U, T del = numeric_limits<T>::max(), T null\
    \ = numeric_limits<T>::max() - 1>\nstruct HashMap{\n    static constexpr __int128_t\
    \ z = 0xf332ac987401cba5;\n    uint64_t n, q, d;\n\n    vector<pair<T, U>> v;\n\
    \n    HashMap() : n(0), q(0), d(1),  v(2, make_pair(null, U())){\n    }\n\n  \
    \  inline uint64_t hash(T key){return uint64_t((z * __int128_t(key)) >> (64 -\
    \ d)) & ((1LL << d) - 1);}\n\n    pair<U, bool> find(T x){\n        for(uint64_t\
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
    \                add(old_table[i].first, old_table[i].second);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/hashmap.cpp
  requiredBy: []
  timestamp: '2020-04-11 13:18:14+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/yfastttrie2_itp.test.cpp
  - verify/hashmap_dict.test.cpp
  - verify/hashmap_itp.test.cpp
  - verify/veb2_set.test.cpp
  - verify/xfastttrie_itp.test.cpp
  - verify/yfastttrie_itp.test.cpp
documentation_of: lib/classes/hashmap.cpp
layout: document
redirect_from:
- /library/lib/classes/hashmap.cpp
- /library/lib/classes/hashmap.cpp.html
title: lib/classes/hashmap.cpp
---
