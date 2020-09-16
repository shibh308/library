struct StringUtils{
    int n;
    string s;
    vector<int> sa, sa_inv, lcp;
    StringUtils(string _s) : n(_s.size() + 1), s(_s + "$"), sa_inv(s.begin(), s.end()), sa(n), lcp(n, 0){
        vector<int> comp(sa_inv);
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
        for(int i = 0; i < n - 1; ++i){
            int j = sa[sa_inv[i] + 1];
            if(h)
                --h;
            for(; i + h < n && j + h < n && s[i + h] == s[j + h]; ++h);
            lcp[sa_inv[i]] = h;
        }
    }
};
