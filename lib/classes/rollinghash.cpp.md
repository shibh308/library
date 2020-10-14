---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/rollinghash.cpp\"\ntemplate <i64 mod1 = MOD,\
    \ i64 mod2 = MOD + 2, i64 base = 10007, typename T = string>\nstruct RollingHash{\n\
    \n    using mint1 = ModInt<mod1>;\n    using mint2 = ModInt<mod2>;\n    using\
    \ pair_type = pair<mint1, mint2>;\n    int len;\n    std::vector<pair_type> v;\n\
    \    static std::vector<pair_type> power, inv;\n\n    RollingHash(T s) :\n   \
    \ len(s.size())\n    {\n        v.assign(1, make_pair(mint1(0), mint2(0)));\n\
    \        for(int i = 0; i < len; ++i){\n            auto c = s[i];\n         \
    \   v.emplace_back(v.back().first + power[i].first * c,\n                    \
    \       v.back().second + power[i].second * c);\n            if(static_cast<int>(power.size())\
    \ == i + 1){\n                power.emplace_back(power.back().first * base,\n\
    \                                   power.back().second * base);\n           \
    \     inv.emplace_back(mpow(power.back().first, mod1 - 2),\n                 \
    \                mpow(power.back().second, mod2 - 2));\n            }\n      \
    \  }\n    };\n\n    pair_type get(int l = 0, int r = -1){\n        if(r == -1)\n\
    \            r = len;\n        assert(l <= r);\n        assert(r <= len);\n  \
    \      auto l_cut = make_pair(v[r].first - v[l].first,\n                     \
    \          v[r].second - v[l].second);\n        return make_pair(l_cut.first *\
    \ inv[l].first,\n                         l_cut.second * inv[l].second);\n   \
    \ }\n\n    pair_type connect(pair_type l, pair_type r, int l_len){\n        return\
    \ make_pair(l.first + power[l_len].first * r.first,\n                        \
    \ l.second + power[l_len].second * r.second);\n    }\n};\n\nusing RH = RollingHash<MOD,\
    \ MOD + 2, 10007>;\ntemplate<> vector<pair<ModInt<MOD>, ModInt<MOD + 2>>> RH::power\
    \ = {make_pair(ModInt<MOD>(1), ModInt<MOD + 2>(1))};\ntemplate<> vector<pair<ModInt<MOD>,\
    \ ModInt<MOD + 2>>> RH::inv = {make_pair(ModInt<MOD>(1), ModInt<MOD + 2>(1))};\n\
    \n"
  code: "template <i64 mod1 = MOD, i64 mod2 = MOD + 2, i64 base = 10007, typename\
    \ T = string>\nstruct RollingHash{\n\n    using mint1 = ModInt<mod1>;\n    using\
    \ mint2 = ModInt<mod2>;\n    using pair_type = pair<mint1, mint2>;\n    int len;\n\
    \    std::vector<pair_type> v;\n    static std::vector<pair_type> power, inv;\n\
    \n    RollingHash(T s) :\n    len(s.size())\n    {\n        v.assign(1, make_pair(mint1(0),\
    \ mint2(0)));\n        for(int i = 0; i < len; ++i){\n            auto c = s[i];\n\
    \            v.emplace_back(v.back().first + power[i].first * c,\n           \
    \                v.back().second + power[i].second * c);\n            if(static_cast<int>(power.size())\
    \ == i + 1){\n                power.emplace_back(power.back().first * base,\n\
    \                                   power.back().second * base);\n           \
    \     inv.emplace_back(mpow(power.back().first, mod1 - 2),\n                 \
    \                mpow(power.back().second, mod2 - 2));\n            }\n      \
    \  }\n    };\n\n    pair_type get(int l = 0, int r = -1){\n        if(r == -1)\n\
    \            r = len;\n        assert(l <= r);\n        assert(r <= len);\n  \
    \      auto l_cut = make_pair(v[r].first - v[l].first,\n                     \
    \          v[r].second - v[l].second);\n        return make_pair(l_cut.first *\
    \ inv[l].first,\n                         l_cut.second * inv[l].second);\n   \
    \ }\n\n    pair_type connect(pair_type l, pair_type r, int l_len){\n        return\
    \ make_pair(l.first + power[l_len].first * r.first,\n                        \
    \ l.second + power[l_len].second * r.second);\n    }\n};\n\nusing RH = RollingHash<MOD,\
    \ MOD + 2, 10007>;\ntemplate<> vector<pair<ModInt<MOD>, ModInt<MOD + 2>>> RH::power\
    \ = {make_pair(ModInt<MOD>(1), ModInt<MOD + 2>(1))};\ntemplate<> vector<pair<ModInt<MOD>,\
    \ ModInt<MOD + 2>>> RH::inv = {make_pair(ModInt<MOD>(1), ModInt<MOD + 2>(1))};\n\
    \n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/rollinghash.cpp
  requiredBy: []
  timestamp: '2020-02-25 16:29:43+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/rollinghash.cpp
layout: document
redirect_from:
- /library/lib/classes/rollinghash.cpp
- /library/lib/classes/rollinghash.cpp.html
title: lib/classes/rollinghash.cpp
---
