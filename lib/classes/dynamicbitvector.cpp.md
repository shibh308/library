---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/dynamicwaveletmatrix_rmq.test.cpp
    title: verify/dynamicwaveletmatrix_rmq.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/dynamicwaveletmatrix_kthmin.test.cpp
    title: verify/dynamicwaveletmatrix_kthmin.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/dynamicbitvector.cpp\"\nstruct DynamicBitVector{\n\
    \    struct Node;\n    using Index = MemoryPool<Node>::Index;\n    MemoryPool<Node>\
    \ pool;\n    struct Node{\n        int siz, cnt, height;\n        short len;\n\
    \        uint64_t val;\n        MemoryPool<Node>::Index l, r;\n        Node(){}\n\
    \        Node(int siz, int cnt, int height, short len, uint64_t val, MemoryPool<Node>::Index\
    \ nil) :\n                siz(siz), cnt(cnt), height(height), len(len), val(val),\
    \ l(nil), r(nil){}\n    };\n    Index root, nil;\n\n    int rank_val;\n    bool\
    \ erase_fl;\n\n    DynamicBitVector(){\n        nil = pool.alloc();\n        auto&\
    \ p = get(nil);\n        p.cnt = p.val = p.siz = p.height = p.len = 0;\n     \
    \   p.l = p.r = nil;\n    }\n\n    Index build(int n, vector<uint64_t>& a, int\
    \ l, int r){\n        assert(n >= 0);\n        int mid = (l + r) / 2;\n      \
    \  Index l_idx = l == mid ? nil : build(n, a, l, mid);\n        Index r_idx =\
    \ mid + 1 == r ? nil : build(n, a, mid + 1, r);\n        Index idx = pool.alloc();\n\
    \        pool[idx] = Node(0, 0, 0, mid + 1 == a.size() ? n - (a.size() - 1) *\
    \ 32 : 32, a[mid], nil);\n        pool[idx].l = l_idx;\n        pool[idx].r =\
    \ r_idx;\n        update(idx);\n\n        return idx;\n    }\n\n    void update(Index\
    \ pi){\n        if(pi == nil)\n            return;\n        auto& p = get(pi);\n\
    \        auto& l = get(p.l);\n        auto& r = get(p.r);\n        p.siz = l.siz\
    \ + r.siz + p.len;\n        p.height = max(l.height, r.height) + 1;\n        p.cnt\
    \ = l.cnt + r.cnt + __builtin_popcountll(p.val);\n    }\n\n    int balance_factor(Index\
    \ pi){return get(get(pi).l).height - get(get(pi).r).height;}\n\n    Index rotl(Index\
    \ pi){\n        assert(pi != nil);\n        auto& p = get(pi);\n        Index\
    \ qi = p.r;\n        assert(qi != nil);\n        auto& q = get(qi);\n        p.r\
    \ = q.l;\n        q.l = pi;\n        update(pi);\n        update(qi);\n      \
    \  return qi;\n    }\n\n    Index rotr(Index pi){\n        assert(pi != nil);\n\
    \        auto& p = get(pi);\n        Index qi = p.l;\n        assert(qi != nil);\n\
    \        auto& q = get(qi);\n        p.l = q.r;\n        q.r = pi;\n        update(pi);\n\
    \        update(qi);\n        return qi;\n    }\n\n    Index balance(Index pi){\n\
    \        if(balance_factor(pi) == 2){\n            auto& p = get(pi);\n      \
    \      if(balance_factor(p.l) < 0)\n                p.l = rotl(p.l);\n       \
    \     return rotr(pi);\n        }\n        if(balance_factor(pi) == -2){\n   \
    \         auto& p = get(pi);\n            if(balance_factor(p.r) > 0)\n      \
    \          p.r = rotr(p.r);\n            return rotl(pi);\n        }\n       \
    \ update(pi);\n        return pi;\n    }\n\n    Index _insert(Index pi, Index\
    \ new_idx){\n        if(pi == nil)\n            return new_idx;\n        auto&\
    \ p = get(pi);\n        p.l = _insert(p.l, new_idx);\n        return balance(pi);\n\
    \    }\n\n    Index insert(Index pi, int k, bool fl){\n        if(pi == nil){\n\
    \            Index idx = pool.alloc();\n            pool[idx] = Node(1, fl, 1,\
    \ 1, fl, nil);\n            return idx;\n        }\n        auto& p = get(pi);\n\
    \        auto& l = get(p.l);\n        auto& r = get(p.r);\n        if(k <= l.siz\
    \ && p.l != nil){\n            p.l = insert(p.l, k, fl);\n        }\n        else\
    \ if(k <= l.siz + p.len){\n            k -= l.siz;\n            rank_val += get(p.l).cnt\
    \ + __builtin_popcountll(p.val & ((1uLL << k) - 1));\n            p.val = (p.val\
    \ & ((1uLL << k) - 1)) | ((p.val & ~((1uLL << k) - 1)) << 1) | (uint64_t(fl) <<\
    \ k);\n            if(++p.len == 64){\n                uint64_t vl = p.val & ((1uLL\
    \ << 32) - 1);\n                uint64_t vr = p.val >> 32;\n                p.val\
    \ = vl;\n                p.len = 32;\n                Index r_idx = pool.alloc();\n\
    \                pool[r_idx] = Node(32, __builtin_popcountll(vr), 1, 32, vr, nil);\n\
    \                p.r = _insert(p.r, r_idx);\n            }\n        }\n      \
    \  else{\n            rank_val += get(p.l).cnt + __builtin_popcountll(p.val);\n\
    \            p.r = insert(p.r, k - p.len - l.siz, fl);\n        }\n        return\
    \ balance(pi);\n    }\n\n    Index _erase_left(Index pi, Index root_idx){\n  \
    \      auto& p = get(pi);\n        if(p.l == nil){\n            if(!merge(root_idx,\
    \ pi, true)){\n                Index qi = p.r;\n                pool.free(pi);\n\
    \                return qi;\n            }\n        }\n        else\n        \
    \    p.l = _erase_left(p.l, root_idx);\n        return balance(pi);\n    }\n\n\
    \    Index _erase_right(Index pi, Index root_idx){\n        auto& p = get(pi);\n\
    \        if(p.r == nil){\n            if(!merge(root_idx, pi, false)){\n     \
    \           Index qi = p.l;\n                pool.free(pi);\n                return\
    \ qi;\n            }\n        }\n        else{\n            p.r = _erase_right(p.r,\
    \ root_idx);\n        }\n        return balance(pi);\n    }\n\n    // ai\u3068\
    bi\u3092\u30DE\u30FC\u30B8\u3057\u3066, \u3082\u30571\u3064\u306B\u3067\u304D\u308B\
    \u306A\u3089ai\u3092\u6B8B\u3059\n    bool merge(Index ai, Index bi, bool a_left){\n\
    \        auto& a = get(ai);\n        auto& b = get(bi);\n        if(!a_left){\n\
    \            swap(a.val, b.val);\n            swap(a.len, b.len);\n        }\n\
    \        short len_sum = a.len + b.len;\n        if(len_sum <= 64){\n        \
    \    a.val = a.val | (b.val << a.len);\n            a.len = len_sum;\n       \
    \     update(ai);\n            return false;\n        }\n        else{\n     \
    \       uint32_t mid = (a.len + b.len) >> 1;\n            uint64_t av, bv;\n \
    \           if(a.len >= mid){\n                av = a.val & ((1uLL << mid) - 1);\n\
    \                bv = (a.val >> mid) | (b.val << (a.len - mid));\n           \
    \ }\n            else{\n                av = (a.val | (b.val << a.len)) & ((1uLL\
    \ << mid) - 1);\n                bv = b.val >> (mid - a.len);\n            }\n\
    \n            a.val = av;\n            b.val = bv;\n            a.len = mid;\n\
    \            b.len = len_sum - mid;\n            if(!a_left){\n              \
    \  swap(a.val, b.val);\n                swap(a.len, b.len);\n            }\n \
    \           return true;\n        }\n    }\n\n    Index erase(Index pi, int k,\
    \ Index par = {-1}){\n        if(par.idx == -1)\n            par = nil;\n    \
    \    if(pi == nil)\n            return nil;\n        auto& p = get(pi);\n    \
    \    auto& l = get(p.l);\n        auto& r = get(p.r);\n        if(k < l.siz)\n\
    \            p.l = erase(p.l, k);\n        else if(k < l.siz + p.len){\n     \
    \       k -= l.siz;\n            --p.len;\n            rank_val += get(p.l).cnt\
    \ + __builtin_popcountll(p.val & ((1uLL << k) - 1));\n            erase_fl = (p.val\
    \ >> k) & 1;\n            p.val = (p.val & ((1uLL << k) - 1)) | ((p.val & ~((1uLL\
    \ << (k + 1)) - 1)) >> 1);\n\n            if(p.len <= 16){\n                if(p.l\
    \ != nil){\n                    p.l = _erase_right(p.l, pi);\n               \
    \ }\n                else if(p.r != nil){\n                    p.r = _erase_left(p.r,\
    \ pi);\n                }\n                else{\n                    if(par ==\
    \ nil){\n                        if(p.len == 0){\n                           \
    \ pool.free(pi);\n                            return nil;\n                  \
    \      }\n                        update(pi);\n                        return\
    \ pi;\n                    }\n                    else{\n                    \
    \    auto& parent = get(par);\n                        if(parent.l == pi){\n \
    \                           if(!merge(par, pi, false)){\n                    \
    \            pool.free(pi);\n                                return nil;\n   \
    \                         }\n                        }\n                     \
    \   else{\n                            assert(parent.r == pi);\n             \
    \               if(!merge(par, pi, true)){\n                                pool.free(pi);\n\
    \                                return nil;\n                            }\n\
    \                        }\n                    }\n                }\n       \
    \     }\n        }\n        else{\n            rank_val += get(p.l).cnt + __builtin_popcountll(p.val);\n\
    \            p.r = erase(p.r, k - p.len - l.siz);\n        }\n        return balance(pi);\n\
    \    }\n\n    int rank(Index pi, int k){\n        if(pi == nil)\n            return\
    \ 0;\n        auto& p = get(pi);\n        auto& l = get(p.l);\n        if(k <\
    \ l.siz)\n            return rank(p.l, k);\n        else if(k < l.siz + p.len)\n\
    \            return l.cnt + __builtin_popcountll(p.val & ((1uLL << (k - l.siz))\
    \ - 1));\n        else\n            return l.cnt + __builtin_popcountll(p.val)\
    \ + rank(p.r, k - l.siz - p.len);\n    }\n\n    bool access(Index pi, int k){\n\
    \        assert(pi != nil);\n        auto& p = get(pi);\n        assert(0 <= k\
    \ && k < p.siz);\n        auto& l = get(p.l);\n        assert(p.siz == p.len +\
    \ l.siz + get(p.r).siz);\n        if(k < l.siz)\n            return access(p.l,\
    \ k);\n        else if(k < l.siz + p.len)\n            return (p.val >> (k - l.siz))\
    \ & 1;\n        else\n            return access(p.r, k - l.siz - p.len);\n   \
    \ }\n\n    Node& get(Index k){return pool[k];}\n    Node& operator[](Index k){return\
    \ pool[k];}\n\n    void build(int n, vector<uint64_t>& a){\n        root = build(n,\
    \ a, 0, a.size());\n        assert(get(root).siz == n);\n    }\n\n    void insert(int\
    \ k, bool fl){\n        rank_val = 0;\n        root = insert(root, k, fl);\n \
    \   }\n\n    void erase(int k){\n        rank_val = 0;\n        root = erase(root,\
    \ k);\n    }\n\n    int rank(int k, bool fl = true){\n        return fl ? rank(root,\
    \ k) : k - rank(root, k);\n    }\n\n    bool access(int k){\n        return access(root,\
    \ k);\n    }\n\n    int zero_cnt(){\n        return get(root).siz - get(root).cnt;\n\
    \    }\n};\n\n"
  code: "struct DynamicBitVector{\n    struct Node;\n    using Index = MemoryPool<Node>::Index;\n\
    \    MemoryPool<Node> pool;\n    struct Node{\n        int siz, cnt, height;\n\
    \        short len;\n        uint64_t val;\n        MemoryPool<Node>::Index l,\
    \ r;\n        Node(){}\n        Node(int siz, int cnt, int height, short len,\
    \ uint64_t val, MemoryPool<Node>::Index nil) :\n                siz(siz), cnt(cnt),\
    \ height(height), len(len), val(val), l(nil), r(nil){}\n    };\n    Index root,\
    \ nil;\n\n    int rank_val;\n    bool erase_fl;\n\n    DynamicBitVector(){\n \
    \       nil = pool.alloc();\n        auto& p = get(nil);\n        p.cnt = p.val\
    \ = p.siz = p.height = p.len = 0;\n        p.l = p.r = nil;\n    }\n\n    Index\
    \ build(int n, vector<uint64_t>& a, int l, int r){\n        assert(n >= 0);\n\
    \        int mid = (l + r) / 2;\n        Index l_idx = l == mid ? nil : build(n,\
    \ a, l, mid);\n        Index r_idx = mid + 1 == r ? nil : build(n, a, mid + 1,\
    \ r);\n        Index idx = pool.alloc();\n        pool[idx] = Node(0, 0, 0, mid\
    \ + 1 == a.size() ? n - (a.size() - 1) * 32 : 32, a[mid], nil);\n        pool[idx].l\
    \ = l_idx;\n        pool[idx].r = r_idx;\n        update(idx);\n\n        return\
    \ idx;\n    }\n\n    void update(Index pi){\n        if(pi == nil)\n         \
    \   return;\n        auto& p = get(pi);\n        auto& l = get(p.l);\n       \
    \ auto& r = get(p.r);\n        p.siz = l.siz + r.siz + p.len;\n        p.height\
    \ = max(l.height, r.height) + 1;\n        p.cnt = l.cnt + r.cnt + __builtin_popcountll(p.val);\n\
    \    }\n\n    int balance_factor(Index pi){return get(get(pi).l).height - get(get(pi).r).height;}\n\
    \n    Index rotl(Index pi){\n        assert(pi != nil);\n        auto& p = get(pi);\n\
    \        Index qi = p.r;\n        assert(qi != nil);\n        auto& q = get(qi);\n\
    \        p.r = q.l;\n        q.l = pi;\n        update(pi);\n        update(qi);\n\
    \        return qi;\n    }\n\n    Index rotr(Index pi){\n        assert(pi !=\
    \ nil);\n        auto& p = get(pi);\n        Index qi = p.l;\n        assert(qi\
    \ != nil);\n        auto& q = get(qi);\n        p.l = q.r;\n        q.r = pi;\n\
    \        update(pi);\n        update(qi);\n        return qi;\n    }\n\n    Index\
    \ balance(Index pi){\n        if(balance_factor(pi) == 2){\n            auto&\
    \ p = get(pi);\n            if(balance_factor(p.l) < 0)\n                p.l =\
    \ rotl(p.l);\n            return rotr(pi);\n        }\n        if(balance_factor(pi)\
    \ == -2){\n            auto& p = get(pi);\n            if(balance_factor(p.r)\
    \ > 0)\n                p.r = rotr(p.r);\n            return rotl(pi);\n     \
    \   }\n        update(pi);\n        return pi;\n    }\n\n    Index _insert(Index\
    \ pi, Index new_idx){\n        if(pi == nil)\n            return new_idx;\n  \
    \      auto& p = get(pi);\n        p.l = _insert(p.l, new_idx);\n        return\
    \ balance(pi);\n    }\n\n    Index insert(Index pi, int k, bool fl){\n       \
    \ if(pi == nil){\n            Index idx = pool.alloc();\n            pool[idx]\
    \ = Node(1, fl, 1, 1, fl, nil);\n            return idx;\n        }\n        auto&\
    \ p = get(pi);\n        auto& l = get(p.l);\n        auto& r = get(p.r);\n   \
    \     if(k <= l.siz && p.l != nil){\n            p.l = insert(p.l, k, fl);\n \
    \       }\n        else if(k <= l.siz + p.len){\n            k -= l.siz;\n   \
    \         rank_val += get(p.l).cnt + __builtin_popcountll(p.val & ((1uLL << k)\
    \ - 1));\n            p.val = (p.val & ((1uLL << k) - 1)) | ((p.val & ~((1uLL\
    \ << k) - 1)) << 1) | (uint64_t(fl) << k);\n            if(++p.len == 64){\n \
    \               uint64_t vl = p.val & ((1uLL << 32) - 1);\n                uint64_t\
    \ vr = p.val >> 32;\n                p.val = vl;\n                p.len = 32;\n\
    \                Index r_idx = pool.alloc();\n                pool[r_idx] = Node(32,\
    \ __builtin_popcountll(vr), 1, 32, vr, nil);\n                p.r = _insert(p.r,\
    \ r_idx);\n            }\n        }\n        else{\n            rank_val += get(p.l).cnt\
    \ + __builtin_popcountll(p.val);\n            p.r = insert(p.r, k - p.len - l.siz,\
    \ fl);\n        }\n        return balance(pi);\n    }\n\n    Index _erase_left(Index\
    \ pi, Index root_idx){\n        auto& p = get(pi);\n        if(p.l == nil){\n\
    \            if(!merge(root_idx, pi, true)){\n                Index qi = p.r;\n\
    \                pool.free(pi);\n                return qi;\n            }\n \
    \       }\n        else\n            p.l = _erase_left(p.l, root_idx);\n     \
    \   return balance(pi);\n    }\n\n    Index _erase_right(Index pi, Index root_idx){\n\
    \        auto& p = get(pi);\n        if(p.r == nil){\n            if(!merge(root_idx,\
    \ pi, false)){\n                Index qi = p.l;\n                pool.free(pi);\n\
    \                return qi;\n            }\n        }\n        else{\n       \
    \     p.r = _erase_right(p.r, root_idx);\n        }\n        return balance(pi);\n\
    \    }\n\n    // ai\u3068bi\u3092\u30DE\u30FC\u30B8\u3057\u3066, \u3082\u3057\
    1\u3064\u306B\u3067\u304D\u308B\u306A\u3089ai\u3092\u6B8B\u3059\n    bool merge(Index\
    \ ai, Index bi, bool a_left){\n        auto& a = get(ai);\n        auto& b = get(bi);\n\
    \        if(!a_left){\n            swap(a.val, b.val);\n            swap(a.len,\
    \ b.len);\n        }\n        short len_sum = a.len + b.len;\n        if(len_sum\
    \ <= 64){\n            a.val = a.val | (b.val << a.len);\n            a.len =\
    \ len_sum;\n            update(ai);\n            return false;\n        }\n  \
    \      else{\n            uint32_t mid = (a.len + b.len) >> 1;\n            uint64_t\
    \ av, bv;\n            if(a.len >= mid){\n                av = a.val & ((1uLL\
    \ << mid) - 1);\n                bv = (a.val >> mid) | (b.val << (a.len - mid));\n\
    \            }\n            else{\n                av = (a.val | (b.val << a.len))\
    \ & ((1uLL << mid) - 1);\n                bv = b.val >> (mid - a.len);\n     \
    \       }\n\n            a.val = av;\n            b.val = bv;\n            a.len\
    \ = mid;\n            b.len = len_sum - mid;\n            if(!a_left){\n     \
    \           swap(a.val, b.val);\n                swap(a.len, b.len);\n       \
    \     }\n            return true;\n        }\n    }\n\n    Index erase(Index pi,\
    \ int k, Index par = {-1}){\n        if(par.idx == -1)\n            par = nil;\n\
    \        if(pi == nil)\n            return nil;\n        auto& p = get(pi);\n\
    \        auto& l = get(p.l);\n        auto& r = get(p.r);\n        if(k < l.siz)\n\
    \            p.l = erase(p.l, k);\n        else if(k < l.siz + p.len){\n     \
    \       k -= l.siz;\n            --p.len;\n            rank_val += get(p.l).cnt\
    \ + __builtin_popcountll(p.val & ((1uLL << k) - 1));\n            erase_fl = (p.val\
    \ >> k) & 1;\n            p.val = (p.val & ((1uLL << k) - 1)) | ((p.val & ~((1uLL\
    \ << (k + 1)) - 1)) >> 1);\n\n            if(p.len <= 16){\n                if(p.l\
    \ != nil){\n                    p.l = _erase_right(p.l, pi);\n               \
    \ }\n                else if(p.r != nil){\n                    p.r = _erase_left(p.r,\
    \ pi);\n                }\n                else{\n                    if(par ==\
    \ nil){\n                        if(p.len == 0){\n                           \
    \ pool.free(pi);\n                            return nil;\n                  \
    \      }\n                        update(pi);\n                        return\
    \ pi;\n                    }\n                    else{\n                    \
    \    auto& parent = get(par);\n                        if(parent.l == pi){\n \
    \                           if(!merge(par, pi, false)){\n                    \
    \            pool.free(pi);\n                                return nil;\n   \
    \                         }\n                        }\n                     \
    \   else{\n                            assert(parent.r == pi);\n             \
    \               if(!merge(par, pi, true)){\n                                pool.free(pi);\n\
    \                                return nil;\n                            }\n\
    \                        }\n                    }\n                }\n       \
    \     }\n        }\n        else{\n            rank_val += get(p.l).cnt + __builtin_popcountll(p.val);\n\
    \            p.r = erase(p.r, k - p.len - l.siz);\n        }\n        return balance(pi);\n\
    \    }\n\n    int rank(Index pi, int k){\n        if(pi == nil)\n            return\
    \ 0;\n        auto& p = get(pi);\n        auto& l = get(p.l);\n        if(k <\
    \ l.siz)\n            return rank(p.l, k);\n        else if(k < l.siz + p.len)\n\
    \            return l.cnt + __builtin_popcountll(p.val & ((1uLL << (k - l.siz))\
    \ - 1));\n        else\n            return l.cnt + __builtin_popcountll(p.val)\
    \ + rank(p.r, k - l.siz - p.len);\n    }\n\n    bool access(Index pi, int k){\n\
    \        assert(pi != nil);\n        auto& p = get(pi);\n        assert(0 <= k\
    \ && k < p.siz);\n        auto& l = get(p.l);\n        assert(p.siz == p.len +\
    \ l.siz + get(p.r).siz);\n        if(k < l.siz)\n            return access(p.l,\
    \ k);\n        else if(k < l.siz + p.len)\n            return (p.val >> (k - l.siz))\
    \ & 1;\n        else\n            return access(p.r, k - l.siz - p.len);\n   \
    \ }\n\n    Node& get(Index k){return pool[k];}\n    Node& operator[](Index k){return\
    \ pool[k];}\n\n    void build(int n, vector<uint64_t>& a){\n        root = build(n,\
    \ a, 0, a.size());\n        assert(get(root).siz == n);\n    }\n\n    void insert(int\
    \ k, bool fl){\n        rank_val = 0;\n        root = insert(root, k, fl);\n \
    \   }\n\n    void erase(int k){\n        rank_val = 0;\n        root = erase(root,\
    \ k);\n    }\n\n    int rank(int k, bool fl = true){\n        return fl ? rank(root,\
    \ k) : k - rank(root, k);\n    }\n\n    bool access(int k){\n        return access(root,\
    \ k);\n    }\n\n    int zero_cnt(){\n        return get(root).siz - get(root).cnt;\n\
    \    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/dynamicbitvector.cpp
  requiredBy: []
  timestamp: '2020-04-25 21:27:24+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/dynamicwaveletmatrix_rmq.test.cpp
  - verify/dynamicwaveletmatrix_kthmin.test.cpp
documentation_of: lib/classes/dynamicbitvector.cpp
layout: document
redirect_from:
- /library/lib/classes/dynamicbitvector.cpp
- /library/lib/classes/dynamicbitvector.cpp.html
title: lib/classes/dynamicbitvector.cpp
---
