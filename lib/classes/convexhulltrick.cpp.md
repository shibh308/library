---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/convexhulltrick.cpp\"\ntemplate <typename T,\
    \ typename U>\nstruct ConvexHullTrick{\n    // \u4EFB\u610F\u306E2\u95A2\u6570\
    \u3067\u5171\u6709\u70B9\u304C\u9AD8\u30051\u500B\u306A\u3089Elm\u306E\u4E2D\u8EAB\
    \u3092\u9069\u5207\u306B\u5909\u3048\u308C\u3070\u901A\u308B\n\n    struct Elm{\n\
    \        T a, b;\n        U operator()(T x){\n            return a * x + b;\n\
    \        }\n    };\n\n    struct Node{\n        Elm f;\n        Node* l;\n   \
    \     Node* r;\n        Node(Elm elm) : f(elm), l(nullptr), r(nullptr){}\n   \
    \ };\n\n    U _min, _max, _inf;\n    Node* root;\n\n    ConvexHullTrick(U _min,\
    \ U _max, U _inf) :\n        _min(_min),\n        _max(_max),\n        _inf(_inf),\n\
    \        root(nullptr)\n    {\n    }\n\n    Node* _insert(Node* p, T st, T en,\
    \ Elm f){\n        if(!p)\n            return new Node(f);\n        if(p->f(st)\
    \ <= f(st) && p->f(en) <= f(en))\n            return p;\n        if(p->f(st) >=\
    \ f(st) && p->f(en) >= f(en)){\n            p->f = f;\n            return p;\n\
    \        }\n        T mid = (st + en) / 2;\n        if(p->f(mid) > f(mid))\n \
    \           swap(p->f, f);\n        if(p->f(st) >= f(st))\n            p->l =\
    \ _insert(p->l, st, mid, f);\n        else\n            p->r = _insert(p->r, mid,\
    \ en, f);\n        return p;\n    }\n\n    U _query(Node* p, T st, T en, T x){\n\
    \        if(!p)\n            return _inf;\n        if(st == en)\n            return\
    \ p->f(x);\n        T mid = (st + en) / 2;\n        if(x <= mid)\n           \
    \ return min(p->f(x), _query(p->l, st, mid, x));\n        else\n            return\
    \ min(p->f(x), _query(p->r, mid, en, x));\n    }\n\n    void insert(Elm f){\n\
    \        root = _insert(root, _min, _max, f);\n    }\n\n    U query(T x){\n  \
    \      return _query(root, _min, _max, x);\n    }\n};\n\n"
  code: "template <typename T, typename U>\nstruct ConvexHullTrick{\n    // \u4EFB\
    \u610F\u306E2\u95A2\u6570\u3067\u5171\u6709\u70B9\u304C\u9AD8\u30051\u500B\u306A\
    \u3089Elm\u306E\u4E2D\u8EAB\u3092\u9069\u5207\u306B\u5909\u3048\u308C\u3070\u901A\
    \u308B\n\n    struct Elm{\n        T a, b;\n        U operator()(T x){\n     \
    \       return a * x + b;\n        }\n    };\n\n    struct Node{\n        Elm\
    \ f;\n        Node* l;\n        Node* r;\n        Node(Elm elm) : f(elm), l(nullptr),\
    \ r(nullptr){}\n    };\n\n    U _min, _max, _inf;\n    Node* root;\n\n    ConvexHullTrick(U\
    \ _min, U _max, U _inf) :\n        _min(_min),\n        _max(_max),\n        _inf(_inf),\n\
    \        root(nullptr)\n    {\n    }\n\n    Node* _insert(Node* p, T st, T en,\
    \ Elm f){\n        if(!p)\n            return new Node(f);\n        if(p->f(st)\
    \ <= f(st) && p->f(en) <= f(en))\n            return p;\n        if(p->f(st) >=\
    \ f(st) && p->f(en) >= f(en)){\n            p->f = f;\n            return p;\n\
    \        }\n        T mid = (st + en) / 2;\n        if(p->f(mid) > f(mid))\n \
    \           swap(p->f, f);\n        if(p->f(st) >= f(st))\n            p->l =\
    \ _insert(p->l, st, mid, f);\n        else\n            p->r = _insert(p->r, mid,\
    \ en, f);\n        return p;\n    }\n\n    U _query(Node* p, T st, T en, T x){\n\
    \        if(!p)\n            return _inf;\n        if(st == en)\n            return\
    \ p->f(x);\n        T mid = (st + en) / 2;\n        if(x <= mid)\n           \
    \ return min(p->f(x), _query(p->l, st, mid, x));\n        else\n            return\
    \ min(p->f(x), _query(p->r, mid, en, x));\n    }\n\n    void insert(Elm f){\n\
    \        root = _insert(root, _min, _max, f);\n    }\n\n    U query(T x){\n  \
    \      return _query(root, _min, _max, x);\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/convexhulltrick.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/convexhulltrick.cpp
layout: document
redirect_from:
- /library/lib/classes/convexhulltrick.cpp
- /library/lib/classes/convexhulltrick.cpp.html
title: lib/classes/convexhulltrick.cpp
---
