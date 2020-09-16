---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/mo.cpp
    title: lib/classes/mo.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425
  bundledCode: "#line 1 \"verify/mo.test.cpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#line 1 \"lib/classes/mo.cpp\"\nstruct Mo{\n    int l, r;\n    function<void(int)>\
    \ left_add, left_erase, right_add, right_erase;\n    Mo(function<void(int)> left_add,\
    \ function<void(int)> left_erase,\n       function<void(int)> right_add, function<void(int)>\
    \ right_erase,\n       int sl = 0, int sr = 0) :\n       l(sl), r(sr), left_add(left_add),\
    \ left_erase(left_erase), right_add(right_add), right_erase(right_erase){}\n \
    \   void move(int next_l, int next_r){\n        for(int i = l; i < next_l; ++i)\n\
    \            left_erase(i);\n        for(int i = l - 1; i >= next_l; --i)\n  \
    \          left_add(i);\n        for(int i = r; i < next_r; ++i)\n           \
    \ right_add(i);\n        for(int i = r - 1; i >= next_r; --i)\n            right_erase(i);\n\
    \        l = next_l, r = next_r;\n    }\n};\n\n#line 10 \"verify/mo.test.cpp\"\
    \n\nsigned main(){\n    int n, k, q;\n    cin >> n >> k >> q;\n    vector<int>\
    \ a(k), b(k);\n    for(int i = 0; i < k; ++i){\n        cin >> a[i] >> b[i];\n\
    \        --a[i], --b[i];\n    }\n    constexpr int packet = 512;\n    constexpr\
    \ int size = (100000 + packet - 1) / packet;\n\n    vector<vector<pair<int,int>>>\
    \ queries(size);\n\n    vector<int> type(q), s(q), t(q), x(q);\n    for(int i\
    \ = 0; i < q; ++i){\n        cin >> type[i] >> s[i] >> t[i] >> x[i];\n       \
    \ --s[i], --x[i];\n        queries[s[i] / packet].emplace_back(t[i], i);\n   \
    \ }\n    for(int i = 0; i < size; ++i)\n        sort(queries[i].begin(), queries[i].end());\n\
    \n\n    vector<int> data(n), idxes(n);\n    iota(data.begin(), data.end(), 0);\n\
    \    iota(idxes.begin(), idxes.end(), 0);\n    auto right_f = [&](int idx){\n\
    \        if(idx >= k)\n            return;\n        swap(data[a[idx]], data[b[idx]]);\n\
    \        idxes[data[a[idx]]] = a[idx];\n        idxes[data[b[idx]]] = b[idx];\n\
    \    };\n    auto left_f = [&](int idx){\n        if(idx >= k)\n            return;\n\
    \        swap(data[idxes[a[idx]]], data[idxes[b[idx]]]);\n        int idx_1 =\
    \ idxes[a[idx]];\n        int data_idx_1 = data[idx_1];\n        int idx_2 = idxes[b[idx]];\n\
    \        int data_idx_2 = data[idx_2];\n        idxes[data_idx_1] = idx_1;\n \
    \       idxes[data_idx_2] = idx_2;\n    };\n    Mo mo(left_f, left_f, right_f,\
    \ right_f);\n\n    vector<int> ans(q, -1);\n\n    for(int i = 0; i < size; ++i){\n\
    \        mo.move(i * packet, i * packet);\n        for(auto& query : queries[i]){\n\
    \            int idx = query.second;\n            int next_l = s[idx];\n     \
    \       int next_r = t[idx];\n            int ty = type[idx];\n            int\
    \ val = x[idx];\n            mo.move(next_l, next_r);\n\n            if(ty ==\
    \ 1){\n                ans[idx] = data[val];\n            }\n            else{\n\
    \                ans[idx] = idxes[val];\n            }\n        }\n    }\n\n \
    \   for(int i = 0; i < q; ++i)\n        cout << ans[i] + 1 << endl;\n\n    return\
    \ 0;\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0425\"\
    \n#include <bits/stdc++.h>\n\nusing namespace std;\n\nusing i64 = long long;\n\
    \n\n#include \"../lib/classes/mo.cpp\"\n\nsigned main(){\n    int n, k, q;\n \
    \   cin >> n >> k >> q;\n    vector<int> a(k), b(k);\n    for(int i = 0; i < k;\
    \ ++i){\n        cin >> a[i] >> b[i];\n        --a[i], --b[i];\n    }\n    constexpr\
    \ int packet = 512;\n    constexpr int size = (100000 + packet - 1) / packet;\n\
    \n    vector<vector<pair<int,int>>> queries(size);\n\n    vector<int> type(q),\
    \ s(q), t(q), x(q);\n    for(int i = 0; i < q; ++i){\n        cin >> type[i] >>\
    \ s[i] >> t[i] >> x[i];\n        --s[i], --x[i];\n        queries[s[i] / packet].emplace_back(t[i],\
    \ i);\n    }\n    for(int i = 0; i < size; ++i)\n        sort(queries[i].begin(),\
    \ queries[i].end());\n\n\n    vector<int> data(n), idxes(n);\n    iota(data.begin(),\
    \ data.end(), 0);\n    iota(idxes.begin(), idxes.end(), 0);\n    auto right_f\
    \ = [&](int idx){\n        if(idx >= k)\n            return;\n        swap(data[a[idx]],\
    \ data[b[idx]]);\n        idxes[data[a[idx]]] = a[idx];\n        idxes[data[b[idx]]]\
    \ = b[idx];\n    };\n    auto left_f = [&](int idx){\n        if(idx >= k)\n \
    \           return;\n        swap(data[idxes[a[idx]]], data[idxes[b[idx]]]);\n\
    \        int idx_1 = idxes[a[idx]];\n        int data_idx_1 = data[idx_1];\n \
    \       int idx_2 = idxes[b[idx]];\n        int data_idx_2 = data[idx_2];\n  \
    \      idxes[data_idx_1] = idx_1;\n        idxes[data_idx_2] = idx_2;\n    };\n\
    \    Mo mo(left_f, left_f, right_f, right_f);\n\n    vector<int> ans(q, -1);\n\
    \n    for(int i = 0; i < size; ++i){\n        mo.move(i * packet, i * packet);\n\
    \        for(auto& query : queries[i]){\n            int idx = query.second;\n\
    \            int next_l = s[idx];\n            int next_r = t[idx];\n        \
    \    int ty = type[idx];\n            int val = x[idx];\n            mo.move(next_l,\
    \ next_r);\n\n            if(ty == 1){\n                ans[idx] = data[val];\n\
    \            }\n            else{\n                ans[idx] = idxes[val];\n  \
    \          }\n        }\n    }\n\n    for(int i = 0; i < q; ++i)\n        cout\
    \ << ans[i] + 1 << endl;\n\n    return 0;\n}\n"
  dependsOn:
  - lib/classes/mo.cpp
  isVerificationFile: true
  path: verify/mo.test.cpp
  requiredBy: []
  timestamp: '2020-03-03 14:01:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/mo.test.cpp
layout: document
redirect_from:
- /verify/verify/mo.test.cpp
- /verify/verify/mo.test.cpp.html
title: verify/mo.test.cpp
---
