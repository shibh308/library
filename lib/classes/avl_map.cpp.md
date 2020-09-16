---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/suffixtree.test.cpp
    title: verify/suffixtree.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/avl_map.cpp\"\ntemplate <typename T, typename\
    \ U>\nstruct AVL_map{\n    struct Node{\n        int height;\n        T key;\n\
    \        U val;\n        Node(T key, U val) : key(key), val(val), height(1){c[0]\
    \ = 0; c[1] = 0;}\n        int c[2];\n    };\n    vector<Node> nodes;\n    stack<int>\
    \ st;\n    AVL_map(){\n        nodes.emplace_back(T(), U());\n        nodes[0].height\
    \ = 0;\n    }\n    template <bool inv>\n    int balance_factor(int x){return (nodes[nodes[x].c[0]].height\
    \ - nodes[nodes[x].c[1]].height) * (inv ? -1 : 1);}\n    void _update(int x){\n\
    \        if(x == 0)\n            return;\n        nodes[x].height = max(nodes[nodes[x].c[0]].height,\
    \ nodes[nodes[x].c[1]].height) + 1;\n    }\n    template <bool is_right>\n   \
    \ int rotate(int x){\n        int y = nodes[x].c[1 ^ is_right];\n        nodes[x].c[1\
    \ ^ is_right] = nodes[y].c[0 ^ is_right];\n        nodes[y].c[0 ^ is_right] =\
    \ x;\n        _update(x);\n        _update(y);\n        return y;\n    }\n   \
    \ template <bool inv>\n    int _balance(int x){\n        if(balance_factor<inv>(x)\
    \ == 2){\n            if(balance_factor<inv>(nodes[x].c[0 ^ inv]) < 0)\n     \
    \           nodes[x].c[0 ^ inv] = rotate<inv>(nodes[x].c[0 ^ inv]);\n        \
    \    x = rotate<1 ^ inv>(x);\n        }\n        return x;\n    }\n    int balance(int\
    \ x){\n        x = _balance<false>(x);\n        x = _balance<true>(x);\n     \
    \   _update(x);\n        return x;\n    }\n    int add(int x, T key, U val){\n\
    \        if(x == 0){\n            if(st.empty()){\n                nodes.emplace_back(key,\
    \ val);\n                return nodes.size() - 1;\n            }\n           \
    \ else{\n                int y = st.top();\n                st.pop();\n      \
    \          nodes[y] = Node(key, val);\n                return y;\n           \
    \ }\n        }\n        else if(key == nodes[x].key)\n            nodes[x].val\
    \ = val;\n        else if(key < nodes[x].key)\n            nodes[x].c[0] = add(nodes[x].c[0],\
    \ key, val);\n        else\n            nodes[x].c[1] = add(nodes[x].c[1], key,\
    \ val);\n        x = balance(x);\n        return x;\n    }\n    // \u5B50\u304C\
    \u7247\u65B9\u3057\u304B\u306A\u3044\u6642\u306B\u30CE\u30FC\u30C9\u3092\u524A\
    \u9664\u3059\u308B\n    int _erase_top(int x, bool del){\n        for(int i =\
    \ 0; i < 2; ++i){\n            if(nodes[x].c[i] == 0){\n                int y\
    \ = nodes[x].c[i ^ 1];\n                if(del)\n                    st.push(x);\n\
    \                return y;\n            }\n        }\n    }\n    // \u6700\u5C0F\
    \u306E\u8981\u7D20\u3092dst\u306B\u30B3\u30D4\u30FC\u3057\u3066\u304B\u3089\u524A\
    \u9664\u3059\u308B\n    int _copy_erase(int x, int dst, bool del){\n        if(nodes[x].c[0]\
    \ == 0){\n            nodes[dst].val = nodes[x].val;\n            return _erase_top(x,\
    \ del);\n        }\n        nodes[x].c[0] = _copy_erase(nodes[x].c[0], dst, del);\n\
    \        x = balance(x);\n        return x;\n    }\n    int erase(int x, T key,\
    \ bool del = true){\n        if(key < nodes[x].key)\n            nodes[x].c[0]\
    \ = erase(nodes[x].c[0], key, del);\n        else if(nodes[x].key < key)\n   \
    \         nodes[x].c[1] = erase(nodes[x].c[1], key, del);\n        else{\n   \
    \         if(nodes[x].c[0] == 0 || nodes[x].c[1] == 0)\n                return\
    \ _erase_top(x, del);\n            nodes[x].c[1] = _copy_erase(nodes[x].c[1],\
    \ x, del);\n        }\n        x = balance(x);\n        return x;\n    }\n   \
    \ pair<U, bool> get(int x, T key){\n        if(x == 0)\n            return {U(),\
    \ false};\n        else if(key == nodes[x].key)\n            return {nodes[x].val,\
    \ true};\n        else if(key < nodes[x].key)\n            return get(nodes[x].c[0],\
    \ key);\n        else\n            return get(nodes[x].c[1], key);\n    }\n  \
    \  vector<pair<T, U>> list(int x){\n        vector<pair<T, U>> v;\n        stack<pair<int,bool>>\
    \ sta;\n        sta.emplace(x, false);\n        bool add;\n        while(!sta.empty()){\n\
    \            tie(x, add) = sta.top();\n            sta.pop();\n            if(x\
    \ == 0)\n                continue;\n            if(add)\n                v.emplace_back(nodes[x].key,\
    \ nodes[x].val);\n            else{\n                if(nodes[x].c[1])\n     \
    \               sta.emplace(nodes[x].c[1], false);\n                sta.emplace(x,\
    \ true);\n                if(nodes[x].c[0])\n                    sta.emplace(nodes[x].c[0],\
    \ false);\n            }\n        }\n        return v;\n    }\n};\n"
  code: "template <typename T, typename U>\nstruct AVL_map{\n    struct Node{\n  \
    \      int height;\n        T key;\n        U val;\n        Node(T key, U val)\
    \ : key(key), val(val), height(1){c[0] = 0; c[1] = 0;}\n        int c[2];\n  \
    \  };\n    vector<Node> nodes;\n    stack<int> st;\n    AVL_map(){\n        nodes.emplace_back(T(),\
    \ U());\n        nodes[0].height = 0;\n    }\n    template <bool inv>\n    int\
    \ balance_factor(int x){return (nodes[nodes[x].c[0]].height - nodes[nodes[x].c[1]].height)\
    \ * (inv ? -1 : 1);}\n    void _update(int x){\n        if(x == 0)\n         \
    \   return;\n        nodes[x].height = max(nodes[nodes[x].c[0]].height, nodes[nodes[x].c[1]].height)\
    \ + 1;\n    }\n    template <bool is_right>\n    int rotate(int x){\n        int\
    \ y = nodes[x].c[1 ^ is_right];\n        nodes[x].c[1 ^ is_right] = nodes[y].c[0\
    \ ^ is_right];\n        nodes[y].c[0 ^ is_right] = x;\n        _update(x);\n \
    \       _update(y);\n        return y;\n    }\n    template <bool inv>\n    int\
    \ _balance(int x){\n        if(balance_factor<inv>(x) == 2){\n            if(balance_factor<inv>(nodes[x].c[0\
    \ ^ inv]) < 0)\n                nodes[x].c[0 ^ inv] = rotate<inv>(nodes[x].c[0\
    \ ^ inv]);\n            x = rotate<1 ^ inv>(x);\n        }\n        return x;\n\
    \    }\n    int balance(int x){\n        x = _balance<false>(x);\n        x =\
    \ _balance<true>(x);\n        _update(x);\n        return x;\n    }\n    int add(int\
    \ x, T key, U val){\n        if(x == 0){\n            if(st.empty()){\n      \
    \          nodes.emplace_back(key, val);\n                return nodes.size()\
    \ - 1;\n            }\n            else{\n                int y = st.top();\n\
    \                st.pop();\n                nodes[y] = Node(key, val);\n     \
    \           return y;\n            }\n        }\n        else if(key == nodes[x].key)\n\
    \            nodes[x].val = val;\n        else if(key < nodes[x].key)\n      \
    \      nodes[x].c[0] = add(nodes[x].c[0], key, val);\n        else\n         \
    \   nodes[x].c[1] = add(nodes[x].c[1], key, val);\n        x = balance(x);\n \
    \       return x;\n    }\n    // \u5B50\u304C\u7247\u65B9\u3057\u304B\u306A\u3044\
    \u6642\u306B\u30CE\u30FC\u30C9\u3092\u524A\u9664\u3059\u308B\n    int _erase_top(int\
    \ x, bool del){\n        for(int i = 0; i < 2; ++i){\n            if(nodes[x].c[i]\
    \ == 0){\n                int y = nodes[x].c[i ^ 1];\n                if(del)\n\
    \                    st.push(x);\n                return y;\n            }\n \
    \       }\n    }\n    // \u6700\u5C0F\u306E\u8981\u7D20\u3092dst\u306B\u30B3\u30D4\
    \u30FC\u3057\u3066\u304B\u3089\u524A\u9664\u3059\u308B\n    int _copy_erase(int\
    \ x, int dst, bool del){\n        if(nodes[x].c[0] == 0){\n            nodes[dst].val\
    \ = nodes[x].val;\n            return _erase_top(x, del);\n        }\n       \
    \ nodes[x].c[0] = _copy_erase(nodes[x].c[0], dst, del);\n        x = balance(x);\n\
    \        return x;\n    }\n    int erase(int x, T key, bool del = true){\n   \
    \     if(key < nodes[x].key)\n            nodes[x].c[0] = erase(nodes[x].c[0],\
    \ key, del);\n        else if(nodes[x].key < key)\n            nodes[x].c[1] =\
    \ erase(nodes[x].c[1], key, del);\n        else{\n            if(nodes[x].c[0]\
    \ == 0 || nodes[x].c[1] == 0)\n                return _erase_top(x, del);\n  \
    \          nodes[x].c[1] = _copy_erase(nodes[x].c[1], x, del);\n        }\n  \
    \      x = balance(x);\n        return x;\n    }\n    pair<U, bool> get(int x,\
    \ T key){\n        if(x == 0)\n            return {U(), false};\n        else\
    \ if(key == nodes[x].key)\n            return {nodes[x].val, true};\n        else\
    \ if(key < nodes[x].key)\n            return get(nodes[x].c[0], key);\n      \
    \  else\n            return get(nodes[x].c[1], key);\n    }\n    vector<pair<T,\
    \ U>> list(int x){\n        vector<pair<T, U>> v;\n        stack<pair<int,bool>>\
    \ sta;\n        sta.emplace(x, false);\n        bool add;\n        while(!sta.empty()){\n\
    \            tie(x, add) = sta.top();\n            sta.pop();\n            if(x\
    \ == 0)\n                continue;\n            if(add)\n                v.emplace_back(nodes[x].key,\
    \ nodes[x].val);\n            else{\n                if(nodes[x].c[1])\n     \
    \               sta.emplace(nodes[x].c[1], false);\n                sta.emplace(x,\
    \ true);\n                if(nodes[x].c[0])\n                    sta.emplace(nodes[x].c[0],\
    \ false);\n            }\n        }\n        return v;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/avl_map.cpp
  requiredBy: []
  timestamp: '2020-09-13 14:27:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/suffixtree.test.cpp
documentation_of: lib/classes/avl_map.cpp
layout: document
redirect_from:
- /library/lib/classes/avl_map.cpp
- /library/lib/classes/avl_map.cpp.html
title: lib/classes/avl_map.cpp
---
