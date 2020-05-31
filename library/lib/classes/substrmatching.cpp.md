---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: lib/classes/substrmatching.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/substrmatching.cpp">View this file on GitHub</a>
    - Last commit date: 2020-05-31 19:48:42+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/multi_str_matching.test.cpp.html">verify/multi_str_matching.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/string_seatch.test.cpp.html">verify/string_seatch.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct SubstrMatching{
    int n;
    string s;
    vector<int> sa, lcp;
    LinearTimeSparseTable<int> lcp_table;
    SubstrMatching(string s) : s(s), n(s.size()), lcp_table(lcp){
        sa_is();
        lcp_build();
        lcp_table = LinearTimeSparseTable<int>(lcp);
    }
    vector<int> induced_sort(vector<int> v, int k){
        if(v.size() == k){
            vector<int> ret(v.size());
            for(int i = 0; i < v.size(); ++i)
                ret[v[i]] = i;
            return ret;
        }
        vector<int> type(v.size(), 1);
        for(int i = v.size() - 2; i >= 0; --i)
            type[i] = (v[i] == v[i + 1] ? type[i + 1] : v[i] < v[i + 1]);
        vector<int> lms;
        vector<vector<int>> lms_str;
        for(int i = 0; i < v.size() - 1; ++i){
            if(!lms_str.empty())
                lms_str.back().emplace_back(v[i + 1]);
            if(!type[i] && type[i + 1]){
                lms_str.emplace_back(1, v[i + 1]);
                type[i + 1] = 2 + lms.size();
                lms.emplace_back(i + 1);
            }
        }
        vector<int> v_cnt(k, 0);
        for(auto x : v)
            ++v_cnt[x];
        vector<int> bin(k + 1, v.size());
        for(int i = 0, idx = 0; i < k; ++i){
            bin[i] = idx;
            idx += v_cnt[i];
        }
        auto calc = [&](auto& seed){
            vector<int> cnt(k, 0);
            vector<int> sa_v(v.size(), -1);
            for(auto i : seed){
                int ch = v[i];
                sa_v[bin[ch + 1] - cnt[ch] - 1] = i;
                ++cnt[ch];
            }
            cnt.assign(k, 0);
            for(int i = 0; i < v.size(); ++i){
                int nex = sa_v[i] - 1;
                if(nex >= 0 && type[nex] == 0){
                    int ch = v[nex];
                    sa_v[bin[ch] + cnt[ch]] = nex;
                    ++cnt[ch];
                }
            }
            cnt.assign(k, 0);

            for(int i = v.size() - 1; i >= 0; --i){
                int nex = sa_v[i] - 1;
                if(nex < 0 || !type[nex])
                    continue;
                if(nex >= 0 && type[nex]){
                    int ch = v[nex];
                    sa_v[bin[ch + 1] - cnt[ch] - 1] = nex;
                    ++cnt[ch];
                }
            }
            return sa_v;
        };
        auto ret_sa = calc(lms);
        int m = lms.size();
        vector<int> lms_idx;
        for(int i = 0; i < v.size(); ++i){
            if(type[ret_sa[i]] >= 2)
                lms_idx.emplace_back(type[ret_sa[i]] - 2);
        }
        int lms_cnt = 0;
        vector<int> lms_id(m, -100);
        for(int i = 0; i < m; ++i){
            if(i && lms_str[lms_idx[i - 1]] != lms_str[lms_idx[i]])
                ++lms_cnt;
            lms_id[lms_idx[i]] = lms_cnt + 0;
        }
        vector<int> ret_seed = induced_sort(lms_id, lms_cnt + 1);
        vector<int> seed(m, 0);
        for(int i = 0; i < m; ++i)
            seed[i] = lms[ret_seed[m - i - 1]];
        ret_sa = calc(seed);
        return ret_sa;
    }
    void sa_is(){
        unordered_set<char> c_uset;
        for(int i = 0; i < n; ++i)
            c_uset.insert(s[i]);
        set<char> c_set;
        for(auto c : c_uset)
            c_set.insert(c);
        unordered_map<int, int> c_idx;
        int k = 1;
        for(auto c : c_set)
            c_idx[c] = k++;
        vector<int> v(n + 1, 0);
        for(int i = 0; i < n; ++i)
            v[i] = c_idx[s[i]];
        sa = induced_sort(v, k);
    }
    void lcp_build(){
        vector<int> sa_inv(n + 1);
        for(int i = 0; i <= n; ++i)
            sa_inv[sa[i]] = i;
        lcp.assign(n + 1, 0);
        for(int i = 0, p = 0; i <= n; ++i){
            if(sa_inv[i] == n)
                continue;
            for(; i + p < n && sa[sa_inv[i] + 1] + p < n && s[i + p] == s[sa[sa_inv[i] + 1] + p]; ++p);
            lcp[sa_inv[i]] = p;
            if(p > 0)
                --p;
        }
    }
    int match_len(string& t){
        int l = 0, r = sa.size();
        int l_lcp = 0;
        while(r - l > 1){
            int mid = (l + r) >> 1;
            int m_lcp = lcp_table.get(l, mid);
            if(l_lcp < m_lcp)
                l = mid;
            else if(l_lcp > m_lcp)
                r = mid;
            else{
                for(m_lcp = l_lcp; m_lcp < t.size() && sa[mid] + m_lcp < s.size() && t[m_lcp] == s[sa[mid] + m_lcp]; ++m_lcp);
                if(sa[mid] + m_lcp == s.size() || m_lcp == t.size() || s[sa[mid] + m_lcp] < t[m_lcp]){
                    l_lcp = m_lcp;
                    l = mid;
                }else
                    r = mid;
            }
        }
        return l_lcp;
    }
    bool contains(string& t){
        return match_len(t) == t.size();
    }
    int lower_bound(string& t){
        int l = 0, r = sa.size();
        int l_lcp = 0;
        while(r - l > 1){
            int mid = (l + r) >> 1;
            int m_lcp = lcp_table.get(l, mid);
            if(l_lcp < m_lcp)
                l = mid;
            else if(l_lcp > m_lcp)
                r = mid;
            else{
                for(m_lcp = l_lcp; m_lcp < t.size() && sa[mid] + m_lcp < s.size() && t[m_lcp] == s[sa[mid] + m_lcp]; ++m_lcp);
                if(sa[mid] + m_lcp == s.size() || m_lcp == t.size() || s[sa[mid] + m_lcp] < t[m_lcp]){
                    l_lcp = m_lcp;
                    l = mid;
                }else
                    r = mid;
            }
        }
        return r;
    }
    pair<int,int> find(string t){
        --t.back();
        auto l = lower_bound(t);
        ++t.back();
        auto r = lower_bound(t);
        return make_pair(l, r);
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/substrmatching.cpp"
struct SubstrMatching{
    int n;
    string s;
    vector<int> sa, lcp;
    LinearTimeSparseTable<int> lcp_table;
    SubstrMatching(string s) : s(s), n(s.size()), lcp_table(lcp){
        sa_is();
        lcp_build();
        lcp_table = LinearTimeSparseTable<int>(lcp);
    }
    vector<int> induced_sort(vector<int> v, int k){
        if(v.size() == k){
            vector<int> ret(v.size());
            for(int i = 0; i < v.size(); ++i)
                ret[v[i]] = i;
            return ret;
        }
        vector<int> type(v.size(), 1);
        for(int i = v.size() - 2; i >= 0; --i)
            type[i] = (v[i] == v[i + 1] ? type[i + 1] : v[i] < v[i + 1]);
        vector<int> lms;
        vector<vector<int>> lms_str;
        for(int i = 0; i < v.size() - 1; ++i){
            if(!lms_str.empty())
                lms_str.back().emplace_back(v[i + 1]);
            if(!type[i] && type[i + 1]){
                lms_str.emplace_back(1, v[i + 1]);
                type[i + 1] = 2 + lms.size();
                lms.emplace_back(i + 1);
            }
        }
        vector<int> v_cnt(k, 0);
        for(auto x : v)
            ++v_cnt[x];
        vector<int> bin(k + 1, v.size());
        for(int i = 0, idx = 0; i < k; ++i){
            bin[i] = idx;
            idx += v_cnt[i];
        }
        auto calc = [&](auto& seed){
            vector<int> cnt(k, 0);
            vector<int> sa_v(v.size(), -1);
            for(auto i : seed){
                int ch = v[i];
                sa_v[bin[ch + 1] - cnt[ch] - 1] = i;
                ++cnt[ch];
            }
            cnt.assign(k, 0);
            for(int i = 0; i < v.size(); ++i){
                int nex = sa_v[i] - 1;
                if(nex >= 0 && type[nex] == 0){
                    int ch = v[nex];
                    sa_v[bin[ch] + cnt[ch]] = nex;
                    ++cnt[ch];
                }
            }
            cnt.assign(k, 0);

            for(int i = v.size() - 1; i >= 0; --i){
                int nex = sa_v[i] - 1;
                if(nex < 0 || !type[nex])
                    continue;
                if(nex >= 0 && type[nex]){
                    int ch = v[nex];
                    sa_v[bin[ch + 1] - cnt[ch] - 1] = nex;
                    ++cnt[ch];
                }
            }
            return sa_v;
        };
        auto ret_sa = calc(lms);
        int m = lms.size();
        vector<int> lms_idx;
        for(int i = 0; i < v.size(); ++i){
            if(type[ret_sa[i]] >= 2)
                lms_idx.emplace_back(type[ret_sa[i]] - 2);
        }
        int lms_cnt = 0;
        vector<int> lms_id(m, -100);
        for(int i = 0; i < m; ++i){
            if(i && lms_str[lms_idx[i - 1]] != lms_str[lms_idx[i]])
                ++lms_cnt;
            lms_id[lms_idx[i]] = lms_cnt + 0;
        }
        vector<int> ret_seed = induced_sort(lms_id, lms_cnt + 1);
        vector<int> seed(m, 0);
        for(int i = 0; i < m; ++i)
            seed[i] = lms[ret_seed[m - i - 1]];
        ret_sa = calc(seed);
        return ret_sa;
    }
    void sa_is(){
        unordered_set<char> c_uset;
        for(int i = 0; i < n; ++i)
            c_uset.insert(s[i]);
        set<char> c_set;
        for(auto c : c_uset)
            c_set.insert(c);
        unordered_map<int, int> c_idx;
        int k = 1;
        for(auto c : c_set)
            c_idx[c] = k++;
        vector<int> v(n + 1, 0);
        for(int i = 0; i < n; ++i)
            v[i] = c_idx[s[i]];
        sa = induced_sort(v, k);
    }
    void lcp_build(){
        vector<int> sa_inv(n + 1);
        for(int i = 0; i <= n; ++i)
            sa_inv[sa[i]] = i;
        lcp.assign(n + 1, 0);
        for(int i = 0, p = 0; i <= n; ++i){
            if(sa_inv[i] == n)
                continue;
            for(; i + p < n && sa[sa_inv[i] + 1] + p < n && s[i + p] == s[sa[sa_inv[i] + 1] + p]; ++p);
            lcp[sa_inv[i]] = p;
            if(p > 0)
                --p;
        }
    }
    int match_len(string& t){
        int l = 0, r = sa.size();
        int l_lcp = 0;
        while(r - l > 1){
            int mid = (l + r) >> 1;
            int m_lcp = lcp_table.get(l, mid);
            if(l_lcp < m_lcp)
                l = mid;
            else if(l_lcp > m_lcp)
                r = mid;
            else{
                for(m_lcp = l_lcp; m_lcp < t.size() && sa[mid] + m_lcp < s.size() && t[m_lcp] == s[sa[mid] + m_lcp]; ++m_lcp);
                if(sa[mid] + m_lcp == s.size() || m_lcp == t.size() || s[sa[mid] + m_lcp] < t[m_lcp]){
                    l_lcp = m_lcp;
                    l = mid;
                }else
                    r = mid;
            }
        }
        return l_lcp;
    }
    bool contains(string& t){
        return match_len(t) == t.size();
    }
    int lower_bound(string& t){
        int l = 0, r = sa.size();
        int l_lcp = 0;
        while(r - l > 1){
            int mid = (l + r) >> 1;
            int m_lcp = lcp_table.get(l, mid);
            if(l_lcp < m_lcp)
                l = mid;
            else if(l_lcp > m_lcp)
                r = mid;
            else{
                for(m_lcp = l_lcp; m_lcp < t.size() && sa[mid] + m_lcp < s.size() && t[m_lcp] == s[sa[mid] + m_lcp]; ++m_lcp);
                if(sa[mid] + m_lcp == s.size() || m_lcp == t.size() || s[sa[mid] + m_lcp] < t[m_lcp]){
                    l_lcp = m_lcp;
                    l = mid;
                }else
                    r = mid;
            }
        }
        return r;
    }
    pair<int,int> find(string t){
        --t.back();
        auto l = lower_bound(t);
        ++t.back();
        auto r = lower_bound(t);
        return make_pair(l, r);
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

