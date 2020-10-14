---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/rerooting_diameter.test.cpp
    title: verify/rerooting_diameter.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/functions/rerooting.cpp\"\ntemplate <typename T>\n//\
    \ T f(T, T): \u5B50\u306E\u7D2F\u7A4D\u306B\u4F7F\u3046\u3082\u306E \u76F4\u5F84\
    \u306A\u3089f(x, y): max(x, y)\n// T g(T, int): \u5B50\u306E\u7D2F\u7A4D\u3092\
    \u5143\u306B\u9069\u7528\u3059\u308B\u969B\u306B\u4F7F\u3046\u3082\u306E \u76F4\
    \u5F84\u306A\u3089g(x, idx): x + 1\nvector<T> rerooting(vector<vector<int>>& edges,\
    \ vector<T> v, function<T(T, T)> f, function<T(T, int)> g, T op){\n    int n =\
    \ edges.size();\n    vector<int> visit(n, 0);\n    vector<T> dp1(v), dp2(n);\n\
    \    vector<vector<int>> childs(n);\n    vector<vector<T>> child_val(n), child_l(n),\
    \ child_r(n);\n    function<void(int)> f1 = [&](int x){\n        visit[x] = true;\n\
    \        T res = op;\n        for(auto y : edges[x]){\n            if(visit[y])\n\
    \                continue;\n            f1(y);\n            childs[x].push_back(y);\n\
    \            child_val[x].push_back(dp1[y]);\n            res = f(res, dp1[y]);\n\
    \        }\n        dp1[x] = g(res, x);\n        child_l[x].push_back(op);\n \
    \       child_r[x].push_back(op);\n        for(int i = 0; i < childs[x].size();\
    \ ++i){\n            child_l[x].push_back(f(child_l[x].back(), child_val[x][i]));\n\
    \            child_r[x].push_back(f(child_r[x].back(), child_val[x][childs[x].size()\
    \ - i - 1]));\n        }\n    };\n    f1(0);\n    function<void(int, T)> f2 =\
    \ [&](int x, T par_val){\n        T res = par_val;\n        for(int i = 0; i <\
    \ childs[x].size(); ++i){\n            int y = childs[x][i];\n            auto\
    \ p = f(par_val, f(child_l[x][i], child_r[x][childs[x].size() - i - 1]));\n  \
    \          T val = g(f(par_val, f(child_l[x][i], child_r[x][childs[x].size() -\
    \ i - 1])), y);\n            res = f(res, dp1[y]);\n            f2(y, val);\n\
    \        }\n        dp2[x] = g(res, x);\n    };\n    f2(0, op);\n    return dp2;\n\
    };\n"
  code: "template <typename T>\n// T f(T, T): \u5B50\u306E\u7D2F\u7A4D\u306B\u4F7F\
    \u3046\u3082\u306E \u76F4\u5F84\u306A\u3089f(x, y): max(x, y)\n// T g(T, int):\
    \ \u5B50\u306E\u7D2F\u7A4D\u3092\u5143\u306B\u9069\u7528\u3059\u308B\u969B\u306B\
    \u4F7F\u3046\u3082\u306E \u76F4\u5F84\u306A\u3089g(x, idx): x + 1\nvector<T> rerooting(vector<vector<int>>&\
    \ edges, vector<T> v, function<T(T, T)> f, function<T(T, int)> g, T op){\n   \
    \ int n = edges.size();\n    vector<int> visit(n, 0);\n    vector<T> dp1(v), dp2(n);\n\
    \    vector<vector<int>> childs(n);\n    vector<vector<T>> child_val(n), child_l(n),\
    \ child_r(n);\n    function<void(int)> f1 = [&](int x){\n        visit[x] = true;\n\
    \        T res = op;\n        for(auto y : edges[x]){\n            if(visit[y])\n\
    \                continue;\n            f1(y);\n            childs[x].push_back(y);\n\
    \            child_val[x].push_back(dp1[y]);\n            res = f(res, dp1[y]);\n\
    \        }\n        dp1[x] = g(res, x);\n        child_l[x].push_back(op);\n \
    \       child_r[x].push_back(op);\n        for(int i = 0; i < childs[x].size();\
    \ ++i){\n            child_l[x].push_back(f(child_l[x].back(), child_val[x][i]));\n\
    \            child_r[x].push_back(f(child_r[x].back(), child_val[x][childs[x].size()\
    \ - i - 1]));\n        }\n    };\n    f1(0);\n    function<void(int, T)> f2 =\
    \ [&](int x, T par_val){\n        T res = par_val;\n        for(int i = 0; i <\
    \ childs[x].size(); ++i){\n            int y = childs[x][i];\n            auto\
    \ p = f(par_val, f(child_l[x][i], child_r[x][childs[x].size() - i - 1]));\n  \
    \          T val = g(f(par_val, f(child_l[x][i], child_r[x][childs[x].size() -\
    \ i - 1])), y);\n            res = f(res, dp1[y]);\n            f2(y, val);\n\
    \        }\n        dp2[x] = g(res, x);\n    };\n    f2(0, op);\n    return dp2;\n\
    };\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/functions/rerooting.cpp
  requiredBy: []
  timestamp: '2020-03-30 02:03:55+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/rerooting_diameter.test.cpp
documentation_of: lib/functions/rerooting.cpp
layout: document
redirect_from:
- /library/lib/functions/rerooting.cpp
- /library/lib/functions/rerooting.cpp.html
title: lib/functions/rerooting.cpp
---
