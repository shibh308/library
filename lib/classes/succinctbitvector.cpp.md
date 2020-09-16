---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/succinctbitvector.cpp\"\nstruct FastSelect {\n\
    \    static const int l_size = 65536;\n    static const int m_size = 256;\n  \
    \  static const int mb = 255;\n    static const int s_size = 32;\n    static const\
    \ int ss_size = 8;\n\n    struct Table{\n        uint16_t l_table[m_size][m_size][s_size];\n\
    \        uint32_t s_table[m_size];\n        Table() : l_table(), s_table(){\n\
    \            for(int i = 0; i < m_size; ++i)\n                for(int j = 0; j\
    \ < m_size; ++j){\n                    for(int k = 0; k < s_size; ++k)\n     \
    \                   l_table[i][j][k] = 0;\n                    for(int k = 0;\
    \ k < m_size; ++k){\n                        if(k >= i && k < i + j)\n       \
    \                     l_table[i][j][k >> 3] |= 1 << ((k & 7) * 2);\n         \
    \               else if(k >= i + j)\n                            l_table[i][j][k\
    \ >> 3] |= 2 << ((k & 7) * 2);\n                    }\n                }\n   \
    \         for(int i = 0; i < m_size; ++i){\n                s_table[i] = 0;\n\
    \                for(int j = 0; j < ss_size; ++j){\n                    int c\
    \ = 0;\n                    for(int k = 0; k < ss_size; ++k){\n              \
    \          c += bool(i & (1 << k));\n                        if(j < c){\n    \
    \                        s_table[i] |= (k << (j * 4));\n                     \
    \       break;\n                        }\n                    }\n           \
    \     }\n            }\n        }\n    };\n    const static Table tab;\n\n   \
    \ struct AbstractSelect{virtual int select(int x) = 0;};\n    struct BigSelect\
    \ : public AbstractSelect{\n        vector<int> w;\n        BigSelect(vector<uint32_t>&\
    \ v, int l, int r, bool fl){\n            for(int i = l; i < r; ++i){\n      \
    \          if(bool(v[i / s_size] & (1u << (i % s_size))) == fl){\n           \
    \         w.emplace_back(i - l);\n                }\n            }\n        }\n\
    \        int select(int x){return w[x];}\n    };\n    struct SmallSelect : public\
    \ AbstractSelect{\n        vector<uint32_t>& v;\n        int l;\n        bool\
    \ fl;\n        vector<int> siz;\n        vector<unsigned char> w;\n        bool\
    \ flag(int i){\n            return bool(v[(l + i) / s_size] & (1u << ((l + i)\
    \ % s_size))) == fl;\n        }\n        uint16_t get(int i){\n            i +=\
    \ l;\n            if(i % s_size <= 24){\n                return (v[i / s_size]\
    \ >> (i % s_size)) & 255;\n            }\n            else{\n                int\
    \ l_bit = 32 - (i % s_size);\n                uint16_t lv = (v[i / s_size] >>\
    \ (i % s_size));\n                uint16_t rv = v[i / s_size + 1] & ((1u << (8\
    \ - l_bit)) - 1);\n                return lv + (rv << l_bit);\n            }\n\
    \        }\n        SmallSelect(vector<uint32_t>& v, int l, int r, bool fl) :\
    \ v(v), l(l), fl(fl){\n            int n = r - l;\n            siz.emplace_back(0);\n\
    \            for(int k = (n + 7) / 8; k != 1; k = (k + 3) / 4){\n            \
    \    siz.emplace_back(siz.back() + (k + 3) / 4 * 4);\n            }\n        \
    \    siz.emplace_back(siz.back() + 1);\n            w.assign(siz.back(), 0);\n\
    \            for(int i = 0; i < n; ++i){\n                if(flag(i)){\n     \
    \               ++w[i / ss_size];\n                }\n            }\n        \
    \    for(int i = 0; i < siz.size() - 2; ++i){\n                for(int j = siz[i];\
    \ j < siz[i + 1]; ++j){\n                    w[siz[i + 1] + (j - siz[i]) / 4]\
    \ += w[j];\n                }\n            }\n        }\n        int select(int\
    \ x){\n            int d = siz.size() - 1;\n            int idx = siz[d];\n  \
    \          for(; d > 0; --d){\n                int ch = siz[d - 1] + (idx - siz[d])\
    \ * 4;\n                int res = (tab.l_table[w[ch]][w[ch + 1]][x >> 3] >> ((x\
    \ & 7) * 2)) & 3;\n                if(res < 2){\n                    if(res)\n\
    \                        x -= w[ch];\n                    idx = ch + res;\n  \
    \              }\n                else{\n                    x -= w[ch] + w[ch\
    \ + 1];\n                    int res2 = (tab.l_table[w[ch + 2]][w[ch + 3]][x >>\
    \ 3] >> ((x & 7) * 2)) & 3;\n                    assert(res2 < 2);\n         \
    \           if(res2)\n                        x -= w[ch + 2];\n              \
    \      idx = ch + 2 + res2;\n                }\n            }\n            return\
    \ idx * ss_size + ((tab.s_table[get(idx * ss_size) ^ (fl ? 0 : 255)] >> (x * 4))\
    \ & 15);\n        }\n    };\n\n    int cnt;\n    vector<AbstractSelect*> b;\n\
    \    vector<int> st;\n    FastSelect(){}\n    FastSelect(int n, vector<uint32_t>&\
    \ v, bool fl) : cnt(0){\n        int s = 0;\n        for(int i = 0; i < n; ++i){\n\
    \            if(bool(v[i / s_size] & (1u << (i % s_size))) == fl){\n         \
    \       ++cnt;\n                if(cnt % mb == 0){\n                    if(i -\
    \ s + 1 > l_size)\n                        b.emplace_back(new BigSelect(v, s,\
    \ i + 1, fl));\n                    else\n                        b.emplace_back(new\
    \ SmallSelect(v, s, i + 1, fl));\n                    st.emplace_back(s);\n  \
    \                  s = i + 1;\n                }\n            }\n        }\n \
    \       if(s != n){\n            st.emplace_back(s);\n            b.emplace_back(new\
    \ BigSelect(v, s, n, fl));\n        }\n    }\n    int select(int x){\n       \
    \ if(x >= cnt)\n            return -1;\n        else{\n            return st[x\
    \ / mb] + b[x / mb]->select(x % mb);\n        }\n    }\n};\n\nconst FastSelect::Table\
    \ FastSelect::tab = FastSelect::Table();\n\nstruct SuccinctBitVector {\n    const\
    \ int m_size = 256;\n    const int s_size = 32;\n    int n;\n    vector<uint32_t>\
    \ l;\n    vector<unsigned char> m;\n    vector<uint32_t> s;\n    FastSelect sel[2];\n\
    \    SuccinctBitVector(int n) : n(n), l((n + m_size - 1) / m_size + 1, 0), m((n\
    \ + s_size - 1) / s_size + 1, 0), s((n + s_size - 1) / s_size, 0){}\n    void\
    \ set(int x, bool fl = true){\n        if(bool(s[x / s_size] & (1u << (x % s_size)))\
    \ == fl)\n            return;\n        if(fl){\n            s[x / s_size] |= (1u\
    \ << (x % s_size));\n            ++l[x / m_size + 1];\n            ++m[x / s_size\
    \ + 1];\n        }\n        else{\n            s[x / s_size] &= ~(1u << (x % s_size));\n\
    \            --l[x / m_size + 1];\n            --m[x / s_size + 1];\n        }\n\
    \    }\n    void build(){\n        for(int i = 0; i < l.size() - 1; ++i)\n   \
    \         l[i + 1] += l[i];\n        for(int i = 0; i < m.size() - 1; ++i){\n\
    \            if(i % 8 != 7)\n                m[i + 1] += m[i];\n            else\n\
    \                m[i + 1] = 0;\n        }\n        sel[0] = FastSelect(n, s, 0);\n\
    \        sel[1] = FastSelect(n, s, 1);\n    }\n    // [0, x)\n    int rank(int\
    \ x){\n        return l[x / m_size] + m[x / s_size] + __builtin_popcount(s[x /\
    \ s_size] & ((1uLL << (x % s_size)) - 1));\n    }\n    int rank(int x, bool fl){\n\
    \        return fl ? rank(x) : x - rank(x);\n    }\n    // fl\u304Cx\u56DE\u76EE\
    \u306B\u51FA\u73FE\u3059\u308B\u4F4D\u7F6E(0-indexed\u306A\u306E\u3067\u6CE8\u610F\
    )\n    int select(int x, bool fl = true){\n        return sel[fl].select(x);\n\
    \    }\n};\n"
  code: "struct FastSelect {\n    static const int l_size = 65536;\n    static const\
    \ int m_size = 256;\n    static const int mb = 255;\n    static const int s_size\
    \ = 32;\n    static const int ss_size = 8;\n\n    struct Table{\n        uint16_t\
    \ l_table[m_size][m_size][s_size];\n        uint32_t s_table[m_size];\n      \
    \  Table() : l_table(), s_table(){\n            for(int i = 0; i < m_size; ++i)\n\
    \                for(int j = 0; j < m_size; ++j){\n                    for(int\
    \ k = 0; k < s_size; ++k)\n                        l_table[i][j][k] = 0;\n   \
    \                 for(int k = 0; k < m_size; ++k){\n                        if(k\
    \ >= i && k < i + j)\n                            l_table[i][j][k >> 3] |= 1 <<\
    \ ((k & 7) * 2);\n                        else if(k >= i + j)\n              \
    \              l_table[i][j][k >> 3] |= 2 << ((k & 7) * 2);\n                \
    \    }\n                }\n            for(int i = 0; i < m_size; ++i){\n    \
    \            s_table[i] = 0;\n                for(int j = 0; j < ss_size; ++j){\n\
    \                    int c = 0;\n                    for(int k = 0; k < ss_size;\
    \ ++k){\n                        c += bool(i & (1 << k));\n                  \
    \      if(j < c){\n                            s_table[i] |= (k << (j * 4));\n\
    \                            break;\n                        }\n             \
    \       }\n                }\n            }\n        }\n    };\n    const static\
    \ Table tab;\n\n    struct AbstractSelect{virtual int select(int x) = 0;};\n \
    \   struct BigSelect : public AbstractSelect{\n        vector<int> w;\n      \
    \  BigSelect(vector<uint32_t>& v, int l, int r, bool fl){\n            for(int\
    \ i = l; i < r; ++i){\n                if(bool(v[i / s_size] & (1u << (i % s_size)))\
    \ == fl){\n                    w.emplace_back(i - l);\n                }\n   \
    \         }\n        }\n        int select(int x){return w[x];}\n    };\n    struct\
    \ SmallSelect : public AbstractSelect{\n        vector<uint32_t>& v;\n       \
    \ int l;\n        bool fl;\n        vector<int> siz;\n        vector<unsigned\
    \ char> w;\n        bool flag(int i){\n            return bool(v[(l + i) / s_size]\
    \ & (1u << ((l + i) % s_size))) == fl;\n        }\n        uint16_t get(int i){\n\
    \            i += l;\n            if(i % s_size <= 24){\n                return\
    \ (v[i / s_size] >> (i % s_size)) & 255;\n            }\n            else{\n \
    \               int l_bit = 32 - (i % s_size);\n                uint16_t lv =\
    \ (v[i / s_size] >> (i % s_size));\n                uint16_t rv = v[i / s_size\
    \ + 1] & ((1u << (8 - l_bit)) - 1);\n                return lv + (rv << l_bit);\n\
    \            }\n        }\n        SmallSelect(vector<uint32_t>& v, int l, int\
    \ r, bool fl) : v(v), l(l), fl(fl){\n            int n = r - l;\n            siz.emplace_back(0);\n\
    \            for(int k = (n + 7) / 8; k != 1; k = (k + 3) / 4){\n            \
    \    siz.emplace_back(siz.back() + (k + 3) / 4 * 4);\n            }\n        \
    \    siz.emplace_back(siz.back() + 1);\n            w.assign(siz.back(), 0);\n\
    \            for(int i = 0; i < n; ++i){\n                if(flag(i)){\n     \
    \               ++w[i / ss_size];\n                }\n            }\n        \
    \    for(int i = 0; i < siz.size() - 2; ++i){\n                for(int j = siz[i];\
    \ j < siz[i + 1]; ++j){\n                    w[siz[i + 1] + (j - siz[i]) / 4]\
    \ += w[j];\n                }\n            }\n        }\n        int select(int\
    \ x){\n            int d = siz.size() - 1;\n            int idx = siz[d];\n  \
    \          for(; d > 0; --d){\n                int ch = siz[d - 1] + (idx - siz[d])\
    \ * 4;\n                int res = (tab.l_table[w[ch]][w[ch + 1]][x >> 3] >> ((x\
    \ & 7) * 2)) & 3;\n                if(res < 2){\n                    if(res)\n\
    \                        x -= w[ch];\n                    idx = ch + res;\n  \
    \              }\n                else{\n                    x -= w[ch] + w[ch\
    \ + 1];\n                    int res2 = (tab.l_table[w[ch + 2]][w[ch + 3]][x >>\
    \ 3] >> ((x & 7) * 2)) & 3;\n                    assert(res2 < 2);\n         \
    \           if(res2)\n                        x -= w[ch + 2];\n              \
    \      idx = ch + 2 + res2;\n                }\n            }\n            return\
    \ idx * ss_size + ((tab.s_table[get(idx * ss_size) ^ (fl ? 0 : 255)] >> (x * 4))\
    \ & 15);\n        }\n    };\n\n    int cnt;\n    vector<AbstractSelect*> b;\n\
    \    vector<int> st;\n    FastSelect(){}\n    FastSelect(int n, vector<uint32_t>&\
    \ v, bool fl) : cnt(0){\n        int s = 0;\n        for(int i = 0; i < n; ++i){\n\
    \            if(bool(v[i / s_size] & (1u << (i % s_size))) == fl){\n         \
    \       ++cnt;\n                if(cnt % mb == 0){\n                    if(i -\
    \ s + 1 > l_size)\n                        b.emplace_back(new BigSelect(v, s,\
    \ i + 1, fl));\n                    else\n                        b.emplace_back(new\
    \ SmallSelect(v, s, i + 1, fl));\n                    st.emplace_back(s);\n  \
    \                  s = i + 1;\n                }\n            }\n        }\n \
    \       if(s != n){\n            st.emplace_back(s);\n            b.emplace_back(new\
    \ BigSelect(v, s, n, fl));\n        }\n    }\n    int select(int x){\n       \
    \ if(x >= cnt)\n            return -1;\n        else{\n            return st[x\
    \ / mb] + b[x / mb]->select(x % mb);\n        }\n    }\n};\n\nconst FastSelect::Table\
    \ FastSelect::tab = FastSelect::Table();\n\nstruct SuccinctBitVector {\n    const\
    \ int m_size = 256;\n    const int s_size = 32;\n    int n;\n    vector<uint32_t>\
    \ l;\n    vector<unsigned char> m;\n    vector<uint32_t> s;\n    FastSelect sel[2];\n\
    \    SuccinctBitVector(int n) : n(n), l((n + m_size - 1) / m_size + 1, 0), m((n\
    \ + s_size - 1) / s_size + 1, 0), s((n + s_size - 1) / s_size, 0){}\n    void\
    \ set(int x, bool fl = true){\n        if(bool(s[x / s_size] & (1u << (x % s_size)))\
    \ == fl)\n            return;\n        if(fl){\n            s[x / s_size] |= (1u\
    \ << (x % s_size));\n            ++l[x / m_size + 1];\n            ++m[x / s_size\
    \ + 1];\n        }\n        else{\n            s[x / s_size] &= ~(1u << (x % s_size));\n\
    \            --l[x / m_size + 1];\n            --m[x / s_size + 1];\n        }\n\
    \    }\n    void build(){\n        for(int i = 0; i < l.size() - 1; ++i)\n   \
    \         l[i + 1] += l[i];\n        for(int i = 0; i < m.size() - 1; ++i){\n\
    \            if(i % 8 != 7)\n                m[i + 1] += m[i];\n            else\n\
    \                m[i + 1] = 0;\n        }\n        sel[0] = FastSelect(n, s, 0);\n\
    \        sel[1] = FastSelect(n, s, 1);\n    }\n    // [0, x)\n    int rank(int\
    \ x){\n        return l[x / m_size] + m[x / s_size] + __builtin_popcount(s[x /\
    \ s_size] & ((1uLL << (x % s_size)) - 1));\n    }\n    int rank(int x, bool fl){\n\
    \        return fl ? rank(x) : x - rank(x);\n    }\n    // fl\u304Cx\u56DE\u76EE\
    \u306B\u51FA\u73FE\u3059\u308B\u4F4D\u7F6E(0-indexed\u306A\u306E\u3067\u6CE8\u610F\
    )\n    int select(int x, bool fl = true){\n        return sel[fl].select(x);\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/succinctbitvector.cpp
  requiredBy: []
  timestamp: '2020-08-25 14:12:39+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/succinctbitvector.cpp
layout: document
redirect_from:
- /library/lib/classes/succinctbitvector.cpp
- /library/lib/classes/succinctbitvector.cpp.html
title: lib/classes/succinctbitvector.cpp
---
