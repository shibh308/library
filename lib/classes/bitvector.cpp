struct BitVector{
    vector<uint64_t> v;
    vector<int> r;
    BitVector(){}
    void build(){
        r.assign(v.size() + 1, 0);
        for(int i = 0; i < v.size(); ++i)
            r[i + 1] = r[i] + __builtin_popcountll(v[i]);
    }
    bool access(int x){
        return (v[x >> 6] >> (x & 63)) & 1;
    }
    // [0, x)の1の出現回数
    int rank(int x){
        return r[x >> 6] + __builtin_popcountll(v[x >> 6] & ((1uLL << (x & 63)) - 1));
    }
    int rank(int x, bool fl){
        return fl ? rank(x) : x - rank(x);
    }
};

