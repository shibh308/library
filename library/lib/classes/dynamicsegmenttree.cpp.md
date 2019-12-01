<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: lib/classes/dynamicsegmenttree.cpp
* category: lib/classes


[Back to top page](../../../index.html)



## Code
```cpp
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


```

[Back to top page](../../../index.html)

