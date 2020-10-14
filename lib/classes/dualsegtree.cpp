template<typename T>
struct Segtree{
    int n;
    T op;
    vector<T> elm;
    function<T(T, T)> f;

    Segtree(int n, T init, function<T(T, T)> f, T op = T()) :
        n(n),
        op(op),
        elm(2 * n, op),
        f(f)
    {
        for(int i = 0; i < n; ++i)
            elm[i + n] = init;
    }

    Segtree(int n, vector<T> init, function<T(T, T)> f, T op = T()) :
        n(n),
        op(op),
        elm(2 * n, op),
        f(f)
    {
        for(int i = 0; i < n; ++i)
            elm[i + n] = init[i];
    }

    void update(int x, int y, T val){
        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){
            if(x & 1){
                elm[x] = f(elm[x], val);
                x++;
            }
            if(!(y & 1)){
                elm[y] = f(elm[y], val);
                y--;
            }
        }
    }

    T get(int x){
        x += n;
        T val = elm[x];
        while(x >>= 1)
            val = f(val, elm[x]);
        return val;
    }
};
