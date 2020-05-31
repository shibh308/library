template<typename T>
struct LinearTimeSparseTable{
    int n, m;
    vector<T> a;
    SparseTable<T> b;
    vector<vector<uint32_t>> c;
    static constexpr uint32_t block = 32;
    LinearTimeSparseTable(vector<T>& v) : n(v.size()), a(v), m((n + block - 1) / block){
        n = m * block;
        v.resize(n, 0);
        vector<T> big_table(m);
        for(int i = 0; i < n; ++i)
            big_table[i / block] = (i & (block - 1) ? min(big_table[i / block], v[i]) : v[i]);
        b = SparseTable<T>(big_table, [](auto x, auto y){return min(x, y);});
        c.assign(m, vector<uint32_t>(block, 0));
        for(int i = 0; i < m; ++i){
            stack<pair<T, int>> st;
            vector<int> g(block, -1);
            for(int j = 0; j < block; ++j){
                T x = v[i * block + j];
                while(!st.empty() && x <= st.top().first)st.pop();
                if(!st.empty())
                    g[j] = st.top().second;
                st.emplace(x, j);
            }
            for(int j = 0; j < block; ++j){
                c[i][j] = (g[j] == -1 ? 0 : c[i][g[j]] | (1u << g[j]));
            }
        }
    }
    T get_small(int i, int j, int k){
        uint32_t w = c[k][j] & ~((1u << i) - 1);
        if(w == 0)
            return a[k * block + j];
        return a[k * block + (__builtin_ffs(w) - 1)];
    }
    T get(int l, int r){
        --r;
        int lb = l / block;
        int rb = r / block;
        int lc = l & (block - 1);
        int rc = r & (block - 1);
        if(lb == rb)
            return get_small(lc, rc, lb);
        T l_res = get_small(lc, block - 1, lb);
        T r_res = get_small(0, rc, rb);
        if(rb - lb == 1)
            return min(l_res, r_res);
        return min({l_res, r_res, b.get(lb + 1, rb)});
    }
};

