template <typename T, typename U>
struct ConvexHullTrick{
    // 任意の2関数で共有点が高々1個ならElmの中身を適切に変えれば通る

    struct Elm{
        T a, b;
        U operator()(T x){
            return a * x + b;
        }
    };

    struct Node{
        Elm f;
        Node* l;
        Node* r;
        Node(Elm elm) : f(elm), l(nullptr), r(nullptr){}
    };

    U _min, _max, _inf;
    Node* root;

    ConvexHullTrick(U _min, U _max, U _inf) :
        _min(_min),
        _max(_max),
        _inf(_inf),
        root(nullptr)
    {
    }

    Node* _insert(Node* p, T low, T high, Elm f){
        if(!p)
            return new Node(f);
        if(p->f(low) <= f(low) && p->f(high) <= f(high))
            return p;
        if(p->f(low) >= f(low) && p->f(high) >= f(high)){
            p->f = f;
            return p;
        }
        T mid = (low + high) / 2;
        if(p->f(mid) > f(mid))
            swap(p->f, f);
        if(p->f(low) >= f(low))
            p->l = _insert(p->l, low, mid, f);
        else
            p->r = _insert(p->r, mid, high, f);
        return p;
    }

    U _query(Node* p, T low, T high, T x){
        if(!p)
            return _inf;
        if(low == high)
            return p->f(x);
        T mid = (low + high) / 2;
        if(x <= mid)
            return min(p->f(x), _query(p->l, low, mid, x));
        else
            return min(p->f(x), _query(p->r, mid, high, x));
    }

    void insert(Elm f){
        root = _insert(root, _min, _max, f);
    }

    U query(T x){
        return _query(root, _min, _max, x);
    }
};

