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

    Node* _insert(Node* p, T st, T en, Elm f){
        if(!p)
            return new Node(f);
        if(p->f(st) <= f(st) && p->f(en) <= f(en))
            return p;
        if(p->f(st) >= f(st) && p->f(en) >= f(en)){
            p->f = f;
            return p;
        }
        T mid = (st + en) / 2;
        if(p->f(mid) > f(mid))
            swap(p->f, f);
        if(p->f(st) >= f(st))
            p->l = _insert(p->l, st, mid, f);
        else
            p->r = _insert(p->r, mid, en, f);
        return p;
    }

    U _query(Node* p, T st, T en, T x){
        if(!p)
            return _inf;
        if(st == en)
            return p->f(x);
        T mid = (st + en) / 2;
        if(x <= mid)
            return min(p->f(x), _query(p->l, st, mid, x));
        else
            return min(p->f(x), _query(p->r, mid, en, x));
    }

    void insert(Elm f){
        root = _insert(root, _min, _max, f);
    }

    U query(T x){
        return _query(root, _min, _max, x);
    }
};

