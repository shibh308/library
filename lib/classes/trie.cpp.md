---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/trie.cpp\"\ntemplate <int size = 26, int start\
    \ = 'a'>\nstruct Trie{\n    struct Node{\n        // \u5024, prefix\u306B\u542B\
    \u3080\u6587\u5B57\u5217\u306E\u6570, \u6587\u5B57\u5217\u306E\u6570\n       \
    \ int val, len, cnt, exist_cnt;\n        // \u5B50\u306Eindex, \u5B50\u306E(index\u306E\
    )\u4E00\u89A7\n        vector<int> next, exist;\n        Node(int val = -1, int\
    \ len = 0, bool back = false) : val(val), len(len), cnt(0), exist_cnt(back), next(size,\
    \ -1){}\n    };\n\n    vector<Node> nodes;\n    Trie() : nodes(1){}\n\n    int\
    \ insert(string& s, int str_index = 0){\n        int pos = 0, idx = str_index;\n\
    \        while(idx != s.size()){\n            ++nodes[pos].cnt;\n            int\
    \ c = s[idx] - start;\n            assert(c < size);\n\n            if(nodes[pos].next[c]\
    \ == -1){\n                nodes[pos].next[c] = nodes.size();\n              \
    \  nodes[pos].exist.emplace_back(nodes.size());\n                nodes.emplace_back(c,\
    \ nodes[pos].len + 1);\n            }\n            pos = nodes[pos].next[c];\n\
    \            ++idx;\n        }\n        ++nodes[pos].cnt;\n        ++nodes[pos].exist_cnt;\n\
    \        return pos;\n    }\n\n    // (s\u306E\u90E8\u5206\u6587\u5B57\u5217,\
    \ s, s\u3092\u90E8\u5206\u6587\u5B57\u5217\u306B\u542B\u3080\u6587\u5B57\u5217\
    )\u306B\u5BFE\u3057\u3066\u95A2\u6570\u3092\u5B9F\u884C\u3059\u308B\n    // \u30E9\
    \u30E0\u30C0\u5185\u3067trie.nodes[idx].exist_cnt\u3092\u5224\u5B9A\u3059\u308B\
    \u4E8B\u3067, \u633F\u5165\u3055\u308C\u305F\u6587\u5B57\u5217\u305D\u306E\u3082\
    \u306E\u4EE5\u5916\u5224\u5B9A\u3057\u306A\u304F\u306A\u308B\n    void query(string&\
    \ s, function<void(int, string&)> f, bool from_prefix, bool correct, bool to_prefix,\
    \ int str_index = 0){\n        int pos = 0, idx = str_index;\n        string str;\n\
    \        while(idx != s.size()){\n            if(from_prefix)\n              \
    \  f(pos, str);\n            int c = s[idx] - start;\n            assert(c < size);\n\
    \n            if(nodes[pos].next[c] == -1)\n                return ;\n       \
    \     pos = nodes[pos].next[c];\n            str += static_cast<char>(nodes[pos].val\
    \ + start);\n            ++idx;\n        }\n        if(correct)\n            f(pos,\
    \ str);\n        function<void(int)> dfs = [&](int pos){\n            for(auto&\
    \ next : nodes[pos].exist){\n                char c = nodes[next].val + start;\n\
    \                if(to_prefix)\n                    f(pos, str);\n           \
    \     str += c;\n                dfs(next);\n                str.pop_back();\n\
    \            }\n        };\n        dfs(pos);\n    }\n};\n\n"
  code: "template <int size = 26, int start = 'a'>\nstruct Trie{\n    struct Node{\n\
    \        // \u5024, prefix\u306B\u542B\u3080\u6587\u5B57\u5217\u306E\u6570, \u6587\
    \u5B57\u5217\u306E\u6570\n        int val, len, cnt, exist_cnt;\n        // \u5B50\
    \u306Eindex, \u5B50\u306E(index\u306E)\u4E00\u89A7\n        vector<int> next,\
    \ exist;\n        Node(int val = -1, int len = 0, bool back = false) : val(val),\
    \ len(len), cnt(0), exist_cnt(back), next(size, -1){}\n    };\n\n    vector<Node>\
    \ nodes;\n    Trie() : nodes(1){}\n\n    int insert(string& s, int str_index =\
    \ 0){\n        int pos = 0, idx = str_index;\n        while(idx != s.size()){\n\
    \            ++nodes[pos].cnt;\n            int c = s[idx] - start;\n        \
    \    assert(c < size);\n\n            if(nodes[pos].next[c] == -1){\n        \
    \        nodes[pos].next[c] = nodes.size();\n                nodes[pos].exist.emplace_back(nodes.size());\n\
    \                nodes.emplace_back(c, nodes[pos].len + 1);\n            }\n \
    \           pos = nodes[pos].next[c];\n            ++idx;\n        }\n       \
    \ ++nodes[pos].cnt;\n        ++nodes[pos].exist_cnt;\n        return pos;\n  \
    \  }\n\n    // (s\u306E\u90E8\u5206\u6587\u5B57\u5217, s, s\u3092\u90E8\u5206\u6587\
    \u5B57\u5217\u306B\u542B\u3080\u6587\u5B57\u5217)\u306B\u5BFE\u3057\u3066\u95A2\
    \u6570\u3092\u5B9F\u884C\u3059\u308B\n    // \u30E9\u30E0\u30C0\u5185\u3067trie.nodes[idx].exist_cnt\u3092\
    \u5224\u5B9A\u3059\u308B\u4E8B\u3067, \u633F\u5165\u3055\u308C\u305F\u6587\u5B57\
    \u5217\u305D\u306E\u3082\u306E\u4EE5\u5916\u5224\u5B9A\u3057\u306A\u304F\u306A\
    \u308B\n    void query(string& s, function<void(int, string&)> f, bool from_prefix,\
    \ bool correct, bool to_prefix, int str_index = 0){\n        int pos = 0, idx\
    \ = str_index;\n        string str;\n        while(idx != s.size()){\n       \
    \     if(from_prefix)\n                f(pos, str);\n            int c = s[idx]\
    \ - start;\n            assert(c < size);\n\n            if(nodes[pos].next[c]\
    \ == -1)\n                return ;\n            pos = nodes[pos].next[c];\n  \
    \          str += static_cast<char>(nodes[pos].val + start);\n            ++idx;\n\
    \        }\n        if(correct)\n            f(pos, str);\n        function<void(int)>\
    \ dfs = [&](int pos){\n            for(auto& next : nodes[pos].exist){\n     \
    \           char c = nodes[next].val + start;\n                if(to_prefix)\n\
    \                    f(pos, str);\n                str += c;\n               \
    \ dfs(next);\n                str.pop_back();\n            }\n        };\n   \
    \     dfs(pos);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/trie.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/trie.cpp
layout: document
redirect_from:
- /library/lib/classes/trie.cpp
- /library/lib/classes/trie.cpp.html
title: lib/classes/trie.cpp
---
