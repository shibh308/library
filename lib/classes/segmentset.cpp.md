---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/segmentset.cpp\"\ntemplate <typename T>\nstruct\
    \ SegmentSet{\n    set<pair<T, T>> s;\n    set<pair<T, T>> s_rev;\n    SegmentSet(){}\n\
    \    // [l, r)\u3092\u8FFD\u52A0\u3059\u308B\n    void insert(T l, T r){\n   \
    \     auto iter = get(l).second;\n        if(iter != s.end() && iter->first <=\
    \ l && r <= iter->second)\n            return;\n        vector<pair<T, T>> erase_elm;\n\
    \        for(auto it = s.lower_bound(make_pair(l, numeric_limits<T>::min()));\
    \ it != s.end() && it->first <= r; ++it)\n            erase_elm.emplace_back(*it);\n\
    \        for(auto it = s_rev.lower_bound(make_pair(l, numeric_limits<T>::min()));\
    \ it != s_rev.end() && it->first <= r; ++it)\n            erase_elm.emplace_back(it->second,\
    \ it->first);\n        for(auto& p : erase_elm){\n            chmin(l, p.first);\n\
    \            chmax(r, p.second);\n            s.erase(p);\n            s_rev.erase(make_pair(p.second,\
    \ p.first));\n        }\n        s.emplace(l, r);\n        s_rev.emplace(r, l);\n\
    \    }\n    // x\u304C\u542B\u307E\u308C\u308B\u3088\u3046\u306A\u533A\u9593\u3092\
    \u8FD4\u3059\n    pair<bool, typename set<pair<T, T>>::const_iterator> get(T x){\n\
    \        auto it = s.lower_bound(make_pair(x, numeric_limits<T>::min()));\n  \
    \      if(it != s.begin())\n            --it;\n        return make_pair(x < it->second,\
    \ it);\n    }\n    set<pair<T, T>>& operator*(){return s;}\n};\n\n"
  code: "template <typename T>\nstruct SegmentSet{\n    set<pair<T, T>> s;\n    set<pair<T,\
    \ T>> s_rev;\n    SegmentSet(){}\n    // [l, r)\u3092\u8FFD\u52A0\u3059\u308B\n\
    \    void insert(T l, T r){\n        auto iter = get(l).second;\n        if(iter\
    \ != s.end() && iter->first <= l && r <= iter->second)\n            return;\n\
    \        vector<pair<T, T>> erase_elm;\n        for(auto it = s.lower_bound(make_pair(l,\
    \ numeric_limits<T>::min())); it != s.end() && it->first <= r; ++it)\n       \
    \     erase_elm.emplace_back(*it);\n        for(auto it = s_rev.lower_bound(make_pair(l,\
    \ numeric_limits<T>::min())); it != s_rev.end() && it->first <= r; ++it)\n   \
    \         erase_elm.emplace_back(it->second, it->first);\n        for(auto& p\
    \ : erase_elm){\n            chmin(l, p.first);\n            chmax(r, p.second);\n\
    \            s.erase(p);\n            s_rev.erase(make_pair(p.second, p.first));\n\
    \        }\n        s.emplace(l, r);\n        s_rev.emplace(r, l);\n    }\n  \
    \  // x\u304C\u542B\u307E\u308C\u308B\u3088\u3046\u306A\u533A\u9593\u3092\u8FD4\
    \u3059\n    pair<bool, typename set<pair<T, T>>::const_iterator> get(T x){\n \
    \       auto it = s.lower_bound(make_pair(x, numeric_limits<T>::min()));\n   \
    \     if(it != s.begin())\n            --it;\n        return make_pair(x < it->second,\
    \ it);\n    }\n    set<pair<T, T>>& operator*(){return s;}\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/segmentset.cpp
  requiredBy: []
  timestamp: '2020-03-25 22:20:24+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/segmentset.cpp
layout: document
redirect_from:
- /library/lib/classes/segmentset.cpp
- /library/lib/classes/segmentset.cpp.html
title: lib/classes/segmentset.cpp
---
