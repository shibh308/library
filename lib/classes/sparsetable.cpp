template <typename T>
struct SparseTable{
    vector<int> len;
    vector<vector<T>> v;
    function<T(T, T)> f;
    SparseTable(){}
    SparseTable(vector<T>& a, function<T(T, T)> f) : len(a.size() + 1, 0), v(1, a), f(f){
        int n = a.size();
        for(int j = 0; (1 << j) < n; ++j){
            v.emplace_back(n);
            for(int i = 0; i < n; ++i)
                v[j + 1][i] = (i + (1 << j) < n ? f(v[j][i], v[j][i + (1 << j)]) : v[j][i]);
        }
        for(int i = 2; i <= n; ++i){
            len[i] = len[i >> 1] + 1;
        }
    }
    T get(int l, int r){
        int siz = r - l;
        return f(v[len[siz]][l], v[len[siz]][r - (1 << len[siz])]);
    }
};

