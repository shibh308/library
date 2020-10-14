---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/hld_composite.test.cpp
    title: verify/hld_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/lca_hld.test.cpp
    title: verify/lca_hld.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/vertex_and_path_sum.test.cpp
    title: verify/vertex_and_path_sum.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/vertex_and_subtree_sum.test.cpp
    title: verify/vertex_and_subtree_sum.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/heavylightdecomposition.cpp\"\nstruct HeavyLightDecomposition{\n\
    \    int n;\n    vector<int> size, par, in, in_rev, heavy_root, depth, heavy_depth,\
    \ out;\n    vector<vector<int>> childs;\n    HeavyLightDecomposition(vector<vector<int>>&\
    \ edges, int root = 0) : n(edges.size()), size(n, 1), par(n, -2), depth(n, 0),\
    \ childs(n), in(n), in_rev(n), heavy_root(n), heavy_depth(n, 0), out(n){\n   \
    \     function<void(int)> swap_dfs = [&](int x){\n            int size_max = 0;\n\
    \            int max_idx = 0;\n            for(int i = 0; i < edges[x].size();\
    \ ++i){\n                int y = edges[x][i];\n                if(par[y] == -2){\n\
    \                    par[y] = x;\n                    depth[y] = depth[x] + 1;\n\
    \                    childs[x].push_back(y);\n                    swap_dfs(y);\n\
    \                    size[x] += size[y];\n                    if(chmax(size_max,\
    \ size[y])){\n                        max_idx = childs[x].size() - 1;\n      \
    \              }\n                }\n            }\n            if(max_idx){\n\
    \                swap(childs[x][0], childs[x][max_idx]);\n            }\n    \
    \    };\n        par[root] = -1;\n        swap_dfs(root);\n\n        int cnt =\
    \ 0;\n        function<void(int,int)> dfs = [&](int x, int segment_root){\n  \
    \          heavy_root[x] = segment_root;\n            in_rev[cnt] = x;\n     \
    \       in[x] = cnt++;\n            for(int i = 0; i < childs[x].size(); ++i){\n\
    \                int y = childs[x][i];\n                if(i == 0){\n        \
    \            dfs(y, segment_root);\n                }\n                else{\n\
    \                    heavy_depth[y] = heavy_depth[segment_root] + 1;\n       \
    \             dfs(y, y);\n                }\n            }\n            out[x]\
    \ = cnt;\n        };\n        dfs(root, root);\n    }\n    int lca(int x, int\
    \ y){\n        while(heavy_root[x] != heavy_root[y]){\n            if(heavy_depth[heavy_root[x]]\
    \ > heavy_depth[heavy_root[y]])\n                swap(x, y);\n            y =\
    \ par[heavy_root[y]];\n        }\n        return depth[x] < depth[y] ? x : y;\n\
    \    }\n    // x\u4EE5\u4E0B\u306E\u90E8\u5206\u6728\u3092\u8FD4\u3059\n    pair<int,int>\
    \ subtree(int x){\n        return make_pair(in[x], out[x]);\n    }\n    // x-z\u306E\
    \u30D1\u30B9\u3068y-z\u306E\u30D1\u30B9\u3092\u8FD4\u3059(\u4E21\u65B9\u3068\u3082\
    \u6839\u5074\u306B\u9032\u3080\u306E\u3067\u6CE8\u610F)\n    // \u305D\u308C\u305E\
    \u308C\u306EHeavy-Path\u306F\u6839\u5074\u306E\u65B9\u304Cindex\u304C\u5C0F\u3055\
    \u3044\u306E\u3067\u6CE8\u610F(\u53EF\u63DB\u30AF\u30A8\u30EA\u51E6\u7406\u3067\
    \u6C17\u3092\u3064\u3051\u308B)\n    pair<vector<pair<int,int>>, vector<pair<int,int>>>\
    \ two_point_path(int x, int y){\n        vector<pair<int,int>> xz, yz;\n     \
    \   int z = lca(x, y);\n        while(heavy_root[x] != heavy_root[z]){\n     \
    \       xz.emplace_back(in[heavy_root[x]], in[x] + 1);\n            x = par[heavy_root[x]];\n\
    \        }\n        while(heavy_root[y] != heavy_root[z]){\n            yz.emplace_back(in[heavy_root[y]],\
    \ in[y] + 1);\n            y = par[heavy_root[y]];\n        }\n        // \u8FBA\
    \u5C5E\u6027\u306B\u3057\u305F\u3044\u5834\u5408\u306F\u3053\u3053\u3092in[z]\
    \ + 1, in[x] + 1\u306B\u3059\u308B\n        xz.emplace_back(in[z], in[x] + 1);\n\
    \        yz.emplace_back(in[z] + 1, in[y] + 1);\n        return make_pair(xz,\
    \ yz);\n    }\n    // \u9802\u70B9x\u304CEuler-Tour\u4E0A\u3067\u4F55\u756A\u76EE\
    \u306B\u4F4D\u7F6E\u3059\u308B\u304B\u3092\u8FD4\u3059\n    // in[\u5143\u306E\
    \u9802\u70B9index] = \u5185\u90E8\u3067\u306Eindex\n    // in_rev[\u5185\u90E8\
    \u3067\u306Eindex] = \u5143\u306E\u9802\u70B9index\n    int get_idx(int x){\n\
    \        return in[x];\n    }\n    // x\u304C\u5C5E\u3059\u308BHeavy-Path\u306E\
    \u6DF1\u3055\u3092\u8FD4\u3059\n    int get_heavy_depth(int x){\n        return\
    \ heavy_depth[heavy_root[x]];\n    }\n};\n\n"
  code: "struct HeavyLightDecomposition{\n    int n;\n    vector<int> size, par, in,\
    \ in_rev, heavy_root, depth, heavy_depth, out;\n    vector<vector<int>> childs;\n\
    \    HeavyLightDecomposition(vector<vector<int>>& edges, int root = 0) : n(edges.size()),\
    \ size(n, 1), par(n, -2), depth(n, 0), childs(n), in(n), in_rev(n), heavy_root(n),\
    \ heavy_depth(n, 0), out(n){\n        function<void(int)> swap_dfs = [&](int x){\n\
    \            int size_max = 0;\n            int max_idx = 0;\n            for(int\
    \ i = 0; i < edges[x].size(); ++i){\n                int y = edges[x][i];\n  \
    \              if(par[y] == -2){\n                    par[y] = x;\n          \
    \          depth[y] = depth[x] + 1;\n                    childs[x].push_back(y);\n\
    \                    swap_dfs(y);\n                    size[x] += size[y];\n \
    \                   if(chmax(size_max, size[y])){\n                        max_idx\
    \ = childs[x].size() - 1;\n                    }\n                }\n        \
    \    }\n            if(max_idx){\n                swap(childs[x][0], childs[x][max_idx]);\n\
    \            }\n        };\n        par[root] = -1;\n        swap_dfs(root);\n\
    \n        int cnt = 0;\n        function<void(int,int)> dfs = [&](int x, int segment_root){\n\
    \            heavy_root[x] = segment_root;\n            in_rev[cnt] = x;\n   \
    \         in[x] = cnt++;\n            for(int i = 0; i < childs[x].size(); ++i){\n\
    \                int y = childs[x][i];\n                if(i == 0){\n        \
    \            dfs(y, segment_root);\n                }\n                else{\n\
    \                    heavy_depth[y] = heavy_depth[segment_root] + 1;\n       \
    \             dfs(y, y);\n                }\n            }\n            out[x]\
    \ = cnt;\n        };\n        dfs(root, root);\n    }\n    int lca(int x, int\
    \ y){\n        while(heavy_root[x] != heavy_root[y]){\n            if(heavy_depth[heavy_root[x]]\
    \ > heavy_depth[heavy_root[y]])\n                swap(x, y);\n            y =\
    \ par[heavy_root[y]];\n        }\n        return depth[x] < depth[y] ? x : y;\n\
    \    }\n    // x\u4EE5\u4E0B\u306E\u90E8\u5206\u6728\u3092\u8FD4\u3059\n    pair<int,int>\
    \ subtree(int x){\n        return make_pair(in[x], out[x]);\n    }\n    // x-z\u306E\
    \u30D1\u30B9\u3068y-z\u306E\u30D1\u30B9\u3092\u8FD4\u3059(\u4E21\u65B9\u3068\u3082\
    \u6839\u5074\u306B\u9032\u3080\u306E\u3067\u6CE8\u610F)\n    // \u305D\u308C\u305E\
    \u308C\u306EHeavy-Path\u306F\u6839\u5074\u306E\u65B9\u304Cindex\u304C\u5C0F\u3055\
    \u3044\u306E\u3067\u6CE8\u610F(\u53EF\u63DB\u30AF\u30A8\u30EA\u51E6\u7406\u3067\
    \u6C17\u3092\u3064\u3051\u308B)\n    pair<vector<pair<int,int>>, vector<pair<int,int>>>\
    \ two_point_path(int x, int y){\n        vector<pair<int,int>> xz, yz;\n     \
    \   int z = lca(x, y);\n        while(heavy_root[x] != heavy_root[z]){\n     \
    \       xz.emplace_back(in[heavy_root[x]], in[x] + 1);\n            x = par[heavy_root[x]];\n\
    \        }\n        while(heavy_root[y] != heavy_root[z]){\n            yz.emplace_back(in[heavy_root[y]],\
    \ in[y] + 1);\n            y = par[heavy_root[y]];\n        }\n        // \u8FBA\
    \u5C5E\u6027\u306B\u3057\u305F\u3044\u5834\u5408\u306F\u3053\u3053\u3092in[z]\
    \ + 1, in[x] + 1\u306B\u3059\u308B\n        xz.emplace_back(in[z], in[x] + 1);\n\
    \        yz.emplace_back(in[z] + 1, in[y] + 1);\n        return make_pair(xz,\
    \ yz);\n    }\n    // \u9802\u70B9x\u304CEuler-Tour\u4E0A\u3067\u4F55\u756A\u76EE\
    \u306B\u4F4D\u7F6E\u3059\u308B\u304B\u3092\u8FD4\u3059\n    // in[\u5143\u306E\
    \u9802\u70B9index] = \u5185\u90E8\u3067\u306Eindex\n    // in_rev[\u5185\u90E8\
    \u3067\u306Eindex] = \u5143\u306E\u9802\u70B9index\n    int get_idx(int x){\n\
    \        return in[x];\n    }\n    // x\u304C\u5C5E\u3059\u308BHeavy-Path\u306E\
    \u6DF1\u3055\u3092\u8FD4\u3059\n    int get_heavy_depth(int x){\n        return\
    \ heavy_depth[heavy_root[x]];\n    }\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/heavylightdecomposition.cpp
  requiredBy: []
  timestamp: '2020-03-14 13:31:04+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/vertex_and_subtree_sum.test.cpp
  - verify/lca_hld.test.cpp
  - verify/hld_composite.test.cpp
  - verify/vertex_and_path_sum.test.cpp
documentation_of: lib/classes/heavylightdecomposition.cpp
layout: document
redirect_from:
- /library/lib/classes/heavylightdecomposition.cpp
- /library/lib/classes/heavylightdecomposition.cpp.html
title: lib/classes/heavylightdecomposition.cpp
---
