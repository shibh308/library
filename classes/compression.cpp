template<typename T>
struct Compression{
    vector<T> compvec;
    void Comp(vector<T>& inp){//圧縮する
        compvec = inp;
        sort(compvec.begin(), compvec.end());
        compvec.erase(unique(compvec.begin(), compvec.end()), compvec.end());
    }
    int Index(T val){//圧縮を元に対応するインデックスを返す
        auto it = lower_bound(compvec.begin(), compvec.end(), val);
        return (*it == val ? distance(compvec.begin(), it) : -1);
    }
};
