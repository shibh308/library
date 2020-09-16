---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/avl_map.cpp
    title: lib/classes/avl_map.cpp
  - icon: ':heavy_check_mark:'
    path: lib/classes/suffixtree.cpp
    title: lib/classes/suffixtree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B
  bundledCode: "#line 1 \"verify/suffixtree.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \n\n#include <bits/stdc++.h>\n\nusing namespace std;\n\n\n#line 1 \"lib/classes/avl_map.cpp\"\
    \ntemplate <typename T, typename U>\nstruct AVL_map{\n    struct Node{\n     \
    \   int height;\n        T key;\n        U val;\n        Node(T key, U val) :\
    \ key(key), val(val), height(1){c[0] = 0; c[1] = 0;}\n        int c[2];\n    };\n\
    \    vector<Node> nodes;\n    stack<int> st;\n    AVL_map(){\n        nodes.emplace_back(T(),\
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
    \ false);\n            }\n        }\n        return v;\n    }\n};\n#line 1 \"\
    lib/classes/suffixtree.cpp\"\nstruct SuffixTree{\n    // Weiner\u3067\u306E\u69CB\
    \u7BC9 [0,n)\u304C\u8449 n\u304C\u6839 [n+1,)\u304C\u5185\u90E8\u7BC0\u70B9 \u756A\
    \u5175'$'\n    struct Node{\n        int pos = -1, par = -1, par_len = -1, dep\
    \ = 0, slink = -1;\n        int child = 0, plink = 0;\n    };\n    AVL_map<char,int>\
    \ avl;\n    int n;\n    string s;\n    vector<Node> nodes;\n    vector<int> sa,\
    \ sa_inv, lcp;\n    SuffixTree(string& _s) : n(_s.size() + 1), s(_s + \"$\"),\
    \ nodes(_s.size() + 3), sa(n), sa_inv(n), lcp(n){\n        nodes[n].slink = n;\n\
    \        nodes[n].par = n + 1;\n        nodes[n].par_len = 1;\n        for(int\
    \ i = n - 1; i >= 0; --i)\n            add(i);\n        make_sa();\n    }\n  \
    \  void make_sa(){\n        stack<pair<int,bool>> sta;\n        int cnt = 0;\n\
    \        int lca = 0;\n        sta.emplace(n, false);\n        int x;\n      \
    \  bool is_lca;\n        while(!sta.empty()){\n            tie(x, is_lca) = sta.top();\n\
    \            sta.pop();\n            if(is_lca){\n                lca = min(lca,\
    \ x);\n                continue;\n            }\n            if(x < n){\n    \
    \            sa[cnt] = x;\n                if(cnt > 0)\n                    lcp[cnt\
    \ - 1] = lca;\n                lca = nodes[x].dep;\n                sa_inv[x]\
    \ = cnt++;\n            }\n            auto chi = avl.list(nodes[x].child);\n\
    \            for(int i = chi.size() - 1; i >= 0; --i){\n                sta.emplace(nodes[x].dep,\
    \ true);\n                sta.emplace(chi[i].second, false);\n            }\n\
    \        }\n    }\n    int child(int x, char c){\n        auto res = avl.get(nodes[x].child,\
    \ c);\n        if(res.second)\n            return res.first;\n        else\n \
    \           return -1;\n    }\n    int plink(int x, char c){\n        if(x ==\
    \ n + 1)\n            return n;\n        auto res = avl.get(nodes[x].plink, c);\n\
    \        if(res.second)\n            return res.first;\n        else\n       \
    \     return -1;\n    }\n    void attach(int par, int ch, char c, int len){\n\
    \        nodes[par].child = avl.add(nodes[par].child, c, ch);\n        nodes[ch].par_len\
    \ = len;\n        nodes[ch].par = par;\n        nodes[ch].dep = nodes[par].dep\
    \ + len;\n    }\n    void add(int i){\n        int old = i + 1;\n        vector<int>\
    \ path(1, old);\n        int vlen = s.size() - i;\n        while(plink(old, s[i])\
    \ == -1){\n            vlen -= nodes[old].par_len;\n            old = nodes[old].par;\n\
    \            path.emplace_back(old);\n        }\n        int now = plink(old,\
    \ s[i]);\n        int ch = child(now, s[i + nodes[now].dep]);\n        int old_idx\
    \ = path.size() - 1;\n        if(ch != -1){\n            int idx = nodes.size();\n\
    \            nodes.emplace_back();\n            int pos;\n            for(pos\
    \ = nodes[ch].pos - nodes[ch].par_len; s[pos] == s[i + vlen]; pos += nodes[old].par_len){\n\
    \                old = path[--old_idx];\n                vlen += nodes[old].par_len;\n\
    \            }\n            nodes[idx].pos = pos;\n            attach(now, idx,\
    \ s[nodes[ch].pos - nodes[ch].par_len], nodes[ch].par_len - (nodes[ch].pos - pos));\n\
    \            attach(idx, ch, s[pos], nodes[ch].pos - pos);\n            now =\
    \ idx;\n            nodes[old].plink = avl.add(nodes[old].plink, s[i], idx);\n\
    \            nodes[idx].slink = old;\n        }\n        old = path.front();\n\
    \        nodes[old].plink = avl.add(nodes[old].plink, s[i], i);\n        nodes[i].slink\
    \ = old;\n        attach(now, i, s[i + nodes[now].dep], s.size() - (i + nodes[now].dep));\n\
    \        nodes[i].pos = n;\n    }\n    void print(int st = -1, string t = \"\"\
    ){\n        if(st == -1)\n            st = n;\n        if(st < n){\n         \
    \   cout << st << \": \" << t << endl;\n        }\n        else{\n           \
    \ cout << \"-\" << \": \" << t << endl;\n        }\n        for(auto p : avl.list(nodes[st].child)){\n\
    \            int ch = p.second;\n            t += s.substr(nodes[ch].pos - nodes[ch].par_len,\
    \ nodes[ch].par_len);\n            print(ch, t);\n            t.erase(prev(t.end(),\
    \ nodes[ch].par_len), t.end());\n        }\n    }\n    // \u9014\u4E2D\u3067\u30DE\
    \u30C3\u30C1\u3057\u305F\u5834\u5408\u306F (\u30DE\u30C3\u30C1\u3057\u305F\u8FBA\
    \u306E\u5B50, \u5B50\u5074\u304B\u3089\u306E\u8DDD\u96E2) \u3092\u8FD4\u3059\n\
    \    // \u30CE\u30FC\u30C9\u3067\u30DE\u30C3\u30C1\u3057\u305F\u5834\u5408\u306F\
    \ (\u30DE\u30C3\u30C1\u3057\u305F\u30CE\u30FC\u30C9, 0) \u306B\u306A\u308B\n \
    \   // \u30DE\u30C3\u30C1\u3057\u306A\u304B\u3063\u305F\u3089 (n, 0) \u3092\u8FD4\
    \u3059\n    pair<int,int> match(string t){\n        int i = 0;\n        int x\
    \ = n;\n        auto res = avl.list(nodes[x].child);\n\n        while(i != t.size()){\n\
    \            int ch = child(x, t[i]);\n            if(ch == -1)\n            \
    \    return {-1, -1};\n            for(int j = 0; j < nodes[ch].par_len; ++i,\
    \ ++j){\n                if(i == t.size()){\n                    return {ch, nodes[ch].par_len\
    \ - j};\n                }\n                int k = nodes[ch].pos - nodes[ch].par_len\
    \ + j;\n                if(s[k] != t[i])\n                    return {n, -1};\n\
    \            }\n            x = ch;\n        }\n        return {x, 0};\n    }\n\
    };\n#line 10 \"verify/suffixtree.test.cpp\"\n\n\nsigned main(){\n    string s,\
    \ t;\n    cin >> s >> t;\n    SuffixTree st(s);\n    vector<int> res;\n    res.reserve(s.size());\n\
    \    stack<int> sta;\n    int node = st.match(t).first;\n    sta.push(node);\n\
    \    while(!sta.empty()){\n        int x = sta.top();\n        sta.pop();\n  \
    \      if(x == st.n)\n            continue;\n        if(x < st.n)\n          \
    \  res.emplace_back(x);\n        for(auto p : st.avl.list(st.nodes[x].child)){\n\
    \            sta.push(p.second);\n        }\n    }\n    sort(res.begin(), res.end());\n\
    \    for(auto x : res)\n        printf(\"%d\\n\", x);\n}\n\n\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B\"\
    \n\n#include <bits/stdc++.h>\n\nusing namespace std;\n\n\n#include \"../lib/classes/avl_map.cpp\"\
    \n#include \"../lib/classes/suffixtree.cpp\"\n\n\nsigned main(){\n    string s,\
    \ t;\n    cin >> s >> t;\n    SuffixTree st(s);\n    vector<int> res;\n    res.reserve(s.size());\n\
    \    stack<int> sta;\n    int node = st.match(t).first;\n    sta.push(node);\n\
    \    while(!sta.empty()){\n        int x = sta.top();\n        sta.pop();\n  \
    \      if(x == st.n)\n            continue;\n        if(x < st.n)\n          \
    \  res.emplace_back(x);\n        for(auto p : st.avl.list(st.nodes[x].child)){\n\
    \            sta.push(p.second);\n        }\n    }\n    sort(res.begin(), res.end());\n\
    \    for(auto x : res)\n        printf(\"%d\\n\", x);\n}\n\n\n"
  dependsOn:
  - lib/classes/avl_map.cpp
  - lib/classes/suffixtree.cpp
  isVerificationFile: true
  path: verify/suffixtree.test.cpp
  requiredBy: []
  timestamp: '2020-09-13 14:27:28+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/suffixtree.test.cpp
layout: document
redirect_from:
- /verify/verify/suffixtree.test.cpp
- /verify/verify/suffixtree.test.cpp.html
title: verify/suffixtree.test.cpp
---
