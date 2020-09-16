---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/zdd_knapsack.test.cpp
    title: verify/zdd_knapsack.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/zdd.cpp\"\nstruct ZDD{\n    struct Node{\n \
    \       int label;\n        using Index = typename MemoryPool<Node>::Index;\n\
    \        Index c[2];\n        Node(){}\n        Node(int label, Index nil) : label(label){\n\
    \            c[0] = c[1] = nil;\n        }\n        Node(int label, Index l, Index\
    \ r) : label(label){\n            c[0] = l;\n            c[1] = r;\n        }\n\
    \    };\n    using Index = typename MemoryPool<Node>::Index;\n    Index nil, true_idx,\
    \ false_idx;\n    MemoryPool<Node> pool;\n    // \u5F15\u6570\u306F(Data, label,\
    \ \u6700\u5F8C\u3069\u3046\u9032\u3093\u3060\u304B)\n    // second\u304C-1\u306A\
    \u3089Data\u3092\u8868\u3059, 0/1\u306A\u3089\u7D42\u7AEF\u72B6\u614B\u3092\u8868\
    \u3059\n    ZDD(){\n        nil = {-1};\n        true_idx = {-2};\n        false_idx\
    \ = {-3};\n    }\n    template<typename Data>\n    Index build(function<pair<Data,\
    \ int>(Data, int, bool)> f, Data init){\n        unordered_map<int, map<Data,\
    \ Index>> node_map;\n        Index root = pool.alloc();\n        pool[root] =\
    \ Node(0, nil);\n        node_map[0][init] = root;\n        build<Data>(root,\
    \ init, f, node_map);\n        return compress(root);\n    }\n    template<typename\
    \ Data>\n    void build(Index pi, Data& d, function<pair<Data, int>(Data, int,\
    \ bool)>& f, unordered_map<int, map<Data, Index>>& node_map){\n        auto& x\
    \ = pool[pi];\n        for(int i = 0; i < 2; ++i){\n            int fl;\n    \
    \        Data y;\n            tie(y, fl) = f(d, x.label, i);\n            if(fl\
    \ == 0){\n                x.c[i] = false_idx;\n            }\n            else\
    \ if(fl == 1){\n                x.c[i] = true_idx;\n            }\n          \
    \  else if(node_map[x.label + 1].find(y) == node_map[x.label + 1].end()){\n  \
    \              Index new_idx = pool.alloc();\n                pool[new_idx] =\
    \ Node(x.label + 1, nil);\n                node_map[x.label + 1][y] = new_idx;\n\
    \                x.c[i] = new_idx;\n                build(node_map[x.label + 1][y],\
    \ y, f, node_map);\n            }else{\n                x.c[i] = node_map[x.label\
    \ + 1][y];\n            }\n        }\n    }\n    Index compress(Index pi, unordered_map<int,\
    \ unordered_map<uint64_t, Index>>& node_map, unordered_map<int, Index>& replace_map){\n\
    \        // \u540C\u578B\u3067\u5B50\u304C\u4E00\u81F4\u3059\u308B\u9802\u70B9\
    \u3092\u7834\u6EC5\n        if(pi == true_idx || pi == false_idx)\n          \
    \  return pi;\n        if(replace_map.find(pi.idx) != replace_map.end())\n   \
    \         return replace_map[pi.idx];\n        auto& p = pool[pi];\n        Index\
    \ li = compress(p.c[0], node_map, replace_map);\n        Index ri = compress(p.c[1],\
    \ node_map, replace_map);\n        p.c[0] = li;\n        p.c[1] = ri;\n      \
    \  uint64_t h = uint32_t(li.idx) | ((1uLL * uint32_t(ri.idx)) << 32);\n      \
    \  if(node_map[p.label].find(h) == node_map[p.label].end())\n            node_map[p.label][h]\
    \ = pi;\n        else\n            pool.free(pi);\n        return replace_map[pi.idx]\
    \ = node_map[p.label][h];\n    }\n    Index compress(Index pi){\n        unordered_map<int,\
    \ unordered_map<uint64_t, Index>> node_map;\n        unordered_map<int, Index>\
    \ replace_map;\n        return compress(pi, node_map, replace_map);\n    }\n \
    \   i64 linear_func_max(Index pi, vector<i64>& a, unordered_map<int, i64>& res){\n\
    \        if(pi == true_idx)\n            return 0;\n        if(pi == false_idx)\n\
    \            return -INF;\n        if(res.find(pi.idx) == res.end())\n       \
    \     res[pi.idx] = max(linear_func_max(pool[pi].c[0], a, res), linear_func_max(pool[pi].c[1],\
    \ a, res) + a[pool[pi].label]);\n        return res[pi.idx];\n    }\n    i64 linear_func_max(Index\
    \ root, vector<i64> a){\n        unordered_map<int, i64> res;\n        return\
    \ linear_func_max(root, a, res);\n    }\n    i64 count(Index pi, unordered_map<int,\
    \ i64>& res){\n        if(pi == true_idx)\n            return 1;\n        if(pi\
    \ == false_idx)\n            return 0;\n        if(res.find(pi.idx) == res.end())\n\
    \            res[pi.idx] = count(pool[pi].c[0], res) + count(pool[pi].c[1], res);\n\
    \        return res[pi.idx];\n    }\n    i64 count(Index root){\n        unordered_map<int,\
    \ i64> res;\n        return count(root, res);\n    }\n    double get_per(Index\
    \ pi, vector<double>& a, unordered_map<int, double>& res){\n        if(pi == true_idx)\n\
    \            return 1;\n        if(pi == false_idx)\n            return 0;\n \
    \       if(res.find(pi.idx) == res.end())\n            res[pi.idx] = a[pool[pi].label]\
    \ * get_per(pool[pi].c[0], a, res) + (1.0 - a[pool[pi].label]) * get_per(pool[pi].c[1],\
    \ a, res);\n        return res[pi.idx];\n    }\n    double get_per(Index root,\
    \ vector<double>& a){\n        unordered_map<int, double> res;\n        return\
    \ get_per(root, a, res);\n    }\n    Index apply(Index li, Index ri, function<Index(Index,\
    \ Index)>& f, unordered_map<uint64_t, Index>& node_map){\n        Index res =\
    \ f(li, ri);\n        if(res != nil)\n            return res;\n        int lidx,\
    \ ridx;\n        tie(lidx, ridx) = minmax(li.idx, ri.idx);\n        uint64_t h\
    \ = lidx | ((1uLL * ridx) << 32);\n        if(node_map.find(h) != node_map.end())\n\
    \            return node_map[h];\n        if(pool[li].label < pool[ri].label)\n\
    \            swap(li, ri);\n        auto& l = pool[li];\n        auto& r = pool[ri];\n\
    \        Index idx = pool.alloc();\n        if(l.label == r.label)\n         \
    \   pool[idx] = Node(l.label, apply(l.c[0], r.c[0], f, node_map), apply(l.c[1],\
    \ r.c[1], f, node_map));\n        else\n            pool[idx] = Node(l.label,\
    \ apply(l.c[0], ri, f, node_map), apply(l.c[1], ri, f, node_map));\n        return\
    \ node_map[h] = idx;\n    }\n    Index apply_and(Index li, Index ri){\n      \
    \  unordered_map<uint64_t, Index> node_map;\n        function<Index(Index, Index)>\
    \ f = [&](Index li, Index ri){\n            if(li == true_idx)\n             \
    \   return ri;\n            if(ri == true_idx)\n                return li;\n \
    \           if(li == false_idx || ri == false_idx)\n                return false_idx;\n\
    \            else\n                return nil;\n        };\n        return apply(li,\
    \ ri, f, node_map);\n    }\n    Index apply_or(Index li, Index ri){\n        unordered_map<uint64_t,\
    \ Index> node_map;\n        function<Index(Index, Index)> f = [&](Index li, Index\
    \ ri){\n            if(li == false_idx)\n                return ri;\n        \
    \    if(ri == false_idx)\n                return li;\n            if(li == true_idx\
    \ || ri == true_idx)\n                return true_idx;\n            else\n   \
    \             return nil;\n        };\n        return apply(li, ri, f, node_map);\n\
    \    }\n};\n\n"
  code: "struct ZDD{\n    struct Node{\n        int label;\n        using Index =\
    \ typename MemoryPool<Node>::Index;\n        Index c[2];\n        Node(){}\n \
    \       Node(int label, Index nil) : label(label){\n            c[0] = c[1] =\
    \ nil;\n        }\n        Node(int label, Index l, Index r) : label(label){\n\
    \            c[0] = l;\n            c[1] = r;\n        }\n    };\n    using Index\
    \ = typename MemoryPool<Node>::Index;\n    Index nil, true_idx, false_idx;\n \
    \   MemoryPool<Node> pool;\n    // \u5F15\u6570\u306F(Data, label, \u6700\u5F8C\
    \u3069\u3046\u9032\u3093\u3060\u304B)\n    // second\u304C-1\u306A\u3089Data\u3092\
    \u8868\u3059, 0/1\u306A\u3089\u7D42\u7AEF\u72B6\u614B\u3092\u8868\u3059\n    ZDD(){\n\
    \        nil = {-1};\n        true_idx = {-2};\n        false_idx = {-3};\n  \
    \  }\n    template<typename Data>\n    Index build(function<pair<Data, int>(Data,\
    \ int, bool)> f, Data init){\n        unordered_map<int, map<Data, Index>> node_map;\n\
    \        Index root = pool.alloc();\n        pool[root] = Node(0, nil);\n    \
    \    node_map[0][init] = root;\n        build<Data>(root, init, f, node_map);\n\
    \        return compress(root);\n    }\n    template<typename Data>\n    void\
    \ build(Index pi, Data& d, function<pair<Data, int>(Data, int, bool)>& f, unordered_map<int,\
    \ map<Data, Index>>& node_map){\n        auto& x = pool[pi];\n        for(int\
    \ i = 0; i < 2; ++i){\n            int fl;\n            Data y;\n            tie(y,\
    \ fl) = f(d, x.label, i);\n            if(fl == 0){\n                x.c[i] =\
    \ false_idx;\n            }\n            else if(fl == 1){\n                x.c[i]\
    \ = true_idx;\n            }\n            else if(node_map[x.label + 1].find(y)\
    \ == node_map[x.label + 1].end()){\n                Index new_idx = pool.alloc();\n\
    \                pool[new_idx] = Node(x.label + 1, nil);\n                node_map[x.label\
    \ + 1][y] = new_idx;\n                x.c[i] = new_idx;\n                build(node_map[x.label\
    \ + 1][y], y, f, node_map);\n            }else{\n                x.c[i] = node_map[x.label\
    \ + 1][y];\n            }\n        }\n    }\n    Index compress(Index pi, unordered_map<int,\
    \ unordered_map<uint64_t, Index>>& node_map, unordered_map<int, Index>& replace_map){\n\
    \        // \u540C\u578B\u3067\u5B50\u304C\u4E00\u81F4\u3059\u308B\u9802\u70B9\
    \u3092\u7834\u6EC5\n        if(pi == true_idx || pi == false_idx)\n          \
    \  return pi;\n        if(replace_map.find(pi.idx) != replace_map.end())\n   \
    \         return replace_map[pi.idx];\n        auto& p = pool[pi];\n        Index\
    \ li = compress(p.c[0], node_map, replace_map);\n        Index ri = compress(p.c[1],\
    \ node_map, replace_map);\n        p.c[0] = li;\n        p.c[1] = ri;\n      \
    \  uint64_t h = uint32_t(li.idx) | ((1uLL * uint32_t(ri.idx)) << 32);\n      \
    \  if(node_map[p.label].find(h) == node_map[p.label].end())\n            node_map[p.label][h]\
    \ = pi;\n        else\n            pool.free(pi);\n        return replace_map[pi.idx]\
    \ = node_map[p.label][h];\n    }\n    Index compress(Index pi){\n        unordered_map<int,\
    \ unordered_map<uint64_t, Index>> node_map;\n        unordered_map<int, Index>\
    \ replace_map;\n        return compress(pi, node_map, replace_map);\n    }\n \
    \   i64 linear_func_max(Index pi, vector<i64>& a, unordered_map<int, i64>& res){\n\
    \        if(pi == true_idx)\n            return 0;\n        if(pi == false_idx)\n\
    \            return -INF;\n        if(res.find(pi.idx) == res.end())\n       \
    \     res[pi.idx] = max(linear_func_max(pool[pi].c[0], a, res), linear_func_max(pool[pi].c[1],\
    \ a, res) + a[pool[pi].label]);\n        return res[pi.idx];\n    }\n    i64 linear_func_max(Index\
    \ root, vector<i64> a){\n        unordered_map<int, i64> res;\n        return\
    \ linear_func_max(root, a, res);\n    }\n    i64 count(Index pi, unordered_map<int,\
    \ i64>& res){\n        if(pi == true_idx)\n            return 1;\n        if(pi\
    \ == false_idx)\n            return 0;\n        if(res.find(pi.idx) == res.end())\n\
    \            res[pi.idx] = count(pool[pi].c[0], res) + count(pool[pi].c[1], res);\n\
    \        return res[pi.idx];\n    }\n    i64 count(Index root){\n        unordered_map<int,\
    \ i64> res;\n        return count(root, res);\n    }\n    double get_per(Index\
    \ pi, vector<double>& a, unordered_map<int, double>& res){\n        if(pi == true_idx)\n\
    \            return 1;\n        if(pi == false_idx)\n            return 0;\n \
    \       if(res.find(pi.idx) == res.end())\n            res[pi.idx] = a[pool[pi].label]\
    \ * get_per(pool[pi].c[0], a, res) + (1.0 - a[pool[pi].label]) * get_per(pool[pi].c[1],\
    \ a, res);\n        return res[pi.idx];\n    }\n    double get_per(Index root,\
    \ vector<double>& a){\n        unordered_map<int, double> res;\n        return\
    \ get_per(root, a, res);\n    }\n    Index apply(Index li, Index ri, function<Index(Index,\
    \ Index)>& f, unordered_map<uint64_t, Index>& node_map){\n        Index res =\
    \ f(li, ri);\n        if(res != nil)\n            return res;\n        int lidx,\
    \ ridx;\n        tie(lidx, ridx) = minmax(li.idx, ri.idx);\n        uint64_t h\
    \ = lidx | ((1uLL * ridx) << 32);\n        if(node_map.find(h) != node_map.end())\n\
    \            return node_map[h];\n        if(pool[li].label < pool[ri].label)\n\
    \            swap(li, ri);\n        auto& l = pool[li];\n        auto& r = pool[ri];\n\
    \        Index idx = pool.alloc();\n        if(l.label == r.label)\n         \
    \   pool[idx] = Node(l.label, apply(l.c[0], r.c[0], f, node_map), apply(l.c[1],\
    \ r.c[1], f, node_map));\n        else\n            pool[idx] = Node(l.label,\
    \ apply(l.c[0], ri, f, node_map), apply(l.c[1], ri, f, node_map));\n        return\
    \ node_map[h] = idx;\n    }\n    Index apply_and(Index li, Index ri){\n      \
    \  unordered_map<uint64_t, Index> node_map;\n        function<Index(Index, Index)>\
    \ f = [&](Index li, Index ri){\n            if(li == true_idx)\n             \
    \   return ri;\n            if(ri == true_idx)\n                return li;\n \
    \           if(li == false_idx || ri == false_idx)\n                return false_idx;\n\
    \            else\n                return nil;\n        };\n        return apply(li,\
    \ ri, f, node_map);\n    }\n    Index apply_or(Index li, Index ri){\n        unordered_map<uint64_t,\
    \ Index> node_map;\n        function<Index(Index, Index)> f = [&](Index li, Index\
    \ ri){\n            if(li == false_idx)\n                return ri;\n        \
    \    if(ri == false_idx)\n                return li;\n            if(li == true_idx\
    \ || ri == true_idx)\n                return true_idx;\n            else\n   \
    \             return nil;\n        };\n        return apply(li, ri, f, node_map);\n\
    \    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/zdd.cpp
  requiredBy: []
  timestamp: '2020-04-29 13:15:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/zdd_knapsack.test.cpp
documentation_of: lib/classes/zdd.cpp
layout: document
redirect_from:
- /library/lib/classes/zdd.cpp
- /library/lib/classes/zdd.cpp.html
title: lib/classes/zdd.cpp
---
