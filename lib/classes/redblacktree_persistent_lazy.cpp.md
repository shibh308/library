---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - https://atcoder.jp/contests/arc030/submissions/12211957/
  bundledCode: "#line 1 \"lib/classes/redblacktree_persistent_lazy.cpp\"\n// verify:\
    \ https://atcoder.jp/contests/arc030/submissions/12211957/\ntemplate <typename\
    \ T, typename U>\nstruct RedBlackTree{\n\n    struct Node;\n    using Index =\
    \ typename MemoryPool<Node>::Index;\n\n    struct Node{\n        int siz, level;\n\
    \        T sum;\n        U lazy;\n        bool red;\n        typename MemoryPool<Node>::Index\
    \ l, r;\n        Node(){}\n        Node(T val, U lazy, bool red, bool leaf, int\
    \ li = -1, int ri = -1) : sum(val), lazy(lazy), siz(leaf), level(0), red(red){\n\
    \            l = {li};\n            r = {ri};\n        }\n        Node(T val,\
    \ U lazy, bool red, bool leaf, Index l, Index r) : sum(val), lazy(lazy), siz(leaf),\
    \ level(0), red(red), l(l), r(r){}\n    };\n\n    MemoryPool<Node> pool;\n   \
    \ Index nil;\n    function<T(T, T)> f;\n    function<U(T, U, int)> g;\n    function<U(U,\
    \ U)> h;\n    T op_t;\n    U op_u;\n    RedBlackTree(function<T(T, T)> f, function<T(T,\
    \ U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t),\
    \ op_u(op_u){\n        nil = pool.alloc();\n        pool[nil] = Node(op_t, op_u,\
    \ false, false);\n        pool[nil].l = pool[nil].r = nil;\n    }\n\n    Index\
    \ build(vector<T>& a){\n        nil = pool.alloc();\n        pool[nil] = Node(op_t,\
    \ op_u, false, false);\n        pool[nil].l = pool[nil].r = nil;\n        int\
    \ siz = a.size();\n        vector<Index> v(siz);\n        for(int i = 0; i < siz;\
    \ ++i)\n            v[i] = make(a[i]);\n        while(siz != 1){\n           \
    \ int nex_siz = (siz + 1) >> 1;\n            vector<Index> nex(nex_siz);\n   \
    \         for(int i = 0; i < (siz >> 1); ++i)\n                nex[i] = merge(v[2\
    \ * i], v[2 * i + 1]);\n            if(siz & 1)\n                nex.back() =\
    \ v.back();\n            siz = nex_siz;\n            v = move(nex);\n        }\n\
    \        return v[0];\n    }\n\n    void clear(){\n        while(!pool.st.empty())\n\
    \            pool.st.pop();\n        for(int i = 1; i <= pool.idx; ++i)\n    \
    \        pool.st.push(i);\n    }\n\n    Index index(int x){return {x};}\n\n  \
    \  T get_val(Index pi){\n        auto& p = get(pi);\n        return g(p.sum, p.lazy,\
    \ p.siz);\n    }\n\n    pair<T, Index> get_val(Index pi, int k){\n        Index\
    \ root;\n        tie(pi, root) = access(pi, k);\n        return make_pair(get_val(pi),\
    \ root);\n    }\n\n    pair<Index, bool> eval(Index pi){\n        if(pi == nil)\n\
    \            return {pi, false};\n        if(get(pi).lazy == op_u)\n         \
    \   return {pi, false};\n        pi = clone(pi);\n        auto& p = get(pi);\n\
    \        if(p.l != nil){\n            p.l = clone(p.l);\n            p.r = clone(p.r);\n\
    \            auto& l = get(p.l);\n            l.lazy = h(l.lazy, p.lazy);\n  \
    \          auto& r = get(p.r);\n            r.lazy = h(r.lazy, p.lazy);\n    \
    \    }\n        p.sum = get_val(pi);\n        p.lazy = op_u;\n        return {pi,\
    \ true};\n    }\n\n    Index make(T val){\n        Index idx = pool.alloc();\n\
    \        pool[idx] = Node(val, op_u, false, true, nil, nil);\n        pool[idx].level\
    \ = 1;\n        return idx;\n    }\n\n    Index clone(Index pi){\n        if(pi\
    \ == nil)\n            return pi;\n        Index qi = pool.alloc();\n        auto&\
    \ p = get(pi);\n        pool[qi] = Node(p.sum, p.lazy, p.red, false, p.l, p.r);\n\
    \        pool[qi].siz = (p.l == nil ? 1 : pool[p.l].siz + pool[p.r].siz);\n  \
    \      pool[qi].level = pool[p.l].level + !pool[p.l].red;\n        return qi;\n\
    \    }\n\n    Index makeInternal(Index l, Index r, bool red){\n        Index idx\
    \ = pool.alloc();\n        pool[idx] = Node(op_t, op_u, red, false, l, r);\n \
    \       pool[idx].sum = f(get_val(l), get_val(r));\n        pool[idx].siz = pool[l].siz\
    \ + pool[r].siz;\n        pool[idx].level = pool[l].level + !pool[l].red;\n  \
    \      return idx;\n    }\n\n    Index mergeSub(Index ai, Index bi){\n       \
    \ ai = eval(ai).first;\n        bi = eval(bi).first;\n        auto& a = get(ai);\n\
    \        auto& b = get(bi);\n        assert(ai != nil && bi != nil);\n       \
    \ if(a.level < b.level){\n            Index ci = mergeSub(ai, b.l);\n        \
    \    auto& c = get(ci);\n            if(!b.red && c.red && get(c.l).red){\n  \
    \              if(!get(b.r).red)\n                    return makeInternal(c.l,\
    \ makeInternal(c.r, b.r, true), false);\n                else{\n             \
    \       b.r = eval(b.r).first;\n                    return makeInternal(makeInternal(c.l,\
    \ c.r, false), makeInternal(get(b.r).l, get(b.r).r, false), true);\n         \
    \       }\n            }\n            return makeInternal(ci, b.r, b.red);\n \
    \       }\n        else if(a.level > b.level){\n            Index ci = mergeSub(a.r,\
    \ bi);\n            auto& c = get(ci);\n            if(!a.red && c.red && get(c.r).red){\n\
    \                if(!get(a.l).red)\n                    return makeInternal(makeInternal(a.l,\
    \ c.l, true), c.r, false);\n                else{\n                    a.l = eval(a.l).first;\n\
    \                    return makeInternal(makeInternal(get(a.l).l, get(a.l).r,\
    \ false), makeInternal(c.l, c.r, false), true);\n                }\n         \
    \   }\n            return makeInternal(a.l, ci, a.red);\n        }\n        else{\n\
    \            if(a.red)\n                ai = makeInternal(a.l, a.r, false);\n\
    \            if(b.red)\n                bi = makeInternal(b.l, b.r, false);\n\
    \            return makeInternal(ai, bi, true);\n        }\n    }\n\n    Index\
    \ merge(Index ai, Index bi){\n        if(ai == nil)\n            return bi;\n\
    \        if(bi == nil)\n            return ai;\n        Index ci = mergeSub(ai,\
    \ bi);\n        auto& c = get(ci);\n        if(c.red){\n            pool.free(ci);\n\
    \            return makeInternal(c.l, c.r, false);\n        }\n        return\
    \ ci;\n    }\n\n    pair<Index, Index> split(Index ai, int k){\n        if(ai\
    \ == nil)\n            return make_pair(nil, nil);\n        bool fl;\n       \
    \ tie(ai, fl) = eval(ai);\n        auto& a = get(ai);\n        if(k == 0)\n  \
    \          return make_pair(nil, ai);\n        if(k == a.siz)\n            return\
    \ make_pair(ai, nil);\n        Index li = a.l;\n        Index ri = a.r;\n    \
    \    if(fl)\n            pool.free(ai);\n        auto& l = get(li);\n        if(k\
    \ < l.siz){\n            auto res = split(li, k);\n            return make_pair(res.first,\
    \ merge(res.second, ri));\n        }\n        else if(k > get(a.l).siz){\n   \
    \         auto res = split(ri, k - l.siz);\n            return make_pair(merge(li,\
    \ res.first), res.second);\n        }\n        else{\n            return make_pair(li,\
    \ ri);\n        }\n    }\n\n    pair<T, Index> range_get(Index pi, int l, int\
    \ r){\n        auto res = split(pi, r);\n        auto res2 = split(res.first,\
    \ l);\n        T val = get_val(res2.second);\n        return make_pair(val, merge(merge(res2.first,\
    \ res2.second), res.second));\n    }\n\n    Index range_update(Index pi, int l,\
    \ int r, U val){\n        if(l == r)\n            return pi;\n        auto res\
    \ = split(pi, r);\n        auto res2 = split(res.first, l);\n        Index mi\
    \ = clone(res2.second);\n        auto& mid = get(mi);\n        mid.lazy = h(mid.lazy,\
    \ val);\n        Index nex_mi;\n        bool fl;\n        tie(nex_mi, fl) = eval(mi);\n\
    \        if(fl)\n            pool.free(mi);\n\n        return merge(merge(res2.first,\
    \ nex_mi), res.second);\n    }\n\n    Index insert(Index pi, int k, T val){\n\
    \        auto res = split(pi, k);\n        return merge(res.first, merge(make(val),\
    \ res.second));\n    }\n\n    Index erase(Index pi, int k){\n        auto res\
    \ = split(pi, k + 1);\n        auto res2 = split(res.first, k);\n        return\
    \ merge(res2.first, res.second);\n    }\n\n    pair<Index, Index> access(Index\
    \ pi, int k){\n        auto res = split(pi, k + 1);\n        auto res2 = split(res.first,\
    \ k);\n        return make_pair(res2.second, merge(merge(res2.first, res2.second),\
    \ res.second));\n    }\n\n    Index set(Index pi, int k, T val, function<T(T,\
    \ T)> af = [](T x, T y){return y;}){\n        auto res = split(pi, k + 1);\n \
    \       auto res2 = split(res.first, k);\n        Index qi = eval(res2.second);\n\
    \        get(qi).sum = af(get_val(qi), val);\n        return make_pair(qi, merge(merge(res2.first,\
    \ qi), res.second));\n    }\n\n    void dump(Index pi, vector<T>& v){\n      \
    \  Index qi = eval(pi).first;\n        auto& q = get(qi);\n        if(q.l != nil){\n\
    \            dump(q.l, v);\n            dump(q.r, v);\n        }\n        else\n\
    \            v.emplace_back(get_val(pi));\n    }\n\n    vector<T> dump(Index pi){\n\
    \        vector<T> v;\n        dump(pi, v);\n        return v;\n    }\n\n    Index\
    \ rebuild(Index pi){\n        auto v = dump(pi);\n        clear();\n        return\
    \ build(v);\n    }\n\n    Node& get(Index k){return pool[k];}\n    Node& operator[](Index\
    \ k){return pool[k];}\n};\n\n"
  code: "// verify: https://atcoder.jp/contests/arc030/submissions/12211957/\ntemplate\
    \ <typename T, typename U>\nstruct RedBlackTree{\n\n    struct Node;\n    using\
    \ Index = typename MemoryPool<Node>::Index;\n\n    struct Node{\n        int siz,\
    \ level;\n        T sum;\n        U lazy;\n        bool red;\n        typename\
    \ MemoryPool<Node>::Index l, r;\n        Node(){}\n        Node(T val, U lazy,\
    \ bool red, bool leaf, int li = -1, int ri = -1) : sum(val), lazy(lazy), siz(leaf),\
    \ level(0), red(red){\n            l = {li};\n            r = {ri};\n        }\n\
    \        Node(T val, U lazy, bool red, bool leaf, Index l, Index r) : sum(val),\
    \ lazy(lazy), siz(leaf), level(0), red(red), l(l), r(r){}\n    };\n\n    MemoryPool<Node>\
    \ pool;\n    Index nil;\n    function<T(T, T)> f;\n    function<U(T, U, int)>\
    \ g;\n    function<U(U, U)> h;\n    T op_t;\n    U op_u;\n    RedBlackTree(function<T(T,\
    \ T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f),\
    \ g(g), h(h), op_t(op_t), op_u(op_u){\n        nil = pool.alloc();\n        pool[nil]\
    \ = Node(op_t, op_u, false, false);\n        pool[nil].l = pool[nil].r = nil;\n\
    \    }\n\n    Index build(vector<T>& a){\n        nil = pool.alloc();\n      \
    \  pool[nil] = Node(op_t, op_u, false, false);\n        pool[nil].l = pool[nil].r\
    \ = nil;\n        int siz = a.size();\n        vector<Index> v(siz);\n       \
    \ for(int i = 0; i < siz; ++i)\n            v[i] = make(a[i]);\n        while(siz\
    \ != 1){\n            int nex_siz = (siz + 1) >> 1;\n            vector<Index>\
    \ nex(nex_siz);\n            for(int i = 0; i < (siz >> 1); ++i)\n           \
    \     nex[i] = merge(v[2 * i], v[2 * i + 1]);\n            if(siz & 1)\n     \
    \           nex.back() = v.back();\n            siz = nex_siz;\n            v\
    \ = move(nex);\n        }\n        return v[0];\n    }\n\n    void clear(){\n\
    \        while(!pool.st.empty())\n            pool.st.pop();\n        for(int\
    \ i = 1; i <= pool.idx; ++i)\n            pool.st.push(i);\n    }\n\n    Index\
    \ index(int x){return {x};}\n\n    T get_val(Index pi){\n        auto& p = get(pi);\n\
    \        return g(p.sum, p.lazy, p.siz);\n    }\n\n    pair<T, Index> get_val(Index\
    \ pi, int k){\n        Index root;\n        tie(pi, root) = access(pi, k);\n \
    \       return make_pair(get_val(pi), root);\n    }\n\n    pair<Index, bool> eval(Index\
    \ pi){\n        if(pi == nil)\n            return {pi, false};\n        if(get(pi).lazy\
    \ == op_u)\n            return {pi, false};\n        pi = clone(pi);\n       \
    \ auto& p = get(pi);\n        if(p.l != nil){\n            p.l = clone(p.l);\n\
    \            p.r = clone(p.r);\n            auto& l = get(p.l);\n            l.lazy\
    \ = h(l.lazy, p.lazy);\n            auto& r = get(p.r);\n            r.lazy =\
    \ h(r.lazy, p.lazy);\n        }\n        p.sum = get_val(pi);\n        p.lazy\
    \ = op_u;\n        return {pi, true};\n    }\n\n    Index make(T val){\n     \
    \   Index idx = pool.alloc();\n        pool[idx] = Node(val, op_u, false, true,\
    \ nil, nil);\n        pool[idx].level = 1;\n        return idx;\n    }\n\n   \
    \ Index clone(Index pi){\n        if(pi == nil)\n            return pi;\n    \
    \    Index qi = pool.alloc();\n        auto& p = get(pi);\n        pool[qi] =\
    \ Node(p.sum, p.lazy, p.red, false, p.l, p.r);\n        pool[qi].siz = (p.l ==\
    \ nil ? 1 : pool[p.l].siz + pool[p.r].siz);\n        pool[qi].level = pool[p.l].level\
    \ + !pool[p.l].red;\n        return qi;\n    }\n\n    Index makeInternal(Index\
    \ l, Index r, bool red){\n        Index idx = pool.alloc();\n        pool[idx]\
    \ = Node(op_t, op_u, red, false, l, r);\n        pool[idx].sum = f(get_val(l),\
    \ get_val(r));\n        pool[idx].siz = pool[l].siz + pool[r].siz;\n        pool[idx].level\
    \ = pool[l].level + !pool[l].red;\n        return idx;\n    }\n\n    Index mergeSub(Index\
    \ ai, Index bi){\n        ai = eval(ai).first;\n        bi = eval(bi).first;\n\
    \        auto& a = get(ai);\n        auto& b = get(bi);\n        assert(ai !=\
    \ nil && bi != nil);\n        if(a.level < b.level){\n            Index ci = mergeSub(ai,\
    \ b.l);\n            auto& c = get(ci);\n            if(!b.red && c.red && get(c.l).red){\n\
    \                if(!get(b.r).red)\n                    return makeInternal(c.l,\
    \ makeInternal(c.r, b.r, true), false);\n                else{\n             \
    \       b.r = eval(b.r).first;\n                    return makeInternal(makeInternal(c.l,\
    \ c.r, false), makeInternal(get(b.r).l, get(b.r).r, false), true);\n         \
    \       }\n            }\n            return makeInternal(ci, b.r, b.red);\n \
    \       }\n        else if(a.level > b.level){\n            Index ci = mergeSub(a.r,\
    \ bi);\n            auto& c = get(ci);\n            if(!a.red && c.red && get(c.r).red){\n\
    \                if(!get(a.l).red)\n                    return makeInternal(makeInternal(a.l,\
    \ c.l, true), c.r, false);\n                else{\n                    a.l = eval(a.l).first;\n\
    \                    return makeInternal(makeInternal(get(a.l).l, get(a.l).r,\
    \ false), makeInternal(c.l, c.r, false), true);\n                }\n         \
    \   }\n            return makeInternal(a.l, ci, a.red);\n        }\n        else{\n\
    \            if(a.red)\n                ai = makeInternal(a.l, a.r, false);\n\
    \            if(b.red)\n                bi = makeInternal(b.l, b.r, false);\n\
    \            return makeInternal(ai, bi, true);\n        }\n    }\n\n    Index\
    \ merge(Index ai, Index bi){\n        if(ai == nil)\n            return bi;\n\
    \        if(bi == nil)\n            return ai;\n        Index ci = mergeSub(ai,\
    \ bi);\n        auto& c = get(ci);\n        if(c.red){\n            pool.free(ci);\n\
    \            return makeInternal(c.l, c.r, false);\n        }\n        return\
    \ ci;\n    }\n\n    pair<Index, Index> split(Index ai, int k){\n        if(ai\
    \ == nil)\n            return make_pair(nil, nil);\n        bool fl;\n       \
    \ tie(ai, fl) = eval(ai);\n        auto& a = get(ai);\n        if(k == 0)\n  \
    \          return make_pair(nil, ai);\n        if(k == a.siz)\n            return\
    \ make_pair(ai, nil);\n        Index li = a.l;\n        Index ri = a.r;\n    \
    \    if(fl)\n            pool.free(ai);\n        auto& l = get(li);\n        if(k\
    \ < l.siz){\n            auto res = split(li, k);\n            return make_pair(res.first,\
    \ merge(res.second, ri));\n        }\n        else if(k > get(a.l).siz){\n   \
    \         auto res = split(ri, k - l.siz);\n            return make_pair(merge(li,\
    \ res.first), res.second);\n        }\n        else{\n            return make_pair(li,\
    \ ri);\n        }\n    }\n\n    pair<T, Index> range_get(Index pi, int l, int\
    \ r){\n        auto res = split(pi, r);\n        auto res2 = split(res.first,\
    \ l);\n        T val = get_val(res2.second);\n        return make_pair(val, merge(merge(res2.first,\
    \ res2.second), res.second));\n    }\n\n    Index range_update(Index pi, int l,\
    \ int r, U val){\n        if(l == r)\n            return pi;\n        auto res\
    \ = split(pi, r);\n        auto res2 = split(res.first, l);\n        Index mi\
    \ = clone(res2.second);\n        auto& mid = get(mi);\n        mid.lazy = h(mid.lazy,\
    \ val);\n        Index nex_mi;\n        bool fl;\n        tie(nex_mi, fl) = eval(mi);\n\
    \        if(fl)\n            pool.free(mi);\n\n        return merge(merge(res2.first,\
    \ nex_mi), res.second);\n    }\n\n    Index insert(Index pi, int k, T val){\n\
    \        auto res = split(pi, k);\n        return merge(res.first, merge(make(val),\
    \ res.second));\n    }\n\n    Index erase(Index pi, int k){\n        auto res\
    \ = split(pi, k + 1);\n        auto res2 = split(res.first, k);\n        return\
    \ merge(res2.first, res.second);\n    }\n\n    pair<Index, Index> access(Index\
    \ pi, int k){\n        auto res = split(pi, k + 1);\n        auto res2 = split(res.first,\
    \ k);\n        return make_pair(res2.second, merge(merge(res2.first, res2.second),\
    \ res.second));\n    }\n\n    Index set(Index pi, int k, T val, function<T(T,\
    \ T)> af = [](T x, T y){return y;}){\n        auto res = split(pi, k + 1);\n \
    \       auto res2 = split(res.first, k);\n        Index qi = eval(res2.second);\n\
    \        get(qi).sum = af(get_val(qi), val);\n        return make_pair(qi, merge(merge(res2.first,\
    \ qi), res.second));\n    }\n\n    void dump(Index pi, vector<T>& v){\n      \
    \  Index qi = eval(pi).first;\n        auto& q = get(qi);\n        if(q.l != nil){\n\
    \            dump(q.l, v);\n            dump(q.r, v);\n        }\n        else\n\
    \            v.emplace_back(get_val(pi));\n    }\n\n    vector<T> dump(Index pi){\n\
    \        vector<T> v;\n        dump(pi, v);\n        return v;\n    }\n\n    Index\
    \ rebuild(Index pi){\n        auto v = dump(pi);\n        clear();\n        return\
    \ build(v);\n    }\n\n    Node& get(Index k){return pool[k];}\n    Node& operator[](Index\
    \ k){return pool[k];}\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/redblacktree_persistent_lazy.cpp
  requiredBy: []
  timestamp: '2020-04-22 12:46:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/redblacktree_persistent_lazy.cpp
layout: document
redirect_from:
- /library/lib/classes/redblacktree_persistent_lazy.cpp
- /library/lib/classes/redblacktree_persistent_lazy.cpp.html
title: lib/classes/redblacktree_persistent_lazy.cpp
---
