---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/functions/scc.cpp
    title: lib/functions/scc.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/two_sat
    links:
    - https://judge.yosupo.jp/problem/two_sat
  bundledCode: "#line 1 \"verify/2-sat.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#line\
    \ 1 \"lib/functions/scc.cpp\"\nvector<int> scc(vector<vector<int>>& edges){\n\
    \    int n = edges.size();\n    vector<vector<int>> rev(n);\n\n    for(int i =\
    \ 0; i < n; ++i)\n        for(auto& x : edges[i])\n            rev[x].emplace_back(i);\n\
    \n    vector<i64> dfs_num(n, -1);\n    vector<i64> flag(n, 0);\n    int num =\
    \ 0;\n    function<void(int)> dfs = [&](int pos){\n        flag[pos] = 1;\n  \
    \      for(auto& xx : edges[pos])\n            if(!flag[xx]){\n              \
    \  dfs(xx);\n        }\n        dfs_num[pos] = num++;\n    };\n\n    for(int i\
    \ = 0; i < n; ++i)\n        if(!flag[i])\n            dfs(i);\n\n    vector<int>\
    \ dfs_inv(n);\n    for(int i = 0; i < n; ++i)\n        dfs_inv[n - 1 - dfs_num[i]]\
    \ = i;\n\n    num = 0;\n\n    vector<int> scc_vec(n, -1);\n\n    function<void(int)>\
    \ rdfs = [&](int pos){\n        scc_vec[pos] = num;\n        for(auto t : rev[pos])\n\
    \            if(scc_vec[t] == -1)\n                rdfs(t);\n    };\n\n    for(int\
    \ i = 0; i < n; ++i)\n        if(scc_vec[dfs_inv[i]] == -1){\n            rdfs(dfs_inv[i]);\n\
    \            ++num;\n        }\n\n    return scc_vec;\n}\n#line 8 \"verify/2-sat.test.cpp\"\
    \n\n\nsigned main() {\n    string p, cnf;\n    int n, m;\n    cin >> p >> cnf\
    \ >> n >> m;\n    /*\n     x |  y  :  !x =>  y\n     x |  y  :  !y =>  x\n   \
    \ !x |  y  :   x =>  y\n    !x |  y  :  !y => !x\n     x | !y  :   y =>  x\n \
    \    x | !y  :  !x => !y\n    !x | !y  :   x => !y\n    !x | !y  :   y => !x\n\
    \     */\n\n    vector<vector<int>> edges(2 * n);\n\n    for(int i = 0; i < m;\
    \ ++i){\n        int a, b, tmp;\n        cin >> a >> b >> tmp;\n        int x\
    \ = abs(a) - 1;\n        int y = abs(b) - 1;\n        // if x_plus: true\n   \
    \     bool x_plus = (a >= 0);\n        bool y_plus = (b >= 0);\n\n        edges[x\
    \ + (x_plus ? 0 : n)].emplace_back(y + (y_plus ? n : 0));\n        edges[y + (y_plus\
    \ ? 0 : n)].emplace_back(x + (x_plus ? n : 0));\n    }\n    auto ret = scc(edges);\n\
    \n    for(int i = 0; i < n; ++i){\n        if(ret[i] == ret[i + n]){\n       \
    \     cout << \"s UNSATISFIABLE\" << endl;\n\n            return 0;\n        }\n\
    \    }\n\n    cout << \"s SATISFIABLE\" << endl;\n    cout << \"v\";\n\n    for(int\
    \ i = 0; i < n; ++i){\n        cout << \" \" << (ret[i] < ret[i + n] ? 1 : -1)\
    \ * (i + 1);\n    }\n    cout << \" \" << 0 << endl;\n\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/two_sat\"\n\n#include <bits/stdc++.h>\n\
    using namespace std;\nusing i64 = long;\n\n#include \"../lib/functions/scc.cpp\"\
    \n\n\nsigned main() {\n    string p, cnf;\n    int n, m;\n    cin >> p >> cnf\
    \ >> n >> m;\n    /*\n     x |  y  :  !x =>  y\n     x |  y  :  !y =>  x\n   \
    \ !x |  y  :   x =>  y\n    !x |  y  :  !y => !x\n     x | !y  :   y =>  x\n \
    \    x | !y  :  !x => !y\n    !x | !y  :   x => !y\n    !x | !y  :   y => !x\n\
    \     */\n\n    vector<vector<int>> edges(2 * n);\n\n    for(int i = 0; i < m;\
    \ ++i){\n        int a, b, tmp;\n        cin >> a >> b >> tmp;\n        int x\
    \ = abs(a) - 1;\n        int y = abs(b) - 1;\n        // if x_plus: true\n   \
    \     bool x_plus = (a >= 0);\n        bool y_plus = (b >= 0);\n\n        edges[x\
    \ + (x_plus ? 0 : n)].emplace_back(y + (y_plus ? n : 0));\n        edges[y + (y_plus\
    \ ? 0 : n)].emplace_back(x + (x_plus ? n : 0));\n    }\n    auto ret = scc(edges);\n\
    \n    for(int i = 0; i < n; ++i){\n        if(ret[i] == ret[i + n]){\n       \
    \     cout << \"s UNSATISFIABLE\" << endl;\n\n            return 0;\n        }\n\
    \    }\n\n    cout << \"s SATISFIABLE\" << endl;\n    cout << \"v\";\n\n    for(int\
    \ i = 0; i < n; ++i){\n        cout << \" \" << (ret[i] < ret[i + n] ? 1 : -1)\
    \ * (i + 1);\n    }\n    cout << \" \" << 0 << endl;\n\n}\n"
  dependsOn:
  - lib/functions/scc.cpp
  isVerificationFile: true
  path: verify/2-sat.test.cpp
  requiredBy: []
  timestamp: '2020-02-24 19:54:34+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/2-sat.test.cpp
layout: document
redirect_from:
- /verify/verify/2-sat.test.cpp
- /verify/verify/2-sat.test.cpp.html
title: verify/2-sat.test.cpp
---
