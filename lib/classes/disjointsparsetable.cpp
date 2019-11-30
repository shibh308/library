template <typename T>
struct DisjointSparseTable{
    function<T(T, T)> f;
    vector<vector<T>> v;

    DisjointSparseTable(vector<T>& inp, function<T(T, T)> f) : f(f){
        int n = inp.size();
        int b;
        for(b = 0; (1 << b) <= inp.size(); ++b);
        v.assign(b, vector<T>(n));
        for(int i = 0; i < n; ++i)
            v[0][i] = inp[i];
        for(int i = 1; i < b; ++i){
            int siz = 1 << i;
            for(int j = 0; j < n; j += siz << 1){
                int t = min(j + siz, n);
                v[i][t - 1] = inp[t - 1];
                for(int k = t - 2; k >= j; --k)
                    v[i][k] = f(inp[k], v[i][k + 1]);
                if(t >= n)
                    break;
                v[i][t] = inp[t];
                int r = min(t + siz, n);
                for(int k = t + 1; k < r; ++k)
                    v[i][k] = f(v[i][k - 1], inp[k]);
            }
        }
    }

    T get(int l, int r){
        if(l >= --r)
            return v[0][l];
        int p = 31 - __builtin_clz(l ^ r);
        return f(v[p][l], v[p][r]);
    }
};

