using value_type = ll;

class Node;
using np = Node*;

class Node{
public:

    static np nil;

    value_type val;
    uint32_t pri;
    np l = nil;
    np r = nil;

    int size;
    value_type sum;

    bool lazy_flag = false;

    value_type lazy_val = value_type();

    Node() : val(0), pri(rndpri()), size(1), sum(0), l(nil), r(nil){}
    Node(value_type v) : val(v), pri(rndpri()), size(1), sum(v), l(nil), r(nil){}
    Node(value_type v, uint32_t p) : val(v), pri(p), size(1), sum(v), l(nil), r(nil){}

    static uint32_t rndpri() {
        static uint32_t x = 123456789, y = 362436069, z = 521288629, w = time(0);
        uint32_t t = x ^ (x << 11);
        x = y;
        y = z;
        z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return max<uint32_t>(1, w & 0x3FFFFFFF);
    }
};

np Node::nil = new Node(value_type(), 0);

class Treap{

public:

    np root;

    Treap() : root(Node::nil){}

    Treap(value_type val) : root(new Node (val)){}

    // イテレータが指す[st,en)の範囲で初期化する
    Treap(vector<value_type>::iterator st, vector<value_type>::iterator en) : root(Node::nil){
        while(st != en){
            root = _merge(root, new Node(*st));
            ++st;
        }
    }

    // 配列で初期化する
    Treap(vector<value_type> v) : root(Node::nil){
        FOREACH(xx,v)
            root = _merge(root, new Node(xx));
    }

protected:

    int _size(np x){return x == Node::nil ? 0 : x->size;}
    value_type _sum(np x){return x == Node::nil ? 0 : x->sum;}

    np _update(np x){

        if(x == Node::nil)
            return x;

        _push(x);
        _push(x->l);
        _push(x->r);

        x->size = _size(x->l) + _size(x->r) + 1;
        x->sum = _sum(x->l) + _sum(x->r) + x->val;
        return x;
    }

    void _push(np x){
        if(!x->lazy_flag)
            return ;

        x->val += x->lazy_val;
        x->sum += x->size * x->lazy_val;

        if(x->l != Node::nil){
            x->l->lazy_flag = true;
            x->l->lazy_val += x->lazy_val;
        }
        if(x->r != Node::nil){
            x->r->lazy_flag = true;
            x->r->lazy_val += x->lazy_val;
        }

        x->lazy_val = 0;
        x->lazy_flag = false;

    }

    np _merge(np l, np r){
        if(l == Node::nil || r == Node::nil)
            return l == Node::nil ? r : l;

        if(l->pri > r->pri){
            l->r = _merge(l->r, r);
            return _update(l);
        }else{
            r->l = _merge(l, r->l);
            return _update(r);
        }
    }

    pair<np,np> _split(np x, int k){
        if(x == Node::nil)
            return mp(Node::nil, Node::nil);

        if(k <= _size(x->l)){
            pair<np,np> s = _split(x->l, k);
            x->l = s.second;
            return mp(s.first, _update(x));

        }else{
            pair<np,np> s = _split(x->r, k - _size(x->l) - 1);
            x->r = s.first;
            return mp(_update(x), s.second);
        }
    }

    np _insert(np x, int k, value_type val){
        np l,r;
        tie(l, r) = _split(x, k);
        return _merge(_merge(l, new Node(val)), r);
    }

    np _erase(np x, int k){
        np l,r,m;
        tie(l, r) = _split(x, k);
        tie(m, r) = _split(r, 1);
        return _merge(l, r);
    }

    void _set(np x, int k, value_type val){
        _update(x);

        if(k < _size(x->l))
            _set(x->l, k, val);
        else if(_size(x->l) == k)
            x->val = val;
        else
            _set(x->r, k - _size(x->l) - 1, val);

        _update(x);
    }

    void _add(np x, int k, value_type val){
        _update(x);

        if(k < _size(x->l))
            _add(x->l, k, val);
        else if(_size(x->l) == k)
            x->val += val;
        else
            _add(x->r, k - _size(x->l) - 1, val);

        _update(x);
    }

    void _add(np x, int l, int r, value_type val){
        _update(x);

        if(x == Node::nil)
            return ;
        l = max(l, 0);
        r = min(r, _size(x));

        int sl = _size(x->l);

        if(l >= r)
            return ;

        if (l == 0 && r == _size(x)){
            x->lazy_flag = true;
            x->lazy_val += val;
        }
        else{
            if(l <= sl && sl < r)
                x->val += val;

            _add(x->l, l, r, val);
            _add(x->r, l - sl - 1, r - sl - 1, val);
        }

        _update(x);
    }

    value_type _get(np x, int k){

        _update(x);

        if(k < _size(x->l))
            return _get(x->l, k);
        else if(_size(x->l) == k)
            return x->val;
        else
            return _get(x->r, k - _size(x->l) - 1);
    }

    value_type _rangesum(np x, int l, int r){
        _update(x);

        l = max(l, 0);
        r = min(r, _size(x));
        if(l >= r)
            return 0;
        if(l == 0 && r == _size(x))
            return _sum(x);
        value_type retval(0);
        int sl = _size(x->l);
        retval += _rangesum(x->l, l, r);
        retval += _rangesum(x->r, l - sl - 1, r - sl - 1);
        if(l <= sl && sl < r)
            retval += x->val;
        return retval;
    }

    int _lowerbound(np x, value_type val){
        _update(x);

        if(x == Node::nil)
            return 0;
        if(val <= x->val)
            return _lowerbound(x->l, val);
        else
            return _lowerbound(x->r,val) + _size(x->l) + 1;
    }

    np _insert(np x, value_type val){
        return _insert(x, _lowerbound(x, val), val);
    }

public:

    void push_front(value_type val){
        root = _merge(new Node(val), root);
    }

    void push_back(value_type val){
        root = _merge(root, new Node(val));
    }

    void pop_front(){
        root = _split(root, 1).second;
    }

    void pop_back(){
        root = _split(root, _size(root) - 1).first;
    }

    // rootを含めたサイズの出力
    int size(){
        return (root == Node::nil ? 0 : root->size);
    }

    // [l, r)の総和 (同様の実装でRMQ等も可能)
    value_type rangesum(int l, int r){
        return _rangesum(root, l, r);
    }

    // k番目への代入
    void set(int k, value_type val){
        return _set(root, k, val);
    }

    // k番目への加算
    void add(int k, value_type val){
        return _add(root, k, val);
    }

    // [l, r)への一様加算
    void add(int l, int r, value_type val){
        return _add(root, l, r, val);
    }

    // k番目の取得
    value_type get(int k){
        return _get(root, k);
    }

    // k番目への挿入
    void insert(int k, value_type val){
        root = _insert(root, k, val);
    }

    // 適切な位置への挿入
    void insert(value_type val){
        root = _insert(root, val);
    }

    // val <= get(k) となるような最小のk
    int lowerbound(value_type val){
        return _lowerbound(root, val);
    }

    // k番目の要素削除
    void erase(int k){
        root = _erase(root, k);
    }

};

