---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/redblacktree_rsq.test.cpp
    title: verify/redblacktree_rsq.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/redblacktree.cpp\"\n// merge/split \u30D9\u30FC\
    \u30B9\u306E\u8D64\u9ED2\u6728(\u8449\u6728)\ntemplate <typename T>\nstruct RedBlackTree{\n\
    \n    struct Node;\n    using Index = typename MemoryPool<Node>::Index;\n\n  \
    \  struct Node{\n        int siz, level;\n        T sum;\n        bool red;\n\
    \        typename MemoryPool<Node>::Index l, r;\n        Node(){}\n        Node(T\
    \ val, bool red, bool leaf, int li = -1, int ri = -1) : sum(val), siz(leaf), level(0),\
    \ red(red){\n            l = {li};\n            r = {ri};\n        }\n    };\n\
    \n    MemoryPool<Node> pool;\n    Index nil;\n    function<T(T, T)> f;\n    T\
    \ op;\n    RedBlackTree(function<T(T, T)> f = [](auto x, auto y){return x + y;},\
    \ T op = T()) : f(f), op(op){\n        nil = pool.alloc();\n        pool[nil]\
    \ = Node(op, false, false);\n        pool[nil].l = pool[nil].r = nil;\n    }\n\
    \n    Index build(vector<T>& a){\n        nil = pool.alloc();\n        pool[nil]\
    \ = Node(op, false, false);\n        pool[nil].l = pool[nil].r = nil;\n      \
    \  int siz = a.size();\n        vector<Index> v(siz);\n        for(int i = 0;\
    \ i < siz; ++i)\n            v[i] = make(a[i]);\n        while(siz != 1){\n  \
    \          int nex_siz = (siz + 1) >> 1;\n            vector<Index> nex(nex_siz);\n\
    \            for(int i = 0; i < (siz >> 1); ++i)\n                nex[i] = merge(v[2\
    \ * i], v[2 * i + 1]);\n            if(siz & 1)\n                nex.back() =\
    \ v.back();\n            siz = nex_siz;\n            v = move(nex);\n        }\n\
    \        return v[0];\n    }\n\n    void clear(){\n        while(!pool.st.empty())\n\
    \            pool.st.pop();\n        for(int i = 1; i <= pool.idx; ++i)\n    \
    \        pool.st.push(i);\n    }\n\n    Index index(int x){return {x};}\n\n\n\
    \    T get_val(Index pi, int k){\n        pi = access(pi, k);\n\t\treturn get(pi).sum;\n\
    \    }\n\n    void update(Index pi){\n        if(pi == nil)\n            return;\n\
    \        auto& p = get(pi);\n        auto& l = get(p.l);\n        auto& r = get(p.r);\n\
    \        p.siz = l.siz + r.siz;\n        if(p.l != nil || p.r != nil)\n      \
    \      p.sum = f(l.sum, r.sum);\n        p.level = l.level + !l.red;\n       \
    \ assert(p.level == r.level + !r.red);\n    }\n\n    Index make(T val){\n    \
    \    Index idx = pool.alloc();\n        pool[idx] = Node(val, false, true, nil.idx,\
    \ nil.idx);\n        pool[idx].level = 1;\n        return idx;\n    }\n\n    Index\
    \ mergeSub(Index ai, Index bi){\n        auto& a = get(ai);\n        auto& b =\
    \ get(bi);\n        assert(ai != nil && bi != nil);\n        if(a.level < b.level){\n\
    \            Index ci = mergeSub(ai, b.l);\n            auto& c = get(ci);\n \
    \           if(!b.red && c.red && get(c.l).red){\n                if(!get(b.r).red){\n\
    \                    b.l = c.l;\n                    c.l = c.r;\n            \
    \        c.r = b.r;\n                    b.r = ci;\n                    update(ci);\n\
    \                    update(bi);\n                    return bi;\n           \
    \     }\n                else{\n                    b.l = ci;\n              \
    \      b.red ^= 1;\n                    get(b.l).red ^= 1;\n                 \
    \   get(b.r).red ^= 1;\n                    update(bi);\n                    return\
    \ bi;\n                }\n            }\n            b.l = ci;\n            update(bi);\n\
    \            return bi;\n        }\n        else if(a.level > b.level){\n    \
    \        Index ci = mergeSub(a.r, bi);\n            auto& c = get(ci);\n     \
    \       if(!a.red && c.red && get(c.r).red){\n                if(!get(a.l).red){\n\
    \                    a.r = c.r;\n                    c.r = c.l;\n            \
    \        c.l = a.l;\n                    a.l = ci;\n                    update(ci);\n\
    \                    update(ai);\n                    return ai;\n           \
    \     }\n                else{\n                    a.r = ci;\n              \
    \      a.red ^= 1;\n                    get(a.l).red ^= 1;\n                 \
    \   get(a.r).red ^= 1;\n                    update(ai);\n                    return\
    \ ai;\n                }\n            }\n            a.r = ci;\n            update(ai);\n\
    \            return ai;\n        }\n        else{\n            a.red = false;\n\
    \            b.red = false;\n            Index d = pool.alloc();\n           \
    \ get(d) = Node(op, true, false, ai.idx, bi.idx);\n            update(d);\n  \
    \          return d;\n        }\n    }\n\n    Index merge(Index ai, Index bi){\n\
    \        if(ai == nil)\n            return bi;\n        if(bi == nil)\n      \
    \      return ai;\n        Index ci = mergeSub(ai, bi);\n        get(ci).red =\
    \ false;\n        return ci;\n    }\n\n    pair<Index, Index> split(Index ai,\
    \ int k){\n        if(ai == nil)\n            return make_pair(nil, nil);\n  \
    \      auto& a = get(ai);\n        if(k == 0)\n            return make_pair(nil,\
    \ ai);\n        if(k == a.siz)\n            return make_pair(ai, nil);\n     \
    \   Index li = a.l;\n        Index ri = a.r;\n        auto& l = get(li);\n   \
    \     pool.free(ai);\n        if(k < l.siz){\n            auto res = split(li,\
    \ k);\n            return make_pair(res.first, merge(res.second, ri));\n     \
    \   }\n        else if(k > get(a.l).siz){\n            auto res = split(ri, k\
    \ - l.siz);\n            return make_pair(merge(li, res.first), res.second);\n\
    \        }\n        else{\n            return make_pair(li, ri);\n        }\n\
    \    }\n\n    pair<T, Index> range_get(Index pi, int l, int r){\n        auto\
    \ res = split(pi, r);\n        auto res2 = split(res.first, l);\n        T val\
    \ = get(res2.second).sum;\n        return make_pair(val, merge(merge(res2.first,\
    \ res2.second), res.second));\n    }\n\n    Index insert(Index pi, int k, T val){\n\
    \        auto res = split(pi, k);\n        return merge(res.first, merge(make(val),\
    \ res.second));\n    }\n\n    Index erase(Index pi, int k){\n        auto res\
    \ = split(pi, k + 1);\n        auto res2 = split(res.first, k);\n        pool.free(res2.second);\n\
    \        return merge(res2.first, res.second);\n    }\n\n    Index access(Index\
    \ pi, int k){\n        while(get(pi).l != nil || get(pi).r != nil){\n        \
    \    auto& p = get(pi);\n            assert(p.l != nil && p.r != nil);\n     \
    \       if(get(p.l).siz <= k){\n                k -= get(p.l).siz;\n         \
    \       pi = p.r;\n            }\n            else{\n                pi = p.l;\n\
    \            }\n        }\n        return pi;\n    }\n\n    void set(Index pi,\
    \ int k, T val, function<T(T, T)> g = [](T x, T y){return y;}){\n        stack<Index>\
    \ st;\n        while(get(pi).l != nil || get(pi).r != nil){\n            auto&\
    \ p = get(pi);\n            st.push(pi);\n            assert(p.l != nil && p.r\
    \ != nil);\n            if(get(p.l).siz <= k){\n                k -= get(p.l).siz;\n\
    \                pi = p.r;\n            }\n            else{\n               \
    \ pi = p.l;\n            }\n        }\n        auto& p = get(pi);\n        p.sum\
    \ = g(p.sum, val);\n        while(!st.empty()){\n            update(st.top());\n\
    \            st.pop();\n        }\n    }\n\n    Node& get(Index k){return pool[k];}\n\
    \    Node& operator[](Index k){return pool[k];}\n};\n\n"
  code: "// merge/split \u30D9\u30FC\u30B9\u306E\u8D64\u9ED2\u6728(\u8449\u6728)\n\
    template <typename T>\nstruct RedBlackTree{\n\n    struct Node;\n    using Index\
    \ = typename MemoryPool<Node>::Index;\n\n    struct Node{\n        int siz, level;\n\
    \        T sum;\n        bool red;\n        typename MemoryPool<Node>::Index l,\
    \ r;\n        Node(){}\n        Node(T val, bool red, bool leaf, int li = -1,\
    \ int ri = -1) : sum(val), siz(leaf), level(0), red(red){\n            l = {li};\n\
    \            r = {ri};\n        }\n    };\n\n    MemoryPool<Node> pool;\n    Index\
    \ nil;\n    function<T(T, T)> f;\n    T op;\n    RedBlackTree(function<T(T, T)>\
    \ f = [](auto x, auto y){return x + y;}, T op = T()) : f(f), op(op){\n       \
    \ nil = pool.alloc();\n        pool[nil] = Node(op, false, false);\n        pool[nil].l\
    \ = pool[nil].r = nil;\n    }\n\n    Index build(vector<T>& a){\n        nil =\
    \ pool.alloc();\n        pool[nil] = Node(op, false, false);\n        pool[nil].l\
    \ = pool[nil].r = nil;\n        int siz = a.size();\n        vector<Index> v(siz);\n\
    \        for(int i = 0; i < siz; ++i)\n            v[i] = make(a[i]);\n      \
    \  while(siz != 1){\n            int nex_siz = (siz + 1) >> 1;\n            vector<Index>\
    \ nex(nex_siz);\n            for(int i = 0; i < (siz >> 1); ++i)\n           \
    \     nex[i] = merge(v[2 * i], v[2 * i + 1]);\n            if(siz & 1)\n     \
    \           nex.back() = v.back();\n            siz = nex_siz;\n            v\
    \ = move(nex);\n        }\n        return v[0];\n    }\n\n    void clear(){\n\
    \        while(!pool.st.empty())\n            pool.st.pop();\n        for(int\
    \ i = 1; i <= pool.idx; ++i)\n            pool.st.push(i);\n    }\n\n    Index\
    \ index(int x){return {x};}\n\n\n    T get_val(Index pi, int k){\n        pi =\
    \ access(pi, k);\n\t\treturn get(pi).sum;\n    }\n\n    void update(Index pi){\n\
    \        if(pi == nil)\n            return;\n        auto& p = get(pi);\n    \
    \    auto& l = get(p.l);\n        auto& r = get(p.r);\n        p.siz = l.siz +\
    \ r.siz;\n        if(p.l != nil || p.r != nil)\n            p.sum = f(l.sum, r.sum);\n\
    \        p.level = l.level + !l.red;\n        assert(p.level == r.level + !r.red);\n\
    \    }\n\n    Index make(T val){\n        Index idx = pool.alloc();\n        pool[idx]\
    \ = Node(val, false, true, nil.idx, nil.idx);\n        pool[idx].level = 1;\n\
    \        return idx;\n    }\n\n    Index mergeSub(Index ai, Index bi){\n     \
    \   auto& a = get(ai);\n        auto& b = get(bi);\n        assert(ai != nil &&\
    \ bi != nil);\n        if(a.level < b.level){\n            Index ci = mergeSub(ai,\
    \ b.l);\n            auto& c = get(ci);\n            if(!b.red && c.red && get(c.l).red){\n\
    \                if(!get(b.r).red){\n                    b.l = c.l;\n        \
    \            c.l = c.r;\n                    c.r = b.r;\n                    b.r\
    \ = ci;\n                    update(ci);\n                    update(bi);\n  \
    \                  return bi;\n                }\n                else{\n    \
    \                b.l = ci;\n                    b.red ^= 1;\n                \
    \    get(b.l).red ^= 1;\n                    get(b.r).red ^= 1;\n            \
    \        update(bi);\n                    return bi;\n                }\n    \
    \        }\n            b.l = ci;\n            update(bi);\n            return\
    \ bi;\n        }\n        else if(a.level > b.level){\n            Index ci =\
    \ mergeSub(a.r, bi);\n            auto& c = get(ci);\n            if(!a.red &&\
    \ c.red && get(c.r).red){\n                if(!get(a.l).red){\n              \
    \      a.r = c.r;\n                    c.r = c.l;\n                    c.l = a.l;\n\
    \                    a.l = ci;\n                    update(ci);\n            \
    \        update(ai);\n                    return ai;\n                }\n    \
    \            else{\n                    a.r = ci;\n                    a.red ^=\
    \ 1;\n                    get(a.l).red ^= 1;\n                    get(a.r).red\
    \ ^= 1;\n                    update(ai);\n                    return ai;\n   \
    \             }\n            }\n            a.r = ci;\n            update(ai);\n\
    \            return ai;\n        }\n        else{\n            a.red = false;\n\
    \            b.red = false;\n            Index d = pool.alloc();\n           \
    \ get(d) = Node(op, true, false, ai.idx, bi.idx);\n            update(d);\n  \
    \          return d;\n        }\n    }\n\n    Index merge(Index ai, Index bi){\n\
    \        if(ai == nil)\n            return bi;\n        if(bi == nil)\n      \
    \      return ai;\n        Index ci = mergeSub(ai, bi);\n        get(ci).red =\
    \ false;\n        return ci;\n    }\n\n    pair<Index, Index> split(Index ai,\
    \ int k){\n        if(ai == nil)\n            return make_pair(nil, nil);\n  \
    \      auto& a = get(ai);\n        if(k == 0)\n            return make_pair(nil,\
    \ ai);\n        if(k == a.siz)\n            return make_pair(ai, nil);\n     \
    \   Index li = a.l;\n        Index ri = a.r;\n        auto& l = get(li);\n   \
    \     pool.free(ai);\n        if(k < l.siz){\n            auto res = split(li,\
    \ k);\n            return make_pair(res.first, merge(res.second, ri));\n     \
    \   }\n        else if(k > get(a.l).siz){\n            auto res = split(ri, k\
    \ - l.siz);\n            return make_pair(merge(li, res.first), res.second);\n\
    \        }\n        else{\n            return make_pair(li, ri);\n        }\n\
    \    }\n\n    pair<T, Index> range_get(Index pi, int l, int r){\n        auto\
    \ res = split(pi, r);\n        auto res2 = split(res.first, l);\n        T val\
    \ = get(res2.second).sum;\n        return make_pair(val, merge(merge(res2.first,\
    \ res2.second), res.second));\n    }\n\n    Index insert(Index pi, int k, T val){\n\
    \        auto res = split(pi, k);\n        return merge(res.first, merge(make(val),\
    \ res.second));\n    }\n\n    Index erase(Index pi, int k){\n        auto res\
    \ = split(pi, k + 1);\n        auto res2 = split(res.first, k);\n        pool.free(res2.second);\n\
    \        return merge(res2.first, res.second);\n    }\n\n    Index access(Index\
    \ pi, int k){\n        while(get(pi).l != nil || get(pi).r != nil){\n        \
    \    auto& p = get(pi);\n            assert(p.l != nil && p.r != nil);\n     \
    \       if(get(p.l).siz <= k){\n                k -= get(p.l).siz;\n         \
    \       pi = p.r;\n            }\n            else{\n                pi = p.l;\n\
    \            }\n        }\n        return pi;\n    }\n\n    void set(Index pi,\
    \ int k, T val, function<T(T, T)> g = [](T x, T y){return y;}){\n        stack<Index>\
    \ st;\n        while(get(pi).l != nil || get(pi).r != nil){\n            auto&\
    \ p = get(pi);\n            st.push(pi);\n            assert(p.l != nil && p.r\
    \ != nil);\n            if(get(p.l).siz <= k){\n                k -= get(p.l).siz;\n\
    \                pi = p.r;\n            }\n            else{\n               \
    \ pi = p.l;\n            }\n        }\n        auto& p = get(pi);\n        p.sum\
    \ = g(p.sum, val);\n        while(!st.empty()){\n            update(st.top());\n\
    \            st.pop();\n        }\n    }\n\n    Node& get(Index k){return pool[k];}\n\
    \    Node& operator[](Index k){return pool[k];}\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/redblacktree.cpp
  requiredBy: []
  timestamp: '2020-04-22 12:46:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/redblacktree_rsq.test.cpp
documentation_of: lib/classes/redblacktree.cpp
layout: document
redirect_from:
- /library/lib/classes/redblacktree.cpp
- /library/lib/classes/redblacktree.cpp.html
title: lib/classes/redblacktree.cpp
---
