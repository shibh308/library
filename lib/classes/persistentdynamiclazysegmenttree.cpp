template<typename T, typename U>
struct Segtree{

    struct SegNode{
        T val;
        U lazy;

        shared_ptr<SegNode> l;
        shared_ptr<SegNode> r;
        SegNode(T val, U lazy) : val(val), lazy(lazy), l(nullptr), r(nullptr){}
    };

    i64 n;
    shared_ptr<SegNode> nil;
    function<T(T, T)> f;
    function<T(T, U, int)> g;
    function<U(U, U)> h;
    T op_t;
    U op_u;

    shared_ptr<SegNode> root;

    Segtree(int n_, function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t), op_u(op_u){
        for(n = 1; n < n_; n <<= 1);
        root = make_shared<SegNode>(op_t, op_u);
    }

    void eval(shared_ptr<SegNode> node, i64 len, bool make = true){
        node->val = g(node->val, node->lazy, len);
        if(make){
            node->l = node->l ? make_shared<SegNode>(*node->l) : make_shared<SegNode>(op_t, op_u);
            node->r = node->r ? make_shared<SegNode>(*node->r) : make_shared<SegNode>(op_t, op_u);
        }
        node->l->lazy = h(node->l->lazy, node->lazy);
        node->r->lazy = h(node->r->lazy, node->lazy);
        node->lazy = op_u;
    }

    // if root -> make new node      -> eval(make child)
    void update(i64 x, i64 y, U val, shared_ptr<SegNode> node = nullptr, i64 l = -1, i64 r = -1){
        bool root_flag = (node == nullptr);
        if(root_flag){
            root = make_shared<SegNode>(*root);
            node = root;
        }
        if(l == -1){
            l = 0;
            r = n;
        }
        eval(node, r - l);
        if(r <= x || y <= l)
            return ;
        if(x <= l && r <= y){
            node->lazy = h(node->lazy, val);
            eval(node, r - l, false);
        }else{
            eval(node, r - l);
            i64 mid = (l + r) >> 1;
            update(x, y, val, node->l, l, mid);
            update(x, y, val, node->r, mid, r);
            node->val = f(node->l->val, node->r->val);
        }
        return ;
    }

    T get(i64 x, i64 y, shared_ptr<SegNode> node = nullptr, i64 l = -1, i64 r = -1){
        bool root_flag = (node == nullptr);
        if(root_flag){
            root = make_shared<SegNode>(*root);
            node = root;
        }
        if(l == -1){
            l = 0;
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


