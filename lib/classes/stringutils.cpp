struct StringUtils{
    int n;
    vector<int> s;
    vector<int> sa, sa_inv, lcp, tab_len;
    vector<vector<int>> lcp_arr;
    StringUtils(string _s) : StringUtils(vector<int>(_s.begin(), _s.end())){}
    StringUtils(vector<int> _s) : n(_s.size() + 1), s(_s), sa(n), lcp(n, 0), tab_len(n + 1, 0){
        s.emplace_back(numeric_limits<int>::min());
        sa_inv = s;
        vector<int> comp(s);
        sort(comp.begin(), comp.end());
        comp.erase(unique(comp.begin(), comp.end()), comp.end());
        for(int i = 0; i < n; ++i)
            sa_inv[i] = distance(comp.begin(), lower_bound(comp.begin(), comp.end(), sa_inv[i]));
        int m = comp.size();
        for(int i = 0; m != n; ++i){
            vector<vector<int>> table(m);
            vector<vector<int>> table2(m);
            for(int j = 0; j < n; ++j){
                table[sa_inv[(j + (1 << i)) % n]].emplace_back(j);
            }
            for(int j = 0; j < m; ++j)
                for(auto idx : table[j]){
                    table2[sa_inv[idx]].emplace_back(idx);
                }
            pair<int,int> pre{-1, -1};
            int pm = m;
            m = -1;
            vector<int> nex(n);
            for(int j = 0; j < pm; ++j)
                for(auto idx : table2[j]){
                    auto p = make_pair(sa_inv[idx], sa_inv[(idx + (1 << i)) % n]);
                    if(p != pre){
                        m++;
                        pre = p;
                    }
                    nex[idx] = m;
                }
            sa_inv = move(nex);
            m++;
        }
        for(int i = 0; i < n; ++i){
            sa[sa_inv[i]] = i;
        }
        int h = 0;
        for(int i = 0; i < n; ++i){
            int j = (sa_inv[i] + 1 == n ? n : sa[sa_inv[i] + 1]);
            if(h)
                --h;
            for(; i + h < n && j + h < n && s[i + h] == s[j + h]; ++h);
            lcp[sa_inv[i]] = h;
        }
        lcp_arr.emplace_back(lcp);
        for(int j = 0; (1 << j) < n; ++j){
            lcp_arr.emplace_back(n);
            for(int i = 0; i < n; ++i)
                lcp_arr[j + 1][i] = (i + (1 << j) < n ? min(lcp_arr[j][i], lcp_arr[j][i + (1 << j)]) : lcp_arr[j][i]);
        }
        for(int i = 2; i <= n; ++i)
            tab_len[i] = tab_len[i >> 1] + 1;
    }
    // [l1, r1) < [l2, r2)
    bool le(int l1, int r1, int l2, int r2){
        int len1 = r1 - l1;
        int len2 = r2 - l2;
        if(get_lcp(l1, l2) >= min(len1, len2))
            return len1 < len2;
        else
            return sa_inv[l1] < sa_inv[l2];
    }
    int get_lcp(int l, int r){
        l = sa_inv[l];
        r = sa_inv[r];
        if(l > r)
            swap(l, r);
        else if(l == r){
            return n - sa[l] - 1;
        }
        int siz = r - l;
        return min(lcp_arr[tab_len[siz]][l], lcp_arr[tab_len[siz]][r - (1 << tab_len[siz])]);
    }
};

