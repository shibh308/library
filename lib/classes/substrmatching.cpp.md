---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: verify/multi_str_matching.test.cpp
    title: verify/multi_str_matching.test.cpp
  - icon: ':heavy_check_mark:'
    path: verify/string_seatch.test.cpp
    title: verify/string_seatch.test.cpp
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"lib/classes/substrmatching.cpp\"\nstruct SubstrMatching{\n\
    \    int n;\n    string s;\n    vector<int> sa, lcp, lcp_table;\n    SubstrMatching(string\
    \ s) : s(s), n(s.size()){\n        sa_is();\n        lcp_build();\n    }\n   \
    \ vector<int> induced_sort(vector<int> v, int k){\n        if(v.size() == k){\n\
    \            vector<int> ret(v.size());\n            for(int i = 0; i < v.size();\
    \ ++i)\n                ret[v[i]] = i;\n            return ret;\n        }\n \
    \       vector<int> type(v.size(), 1);\n        for(int i = v.size() - 2; i >=\
    \ 0; --i)\n            type[i] = (v[i] == v[i + 1] ? type[i + 1] : v[i] < v[i\
    \ + 1]);\n        vector<int> lms;\n        vector<vector<int>> lms_str;\n   \
    \     for(int i = 0; i < v.size() - 1; ++i){\n            if(!lms_str.empty())\n\
    \                lms_str.back().emplace_back(v[i + 1]);\n            if(!type[i]\
    \ && type[i + 1]){\n                lms_str.emplace_back(1, v[i + 1]);\n     \
    \           type[i + 1] = 2 + lms.size();\n                lms.emplace_back(i\
    \ + 1);\n            }\n        }\n        vector<int> v_cnt(k, 0);\n        for(auto\
    \ x : v)\n            ++v_cnt[x];\n        vector<int> bin(k + 1, v.size());\n\
    \        for(int i = 0, idx = 0; i < k; ++i){\n            bin[i] = idx;\n   \
    \         idx += v_cnt[i];\n        }\n        auto calc = [&](auto& seed){\n\
    \            vector<int> cnt(k, 0);\n            vector<int> sa_v(v.size(), -1);\n\
    \            for(auto i : seed){\n                int ch = v[i];\n           \
    \     sa_v[bin[ch + 1] - cnt[ch] - 1] = i;\n                ++cnt[ch];\n     \
    \       }\n            cnt.assign(k, 0);\n            for(int i = 0; i < v.size();\
    \ ++i){\n                int nex = sa_v[i] - 1;\n                if(nex >= 0 &&\
    \ type[nex] == 0){\n                    int ch = v[nex];\n                   \
    \ sa_v[bin[ch] + cnt[ch]] = nex;\n                    ++cnt[ch];\n           \
    \     }\n            }\n            cnt.assign(k, 0);\n\n            for(int i\
    \ = v.size() - 1; i >= 0; --i){\n                int nex = sa_v[i] - 1;\n    \
    \            if(nex < 0 || !type[nex])\n                    continue;\n      \
    \          if(nex >= 0 && type[nex]){\n                    int ch = v[nex];\n\
    \                    sa_v[bin[ch + 1] - cnt[ch] - 1] = nex;\n                \
    \    ++cnt[ch];\n                }\n            }\n            return sa_v;\n\
    \        };\n        auto ret_sa = calc(lms);\n        int m = lms.size();\n \
    \       vector<int> lms_idx;\n        for(int i = 0; i < v.size(); ++i){\n   \
    \         if(type[ret_sa[i]] >= 2)\n                lms_idx.emplace_back(type[ret_sa[i]]\
    \ - 2);\n        }\n        int lms_cnt = 0;\n        vector<int> lms_id(m, -100);\n\
    \        for(int i = 0; i < m; ++i){\n            if(i && lms_str[lms_idx[i -\
    \ 1]] != lms_str[lms_idx[i]])\n                ++lms_cnt;\n            lms_id[lms_idx[i]]\
    \ = lms_cnt + 0;\n        }\n        vector<int> ret_seed = induced_sort(lms_id,\
    \ lms_cnt + 1);\n        vector<int> seed(m, 0);\n        for(int i = 0; i < m;\
    \ ++i)\n            seed[i] = lms[ret_seed[m - i - 1]];\n        ret_sa = calc(seed);\n\
    \        return ret_sa;\n    }\n    void sa_is(){\n        unordered_set<char>\
    \ c_uset;\n        for(int i = 0; i < n; ++i)\n            c_uset.insert(s[i]);\n\
    \        set<char> c_set;\n        for(auto c : c_uset)\n            c_set.insert(c);\n\
    \        unordered_map<int, int> c_idx;\n        int k = 1;\n        for(auto\
    \ c : c_set)\n            c_idx[c] = k++;\n        vector<int> v(n + 1, 0);\n\
    \        for(int i = 0; i < n; ++i)\n            v[i] = c_idx[s[i]];\n       \
    \ sa = induced_sort(v, k);\n    }\n    void lcp_build(){\n        vector<int>\
    \ sa_inv(n + 1);\n        for(int i = 0; i <= n; ++i)\n            sa_inv[sa[i]]\
    \ = i;\n        lcp.assign(n + 1, 0);\n        for(int i = 0, p = 0; i <= n; ++i){\n\
    \            if(sa_inv[i] == n)\n                continue;\n            for(;\
    \ i + p < n && sa[sa_inv[i] + 1] + p < n && s[i + p] == s[sa[sa_inv[i] + 1] +\
    \ p]; ++p);\n            lcp[sa_inv[i]] = p;\n            if(p > 0)\n        \
    \        --p;\n        }\n        int siz = 1;\n        for(; siz <= n; siz *=\
    \ 2);\n        lcp_table.resize(2 * siz, -1);\n        for(int i = 0; i < n; ++i)\n\
    \            lcp_table[i + siz] = lcp[i];\n        for(int i = siz - 1; i > 0;\
    \ --i)\n            lcp_table[i] = min(lcp_table[i << 1], lcp_table[(i << 1) |\
    \ 1]);\n    }\n    int match_len(string& t){\n        int l = 0, r = lcp_table.size()\
    \ / 2;\n        int l_lcp = 0;\n        int idx = 1;\n        while(r - l > 1){\n\
    \            int mid = (l + r) >> 1;\n            int m_lcp = lcp_table[idx <<=\
    \ 1];\n            if(m_lcp == lcp_table[0])\n                r = mid;\n     \
    \       else if(l_lcp < m_lcp){\n                l = mid;\n                ++idx;\n\
    \            }\n            else if(l_lcp > m_lcp)\n                r = mid;\n\
    \            else{\n                for(m_lcp = l_lcp; m_lcp < t.size() && sa[mid]\
    \ + m_lcp < s.size() && t[m_lcp] == s[sa[mid] + m_lcp]; ++m_lcp);\n          \
    \      if(sa[mid] + m_lcp == s.size() || m_lcp == t.size() || s[sa[mid] + m_lcp]\
    \ < t[m_lcp]){\n                    l_lcp = m_lcp;\n                    l = mid;\n\
    \                    ++idx;\n                }else{\n                    r = mid;\n\
    \                }\n            }\n        }\n        return l_lcp;\n    }\n \
    \   bool contains(string& t){\n        return match_len(t) == t.size();\n    }\n\
    \    int lower_bound(string& t){\n        int l = 0, r = lcp_table.size() / 2;\n\
    \        int l_lcp = 0;\n        int idx = 1;\n        while(r - l > 1){\n   \
    \         int mid = (l + r) >> 1;\n            int m_lcp = lcp_table[idx <<= 1];\n\
    \n            if(m_lcp == lcp_table[0])\n                r = mid;\n          \
    \  else if(l_lcp < m_lcp){\n                l = mid;\n                ++idx;\n\
    \            }\n            else if(l_lcp > m_lcp)\n                r = mid;\n\
    \            else{\n                for(m_lcp = l_lcp; m_lcp < t.size() && sa[mid]\
    \ + m_lcp < s.size() && t[m_lcp] == s[sa[mid] + m_lcp]; ++m_lcp);\n          \
    \      if(sa[mid] + m_lcp == s.size() || m_lcp == t.size() || s[sa[mid] + m_lcp]\
    \ < t[m_lcp]){\n                    l_lcp = m_lcp;\n                    l = mid;\n\
    \                    ++idx;\n                }else{\n                    r = mid;\n\
    \                }\n            }\n        }\n        return r;\n    }\n    pair<int,int>\
    \ find(string t){\n        --t.back();\n        auto l = lower_bound(t);\n   \
    \     ++t.back();\n        auto r = lower_bound(t);\n        return make_pair(l,\
    \ r);\n    }\n};\n"
  code: "struct SubstrMatching{\n    int n;\n    string s;\n    vector<int> sa, lcp,\
    \ lcp_table;\n    SubstrMatching(string s) : s(s), n(s.size()){\n        sa_is();\n\
    \        lcp_build();\n    }\n    vector<int> induced_sort(vector<int> v, int\
    \ k){\n        if(v.size() == k){\n            vector<int> ret(v.size());\n  \
    \          for(int i = 0; i < v.size(); ++i)\n                ret[v[i]] = i;\n\
    \            return ret;\n        }\n        vector<int> type(v.size(), 1);\n\
    \        for(int i = v.size() - 2; i >= 0; --i)\n            type[i] = (v[i] ==\
    \ v[i + 1] ? type[i + 1] : v[i] < v[i + 1]);\n        vector<int> lms;\n     \
    \   vector<vector<int>> lms_str;\n        for(int i = 0; i < v.size() - 1; ++i){\n\
    \            if(!lms_str.empty())\n                lms_str.back().emplace_back(v[i\
    \ + 1]);\n            if(!type[i] && type[i + 1]){\n                lms_str.emplace_back(1,\
    \ v[i + 1]);\n                type[i + 1] = 2 + lms.size();\n                lms.emplace_back(i\
    \ + 1);\n            }\n        }\n        vector<int> v_cnt(k, 0);\n        for(auto\
    \ x : v)\n            ++v_cnt[x];\n        vector<int> bin(k + 1, v.size());\n\
    \        for(int i = 0, idx = 0; i < k; ++i){\n            bin[i] = idx;\n   \
    \         idx += v_cnt[i];\n        }\n        auto calc = [&](auto& seed){\n\
    \            vector<int> cnt(k, 0);\n            vector<int> sa_v(v.size(), -1);\n\
    \            for(auto i : seed){\n                int ch = v[i];\n           \
    \     sa_v[bin[ch + 1] - cnt[ch] - 1] = i;\n                ++cnt[ch];\n     \
    \       }\n            cnt.assign(k, 0);\n            for(int i = 0; i < v.size();\
    \ ++i){\n                int nex = sa_v[i] - 1;\n                if(nex >= 0 &&\
    \ type[nex] == 0){\n                    int ch = v[nex];\n                   \
    \ sa_v[bin[ch] + cnt[ch]] = nex;\n                    ++cnt[ch];\n           \
    \     }\n            }\n            cnt.assign(k, 0);\n\n            for(int i\
    \ = v.size() - 1; i >= 0; --i){\n                int nex = sa_v[i] - 1;\n    \
    \            if(nex < 0 || !type[nex])\n                    continue;\n      \
    \          if(nex >= 0 && type[nex]){\n                    int ch = v[nex];\n\
    \                    sa_v[bin[ch + 1] - cnt[ch] - 1] = nex;\n                \
    \    ++cnt[ch];\n                }\n            }\n            return sa_v;\n\
    \        };\n        auto ret_sa = calc(lms);\n        int m = lms.size();\n \
    \       vector<int> lms_idx;\n        for(int i = 0; i < v.size(); ++i){\n   \
    \         if(type[ret_sa[i]] >= 2)\n                lms_idx.emplace_back(type[ret_sa[i]]\
    \ - 2);\n        }\n        int lms_cnt = 0;\n        vector<int> lms_id(m, -100);\n\
    \        for(int i = 0; i < m; ++i){\n            if(i && lms_str[lms_idx[i -\
    \ 1]] != lms_str[lms_idx[i]])\n                ++lms_cnt;\n            lms_id[lms_idx[i]]\
    \ = lms_cnt + 0;\n        }\n        vector<int> ret_seed = induced_sort(lms_id,\
    \ lms_cnt + 1);\n        vector<int> seed(m, 0);\n        for(int i = 0; i < m;\
    \ ++i)\n            seed[i] = lms[ret_seed[m - i - 1]];\n        ret_sa = calc(seed);\n\
    \        return ret_sa;\n    }\n    void sa_is(){\n        unordered_set<char>\
    \ c_uset;\n        for(int i = 0; i < n; ++i)\n            c_uset.insert(s[i]);\n\
    \        set<char> c_set;\n        for(auto c : c_uset)\n            c_set.insert(c);\n\
    \        unordered_map<int, int> c_idx;\n        int k = 1;\n        for(auto\
    \ c : c_set)\n            c_idx[c] = k++;\n        vector<int> v(n + 1, 0);\n\
    \        for(int i = 0; i < n; ++i)\n            v[i] = c_idx[s[i]];\n       \
    \ sa = induced_sort(v, k);\n    }\n    void lcp_build(){\n        vector<int>\
    \ sa_inv(n + 1);\n        for(int i = 0; i <= n; ++i)\n            sa_inv[sa[i]]\
    \ = i;\n        lcp.assign(n + 1, 0);\n        for(int i = 0, p = 0; i <= n; ++i){\n\
    \            if(sa_inv[i] == n)\n                continue;\n            for(;\
    \ i + p < n && sa[sa_inv[i] + 1] + p < n && s[i + p] == s[sa[sa_inv[i] + 1] +\
    \ p]; ++p);\n            lcp[sa_inv[i]] = p;\n            if(p > 0)\n        \
    \        --p;\n        }\n        int siz = 1;\n        for(; siz <= n; siz *=\
    \ 2);\n        lcp_table.resize(2 * siz, -1);\n        for(int i = 0; i < n; ++i)\n\
    \            lcp_table[i + siz] = lcp[i];\n        for(int i = siz - 1; i > 0;\
    \ --i)\n            lcp_table[i] = min(lcp_table[i << 1], lcp_table[(i << 1) |\
    \ 1]);\n    }\n    int match_len(string& t){\n        int l = 0, r = lcp_table.size()\
    \ / 2;\n        int l_lcp = 0;\n        int idx = 1;\n        while(r - l > 1){\n\
    \            int mid = (l + r) >> 1;\n            int m_lcp = lcp_table[idx <<=\
    \ 1];\n            if(m_lcp == lcp_table[0])\n                r = mid;\n     \
    \       else if(l_lcp < m_lcp){\n                l = mid;\n                ++idx;\n\
    \            }\n            else if(l_lcp > m_lcp)\n                r = mid;\n\
    \            else{\n                for(m_lcp = l_lcp; m_lcp < t.size() && sa[mid]\
    \ + m_lcp < s.size() && t[m_lcp] == s[sa[mid] + m_lcp]; ++m_lcp);\n          \
    \      if(sa[mid] + m_lcp == s.size() || m_lcp == t.size() || s[sa[mid] + m_lcp]\
    \ < t[m_lcp]){\n                    l_lcp = m_lcp;\n                    l = mid;\n\
    \                    ++idx;\n                }else{\n                    r = mid;\n\
    \                }\n            }\n        }\n        return l_lcp;\n    }\n \
    \   bool contains(string& t){\n        return match_len(t) == t.size();\n    }\n\
    \    int lower_bound(string& t){\n        int l = 0, r = lcp_table.size() / 2;\n\
    \        int l_lcp = 0;\n        int idx = 1;\n        while(r - l > 1){\n   \
    \         int mid = (l + r) >> 1;\n            int m_lcp = lcp_table[idx <<= 1];\n\
    \n            if(m_lcp == lcp_table[0])\n                r = mid;\n          \
    \  else if(l_lcp < m_lcp){\n                l = mid;\n                ++idx;\n\
    \            }\n            else if(l_lcp > m_lcp)\n                r = mid;\n\
    \            else{\n                for(m_lcp = l_lcp; m_lcp < t.size() && sa[mid]\
    \ + m_lcp < s.size() && t[m_lcp] == s[sa[mid] + m_lcp]; ++m_lcp);\n          \
    \      if(sa[mid] + m_lcp == s.size() || m_lcp == t.size() || s[sa[mid] + m_lcp]\
    \ < t[m_lcp]){\n                    l_lcp = m_lcp;\n                    l = mid;\n\
    \                    ++idx;\n                }else{\n                    r = mid;\n\
    \                }\n            }\n        }\n        return r;\n    }\n    pair<int,int>\
    \ find(string t){\n        --t.back();\n        auto l = lower_bound(t);\n   \
    \     ++t.back();\n        auto r = lower_bound(t);\n        return make_pair(l,\
    \ r);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/substrmatching.cpp
  requiredBy: []
  timestamp: '2020-06-02 15:59:15+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - verify/multi_str_matching.test.cpp
  - verify/string_seatch.test.cpp
documentation_of: lib/classes/substrmatching.cpp
layout: document
redirect_from:
- /library/lib/classes/substrmatching.cpp
- /library/lib/classes/substrmatching.cpp.html
title: lib/classes/substrmatching.cpp
---
