template <typename T>
struct BIT{
    vector<T> elm;
    BIT(int n, T init = T()) : elm(n + 1, init){
    }

    // [0, x)
    T sum(int x){
        T val = 0;
        for(; x > 0; x -= x & -x)
            val += elm[x];
        return val;
    }

    void add(int x, T val){
        for(++x; x < elm.size(); x += x & -x)
            elm[x] += val;
    }
};

