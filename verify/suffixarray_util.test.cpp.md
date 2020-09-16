---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/stringutils.cpp
    title: lib/classes/stringutils.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/suffixarray
    links:
    - https://judge.yosupo.jp/problem/suffixarray
  bundledCode: "#line 1 \"verify/suffixarray_util.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#line\
    \ 1 \"lib/classes/stringutils.cpp\"\nstruct StringUtils{\n    int n;\n    string\
    \ s;\n    vector<int> sa, sa_inv, lcp, tab_len;\n    vector<vector<int>> lcp_arr;\n\
    \    StringUtils(string _s) : n(_s.size() + 1), s(_s + \"$\"), sa_inv(s.begin(),\
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
    \ tab_len[siz])]);\n    }\n};\n\n#line 8 \"verify/suffixarray_util.test.cpp\"\n\
    \n\nsigned main() {\n\tstring s;\n\tcin >> s;\n\tStringUtils st(s);\n\tint n =\
    \ s.size();\n\tfor(int i = 0; i < n; ++i)\n\t\tcout << st.sa[i + 1] << \" \\n\"\
    [i == n - 1];\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/suffixarray\"\n\n#include\
    \ <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#include \"../lib/classes/stringutils.cpp\"\
    \n\n\nsigned main() {\n\tstring s;\n\tcin >> s;\n\tStringUtils st(s);\n\tint n\
    \ = s.size();\n\tfor(int i = 0; i < n; ++i)\n\t\tcout << st.sa[i + 1] << \" \\\
    n\"[i == n - 1];\n}\n"
  dependsOn:
  - lib/classes/stringutils.cpp
  isVerificationFile: true
  path: verify/suffixarray_util.test.cpp
  requiredBy: []
  timestamp: '2020-09-16 20:37:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/suffixarray_util.test.cpp
layout: document
redirect_from:
- /verify/verify/suffixarray_util.test.cpp
- /verify/verify/suffixarray_util.test.cpp.html
title: verify/suffixarray_util.test.cpp
---
