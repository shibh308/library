---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/suffixarray_util.test.cpp
    title: verify/suffixarray_util.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/stringutils.cpp\"\nstruct StringUtils{\n   \
    \ int n;\n    string s;\n    vector<int> sa, sa_inv, lcp, tab_len;\n    vector<vector<int>>\
    \ lcp_arr;\n    StringUtils(string _s) : n(_s.size() + 1), s(_s + \"$\"), sa_inv(s.begin(),\
    \ s.end()), sa(n), lcp(n, 0), tab_len(n + 1, 0){\n        vector<int> comp(sa_inv);\n\
    \        sort(comp.begin(), comp.end());\n        comp.erase(unique(comp.begin(),\
    \ comp.end()), comp.end());\n        for(int i = 0; i < n; ++i)\n            sa_inv[i]\
    \ = distance(comp.begin(), lower_bound(comp.begin(), comp.end(), sa_inv[i]));\n\
    \        int m = comp.size();\n        for(int i = 0; m != n; ++i){\n        \
    \    vector<vector<int>> table(m);\n            vector<vector<int>> table2(m);\n\
    \            for(int j = 0; j < n; ++j){\n                table[sa_inv[(j + (1\
    \ << i)) % n]].emplace_back(j);\n            }\n            for(int j = 0; j <\
    \ m; ++j)\n                for(auto idx : table[j]){\n                    table2[sa_inv[idx]].emplace_back(idx);\n\
    \                }\n            pair<int,int> pre{-1, -1};\n            int pm\
    \ = m;\n            m = -1;\n            vector<int> nex(n);\n            for(int\
    \ j = 0; j < pm; ++j)\n                for(auto idx : table2[j]){\n          \
    \          auto p = make_pair(sa_inv[idx], sa_inv[(idx + (1 << i)) % n]);\n  \
    \                  if(p != pre){\n                        m++;\n             \
    \           pre = p;\n                    }\n                    nex[idx] = m;\n\
    \                }\n            sa_inv = move(nex);\n            m++;\n      \
    \  }\n        for(int i = 0; i < n; ++i){\n            sa[sa_inv[i]] = i;\n  \
    \      }\n        int h = 0;\n        for(int i = 0; i < n - 1; ++i){\n      \
    \      int j = sa[sa_inv[i] + 1];\n            if(h)\n                --h;\n \
    \           for(; i + h < n && j + h < n && s[i + h] == s[j + h]; ++h);\n    \
    \        lcp[sa_inv[i]] = h;\n        }\n\n        lcp_arr.emplace_back(lcp);\n\
    \        for(int j = 0; (1 << j) < n; ++j){\n            lcp_arr.emplace_back(n);\n\
    \            for(int i = 0; i < n; ++i)\n                lcp_arr[j + 1][i] = (i\
    \ + (1 << j) < n ? min(lcp_arr[j][i], lcp_arr[j][i + (1 << j)]) : lcp_arr[j][i]);\n\
    \        }\n        for(int i = 2; i <= n; ++i)\n            tab_len[i] = tab_len[i\
    \ >> 1]+ 1;\n    }\n    int get_lcp(int l, int r){\n        int siz = r - l;\n\
    \        return min(lcp_arr[tab_len[siz]][l], lcp_arr[tab_len[siz]][r - (1 <<\
    \ tab_len[siz])]);\n    }\n};\n\n"
  code: "struct StringUtils{\n    int n;\n    string s;\n    vector<int> sa, sa_inv,\
    \ lcp, tab_len;\n    vector<vector<int>> lcp_arr;\n    StringUtils(string _s)\
    \ : n(_s.size() + 1), s(_s + \"$\"), sa_inv(s.begin(), s.end()), sa(n), lcp(n,\
    \ 0), tab_len(n + 1, 0){\n        vector<int> comp(sa_inv);\n        sort(comp.begin(),\
    \ comp.end());\n        comp.erase(unique(comp.begin(), comp.end()), comp.end());\n\
    \        for(int i = 0; i < n; ++i)\n            sa_inv[i] = distance(comp.begin(),\
    \ lower_bound(comp.begin(), comp.end(), sa_inv[i]));\n        int m = comp.size();\n\
    \        for(int i = 0; m != n; ++i){\n            vector<vector<int>> table(m);\n\
    \            vector<vector<int>> table2(m);\n            for(int j = 0; j < n;\
    \ ++j){\n                table[sa_inv[(j + (1 << i)) % n]].emplace_back(j);\n\
    \            }\n            for(int j = 0; j < m; ++j)\n                for(auto\
    \ idx : table[j]){\n                    table2[sa_inv[idx]].emplace_back(idx);\n\
    \                }\n            pair<int,int> pre{-1, -1};\n            int pm\
    \ = m;\n            m = -1;\n            vector<int> nex(n);\n            for(int\
    \ j = 0; j < pm; ++j)\n                for(auto idx : table2[j]){\n          \
    \          auto p = make_pair(sa_inv[idx], sa_inv[(idx + (1 << i)) % n]);\n  \
    \                  if(p != pre){\n                        m++;\n             \
    \           pre = p;\n                    }\n                    nex[idx] = m;\n\
    \                }\n            sa_inv = move(nex);\n            m++;\n      \
    \  }\n        for(int i = 0; i < n; ++i){\n            sa[sa_inv[i]] = i;\n  \
    \      }\n        int h = 0;\n        for(int i = 0; i < n - 1; ++i){\n      \
    \      int j = sa[sa_inv[i] + 1];\n            if(h)\n                --h;\n \
    \           for(; i + h < n && j + h < n && s[i + h] == s[j + h]; ++h);\n    \
    \        lcp[sa_inv[i]] = h;\n        }\n\n        lcp_arr.emplace_back(lcp);\n\
    \        for(int j = 0; (1 << j) < n; ++j){\n            lcp_arr.emplace_back(n);\n\
    \            for(int i = 0; i < n; ++i)\n                lcp_arr[j + 1][i] = (i\
    \ + (1 << j) < n ? min(lcp_arr[j][i], lcp_arr[j][i + (1 << j)]) : lcp_arr[j][i]);\n\
    \        }\n        for(int i = 2; i <= n; ++i)\n            tab_len[i] = tab_len[i\
    \ >> 1]+ 1;\n    }\n    int get_lcp(int l, int r){\n        int siz = r - l;\n\
    \        return min(lcp_arr[tab_len[siz]][l], lcp_arr[tab_len[siz]][r - (1 <<\
    \ tab_len[siz])]);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/stringutils.cpp
  requiredBy: []
  timestamp: '2020-09-16 20:22:56+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/suffixarray_util.test.cpp
documentation_of: lib/classes/stringutils.cpp
layout: document
redirect_from:
- /library/lib/classes/stringutils.cpp
- /library/lib/classes/stringutils.cpp.html
title: lib/classes/stringutils.cpp
---
