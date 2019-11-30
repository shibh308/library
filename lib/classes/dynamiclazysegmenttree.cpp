template<typename T, typename U>
struct Segtree{

    struct SegNode{
        T val;
        U lazy;

        SegNode* l;
        SegNode* r;
        SegNode(T val, U lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr){}
    };

    i64 n;
    function<T(T, T)> f;
    function<T(T, U, int)> g;
    function<U(U, U)> h;
    T op_t;
    U op_u;

    SegNode* root;

    Segtree(int n_, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t), op_u(op_u){
        for(n = 1; n < n_; n <<= 1);
        root = new SegNode(op_t, op_u);
    }

    SegNode* getl(SegNode* node){
        return node->l ? node->l : node->l = new SegNode(op_t, op_u);
    }

    SegNode* getr(SegNode* node){
        return node->r ? node->r : node->r = new SegNode(op_t, op_u);
    }

    void eval(SegNode* node, i64 len){
        node->val = g(node->val, node->lazy, len);
        getl(node);
        node->l->lazy = h(node->l->lazy, node->lazy);
        getr(node);
        node->r->lazy = h(node->r->lazy, node->lazy);
        node->lazy = op_u;
    }

    void update(i64 x, i64 y, U val, SegNode* node = nullptr, i64 l = 0, i64 r = 0){
        if(node == nullptr){
            node = root;
            r = n;
        }
        eval(node, r - l);
        if(r <= x || y <= l)
            return ;
        if(x <= l && r <= y){
            node->lazy = h(node->lazy, val);
            eval(node, r - l);
        }else{
            i64 mid = (l + r) >> 1;
            update(x, y, val, getl(node), l, mid);
            update(x, y, val, getr(node), mid, r);
            node->val = f(node->l->val, node->r->val);
        }
    }

    T get(i64 x, i64 y, SegNode* node = nullptr, i64 l = 0, i64 r = 0){
        if(node	== nullptr){
            node = root;
            r = n;
        }

        if(r <= x || y <= l)
            return op_t;
        eval(node, r - l);
        if(x <= l && r <= y)
            return node->val;

        i64 val_l = op_t, val_r = op_t;
        i64 mid = (l + r) >> 1;

        if(node->l)
            val_l = get(x, y, node->l, l, mid);
        if(node->r)
            val_r = get(x, y, node->r, mid, r);
        return f(val_l, val_r);
    }

};

