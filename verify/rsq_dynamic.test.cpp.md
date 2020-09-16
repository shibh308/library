---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: lib/classes/dynamicsegmenttree.cpp
    title: lib/classes/dynamicsegmenttree.cpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 1 \"verify/rsq_dynamic.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\
    \n\n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#line\
    \ 1 \"lib/classes/dynamicsegmenttree.cpp\"\ntemplate <typename T>\nstruct Segtree{\n\
    \n    struct SegNode;\n\n    struct SegNode{\n        T val;\n        SegNode*\
    \ l;\n        SegNode* r;\n\n        SegNode(T val) : val(val), l(nullptr), r(nullptr){}\n\
    \    };\n\n    i64 n;\n    function<T(T, T)> f;\n    T op;\n    SegNode* root;\n\
    \n    Segtree(int n_, function<T(T, T)> f, T op) : f(f), op(op){\n        for(n\
    \ = 1; n < n_; n <<= 1);\n        root = new SegNode(op);\n    }\n\n    SegNode*\
    \ getl(SegNode* node, T val){\n        return node->l == nullptr ? node->l = new\
    \ SegNode(val) : node->l;\n    }\n\n    SegNode* getr(SegNode* node, T val){\n\
    \        return node->r == nullptr ? node->r = new SegNode(val) : node->r;\n \
    \   }\n\n    void eval(SegNode* node){\n        node->val = f(node->l == nullptr\
    \ ? op : node->l->val, node->r == nullptr ? op : node->r->val);\n    }\n\n   \
    \ void set(i64 x, T val){\n        assert(0 <= x && x < n);\n\n        SegNode*\
    \ node = root;\n        stack<SegNode*> nodes;\n        i64 l = 0, r = n;\n\n\
    \        while(r - l > 1){\n            nodes.push(node);\n            i64 mid\
    \ = (l + r) >> 1;\n\n            if(x < mid){\n                node = getl(node,\
    \ x);\n                r = mid;\n            }else{\n                node = getr(node,\
    \ x);\n                l = mid;\n            }\n        }\n\n        node->val\
    \ = val;\n        while(!nodes.empty()){\n            eval(nodes.top());\n   \
    \         nodes.pop();\n        }\n    }\n\n    void update(i64 x, T val){\n \
    \       assert(0 <= x && x < n);\n\n        SegNode* node = root;\n        stack<SegNode*>\
    \ nodes;\n        i64 l = 0, r = n;\n\n        while(r - l > 1){\n           \
    \ nodes.push(node);\n            i64 mid = (l + r) >> 1;\n\n            if(x <\
    \ mid){\n                node = getl(node, x);\n                r = mid;\n   \
    \         }else{\n                node = getr(node, x);\n                l = mid;\n\
    \            }\n        }\n\n        node->val = f(node->val, val);\n        while(!nodes.empty()){\n\
    \            eval(nodes.top());\n            nodes.pop();\n        }\n    }\n\n\
    \    T get(i64 x, i64 y, SegNode* node = nullptr, i64 l = 0,  i64 r = 0){\n\n\
    \        if(node == nullptr){\n            node = root;\n            r = n;\n\
    \        }\n\n        if(x <= l && r <= y)\n            return node->val;\n\n\
    \        if(r <= x || y <= l)\n            return op;\n\n        T val_l = op,\
    \ val_r = op;\n        i64 mid = (l + r) >> 1;\n\n        if(node->l != nullptr)\n\
    \            val_l = f(val_l, get(x, y, node->l, l, mid));\n        if(node->r\
    \ != nullptr)\n            val_r = f(get(x, y, node->r, mid, r), val_r);\n\n \
    \       return f(val_l, val_r);\n    }\n\n};\n\n#line 8 \"verify/rsq_dynamic.test.cpp\"\
    \n\n\nsigned main() {\n\n    int n, q;\n    scanf(\"%d%d\", &n, &q);\n\n    Segtree<i64>\
    \ seg(1e9, [](auto x, auto y){return x + y;}, 0);\n    for(int i = 0; i < n; ++i){\n\
    \        int a;\n        cin >> a;\n        seg.set(i, a);\n    }\n    for(int\
    \ i = 0; i < q; ++i){\n        int t, a, c;\n        cin >> t >> a >> c;\n   \
    \     if(t == 0){\n            seg.update(a, c);\n        }\n        else{\n \
    \           cout << seg.get(a, c) << endl;\n        }\n    }\n}\n\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\
    \n#include <bits/stdc++.h>\nusing namespace std;\nusing i64 = long;\n\n#include\
    \ \"../lib/classes/dynamicsegmenttree.cpp\"\n\n\nsigned main() {\n\n    int n,\
    \ q;\n    scanf(\"%d%d\", &n, &q);\n\n    Segtree<i64> seg(1e9, [](auto x, auto\
    \ y){return x + y;}, 0);\n    for(int i = 0; i < n; ++i){\n        int a;\n  \
    \      cin >> a;\n        seg.set(i, a);\n    }\n    for(int i = 0; i < q; ++i){\n\
    \        int t, a, c;\n        cin >> t >> a >> c;\n        if(t == 0){\n    \
    \        seg.update(a, c);\n        }\n        else{\n            cout << seg.get(a,\
    \ c) << endl;\n        }\n    }\n}\n\n"
  dependsOn:
  - lib/classes/dynamicsegmenttree.cpp
  isVerificationFile: true
  path: verify/rsq_dynamic.test.cpp
  requiredBy: []
  timestamp: '2020-02-25 07:58:59+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: verify/rsq_dynamic.test.cpp
layout: document
redirect_from:
- /verify/verify/rsq_dynamic.test.cpp
- /verify/verify/rsq_dynamic.test.cpp.html
title: verify/rsq_dynamic.test.cpp
---
