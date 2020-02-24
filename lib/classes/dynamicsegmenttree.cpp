template <typename T>
struct Segtree{

    struct SegNode;

    struct SegNode{
        T val;
        SegNode* l;
        SegNode* r;

        SegNode(T val) : val(val), l(nullptr), r(nullptr){}
    };

    i64 n;
    function<T(T, T)> f;
    T op;
    SegNode* root;

    Segtree(int n_, function<T(T, T)> f, T op) : f(f), op(op){
        for(n = 1; n < n_; n <<= 1);
        root = new SegNode(op);
    }

    SegNode* getl(SegNode* node, T val){
        return node->l == nullptr ? node->l = new SegNode(val) : node->l;
    }

    SegNode* getr(SegNode* node, T val){
        return node->r == nullptr ? node->r = new SegNode(val) : node->r;
    }

    void eval(SegNode* node){
        node->val = f(node->l == nullptr ? op : node->l->val, node->r == nullptr ? op : node->r->val);
    }

    void set(i64 x, T val){
        assert(0 <= x && x < n);

        SegNode* node = root;
        stack<SegNode*> nodes;
        i64 l = 0, r = n;

        while(r - l > 1){
            nodes.push(node);
            i64 mid = (l + r) >> 1;

            if(x < mid){
                node = getl(node, x);
                r = mid;
            }else{
                node = getr(node, x);
                l = mid;
            }
        }

        node->val = val;
        while(!nodes.empty()){
            eval(nodes.top());
            nodes.pop();
        }
    }

    void update(i64 x, T val){
        assert(0 <= x && x < n);

        SegNode* node = root;
        stack<SegNode*> nodes;
        i64 l = 0, r = n;

        while(r - l > 1){
            nodes.push(node);
            i64 mid = (l + r) >> 1;

            if(x < mid){
                node = getl(node, x);
                r = mid;
            }else{
                node = getr(node, x);
                l = mid;
            }
        }

        node->val = f(node->val, val);
        while(!nodes.empty()){
            eval(nodes.top());
            nodes.pop();
        }
    }

    T get(i64 x, i64 y, SegNode* node = nullptr, i64 l = 0,  i64 r = 0){

        if(node == nullptr){
            node = root;
            r = n;
        }

        if(x <= l && r <= y)
            return node->val;

        if(r <= x || y <= l)
            return op;

        T val_l = op, val_r = op;
        i64 mid = (l + r) >> 1;

        if(node->l != nullptr)
            val_l = f(val_l, get(x, y, node->l, l, mid));
        if(node->r != nullptr)
            val_r = f(get(x, y, node->r, mid, r), val_r);

        return f(val_l, val_r);
    }

};

