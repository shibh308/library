template<typename T, typename U>
struct Segtree{
    int n;
    T op_t;
    U op_u;
    vector<T> elm;
    vector<U> lazy;
    vector<int> length;
    function<T(T, T)> f;
    function<T(T, U, int)> g;
    function<U(U, U)> h;

    Segtree(int n, T init, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t = T(), U op_u = U()) :
        n(n),
        op_t(op_t),
        op_u(op_u),
        elm(2 * n, init),
        lazy(2 * n, op_u),
        length(2 * n, 0),
        f(f),
        g(g),
        h(h)
    {
        for(int i = n - 1; i > 0; --i){
            elm[i] = f(elm[2 * i], elm[2 * i + 1]);
            length[i] = length[2 * i] + 1;
        }
    }

    Segtree(int n, vector<T> init, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t = T(), U op_u = U()) :
        n(n),
        op_t(op_t),
        op_u(op_u),
        elm(2 * n),
        lazy(2 * n, op_u),
        length(2 * n, 0),
        f(f),
        g(g),
        h(h)
    {
        for(int i = 0; i < n; ++i)
            elm[i + n] = init[i];

        for(int i = n - 1; i > 0; --i){
            elm[i] = f(elm[2 * i], elm[2 * i + 1]);
            length[i] = length[2 * i] + 1;
        }
    }

    vector<int> get_list(int x, int y){

        vector<int> ret_list;
        for(x += n, y += n - 1; x; x >>= 1, y >>= 1){
            ret_list.emplace_back(x);
            if(x != y)
                ret_list.emplace_back(y);
        }

        return ret_list;
    }

    void eval(int x){

        elm[x] = g(elm[x], lazy[x], 1 << length[x]);
        if(x < n){
            lazy[2 * x] = h(lazy[2 * x], lazy[x]);
            lazy[2 * x + 1] = h(lazy[2 * x + 1], lazy[x]);
        }
        lazy[x] = op_u;
    }

    void update(int x, int y, U val){

        vector<int> index_list = get_list(x, y);
        for(int i = index_list.size() - 1; i >= 0; --i)
            eval(index_list[i]);

        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){
            if(x & 1){
                lazy[x] = h(lazy[x], val);
                eval(x++);
            }
            if(!(y & 1)){
                lazy[y] = h(lazy[y], val);
                eval(y--);
            }
        }

        for(auto index : index_list){
            if(index < n){
                eval(2 * index);
                eval(2 * index + 1);
                elm[index] = f(elm[2 * index], elm[2 * index + 1]);
            }
        }
    }

    T get(int x, int y){

        vector<int> index_list = get_list(x, y);
        for(int i = index_list.size() - 1; i >= 0; --i)
            eval(index_list[i]);

        T l = op_t, r = op_t;
        for(x += n, y += n - 1; x <= y; x >>= 1, y >>= 1){
            if(x & 1){
                eval(x);
                l = f(l, elm[x++]);
            }
            if(!(y & 1)){
                eval(y);
                r = f(elm[y--], r);
            }
        }
        return f(l, r);
    }
};

