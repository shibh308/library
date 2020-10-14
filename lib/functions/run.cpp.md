---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/runenumerate.test.cpp
    title: verify/runenumerate.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/functions/run.cpp\"\nstruct RunInfo{\n    // (t, l,\
    \ r) \u306E\u5F62\u3067\u8FD4\u3059 t\u306F\u6700\u5C0F\u5468\u671F\u30670-indexed\u534A\
    \u958B\u533A\u9593\n    set<tuple<int,int,int>> run;\n    // \u6700\u5927\u306E\
    Lyndon word\u3092\u6301\u3064 [2][n]\u30671\u5074\u304C\u53CD\u8EE2\n    vector<vector<int>>\
    \ l;\n    // Lyndon Factorization (\u958B\u59CB\u4F4D\u7F6E\u5217\u6319)\n   \
    \ vector<int> lyndon_fac;\n};\n\nRunInfo getRunInfo(string s){\n    vector<StringUtils>\
    \ su;\n    int n = s.size();\n    s += \"$\" + string(s.rbegin(), s.rend());\n\
    \    vector<int> v(s.begin(), s.end());\n    su.emplace_back(v);\n    for(int\
    \ i = 0; i < s.size(); ++i)\n        v[i] *= -1;\n    su.emplace_back(v);\n  \
    \  vector<vector<int>> l(2, vector<int>(n, 0));\n    for(int fl = 0; fl < 2; ++fl){\n\
    \        stack<pair<int,int>> st;\n        for(int i = n - 1; i >= 0; --i){\n\
    \            int j = i + 1;\n            while(!st.empty()){\n               \
    \ int x, y;\n                tie(x, y) = st.top();\n                if(!su[fl].le(i,\
    \ j, x, y))\n                    break;\n                j = y;\n            \
    \    st.pop();\n            }\n            l[fl][i] = j;\n            st.emplace(i,\
    \ j);\n        }\n    }\n    set<tuple<int,int,int>> run;\n    for(int fl = 0;\
    \ fl < 2; ++fl){\n        for(int i = 0; i < n; ++i){\n            int j = l[fl][i];\n\
    \            int t = j - i;\n            int l_lcp = su[fl].get_lcp(s.size() -\
    \ j, s.size() - i);\n            int r_lcp = su[fl].get_lcp(i, j);\n         \
    \   int ii = i - l_lcp;\n            int jj = j + r_lcp;\n            if(jj -\
    \ ii >= 2 * t)\n                run.emplace(t, ii, jj);\n        }\n    }\n  \
    \  vector<int> dec;\n    for(int i = 0; i < n; i = l[0][i])\n        dec.emplace_back(i);\n\
    \    return RunInfo{run, l, dec};\n}\n"
  code: "struct RunInfo{\n    // (t, l, r) \u306E\u5F62\u3067\u8FD4\u3059 t\u306F\u6700\
    \u5C0F\u5468\u671F\u30670-indexed\u534A\u958B\u533A\u9593\n    set<tuple<int,int,int>>\
    \ run;\n    // \u6700\u5927\u306ELyndon word\u3092\u6301\u3064 [2][n]\u30671\u5074\
    \u304C\u53CD\u8EE2\n    vector<vector<int>> l;\n    // Lyndon Factorization (\u958B\
    \u59CB\u4F4D\u7F6E\u5217\u6319)\n    vector<int> lyndon_fac;\n};\n\nRunInfo getRunInfo(string\
    \ s){\n    vector<StringUtils> su;\n    int n = s.size();\n    s += \"$\" + string(s.rbegin(),\
    \ s.rend());\n    vector<int> v(s.begin(), s.end());\n    su.emplace_back(v);\n\
    \    for(int i = 0; i < s.size(); ++i)\n        v[i] *= -1;\n    su.emplace_back(v);\n\
    \    vector<vector<int>> l(2, vector<int>(n, 0));\n    for(int fl = 0; fl < 2;\
    \ ++fl){\n        stack<pair<int,int>> st;\n        for(int i = n - 1; i >= 0;\
    \ --i){\n            int j = i + 1;\n            while(!st.empty()){\n       \
    \         int x, y;\n                tie(x, y) = st.top();\n                if(!su[fl].le(i,\
    \ j, x, y))\n                    break;\n                j = y;\n            \
    \    st.pop();\n            }\n            l[fl][i] = j;\n            st.emplace(i,\
    \ j);\n        }\n    }\n    set<tuple<int,int,int>> run;\n    for(int fl = 0;\
    \ fl < 2; ++fl){\n        for(int i = 0; i < n; ++i){\n            int j = l[fl][i];\n\
    \            int t = j - i;\n            int l_lcp = su[fl].get_lcp(s.size() -\
    \ j, s.size() - i);\n            int r_lcp = su[fl].get_lcp(i, j);\n         \
    \   int ii = i - l_lcp;\n            int jj = j + r_lcp;\n            if(jj -\
    \ ii >= 2 * t)\n                run.emplace(t, ii, jj);\n        }\n    }\n  \
    \  vector<int> dec;\n    for(int i = 0; i < n; i = l[0][i])\n        dec.emplace_back(i);\n\
    \    return RunInfo{run, l, dec};\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/run.cpp
  requiredBy: []
  timestamp: '2020-09-17 02:41:23+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/runenumerate.test.cpp
documentation_of: lib/functions/run.cpp
layout: document
redirect_from:
- /library/lib/functions/run.cpp
- /library/lib/functions/run.cpp.html
title: lib/functions/run.cpp
---
