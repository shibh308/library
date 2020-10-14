---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/hld_composite.test.cpp
    title: verify/hld_composite.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/segtree_composite.test.cpp
    title: verify/segtree_composite.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/modint.cpp\"\ntemplate <i64 mod = MOD>\nstruct\
    \ ModInt{\n    i64 p;\n\n    ModInt() : p(0){}\n    ModInt(i64 x){p = x >= 0 ?\
    \ x % mod : x + (-x + mod - 1) / mod * mod;}\n\n    ModInt& operator+=(const ModInt&\
    \ y){p = p + *y - ((p + *y) >= mod ? mod : 0); return *this;}\n    ModInt& operator-=(const\
    \ ModInt& y){p = p - *y + (p - *y < 0 ? mod : 0); return *this;}\n    ModInt&\
    \ operator*=(const ModInt& y){p = (p * *y) % mod; return *this;}\n    ModInt&\
    \ operator%=(const ModInt& y){if(y)p %= *y; return *this;}\n\n    ModInt operator+(const\
    \ ModInt& y) const{ModInt x = *this; return x += y;}\n    ModInt operator-(const\
    \ ModInt& y) const{ModInt x = *this; return x -= y;}\n    ModInt operator*(const\
    \ ModInt& y) const{ModInt x = *this; return x *= y;}\n    ModInt operator%(const\
    \ ModInt& y) const{ModInt x = *this; return x %= y;}\n\n    friend ostream& operator<<(ostream&\
    \ stream, const ModInt<mod>& x){\n        stream << *x;\n        return stream;\n\
    \    }\n\n    friend ostream& operator>>(ostream& stream, const ModInt<mod>& x){\n\
    \        stream >> *x;\n        return stream;\n    }\n\n    ModInt& operator++(){p\
    \ = (p + 1) % mod; return *this;}\n    ModInt& operator--(){p = (p - 1 + mod)\
    \ % mod; return *this;}\n\n    bool operator==(const ModInt& y) const{return p\
    \ == *y;}\n    bool operator!=(const ModInt& y) const{return p != *y;}\n\n   \
    \ const i64& operator*() const{return p;}\n    i64& operator*(){return p;}\n\n\
    };\n\nusing mint = ModInt<>;\n\n"
  code: "template <i64 mod = MOD>\nstruct ModInt{\n    i64 p;\n\n    ModInt() : p(0){}\n\
    \    ModInt(i64 x){p = x >= 0 ? x % mod : x + (-x + mod - 1) / mod * mod;}\n\n\
    \    ModInt& operator+=(const ModInt& y){p = p + *y - ((p + *y) >= mod ? mod :\
    \ 0); return *this;}\n    ModInt& operator-=(const ModInt& y){p = p - *y + (p\
    \ - *y < 0 ? mod : 0); return *this;}\n    ModInt& operator*=(const ModInt& y){p\
    \ = (p * *y) % mod; return *this;}\n    ModInt& operator%=(const ModInt& y){if(y)p\
    \ %= *y; return *this;}\n\n    ModInt operator+(const ModInt& y) const{ModInt\
    \ x = *this; return x += y;}\n    ModInt operator-(const ModInt& y) const{ModInt\
    \ x = *this; return x -= y;}\n    ModInt operator*(const ModInt& y) const{ModInt\
    \ x = *this; return x *= y;}\n    ModInt operator%(const ModInt& y) const{ModInt\
    \ x = *this; return x %= y;}\n\n    friend ostream& operator<<(ostream& stream,\
    \ const ModInt<mod>& x){\n        stream << *x;\n        return stream;\n    }\n\
    \n    friend ostream& operator>>(ostream& stream, const ModInt<mod>& x){\n   \
    \     stream >> *x;\n        return stream;\n    }\n\n    ModInt& operator++(){p\
    \ = (p + 1) % mod; return *this;}\n    ModInt& operator--(){p = (p - 1 + mod)\
    \ % mod; return *this;}\n\n    bool operator==(const ModInt& y) const{return p\
    \ == *y;}\n    bool operator!=(const ModInt& y) const{return p != *y;}\n\n   \
    \ const i64& operator*() const{return p;}\n    i64& operator*(){return p;}\n\n\
    };\n\nusing mint = ModInt<>;\n\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/modint.cpp
  requiredBy: []
  timestamp: '2019-11-30 20:08:52+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/segtree_composite.test.cpp
  - verify/hld_composite.test.cpp
documentation_of: lib/classes/modint.cpp
layout: document
redirect_from:
- /library/lib/classes/modint.cpp
- /library/lib/classes/modint.cpp.html
title: lib/classes/modint.cpp
---
