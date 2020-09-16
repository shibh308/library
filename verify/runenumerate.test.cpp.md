---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/stringutils.cpp
    title: lib/classes/stringutils.cpp
  - icon: ':heavy_check_mark:'
    path: lib/functions/run.cpp
    title: lib/functions/run.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/runenumerate
    links:
    - https://judge.yosupo.jp/problem/runenumerate
  bundledCode: "#line 1 \"verify/runenumerate.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\n\n#line 1 \"lib/classes/stringutils.cpp\"\
    \nstruct StringUtils{\n    int n;\n    vector<int> s;\n    vector<int> sa, sa_inv,\
    \ lcp, tab_len;\n    vector<vector<int>> lcp_arr;\n    StringUtils(string _s)\
    \ : StringUtils(vector<int>(_s.begin(), _s.end())){}\n    StringUtils(vector<int>\
    \ _s) : n(_s.size() + 1), s(_s), sa(n), lcp(n, 0), tab_len(n + 1, 0){\n      \
    \  s.emplace_back(numeric_limits<int>::min());\n        sa_inv = s;\n        vector<int>\
    \ comp(s);\n        sort(comp.begin(), comp.end());\n        comp.erase(unique(comp.begin(),\
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
    \      }\n        int h = 0;\n        for(int i = 0; i < n; ++i){\n          \
    \  int j = (sa_inv[i] + 1 == n ? n : sa[sa_inv[i] + 1]);\n            if(h)\n\
    \                --h;\n            for(; i + h < n && j + h < n && s[i + h] ==\
    \ s[j + h]; ++h);\n            lcp[sa_inv[i]] = h;\n        }\n        lcp_arr.emplace_back(lcp);\n\
    \        for(int j = 0; (1 << j) < n; ++j){\n            lcp_arr.emplace_back(n);\n\
    \            for(int i = 0; i < n; ++i)\n                lcp_arr[j + 1][i] = (i\
    \ + (1 << j) < n ? min(lcp_arr[j][i], lcp_arr[j][i + (1 << j)]) : lcp_arr[j][i]);\n\
    \        }\n        for(int i = 2; i <= n; ++i)\n            tab_len[i] = tab_len[i\
    \ >> 1] + 1;\n    }\n    // [l1, r1) < [l2, r2)\n    bool le(int l1, int r1, int\
    \ l2, int r2){\n        int len1 = r1 - l1;\n        int len2 = r2 - l2;\n   \
    \     if(get_lcp(l1, l2) >= min(len1, len2))\n            return len1 < len2;\n\
    \        else\n            return sa_inv[l1] < sa_inv[l2];\n    }\n    int get_lcp(int\
    \ l, int r){\n        l = sa_inv[l];\n        r = sa_inv[r];\n        if(l > r)\n\
    \            swap(l, r);\n        else if(l == r){\n            return n - sa[l]\
    \ - 1;\n        }\n        int siz = r - l;\n        return min(lcp_arr[tab_len[siz]][l],\
    \ lcp_arr[tab_len[siz]][r - (1 << tab_len[siz])]);\n    }\n};\n\n#line 1 \"lib/functions/run.cpp\"\
    \nstruct RunInfo{\n    // (t, l, r) \u306E\u5F62\u3067\u8FD4\u3059 t\u306F\u6700\
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
    \    return RunInfo{run, l, dec};\n}\n#line 9 \"verify/runenumerate.test.cpp\"\
    \n\n\nsigned main(){\n    string s;\n    cin >> s;\n    set<tuple<int,int,int>>\
    \ v = getRunInfo(s).run;\n    cout << v.size() << endl;\n    for(auto x : v){\n\
    \        int t, l, r;\n        tie(t, l, r) = x;\n        cout << t << \" \" <<\
    \ l << \" \" << r << endl;\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/runenumerate\"\n#include\
    \ <bits/stdc++.h>\n\nusing namespace std;\n\n\n#include \"../lib/classes/stringutils.cpp\"\
    \n#include \"../lib/functions/run.cpp\"\n\n\nsigned main(){\n    string s;\n \
    \   cin >> s;\n    set<tuple<int,int,int>> v = getRunInfo(s).run;\n    cout <<\
    \ v.size() << endl;\n    for(auto x : v){\n        int t, l, r;\n        tie(t,\
    \ l, r) = x;\n        cout << t << \" \" << l << \" \" << r << endl;\n    }\n\
    }\n"
  dependsOn:
  - lib/classes/stringutils.cpp
  - lib/functions/run.cpp
  isVerificationFile: true
  path: verify/runenumerate.test.cpp
  requiredBy: []
  timestamp: '2020-09-17 02:54:42+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/runenumerate.test.cpp
layout: document
redirect_from:
- /verify/verify/runenumerate.test.cpp
- /verify/verify/runenumerate.test.cpp.html
title: verify/runenumerate.test.cpp
---
