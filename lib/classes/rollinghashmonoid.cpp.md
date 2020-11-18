---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/rollighashmonoid.test.cpp
    title: verify/rollighashmonoid.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/rollinghashmonoid.cpp\"\nstruct RollingHashMonoid{\n\
    \    using Hash = RollingHashMonoid;\n    using u64 = uint64_t;\n    static constexpr\
    \ u64 mod = (1uLL << 61) - 1;\n    static constexpr u64 m30 = (1uLL << 30) - 1;\n\
    \    static constexpr u64 m31 = (1uLL << 31) - 1;\n    static constexpr u64 m61\
    \ = mod;\n    static constexpr u64 _base = 550390130435464343;\n    static constexpr\
    \ u64 _base_inv = 1803816245541264939;\n    static vector<u64> base, base_inv;\n\
    \n    static inline u64 calc_mod(u64 x){\n        u64 xu = x >> 61;\n        u64\
    \ xd = x & m61;\n        u64 res = xu + xd;\n        if(res >= mod)\n        \
    \    res -= mod;\n        return res;\n    }\n\n    static inline u64 raw_mul(u64\
    \ a, u64 b){\n        u64 au = a >> 31;\n        u64 ad = a & m31;\n        u64\
    \ bu = b >> 31;\n        u64 bd = b & m31;\n        u64 mid = ad * bu + au * bd;\n\
    \        u64 midu = mid >> 30;\n        u64 midd = mid & m30;\n        return\
    \ au * bu * 2 + midu + (midd << 31) + ad * bd;\n    }\n\n    static void remake_table(int\
    \ len){\n        while(base.size() <= len){\n            base.emplace_back(calc_mod(raw_mul(base.back(),\
    \ _base)));\n            base_inv.emplace_back(calc_mod(raw_mul(base_inv.back(),\
    \ _base_inv)));\n        }\n    }\n\n    u64 h, l;\n\n    static inline u64 lshift(u64\
    \ a, int len){\n        remake_table(len);\n        return raw_mul(a, base[len]);\n\
    \    }\n    static inline u64 rshift(u64 a, int len){\n        remake_table(len);\n\
    \        return raw_mul(a, base_inv[len]);\n    }\n\n    Hash concat(const Hash&\
    \ b) const{\n        return RollingHashMonoid(\n                calc_mod(h + lshift(b.h,\
    \ l)),\n                l + b.l\n                );\n    }\n    Hash sub(const\
    \ Hash& b) const{\n        return RollingHashMonoid(\n                calc_mod(rshift(h\
    \ + mod - b.h, b.l)),\n                l - b.l\n                );\n    }\n\n\
    \    RollingHashMonoid() : h(0), l(0){}\n    RollingHashMonoid(u64 x) : h(x),\
    \ l(1){}\n    RollingHashMonoid(u64 h, u64 l) : h(h), l(l){}\n\n    friend bool\
    \ operator==(const Hash& a, const Hash& b){return a.h == b.h && a.l == b.l;}\n\
    \n    template <typename T>\n    static vector<Hash> make(vector<T>& x){\n   \
    \     vector<Hash> v(x.size() + 1);\n        for(int i = 0; i < x.size(); ++i){\n\
    \            v[i + 1] = v[i].concat(x[i]);\n        }\n        return v;\n   \
    \ }\n    static vector<Hash> make(string& x){\n        vector<Hash> v(x.size()\
    \ + 1);\n        for(int i = 0; i < x.size(); ++i){\n            v[i + 1] = v[i].concat(x[i]);\n\
    \        }\n        return v;\n    }\n};\n\nnamespace std{\ntemplate<> struct\
    \ hash<RollingHashMonoid>{\nsize_t operator()(const RollingHashMonoid x) const\
    \ noexcept{\n    return x.concat(x.l).h;\n}\n};\n}\n\n\nusing Hash = RollingHashMonoid;\n\
    vector<uint64_t> Hash::base = {1};\nvector<uint64_t> Hash::base_inv = {1};\n"
  code: "struct RollingHashMonoid{\n    using Hash = RollingHashMonoid;\n    using\
    \ u64 = uint64_t;\n    static constexpr u64 mod = (1uLL << 61) - 1;\n    static\
    \ constexpr u64 m30 = (1uLL << 30) - 1;\n    static constexpr u64 m31 = (1uLL\
    \ << 31) - 1;\n    static constexpr u64 m61 = mod;\n    static constexpr u64 _base\
    \ = 550390130435464343;\n    static constexpr u64 _base_inv = 1803816245541264939;\n\
    \    static vector<u64> base, base_inv;\n\n    static inline u64 calc_mod(u64\
    \ x){\n        u64 xu = x >> 61;\n        u64 xd = x & m61;\n        u64 res =\
    \ xu + xd;\n        if(res >= mod)\n            res -= mod;\n        return res;\n\
    \    }\n\n    static inline u64 raw_mul(u64 a, u64 b){\n        u64 au = a >>\
    \ 31;\n        u64 ad = a & m31;\n        u64 bu = b >> 31;\n        u64 bd =\
    \ b & m31;\n        u64 mid = ad * bu + au * bd;\n        u64 midu = mid >> 30;\n\
    \        u64 midd = mid & m30;\n        return au * bu * 2 + midu + (midd << 31)\
    \ + ad * bd;\n    }\n\n    static void remake_table(int len){\n        while(base.size()\
    \ <= len){\n            base.emplace_back(calc_mod(raw_mul(base.back(), _base)));\n\
    \            base_inv.emplace_back(calc_mod(raw_mul(base_inv.back(), _base_inv)));\n\
    \        }\n    }\n\n    u64 h, l;\n\n    static inline u64 lshift(u64 a, int\
    \ len){\n        remake_table(len);\n        return raw_mul(a, base[len]);\n \
    \   }\n    static inline u64 rshift(u64 a, int len){\n        remake_table(len);\n\
    \        return raw_mul(a, base_inv[len]);\n    }\n\n    Hash concat(const Hash&\
    \ b) const{\n        return RollingHashMonoid(\n                calc_mod(h + lshift(b.h,\
    \ l)),\n                l + b.l\n                );\n    }\n    Hash sub(const\
    \ Hash& b) const{\n        return RollingHashMonoid(\n                calc_mod(rshift(h\
    \ + mod - b.h, b.l)),\n                l - b.l\n                );\n    }\n\n\
    \    RollingHashMonoid() : h(0), l(0){}\n    RollingHashMonoid(u64 x) : h(x),\
    \ l(1){}\n    RollingHashMonoid(u64 h, u64 l) : h(h), l(l){}\n\n    friend bool\
    \ operator==(const Hash& a, const Hash& b){return a.h == b.h && a.l == b.l;}\n\
    \n    template <typename T>\n    static vector<Hash> make(vector<T>& x){\n   \
    \     vector<Hash> v(x.size() + 1);\n        for(int i = 0; i < x.size(); ++i){\n\
    \            v[i + 1] = v[i].concat(x[i]);\n        }\n        return v;\n   \
    \ }\n    static vector<Hash> make(string& x){\n        vector<Hash> v(x.size()\
    \ + 1);\n        for(int i = 0; i < x.size(); ++i){\n            v[i + 1] = v[i].concat(x[i]);\n\
    \        }\n        return v;\n    }\n};\n\nnamespace std{\ntemplate<> struct\
    \ hash<RollingHashMonoid>{\nsize_t operator()(const RollingHashMonoid x) const\
    \ noexcept{\n    return x.concat(x.l).h;\n}\n};\n}\n\n\nusing Hash = RollingHashMonoid;\n\
    vector<uint64_t> Hash::base = {1};\nvector<uint64_t> Hash::base_inv = {1};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/rollinghashmonoid.cpp
  requiredBy: []
  timestamp: '2020-11-18 11:08:42+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/rollighashmonoid.test.cpp
documentation_of: lib/classes/rollinghashmonoid.cpp
layout: document
redirect_from:
- /library/lib/classes/rollinghashmonoid.cpp
- /library/lib/classes/rollinghashmonoid.cpp.html
title: lib/classes/rollinghashmonoid.cpp
---
