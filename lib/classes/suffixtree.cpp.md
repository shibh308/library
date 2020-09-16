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
  bundledCode: "#line 1 \"lib/classes/suffixtree.cpp\"\nstruct SuffixTree{\n    //\
    \ Weiner\u3067\u306E\u69CB\u7BC9 [0,n)\u304C\u8449 n\u304C\u6839 [n+1,)\u304C\u5185\
    \u90E8\u7BC0\u70B9 \u756A\u5175'$'\n    struct Node{\n        int pos = -1, par\
    \ = -1, par_len = -1, dep = 0, slink = -1;\n        int child = 0, plink = 0;\n\
    \    };\n    AVL_map<char,int> avl;\n    int n;\n    string s;\n    vector<Node>\
    \ nodes;\n    vector<int> sa, sa_inv, lcp;\n    SuffixTree(string& _s) : n(_s.size()\
    \ + 1), s(_s + \"$\"), nodes(_s.size() + 3), sa(n), sa_inv(n), lcp(n){\n     \
    \   nodes[n].slink = n;\n        nodes[n].par = n + 1;\n        nodes[n].par_len\
    \ = 1;\n        for(int i = n - 1; i >= 0; --i)\n            add(i);\n       \
    \ make_sa();\n    }\n    void make_sa(){\n        stack<pair<int,bool>> sta;\n\
    \        int cnt = 0;\n        int lca = 0;\n        sta.emplace(n, false);\n\
    \        int x;\n        bool is_lca;\n        while(!sta.empty()){\n        \
    \    tie(x, is_lca) = sta.top();\n            sta.pop();\n            if(is_lca){\n\
    \                lca = min(lca, x);\n                continue;\n            }\n\
    \            if(x < n){\n                sa[cnt] = x;\n                if(cnt\
    \ > 0)\n                    lcp[cnt - 1] = lca;\n                lca = nodes[x].dep;\n\
    \                sa_inv[x] = cnt++;\n            }\n            auto chi = avl.list(nodes[x].child);\n\
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
    };\n"
  code: "struct SuffixTree{\n    // Weiner\u3067\u306E\u69CB\u7BC9 [0,n)\u304C\u8449\
    \ n\u304C\u6839 [n+1,)\u304C\u5185\u90E8\u7BC0\u70B9 \u756A\u5175'$'\n    struct\
    \ Node{\n        int pos = -1, par = -1, par_len = -1, dep = 0, slink = -1;\n\
    \        int child = 0, plink = 0;\n    };\n    AVL_map<char,int> avl;\n    int\
    \ n;\n    string s;\n    vector<Node> nodes;\n    vector<int> sa, sa_inv, lcp;\n\
    \    SuffixTree(string& _s) : n(_s.size() + 1), s(_s + \"$\"), nodes(_s.size()\
    \ + 3), sa(n), sa_inv(n), lcp(n){\n        nodes[n].slink = n;\n        nodes[n].par\
    \ = n + 1;\n        nodes[n].par_len = 1;\n        for(int i = n - 1; i >= 0;\
    \ --i)\n            add(i);\n        make_sa();\n    }\n    void make_sa(){\n\
    \        stack<pair<int,bool>> sta;\n        int cnt = 0;\n        int lca = 0;\n\
    \        sta.emplace(n, false);\n        int x;\n        bool is_lca;\n      \
    \  while(!sta.empty()){\n            tie(x, is_lca) = sta.top();\n           \
    \ sta.pop();\n            if(is_lca){\n                lca = min(lca, x);\n  \
    \              continue;\n            }\n            if(x < n){\n            \
    \    sa[cnt] = x;\n                if(cnt > 0)\n                    lcp[cnt -\
    \ 1] = lca;\n                lca = nodes[x].dep;\n                sa_inv[x] =\
    \ cnt++;\n            }\n            auto chi = avl.list(nodes[x].child);\n  \
    \          for(int i = chi.size() - 1; i >= 0; --i){\n                sta.emplace(nodes[x].dep,\
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
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/suffixtree.cpp
  requiredBy: []
  timestamp: '2020-09-13 14:27:28+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/suffixtree.test.cpp
documentation_of: lib/classes/suffixtree.cpp
layout: document
redirect_from:
- /library/lib/classes/suffixtree.cpp
- /library/lib/classes/suffixtree.cpp.html
title: lib/classes/suffixtree.cpp
---
