---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/joisc2012/submissions/12202620/
  bundledCode: "#line 1 \"lib/classes/redblacktree_persistent.cpp\"\n// verify: https://atcoder.jp/contests/joisc2012/submissions/12202620/\n\
    template <typename T>\nstruct RedBlackTree{\n\n    struct Node;\n    using Index\
    \ = typename MemoryPool<Node>::Index;\n\n    struct Node{\n        int siz, level;\n\
    \        T sum;\n        bool red;\n        typename MemoryPool<Node>::Index l,\
    \ r;\n        Node(){}\n        Node(T val, bool red, bool leaf, int li = -1,\
    \ int ri = -1) : sum(val), siz(leaf), level(0), red(red){\n            l = {li};\n\
    \            r = {ri};\n        }\n        Node(T val, bool red, bool leaf, Index\
    \ l, Index r) : sum(val), siz(leaf), level(0), red(red), l(l), r(r){}\n    };\n\
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
    \        pool.st.push(i);\n    }\n\n    Index index(int x){return {x};}\n\n  \
    \  T get_val(Index pi, int k){\n        pi = access(pi, k);\n        return get(pi).sum;\n\
    \    }\n\n    Index make(T val){\n        Index idx = pool.alloc();\n        pool[idx]\
    \ = Node(val, false, true, nil.idx, nil.idx);\n        pool[idx].level = 1;\n\
    \        return idx;\n    }\n\n    Index makeInternal(Index l, Index r, bool red){\n\
    \        auto idx = pool.alloc();\n        pool[idx] = Node(op, red, false, l,\
    \ r);\n        pool[idx].sum = f(pool[l].sum, pool[r].sum);\n        pool[idx].siz\
    \ = pool[l].siz + pool[r].siz;\n        pool[idx].level = pool[l].level + !pool[l].red;\n\
    \        return idx;\n    }\n\n    Index makeLeaf(T val, bool red){\n        auto\
    \ idx = pool.alloc();\n        pool[idx] = Node(val, red, true);\n        pool[idx].l\
    \ = pool[idx].r = nil;\n        pool[idx].level = 1;\n        return idx;\n  \
    \  }\n\n    Index mergeSub(Index ai, Index bi){\n        auto& a = get(ai);\n\
    \        auto& b = get(bi);\n        assert(ai != nil && bi != nil);\n       \
    \ if(a.level < b.level){\n            Index ci = mergeSub(ai, b.l);\n        \
    \    auto& c = get(ci);\n            if(!b.red && c.red && get(c.l).red){\n  \
    \              if(!get(b.r).red)\n                    return makeInternal(c.l,\
    \ makeInternal(c.r, b.r, true), false);\n                else\n              \
    \      return makeInternal(makeInternal(c.l, c.r, false), makeInternal(get(b.r).l,\
    \ get(b.r).r, false), true);\n            }\n            return makeInternal(ci,\
    \ b.r, b.red);\n        }\n        else if(a.level > b.level){\n            Index\
    \ ci = mergeSub(a.r, bi);\n            auto& c = get(ci);\n            if(!a.red\
    \ && c.red && get(c.r).red){\n                if(!get(a.l).red)\n            \
    \        return makeInternal(makeInternal(a.l, c.l, true), c.r, false);\n    \
    \            else\n                    return makeInternal(makeInternal(get(a.l).l,\
    \ get(a.l).r, false), makeInternal(c.l, c.r, false), true);\n            }\n \
    \           return makeInternal(a.l, ci, a.red);\n        }\n        else{\n \
    \           if(a.red)\n                ai = makeInternal(a.l, a.r, false);\n \
    \           if(b.red)\n                bi = makeInternal(b.l, b.r, false);\n \
    \           return makeInternal(ai, bi, true);\n        }\n    }\n\n    Index\
    \ merge(Index ai, Index bi){\n        if(ai == nil)\n            return bi;\n\
    \        if(bi == nil)\n            return ai;\n        Index ci = mergeSub(ai,\
    \ bi);\n        auto& c = get(ci);\n        if(c.red){\n            pool.free(ci);\n\
    \            return makeInternal(c.l, c.r, false);\n        }\n        return\
    \ ci;\n    }\n\n    pair<Index, Index> split(Index ai, int k){\n        if(ai\
    \ == nil)\n            return make_pair(nil, nil);\n        auto& a = get(ai);\n\
    \        if(k == 0)\n            return make_pair(nil, ai);\n        if(k == a.siz)\n\
    \            return make_pair(ai, nil);\n        Index li = a.l;\n        Index\
    \ ri = a.r;\n        auto& l = get(li);\n        if(k < l.siz){\n            auto\
    \ res = split(li, k);\n            return make_pair(res.first, merge(res.second,\
    \ ri));\n        }\n        else if(k > get(a.l).siz){\n            auto res =\
    \ split(ri, k - l.siz);\n            return make_pair(merge(li, res.first), res.second);\n\
    \        }\n        else{\n            return make_pair(li, ri);\n        }\n\
    \    }\n\n    pair<T, Index> range_get(Index pi, int l, int r){\n        auto\
    \ res = split(pi, r);\n        auto res2 = split(res.first, l);\n        T val\
    \ = get(res2.second).sum;\n        return make_pair(val, merge(merge(res2.first,\
    \ res2.second), res.second));\n    }\n\n    Index insert(Index pi, int k, T val){\n\
    \        auto res = split(pi, k);\n        return merge(res.first, merge(make(val),\
    \ res.second));\n    }\n\n    Index erase(Index pi, int k){\n        auto res\
    \ = split(pi, k + 1);\n        auto res2 = split(res.first, k);\n        return\
    \ merge(res2.first, res.second);\n    }\n\n    Index access(Index pi, int k){\n\
    \        while(get(pi).l != nil || get(pi).r != nil){\n            auto& p = get(pi);\n\
    \            assert(p.l != nil && p.r != nil);\n            if(get(p.l).siz <=\
    \ k){\n                k -= get(p.l).siz;\n                pi = p.r;\n       \
    \     }\n            else{\n                pi = p.l;\n            }\n       \
    \ }\n        return pi;\n    }\n\n    Index set(Index pi, int k, T val, function<T(T,\
    \ T)> g = [](T x, T y){return y;}){\n        stack<pair<Index, bool>> st;\n  \
    \      while(get(pi).l != nil || get(pi).r != nil){\n            auto& p = get(pi);\n\
    \            assert(p.l != nil && p.r != nil);\n            if(get(p.l).siz <=\
    \ k){\n                k -= get(p.l).siz;\n                st.emplace(pi, true);\n\
    \                pi = p.r;\n            }\n            else{\n               \
    \ st.emplace(pi, false);\n                pi = p.l;\n            }\n        }\n\
    \        Index new_idx = makeLeaf(g(get(pi).sum, val), get(pi).red);\n       \
    \ while(!st.empty()){\n            Index idx;\n            bool is_right;\n  \
    \          tie(idx, is_right) = st.top();\n            auto& p = get(idx);\n \
    \           if(is_right)\n                new_idx = makeInternal(p.l, new_idx,\
    \ p.red);\n            else\n                new_idx = makeInternal(new_idx, p.r,\
    \ p.red);\n            st.pop();\n        }\n        return new_idx;\n    }\n\n\
    \    void dump(Index pi, vector<T>& v){\n        auto& p = get(pi);\n        if(p.l\
    \ != nil)\n            dump(p.l, v);\n        v.emplace_back(get_val(pi));\n \
    \       if(p.r != nil)\n            dump(p.r, v);\n    }\n\n    vector<T> dump(Index\
    \ pi){\n        vector<T> v;\n        dump(pi, v);\n        return v;\n    }\n\
    \n    Index rebuild(Index pi){\n        auto v = dump(pi);\n        clear();\n\
    \        return build(v);\n    }\n\n    Node& get(Index k){return pool[k];}\n\
    \    Node& operator[](Index k){return pool[k];}\n};\n\n"
  code: "// verify: https://atcoder.jp/contests/joisc2012/submissions/12202620/\n\
    template <typename T>\nstruct RedBlackTree{\n\n    struct Node;\n    using Index\
    \ = typename MemoryPool<Node>::Index;\n\n    struct Node{\n        int siz, level;\n\
    \        T sum;\n        bool red;\n        typename MemoryPool<Node>::Index l,\
    \ r;\n        Node(){}\n        Node(T val, bool red, bool leaf, int li = -1,\
    \ int ri = -1) : sum(val), siz(leaf), level(0), red(red){\n            l = {li};\n\
    \            r = {ri};\n        }\n        Node(T val, bool red, bool leaf, Index\
    \ l, Index r) : sum(val), siz(leaf), level(0), red(red), l(l), r(r){}\n    };\n\
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
    \        pool.st.push(i);\n    }\n\n    Index index(int x){return {x};}\n\n  \
    \  T get_val(Index pi, int k){\n        pi = access(pi, k);\n        return get(pi).sum;\n\
    \    }\n\n    Index make(T val){\n        Index idx = pool.alloc();\n        pool[idx]\
    \ = Node(val, false, true, nil.idx, nil.idx);\n        pool[idx].level = 1;\n\
    \        return idx;\n    }\n\n    Index makeInternal(Index l, Index r, bool red){\n\
    \        auto idx = pool.alloc();\n        pool[idx] = Node(op, red, false, l,\
    \ r);\n        pool[idx].sum = f(pool[l].sum, pool[r].sum);\n        pool[idx].siz\
    \ = pool[l].siz + pool[r].siz;\n        pool[idx].level = pool[l].level + !pool[l].red;\n\
    \        return idx;\n    }\n\n    Index makeLeaf(T val, bool red){\n        auto\
    \ idx = pool.alloc();\n        pool[idx] = Node(val, red, true);\n        pool[idx].l\
    \ = pool[idx].r = nil;\n        pool[idx].level = 1;\n        return idx;\n  \
    \  }\n\n    Index mergeSub(Index ai, Index bi){\n        auto& a = get(ai);\n\
    \        auto& b = get(bi);\n        assert(ai != nil && bi != nil);\n       \
    \ if(a.level < b.level){\n            Index ci = mergeSub(ai, b.l);\n        \
    \    auto& c = get(ci);\n            if(!b.red && c.red && get(c.l).red){\n  \
    \              if(!get(b.r).red)\n                    return makeInternal(c.l,\
    \ makeInternal(c.r, b.r, true), false);\n                else\n              \
    \      return makeInternal(makeInternal(c.l, c.r, false), makeInternal(get(b.r).l,\
    \ get(b.r).r, false), true);\n            }\n            return makeInternal(ci,\
    \ b.r, b.red);\n        }\n        else if(a.level > b.level){\n            Index\
    \ ci = mergeSub(a.r, bi);\n            auto& c = get(ci);\n            if(!a.red\
    \ && c.red && get(c.r).red){\n                if(!get(a.l).red)\n            \
    \        return makeInternal(makeInternal(a.l, c.l, true), c.r, false);\n    \
    \            else\n                    return makeInternal(makeInternal(get(a.l).l,\
    \ get(a.l).r, false), makeInternal(c.l, c.r, false), true);\n            }\n \
    \           return makeInternal(a.l, ci, a.red);\n        }\n        else{\n \
    \           if(a.red)\n                ai = makeInternal(a.l, a.r, false);\n \
    \           if(b.red)\n                bi = makeInternal(b.l, b.r, false);\n \
    \           return makeInternal(ai, bi, true);\n        }\n    }\n\n    Index\
    \ merge(Index ai, Index bi){\n        if(ai == nil)\n            return bi;\n\
    \        if(bi == nil)\n            return ai;\n        Index ci = mergeSub(ai,\
    \ bi);\n        auto& c = get(ci);\n        if(c.red){\n            pool.free(ci);\n\
    \            return makeInternal(c.l, c.r, false);\n        }\n        return\
    \ ci;\n    }\n\n    pair<Index, Index> split(Index ai, int k){\n        if(ai\
    \ == nil)\n            return make_pair(nil, nil);\n        auto& a = get(ai);\n\
    \        if(k == 0)\n            return make_pair(nil, ai);\n        if(k == a.siz)\n\
    \            return make_pair(ai, nil);\n        Index li = a.l;\n        Index\
    \ ri = a.r;\n        auto& l = get(li);\n        if(k < l.siz){\n            auto\
    \ res = split(li, k);\n            return make_pair(res.first, merge(res.second,\
    \ ri));\n        }\n        else if(k > get(a.l).siz){\n            auto res =\
    \ split(ri, k - l.siz);\n            return make_pair(merge(li, res.first), res.second);\n\
    \        }\n        else{\n            return make_pair(li, ri);\n        }\n\
    \    }\n\n    pair<T, Index> range_get(Index pi, int l, int r){\n        auto\
    \ res = split(pi, r);\n        auto res2 = split(res.first, l);\n        T val\
    \ = get(res2.second).sum;\n        return make_pair(val, merge(merge(res2.first,\
    \ res2.second), res.second));\n    }\n\n    Index insert(Index pi, int k, T val){\n\
    \        auto res = split(pi, k);\n        return merge(res.first, merge(make(val),\
    \ res.second));\n    }\n\n    Index erase(Index pi, int k){\n        auto res\
    \ = split(pi, k + 1);\n        auto res2 = split(res.first, k);\n        return\
    \ merge(res2.first, res.second);\n    }\n\n    Index access(Index pi, int k){\n\
    \        while(get(pi).l != nil || get(pi).r != nil){\n            auto& p = get(pi);\n\
    \            assert(p.l != nil && p.r != nil);\n            if(get(p.l).siz <=\
    \ k){\n                k -= get(p.l).siz;\n                pi = p.r;\n       \
    \     }\n            else{\n                pi = p.l;\n            }\n       \
    \ }\n        return pi;\n    }\n\n    Index set(Index pi, int k, T val, function<T(T,\
    \ T)> g = [](T x, T y){return y;}){\n        stack<pair<Index, bool>> st;\n  \
    \      while(get(pi).l != nil || get(pi).r != nil){\n            auto& p = get(pi);\n\
    \            assert(p.l != nil && p.r != nil);\n            if(get(p.l).siz <=\
    \ k){\n                k -= get(p.l).siz;\n                st.emplace(pi, true);\n\
    \                pi = p.r;\n            }\n            else{\n               \
    \ st.emplace(pi, false);\n                pi = p.l;\n            }\n        }\n\
    \        Index new_idx = makeLeaf(g(get(pi).sum, val), get(pi).red);\n       \
    \ while(!st.empty()){\n            Index idx;\n            bool is_right;\n  \
    \          tie(idx, is_right) = st.top();\n            auto& p = get(idx);\n \
    \           if(is_right)\n                new_idx = makeInternal(p.l, new_idx,\
    \ p.red);\n            else\n                new_idx = makeInternal(new_idx, p.r,\
    \ p.red);\n            st.pop();\n        }\n        return new_idx;\n    }\n\n\
    \    void dump(Index pi, vector<T>& v){\n        auto& p = get(pi);\n        if(p.l\
    \ != nil)\n            dump(p.l, v);\n        v.emplace_back(get_val(pi));\n \
    \       if(p.r != nil)\n            dump(p.r, v);\n    }\n\n    vector<T> dump(Index\
    \ pi){\n        vector<T> v;\n        dump(pi, v);\n        return v;\n    }\n\
    \n    Index rebuild(Index pi){\n        auto v = dump(pi);\n        clear();\n\
    \        return build(v);\n    }\n\n    Node& get(Index k){return pool[k];}\n\
    \    Node& operator[](Index k){return pool[k];}\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/redblacktree_persistent.cpp
  requiredBy: []
  timestamp: '2020-04-22 12:46:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/redblacktree_persistent.cpp
layout: document
redirect_from:
- /library/lib/classes/redblacktree_persistent.cpp
- /library/lib/classes/redblacktree_persistent.cpp.html
title: lib/classes/redblacktree_persistent.cpp
---
