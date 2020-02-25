---
layout: default
---

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


# :heavy_check_mark: lib/classes/avl.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/avl.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-26 07:59:33+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/rsq_avl.test.cpp.html">verify/rsq_avl.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/rsq_avl_erase.test.cpp.html">verify/rsq_avl_erase.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct AVL{
    template <typename U>
    struct Node{
        int size, height;
        U val, sum;
        Node(U val, Node<U>* nil) : val(val), sum(val), size(1), height(1){c[0] = nil; c[1] = nil;}
        Node<U>* c[2];
    };

    using NodePtr = Node<T>*;
    function<T(T, T)> f = [](auto x, auto y){return x + y;};
    T op;
    NodePtr nil;

    AVL(function<T(T, T)> f, T op) : f(f), op(op){
        nil = new Node<T>(op, nullptr);
        nil->size = 0;
        nil->height = 0;
        nil->c[0] = nil;
        nil->c[1] = nil;
    }

    template <bool inv>
    int balance_factor(NodePtr x){return (x->c[0]->height - x->c[1]->height) * (inv ? -1 : 1);}
    void _update(NodePtr x){
        if(x == nil)
            return;
        x->size = x->c[0]->size + x->c[1]->size + 1;
        x->height = max(x->c[0]->height, x->c[1]->height) + 1;
        x->sum = f(f(x->c[0]->sum, x->val), x->c[1]->sum);
    }
    template <bool is_right>
    NodePtr rotate(NodePtr x){
        NodePtr new_root = x->c[1 ^ is_right];
        x->c[1 ^ is_right] = new_root->c[0 ^ is_right];
        new_root->c[0 ^ is_right] = x;
        _update(x);
        _update(new_root);
        return new_root;
    }
    template <bool inv>
    NodePtr _balance(NodePtr x){
        if(balance_factor<inv>(x) == 2){
            if(balance_factor<inv>(x->c[0 ^ inv]) < 0)
                x->c[0 ^ inv] = rotate<inv>(x->c[0 ^ inv]);
            x = rotate<1 ^ inv>(x);
        }
        return x;
    }
    NodePtr balance(NodePtr x){
        x = _balance<false>(x);
        x = _balance<true>(x);
        _update(x);
        return x;
    }
    NodePtr insert(NodePtr x, int idx, T val){
        if(x == nil)
            return new Node<T>(val, nil);
        int left_size = x->c[0]->size;
        if(idx <= left_size)
            x->c[0] = insert(x->c[0], idx, val);
        else
            x->c[1] = insert(x->c[1], idx - left_size - 1, val);
        x = balance(x);
        return x;
    }

    // 子が片方しかない時にノードを削除する
    NodePtr _erase_top(NodePtr x, bool del){
        for(int i = 0; i < 2; ++i){
            if(x->c[i] == nil){
                NodePtr new_node = x->c[i ^ 1];
                if(del)
                    delete(x);
                return new_node;
            }
        }
    }
    // 最小の要素をdstにコピーしてから削除する
    NodePtr _copy_erase(NodePtr x, NodePtr dst, bool del){
        if(x->c[0] == nil){
            dst->val = x->val;
            return _erase_top(x, del);
        }
        x->c[0] = _copy_erase(x->c[0], dst, del);
        x = balance(x);
        return x;
    }
    NodePtr erase(NodePtr x, int idx, bool del = true){
        int left_size = x->c[0]->size;
        if(idx < left_size)
            x->c[0] = erase(x->c[0], idx, del);
        else if(left_size < idx)
            x->c[1] = erase(x->c[1], idx - left_size - 1, del);
        else{
            if(x->c[0] == nil || x->c[1] == nil)
                return _erase_top(x, del);
            x->c[1] = _copy_erase(x->c[1], x, del);
        }
        x = balance(x);
        return x;
    }
    NodePtr getNode(NodePtr x, int idx){
        int left_size = x->c[0]->size;
        if(idx < left_size)
            return getNode(x->c[0], idx);
        else if(left_size < idx)
            return getNode(x->c[1], idx - left_size - 1);
        else
            return x;
    }
    T get(NodePtr x, int l, int r){
        if(l <= 0 && x->size <= r)
            return x->sum;
        int left_size = x->c[0]->size;
        T res = op;
        if(l <= left_size && left_size < r)
            res = x->val;
        if(l < left_size)
            res = f(get(x->c[0], l, r), res);
        if(left_size + 1 < r)
            res = f(res, get(x->c[1], l - left_size - 1, r - left_size - 1));
        return res;
    }
    NodePtr update(NodePtr x, int idx, T val, function<T(T, T)> g = [](auto x, auto y){return x + y;}){
        int left_size = x->c[0]->size;
        if(idx < left_size)
            x->c[0] = update(x->c[0], idx, val, g);
        else if(left_size < idx)
            x->c[1] = update(x->c[1], idx - left_size - 1, val, g);
        else
            x->val = g(x->val, val);
        _update(x);

        return x;
    }
    NodePtr set(NodePtr x, int idx, T val){
        int left_size = x->c[0]->size;
        if(idx < left_size)
            x->c[0] = set(x->c[0], idx, val);
        else if(left_size < idx)
            x->c[1] = set(x->c[1], idx - left_size - 1, val);
        else
            x->val = val;
        _update(x);
        return x;
    }

    void print(NodePtr x, int p = 0){
        if(x == nil)return;
        if(p == 0)
            cout << "----print----" << endl;
        print(x->c[0], p + 12);
        for(int i = 0; i < p; ++i)
            cout << " ";
        cout << "val:" << x->val << " ";
        cout << "sum:" << x->sum << " ";
        cout << "size:" << x->size << " ";
        cout << "height:" << x->height << endl;
        print(x->c[1], p + 12);
        if(p == 0)
            cout << "-------------" << endl;
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/avl.cpp"
template <typename T>
struct AVL{
    template <typename U>
    struct Node{
        int size, height;
        U val, sum;
        Node(U val, Node<U>* nil) : val(val), sum(val), size(1), height(1){c[0] = nil; c[1] = nil;}
        Node<U>* c[2];
    };

    using NodePtr = Node<T>*;
    function<T(T, T)> f = [](auto x, auto y){return x + y;};
    T op;
    NodePtr nil;

    AVL(function<T(T, T)> f, T op) : f(f), op(op){
        nil = new Node<T>(op, nullptr);
        nil->size = 0;
        nil->height = 0;
        nil->c[0] = nil;
        nil->c[1] = nil;
    }

    template <bool inv>
    int balance_factor(NodePtr x){return (x->c[0]->height - x->c[1]->height) * (inv ? -1 : 1);}
    void _update(NodePtr x){
        if(x == nil)
            return;
        x->size = x->c[0]->size + x->c[1]->size + 1;
        x->height = max(x->c[0]->height, x->c[1]->height) + 1;
        x->sum = f(f(x->c[0]->sum, x->val), x->c[1]->sum);
    }
    template <bool is_right>
    NodePtr rotate(NodePtr x){
        NodePtr new_root = x->c[1 ^ is_right];
        x->c[1 ^ is_right] = new_root->c[0 ^ is_right];
        new_root->c[0 ^ is_right] = x;
        _update(x);
        _update(new_root);
        return new_root;
    }
    template <bool inv>
    NodePtr _balance(NodePtr x){
        if(balance_factor<inv>(x) == 2){
            if(balance_factor<inv>(x->c[0 ^ inv]) < 0)
                x->c[0 ^ inv] = rotate<inv>(x->c[0 ^ inv]);
            x = rotate<1 ^ inv>(x);
        }
        return x;
    }
    NodePtr balance(NodePtr x){
        x = _balance<false>(x);
        x = _balance<true>(x);
        _update(x);
        return x;
    }
    NodePtr insert(NodePtr x, int idx, T val){
        if(x == nil)
            return new Node<T>(val, nil);
        int left_size = x->c[0]->size;
        if(idx <= left_size)
            x->c[0] = insert(x->c[0], idx, val);
        else
            x->c[1] = insert(x->c[1], idx - left_size - 1, val);
        x = balance(x);
        return x;
    }

    // 子が片方しかない時にノードを削除する
    NodePtr _erase_top(NodePtr x, bool del){
        for(int i = 0; i < 2; ++i){
            if(x->c[i] == nil){
                NodePtr new_node = x->c[i ^ 1];
                if(del)
                    delete(x);
                return new_node;
            }
        }
    }
    // 最小の要素をdstにコピーしてから削除する
    NodePtr _copy_erase(NodePtr x, NodePtr dst, bool del){
        if(x->c[0] == nil){
            dst->val = x->val;
            return _erase_top(x, del);
        }
        x->c[0] = _copy_erase(x->c[0], dst, del);
        x = balance(x);
        return x;
    }
    NodePtr erase(NodePtr x, int idx, bool del = true){
        int left_size = x->c[0]->size;
        if(idx < left_size)
            x->c[0] = erase(x->c[0], idx, del);
        else if(left_size < idx)
            x->c[1] = erase(x->c[1], idx - left_size - 1, del);
        else{
            if(x->c[0] == nil || x->c[1] == nil)
                return _erase_top(x, del);
            x->c[1] = _copy_erase(x->c[1], x, del);
        }
        x = balance(x);
        return x;
    }
    NodePtr getNode(NodePtr x, int idx){
        int left_size = x->c[0]->size;
        if(idx < left_size)
            return getNode(x->c[0], idx);
        else if(left_size < idx)
            return getNode(x->c[1], idx - left_size - 1);
        else
            return x;
    }
    T get(NodePtr x, int l, int r){
        if(l <= 0 && x->size <= r)
            return x->sum;
        int left_size = x->c[0]->size;
        T res = op;
        if(l <= left_size && left_size < r)
            res = x->val;
        if(l < left_size)
            res = f(get(x->c[0], l, r), res);
        if(left_size + 1 < r)
            res = f(res, get(x->c[1], l - left_size - 1, r - left_size - 1));
        return res;
    }
    NodePtr update(NodePtr x, int idx, T val, function<T(T, T)> g = [](auto x, auto y){return x + y;}){
        int left_size = x->c[0]->size;
        if(idx < left_size)
            x->c[0] = update(x->c[0], idx, val, g);
        else if(left_size < idx)
            x->c[1] = update(x->c[1], idx - left_size - 1, val, g);
        else
            x->val = g(x->val, val);
        _update(x);

        return x;
    }
    NodePtr set(NodePtr x, int idx, T val){
        int left_size = x->c[0]->size;
        if(idx < left_size)
            x->c[0] = set(x->c[0], idx, val);
        else if(left_size < idx)
            x->c[1] = set(x->c[1], idx - left_size - 1, val);
        else
            x->val = val;
        _update(x);
        return x;
    }

    void print(NodePtr x, int p = 0){
        if(x == nil)return;
        if(p == 0)
            cout << "----print----" << endl;
        print(x->c[0], p + 12);
        for(int i = 0; i < p; ++i)
            cout << " ";
        cout << "val:" << x->val << " ";
        cout << "sum:" << x->sum << " ";
        cout << "size:" << x->size << " ";
        cout << "height:" << x->height << endl;
        print(x->c[1], p + 12);
        if(p == 0)
            cout << "-------------" << endl;
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

