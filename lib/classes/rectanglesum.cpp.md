---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/rectanglesum.cpp\"\nstruct RectangleSum{//O(HW)\u3067\
    \u521D\u671F\u5316\u3057\u3066O(1)\u3067\u9577\u65B9\u5F62\u306E\u548C\u3092\u51FA\
    \u3059(\u534A\u958B\u533A\u9593)\n    vector<vector<i64>> sum;\n    int h, w;\n\
    \    RectangleSum(vector<vector<i64>>& v) :\n        h(v.size()),\n        w(v[0].size()),\n\
    \        sum(v)\n    {}\n\n    // \u534A\u958B\u533A\u9593\u3067\u8A2D\u5B9A\u3059\
    \u308B\u4E8B\u306B\u6CE8\u610F\u3059\u308B\n    void set(int sx, int sy, int ex,\
    \ int ey, i64 val){\n        sum[sx][sy] += val;\n        sum[sx][ey] -= val;\n\
    \        sum[ex][sy] -= val;\n        sum[ex][ey] += val;\n    }\n\n    void run(){\n\
    \n        for(int i = 0; i < h; ++i)\n            for(int j = 0; j < w + 1; ++j)\n\
    \                sum[i + 1][j] += sum[i][j];\n\n        for(int i = 0; i < h +\
    \ 1; ++i)\n            for(int j = 0; j < w; ++j)\n                sum[i][j +\
    \ 1] += sum[i][j];\n    }\n\n    i64 getSum(int sx, int sy, int ex, int ey){\n\
    \        return sum[ex][ey] + sum[sx][sy] - sum[sx][ey] - sum[ex][sy];\n    }\n\
    };\n\n\n"
  code: "struct RectangleSum{//O(HW)\u3067\u521D\u671F\u5316\u3057\u3066O(1)\u3067\
    \u9577\u65B9\u5F62\u306E\u548C\u3092\u51FA\u3059(\u534A\u958B\u533A\u9593)\n \
    \   vector<vector<i64>> sum;\n    int h, w;\n    RectangleSum(vector<vector<i64>>&\
    \ v) :\n        h(v.size()),\n        w(v[0].size()),\n        sum(v)\n    {}\n\
    \n    // \u534A\u958B\u533A\u9593\u3067\u8A2D\u5B9A\u3059\u308B\u4E8B\u306B\u6CE8\
    \u610F\u3059\u308B\n    void set(int sx, int sy, int ex, int ey, i64 val){\n \
    \       sum[sx][sy] += val;\n        sum[sx][ey] -= val;\n        sum[ex][sy]\
    \ -= val;\n        sum[ex][ey] += val;\n    }\n\n    void run(){\n\n        for(int\
    \ i = 0; i < h; ++i)\n            for(int j = 0; j < w + 1; ++j)\n           \
    \     sum[i + 1][j] += sum[i][j];\n\n        for(int i = 0; i < h + 1; ++i)\n\
    \            for(int j = 0; j < w; ++j)\n                sum[i][j + 1] += sum[i][j];\n\
    \    }\n\n    i64 getSum(int sx, int sy, int ex, int ey){\n        return sum[ex][ey]\
    \ + sum[sx][sy] - sum[sx][ey] - sum[ex][sy];\n    }\n};\n\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/rectanglesum.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/rectanglesum.cpp
layout: document
redirect_from:
- /library/lib/classes/rectanglesum.cpp
- /library/lib/classes/rectanglesum.cpp.html
title: lib/classes/rectanglesum.cpp
---
