struct RunInfo{
    // (t, l, r) の形で返す tは最小周期で0-indexed半開区間
    set<tuple<int,int,int>> run;
    // 最大のLyndon wordを持つ [2][n]で1側が反転
    vector<vector<int>> l;
    // Lyndon Factorization (開始位置列挙)
    vector<int> lyndon_fac;
};

RunInfo getRunInfo(string s){
    vector<StringUtils> su;
    int n = s.size();
    s += "$" + string(s.rbegin(), s.rend());
    vector<int> v(s.begin(), s.end());
    su.emplace_back(v);
    for(int i = 0; i < s.size(); ++i)
        v[i] *= -1;
    su.emplace_back(v);
    vector<vector<int>> l(2, vector<int>(n, 0));
    for(int fl = 0; fl < 2; ++fl){
        stack<pair<int,int>> st;
        for(int i = n - 1; i >= 0; --i){
            int j = i + 1;
            while(!st.empty()){
                int x, y;
                tie(x, y) = st.top();
                if(!su[fl].le(i, j, x, y))
                    break;
                j = y;
                st.pop();
            }
            l[fl][i] = j;
            st.emplace(i, j);
        }
    }
    set<tuple<int,int,int>> run;
    for(int fl = 0; fl < 2; ++fl){
        for(int i = 0; i < n; ++i){
            int j = l[fl][i];
            int t = j - i;
            int l_lcp = su[fl].get_lcp(s.size() - j, s.size() - i);
            int r_lcp = su[fl].get_lcp(i, j);
            int ii = i - l_lcp;
            int jj = j + r_lcp;
            if(jj - ii >= 2 * t)
                run.emplace(t, ii, jj);
        }
    }
    vector<int> dec;
    for(int i = 0; i < n; i = l[0][i])
        dec.emplace_back(i);
    return RunInfo{run, l, dec};
}
