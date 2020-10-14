---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/matrix.test.cpp
    title: verify/matrix.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/matrix.cpp\"\ntemplate <typename T>\nstruct\
    \ Matrix{\n    int h, w;\n    vector<T> v;\n\n    Matrix() : h(1), w(1), v(1,\
    \ 1){}\n    Matrix(int n){*this = makeUnit(n);}\n    Matrix(int h, int w) : h(h),\
    \ w(w), v(h * w, 0){}\n\n    Matrix(vector<vector<T>> v_) : h(v_.size()), w(v_[0].size()),\
    \ v(h * w){\n        for(int i = 0; i < h; ++i)\n            for(int j = 0; j\
    \ < w; ++j)\n                v[i * w + j] = v_[i][j];\n    }\n\n    static Matrix\
    \ makeUnit(int n){\n        Matrix mat(n, n);\n        for(int i = 0; i < n; ++i)\n\
    \            mat.at(i, i) = 1;\n        return mat;\n    }\n\n    T& at(int i,\
    \ int j){\n        assert(0 <= i && i <= h && 0 <= j && j < w);\n        return\
    \ v[i * w + j];\n    };\n\n    Matrix pow(i64 x){\n        assert(h == w);\n \
    \       auto mat = x & 1 ? *this : makeUnit(h);\n        auto u = *this;\n   \
    \     while(u = u * u, x >>= 1)\n            if(x & 1)\n                mat *=\
    \ u;\n        return mat;\n    }\n\n    Matrix& operator+=(const Matrix& mat){\n\
    \        assert(h == mat.h && w == mat.w);\n        for(int i = 0; i < h * w;\
    \ ++i)\n            v[i] += mat.v[i];\n        return *this;\n    }\n\n    Matrix&\
    \ operator-=(const Matrix& mat){\n        assert(h == mat.h && w == mat.w);\n\
    \        for(int i = 0; i < h * w; ++i)\n            v[i] -= mat.v[i];\n     \
    \   return *this;\n    }\n\n    Matrix& operator%=(const T mod){\n        for(int\
    \ i = 0; i < h * w; ++i)\n            v[i] %= mod;\n        return *this;\n  \
    \  }\n\n    Matrix operator*(const Matrix& mat){\n        assert(w == mat.h);\n\
    \        Matrix ret(h, mat.w);\n        for(int i = 0; i < h; ++i)\n         \
    \   for(int k = 0; k < w; ++k)\n                for(int j = 0; j < mat.w; ++j)\n\
    \                    ret.v[i * mat.w + j] += v[i * w + k] * mat.v[k * mat.w +\
    \ j];\n        return ret;\n    }\n\n    Matrix operator+(const Matrix& mat){return\
    \ Matrix(*this) += mat;}\n    Matrix operator-(const Matrix& mat){return Matrix(*this)\
    \ -= mat;}\n    Matrix operator%(const T mod){return Matrix(*this) %= mod;}\n\
    \    Matrix& operator*=(const Matrix& mat){return *this = *this * mat;}\n};\n\n"
  code: "template <typename T>\nstruct Matrix{\n    int h, w;\n    vector<T> v;\n\n\
    \    Matrix() : h(1), w(1), v(1, 1){}\n    Matrix(int n){*this = makeUnit(n);}\n\
    \    Matrix(int h, int w) : h(h), w(w), v(h * w, 0){}\n\n    Matrix(vector<vector<T>>\
    \ v_) : h(v_.size()), w(v_[0].size()), v(h * w){\n        for(int i = 0; i < h;\
    \ ++i)\n            for(int j = 0; j < w; ++j)\n                v[i * w + j] =\
    \ v_[i][j];\n    }\n\n    static Matrix makeUnit(int n){\n        Matrix mat(n,\
    \ n);\n        for(int i = 0; i < n; ++i)\n            mat.at(i, i) = 1;\n   \
    \     return mat;\n    }\n\n    T& at(int i, int j){\n        assert(0 <= i &&\
    \ i <= h && 0 <= j && j < w);\n        return v[i * w + j];\n    };\n\n    Matrix\
    \ pow(i64 x){\n        assert(h == w);\n        auto mat = x & 1 ? *this : makeUnit(h);\n\
    \        auto u = *this;\n        while(u = u * u, x >>= 1)\n            if(x\
    \ & 1)\n                mat *= u;\n        return mat;\n    }\n\n    Matrix& operator+=(const\
    \ Matrix& mat){\n        assert(h == mat.h && w == mat.w);\n        for(int i\
    \ = 0; i < h * w; ++i)\n            v[i] += mat.v[i];\n        return *this;\n\
    \    }\n\n    Matrix& operator-=(const Matrix& mat){\n        assert(h == mat.h\
    \ && w == mat.w);\n        for(int i = 0; i < h * w; ++i)\n            v[i] -=\
    \ mat.v[i];\n        return *this;\n    }\n\n    Matrix& operator%=(const T mod){\n\
    \        for(int i = 0; i < h * w; ++i)\n            v[i] %= mod;\n        return\
    \ *this;\n    }\n\n    Matrix operator*(const Matrix& mat){\n        assert(w\
    \ == mat.h);\n        Matrix ret(h, mat.w);\n        for(int i = 0; i < h; ++i)\n\
    \            for(int k = 0; k < w; ++k)\n                for(int j = 0; j < mat.w;\
    \ ++j)\n                    ret.v[i * mat.w + j] += v[i * w + k] * mat.v[k * mat.w\
    \ + j];\n        return ret;\n    }\n\n    Matrix operator+(const Matrix& mat){return\
    \ Matrix(*this) += mat;}\n    Matrix operator-(const Matrix& mat){return Matrix(*this)\
    \ -= mat;}\n    Matrix operator%(const T mod){return Matrix(*this) %= mod;}\n\
    \    Matrix& operator*=(const Matrix& mat){return *this = *this * mat;}\n};\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/matrix.cpp
  requiredBy: []
  timestamp: '2019-12-25 20:51:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/matrix.test.cpp
documentation_of: lib/classes/matrix.cpp
layout: document
redirect_from:
- /library/lib/classes/matrix.cpp
- /library/lib/classes/matrix.cpp.html
title: lib/classes/matrix.cpp
---
