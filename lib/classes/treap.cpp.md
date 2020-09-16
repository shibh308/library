---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links: []
  bundledCode: "#line 1 \"lib/classes/treap.cpp\"\ntemplate <typename T, typename\
    \ U = int>\nstruct Node{\n\n    using np = Node<T, U>*;\n\n    static np nil;\n\
    \n    T val;\n    U lazy;\n    uint32_t pri;\n\n    int size;\n    T sum;\n\n\
    \    np l = nil;\n    np r = nil;\n\n    Node(T v, U OU = U()) : val(v), lazy(OU),\
    \ pri(rndpri()), size(1), sum(v), l(nil), r(nil){}\n    Node(T v, U OU, uint32_t\
    \ p) : val(v), lazy(OU), pri(p), size(1), sum(v), l(nil), r(nil){}\n\n    static\
    \ uint32_t rndpri() {\n        static uint32_t x = 123456789, y = 362436069, z\
    \ = 521288629, w = time(0);\n        uint32_t t = x ^ (x << 11);\n        x =\
    \ y;\n        y = z;\n        z = w;\n        w = (w ^ (w >> 19)) ^ (t ^ (t >>\
    \ 8));\n        return max<uint32_t>(1, w & 0x3FFFFFFF);\n    }\n};\n\n\ntemplate\
    \ <typename T, typename U = int>\nclass Treap{\n\n    using nt = Node<T, U>;\n\
    \    using np = nt*;\n    using F = function<T(T, T)>;\n    using G = function<T(T,\
    \ U, int)>;\n    using H = function<U(U, U)>;\n\npublic:\n\n    np root;\n   \
    \ bool is_list;\n    F f;\n    G g;\n    H h;\n    T OT;\n    U OU;\n\n    Treap(bool\
    \ is_list, F f, G g, H h, T OT, U OU) : root(nt::nil), is_list(is_list), f(f),\
    \ g(g), h(h), OT(OT), OU(OU){}\n\n    Treap(T val, bool is_list, F f, G g, H h,\
    \ T OT, U OU) : root(new nt(val)), is_list(is_list), f(f), g(g), h(h), OT(OT),\
    \ OU(OU){}\n\n    // \u914D\u5217\u3067\u521D\u671F\u5316\u3059\u308B\n    Treap(vector<T>\
    \ v, bool is_list, F f, G g, H h, T OT, U OU) : root(nt::nil), is_list(is_list),\
    \ f(f), g(g), h(h), OT(OT), OU(OU){\n        for(auto& xx : v)\n            root\
    \ = _merge(root, new nt(xx, OU));\n    }\n\n    static Treap make(bool is_list,\
    \ F f = [](T x, T){return x;}, T OT = T(), G g = [](auto x, auto, auto){return\
    \ x;}, H h = [](auto x, auto){return x;}, U OU = U()){\n        assert(nt::nil\
    \ != nullptr);\n        return Treap(is_list, f, g, h, OT, OU);\n    }\n\n   \
    \ static Treap make(T val, bool is_list, F f = [](auto x, auto){return x;}, T\
    \ OT = T(), G g = [](auto x, auto, auto){return x;}, H h = [](auto x, auto){return\
    \ x;}, U OU = U()){\n        assert(nt::nil != nullptr);\n        return Treap(val,\
    \ is_list, f, g, h, OT, OU);\n    }\n\n    static Treap make(vector<T> val, bool\
    \ is_list, F f = [](auto x, auto){return x;}, T OT = T(), G g = [](auto x, auto,\
    \ auto){return x;}, H h = [](auto x, auto){return x;}, U OU = U()){\n        assert(nt::nil\
    \ != nullptr);\n        return Treap(val, is_list, f, g, h, OT, OU);\n    }\n\n\
    \    ~Treap(){\n        clear();\n        if(root != nt::nil)\n            delete\
    \ root;\n    }\n\n    int _size(np x){return x == nt::nil ? 0 : x->size;}\n  \
    \  T _sum(np x){return x == nt::nil ? OT : x->sum;}\n\n    np _update(np x){\n\
    \n        if(x == nt::nil)\n            return x;\n\n        if(is_list){\n  \
    \          _push(x);\n            _push(x->l);\n            _push(x->r);\n   \
    \     }\n\n\t\tx->sum = f(f(_sum(x->l), x->val), _sum(x->r));\n\t\tx->size = _size(x->l)\
    \ + _size(x->r) + 1;\n        return x;\n    }\n\n    void _push(np x){\n    \
    \    if(x->lazy == OU)\n            return ;\n\n        x->sum = g(x->sum, x->lazy,\
    \ x->size);\n        x->val = g(x->val, x->lazy, 1);\n\n        if(x->l != nt::nil)\n\
    \            x->l->lazy = h(x->l->lazy, x->lazy);\n        if(x->r != nt::nil)\n\
    \            x->r->lazy = h(x->r->lazy, x->lazy);\n\n        x->lazy = OU;\n\n\
    \    }\n\n    np _merge(np l, np r){\n        if(l == nt::nil || r ==nt::nil)\n\
    \            return l == nt::nil ? r : l;\n\n        if(l->pri > r->pri){\n  \
    \          l->r = _merge(l->r, r);\n            return _update(l);\n        }else{\n\
    \            r->l = _merge(l, r->l);\n            return _update(r);\n       \
    \ }\n    }\n\n    pair<np,np> _split(np x, int k){\n        if(x == nt::nil)\n\
    \            return make_pair(nt::nil, nt::nil);\n\n        assert(0 <= k && k\
    \ <= _size(x));\n\n        if(k <= _size(x->l)){\n            pair<np, np> s =\
    \ _split(x->l, k);\n            x->l = s.second;\n            return make_pair(s.first,\
    \ _update(x));\n\n        }else{\n            pair<np, np> s = _split(x->r, k\
    \ - _size(x->l) - 1);\n            x->r = s.first;\n            return make_pair(_update(x),\
    \ s.second);\n        }\n    }\n\n    np _insert(np x, int k, T val){\n      \
    \  np l, r;\n        tie(l, r) = _split(x, k);\n        return _merge(_merge(l,\
    \ new nt(val, OU)), r);\n    }\n\n    np _erase(np x, int k){\n        np l, r,\
    \ m;\n        tie(l, r) = _split(x, k);\n        tie(m, r) = _split(r, 1);\n \
    \       if(m != nt::nil)\n            delete m;\n        return _merge(l, r);\n\
    \    }\n\n    void _set(np x, int k, T val){\n        _update(x);\n\n        if(k\
    \ < _size(x->l))\n            _set(x->l, k, val);\n        else if(_size(x->l)\
    \ == k)\n            x->val = val;\n        else\n            _set(x->r, k - _size(x->l)\
    \ - 1, val);\n\n        _update(x);\n    }\n\n    void _add(np x, int l, int r,\
    \ U val){\n        assert(is_list);\n        _update(x);\n\n        if(x == nt::nil)\n\
    \            return ;\n        l = max(l, 0);\n        r = min(r, _size(x));\n\
    \n        int sl = _size(x->l);\n\n        if(l >= r)\n            return ;\n\n\
    \        if (l == 0 && r == _size(x)){\n            x->lazy = h(x->lazy, val);\n\
    \        }\n        else{\n            if(l <= sl && sl < r)\n               \
    \ x->val = g(x->val, val, 1);\n\n            _add(x->l, l, r, val);\n        \
    \    _add(x->r, l - sl - 1, r - sl - 1, val);\n        }\n\n        _update(x);\n\
    \    }\n\n    np _getnode(np x, int k){\n\n        _update(x);\n\n        assert(0\
    \ <= k && k < _size(x));\n\n        if(k < _size(x->l))\n            return _getnode(x->l,\
    \ k);\n        else if(_size(x->l) == k)\n            return x;\n        else\n\
    \            return _getnode(x->r, k - _size(x->l) - 1);\n    }\n\n    T _get(np\
    \ x, int k){\n        return _getnode(x, k)->val;\n    }\n\n    T _rangesum(np\
    \ x, int l, int r){\n        _update(x);\n\n        l = max(l, 0);\n        r\
    \ = min(r, _size(x));\n        if(l >= r)\n            return OT;\n        if(l\
    \ == 0 && r == _size(x))\n            return _sum(x);\n\n        int sl = _size(x->l);\n\
    \        T ret = (l <= sl && sl < r ? x->val : OT);\n        ret = f(_rangesum(x->l,\
    \ l, r), ret);\n        ret = f(ret, _rangesum(x->r, l - sl - 1, r - sl - 1));\n\
    \        return ret;\n    }\n\n    int _lowerbound(np x, T val){\n        _update(x);\n\
    \n        if(x == nt::nil)\n            return 0;\n        if(val <= x->val)\n\
    \            return _lowerbound(x->l, val);\n        else\n            return\
    \ _lowerbound(x->r,val) + _size(x->l) + 1;\n    }\n\n    int _upperbound(np x,\
    \ T val){\n        _update(x);\n\n        if(x == nt::nil)\n            return\
    \ 0;\n        if(val < x->val)\n            return _upperbound(x->l, val);\n \
    \       else\n            return _upperbound(x->r,val) + _size(x->l) + 1;\n  \
    \  }\n\n    np _insert(np x, T val){\n        return _insert(x, _lowerbound(x,\
    \ val), val);\n    }\n\n    void _clear(np x){\n        if(x->l != nt::nil){\n\
    \            _clear(x->l);\n            delete(x->l);\n            x->l = nt::nil;\n\
    \        }\n        if(x->r != nt::nil){\n            _clear(x->r);\n        \
    \    delete(x->r);\n            x->r = nt::nil;\n        }\n    }\n\n    void\
    \ push_front(T val){\n        root = _merge(new nt(val, OU), root);\n    }\n\n\
    \    void push_back(T val){\n        root = _merge(root, new nt(val, OU));\n \
    \   }\n\n    void pop_front(){\n        root = _split(root, 1).second;\n    }\n\
    \n    void pop_back(){\n        root = _split(root, _size(root) - 1).first;\n\
    \    }\n\n    // [0, k)\u3068[k, size)\u306B\u5206\u5272\u3057\u3066, [k, size)\u5074\
    \u3092\u8FD4\u3059\n    Treap split_left(int k){\n        np p;\n        tie(root,\
    \ p) = _split(root, k);\n        return decltype(this)(f, g, h, p);\n    }\n\n\
    \    // [0, k)\u3068[k, size)\u306B\u5206\u5272\u3057\u3066, [0, k)\u5074\u3092\
    \u8FD4\u3059\n    Treap split_right(int k){\n        np p;\n        tie(p, root)\
    \ = _split(root, k);\n        return decltype(this)(f, g, h, p);\n    }\n\n  \
    \  // root\u3092\u542B\u3081\u305F\u30B5\u30A4\u30BA\u306E\u51FA\u529B\n    int\
    \ size(){\n        return (root == nt::nil ? 0 : root->size);\n    }\n\n    //\
    \ k\u756A\u76EE\u3078\u306E\u4EE3\u5165\n    void set(int k, T val){\n       \
    \ return _set(root, k, val);\n    }\n\n    // k\u756A\u76EE\u3078\u306E\u52A0\u7B97\
    \n    void add(int k, U val){\n        assert(is_list);\n        return _add(root,\
    \ k, k + 1, val);\n    }\n\n    // [l, r)\u3078\u306E\u4E00\u69D8\u52A0\u7B97\n\
    \    void add(int l, int r, U val){\n        assert(is_list);\n        return\
    \ _add(root, l, r, val);\n    }\n\n    // k\u756A\u76EE\u306E\u53D6\u5F97\n  \
    \  T get(int k){\n        return _get(root, k);\n    }\n\n    // [l, r)\u306E\u7DCF\
    \u548C (\u540C\u69D8\u306E\u5B9F\u88C5\u3067RMQ\u7B49\u3082\u53EF\u80FD)\n   \
    \ T get(int l, int r){\n        return _rangesum(root, l, r);\n    }\n\n    //\
    \ k\u756A\u76EE\u3078\u306E\u633F\u5165\n    void insert(int k, T val){\n    \
    \    assert(is_list);\n        root = _insert(root, k, val);\n    }\n\n    //\
    \ \u9069\u5207\u306A\u4F4D\u7F6E\u3078\u306E\u633F\u5165\n    void insert(T val){\n\
    \        root = _insert(root, val);\n    }\n\n    // val <= get(k) \u3068\u306A\
    \u308B\u3088\u3046\u306A\u6700\u5C0F\u306Ek\n    int lowerbound(T val){\n    \
    \    return _lowerbound(root, val);\n    }\n\n    // val < get(k) \u3068\u306A\
    \u308B\u3088\u3046\u306A\u6700\u5C0F\u306Ek\n    int upperbound(T val){\n    \
    \    return _upperbound(root, val);\n    }\n\n    // k\u756A\u76EE\u306E\u8981\
    \u7D20\u524A\u9664\n    void erase(int k){\n        root = _erase(root, k);\n\
    \    }\n\n    void clear(){\n        if(root != nt::nil){\n            _clear(root);\n\
    \            delete(root);\n            root = nt::nil;\n        }\n    }\n};\n\
    \nconst i64 val = 0;\nconst i64 op = -1e9;\nusing node_type = Node<i64, i64>;\n\
    template<> node_type* node_type::nil = new node_type(0, op, 0);\n"
  code: "template <typename T, typename U = int>\nstruct Node{\n\n    using np = Node<T,\
    \ U>*;\n\n    static np nil;\n\n    T val;\n    U lazy;\n    uint32_t pri;\n\n\
    \    int size;\n    T sum;\n\n    np l = nil;\n    np r = nil;\n\n    Node(T v,\
    \ U OU = U()) : val(v), lazy(OU), pri(rndpri()), size(1), sum(v), l(nil), r(nil){}\n\
    \    Node(T v, U OU, uint32_t p) : val(v), lazy(OU), pri(p), size(1), sum(v),\
    \ l(nil), r(nil){}\n\n    static uint32_t rndpri() {\n        static uint32_t\
    \ x = 123456789, y = 362436069, z = 521288629, w = time(0);\n        uint32_t\
    \ t = x ^ (x << 11);\n        x = y;\n        y = z;\n        z = w;\n       \
    \ w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));\n        return max<uint32_t>(1, w & 0x3FFFFFFF);\n\
    \    }\n};\n\n\ntemplate <typename T, typename U = int>\nclass Treap{\n\n    using\
    \ nt = Node<T, U>;\n    using np = nt*;\n    using F = function<T(T, T)>;\n  \
    \  using G = function<T(T, U, int)>;\n    using H = function<U(U, U)>;\n\npublic:\n\
    \n    np root;\n    bool is_list;\n    F f;\n    G g;\n    H h;\n    T OT;\n \
    \   U OU;\n\n    Treap(bool is_list, F f, G g, H h, T OT, U OU) : root(nt::nil),\
    \ is_list(is_list), f(f), g(g), h(h), OT(OT), OU(OU){}\n\n    Treap(T val, bool\
    \ is_list, F f, G g, H h, T OT, U OU) : root(new nt(val)), is_list(is_list), f(f),\
    \ g(g), h(h), OT(OT), OU(OU){}\n\n    // \u914D\u5217\u3067\u521D\u671F\u5316\u3059\
    \u308B\n    Treap(vector<T> v, bool is_list, F f, G g, H h, T OT, U OU) : root(nt::nil),\
    \ is_list(is_list), f(f), g(g), h(h), OT(OT), OU(OU){\n        for(auto& xx :\
    \ v)\n            root = _merge(root, new nt(xx, OU));\n    }\n\n    static Treap\
    \ make(bool is_list, F f = [](T x, T){return x;}, T OT = T(), G g = [](auto x,\
    \ auto, auto){return x;}, H h = [](auto x, auto){return x;}, U OU = U()){\n  \
    \      assert(nt::nil != nullptr);\n        return Treap(is_list, f, g, h, OT,\
    \ OU);\n    }\n\n    static Treap make(T val, bool is_list, F f = [](auto x, auto){return\
    \ x;}, T OT = T(), G g = [](auto x, auto, auto){return x;}, H h = [](auto x, auto){return\
    \ x;}, U OU = U()){\n        assert(nt::nil != nullptr);\n        return Treap(val,\
    \ is_list, f, g, h, OT, OU);\n    }\n\n    static Treap make(vector<T> val, bool\
    \ is_list, F f = [](auto x, auto){return x;}, T OT = T(), G g = [](auto x, auto,\
    \ auto){return x;}, H h = [](auto x, auto){return x;}, U OU = U()){\n        assert(nt::nil\
    \ != nullptr);\n        return Treap(val, is_list, f, g, h, OT, OU);\n    }\n\n\
    \    ~Treap(){\n        clear();\n        if(root != nt::nil)\n            delete\
    \ root;\n    }\n\n    int _size(np x){return x == nt::nil ? 0 : x->size;}\n  \
    \  T _sum(np x){return x == nt::nil ? OT : x->sum;}\n\n    np _update(np x){\n\
    \n        if(x == nt::nil)\n            return x;\n\n        if(is_list){\n  \
    \          _push(x);\n            _push(x->l);\n            _push(x->r);\n   \
    \     }\n\n\t\tx->sum = f(f(_sum(x->l), x->val), _sum(x->r));\n\t\tx->size = _size(x->l)\
    \ + _size(x->r) + 1;\n        return x;\n    }\n\n    void _push(np x){\n    \
    \    if(x->lazy == OU)\n            return ;\n\n        x->sum = g(x->sum, x->lazy,\
    \ x->size);\n        x->val = g(x->val, x->lazy, 1);\n\n        if(x->l != nt::nil)\n\
    \            x->l->lazy = h(x->l->lazy, x->lazy);\n        if(x->r != nt::nil)\n\
    \            x->r->lazy = h(x->r->lazy, x->lazy);\n\n        x->lazy = OU;\n\n\
    \    }\n\n    np _merge(np l, np r){\n        if(l == nt::nil || r ==nt::nil)\n\
    \            return l == nt::nil ? r : l;\n\n        if(l->pri > r->pri){\n  \
    \          l->r = _merge(l->r, r);\n            return _update(l);\n        }else{\n\
    \            r->l = _merge(l, r->l);\n            return _update(r);\n       \
    \ }\n    }\n\n    pair<np,np> _split(np x, int k){\n        if(x == nt::nil)\n\
    \            return make_pair(nt::nil, nt::nil);\n\n        assert(0 <= k && k\
    \ <= _size(x));\n\n        if(k <= _size(x->l)){\n            pair<np, np> s =\
    \ _split(x->l, k);\n            x->l = s.second;\n            return make_pair(s.first,\
    \ _update(x));\n\n        }else{\n            pair<np, np> s = _split(x->r, k\
    \ - _size(x->l) - 1);\n            x->r = s.first;\n            return make_pair(_update(x),\
    \ s.second);\n        }\n    }\n\n    np _insert(np x, int k, T val){\n      \
    \  np l, r;\n        tie(l, r) = _split(x, k);\n        return _merge(_merge(l,\
    \ new nt(val, OU)), r);\n    }\n\n    np _erase(np x, int k){\n        np l, r,\
    \ m;\n        tie(l, r) = _split(x, k);\n        tie(m, r) = _split(r, 1);\n \
    \       if(m != nt::nil)\n            delete m;\n        return _merge(l, r);\n\
    \    }\n\n    void _set(np x, int k, T val){\n        _update(x);\n\n        if(k\
    \ < _size(x->l))\n            _set(x->l, k, val);\n        else if(_size(x->l)\
    \ == k)\n            x->val = val;\n        else\n            _set(x->r, k - _size(x->l)\
    \ - 1, val);\n\n        _update(x);\n    }\n\n    void _add(np x, int l, int r,\
    \ U val){\n        assert(is_list);\n        _update(x);\n\n        if(x == nt::nil)\n\
    \            return ;\n        l = max(l, 0);\n        r = min(r, _size(x));\n\
    \n        int sl = _size(x->l);\n\n        if(l >= r)\n            return ;\n\n\
    \        if (l == 0 && r == _size(x)){\n            x->lazy = h(x->lazy, val);\n\
    \        }\n        else{\n            if(l <= sl && sl < r)\n               \
    \ x->val = g(x->val, val, 1);\n\n            _add(x->l, l, r, val);\n        \
    \    _add(x->r, l - sl - 1, r - sl - 1, val);\n        }\n\n        _update(x);\n\
    \    }\n\n    np _getnode(np x, int k){\n\n        _update(x);\n\n        assert(0\
    \ <= k && k < _size(x));\n\n        if(k < _size(x->l))\n            return _getnode(x->l,\
    \ k);\n        else if(_size(x->l) == k)\n            return x;\n        else\n\
    \            return _getnode(x->r, k - _size(x->l) - 1);\n    }\n\n    T _get(np\
    \ x, int k){\n        return _getnode(x, k)->val;\n    }\n\n    T _rangesum(np\
    \ x, int l, int r){\n        _update(x);\n\n        l = max(l, 0);\n        r\
    \ = min(r, _size(x));\n        if(l >= r)\n            return OT;\n        if(l\
    \ == 0 && r == _size(x))\n            return _sum(x);\n\n        int sl = _size(x->l);\n\
    \        T ret = (l <= sl && sl < r ? x->val : OT);\n        ret = f(_rangesum(x->l,\
    \ l, r), ret);\n        ret = f(ret, _rangesum(x->r, l - sl - 1, r - sl - 1));\n\
    \        return ret;\n    }\n\n    int _lowerbound(np x, T val){\n        _update(x);\n\
    \n        if(x == nt::nil)\n            return 0;\n        if(val <= x->val)\n\
    \            return _lowerbound(x->l, val);\n        else\n            return\
    \ _lowerbound(x->r,val) + _size(x->l) + 1;\n    }\n\n    int _upperbound(np x,\
    \ T val){\n        _update(x);\n\n        if(x == nt::nil)\n            return\
    \ 0;\n        if(val < x->val)\n            return _upperbound(x->l, val);\n \
    \       else\n            return _upperbound(x->r,val) + _size(x->l) + 1;\n  \
    \  }\n\n    np _insert(np x, T val){\n        return _insert(x, _lowerbound(x,\
    \ val), val);\n    }\n\n    void _clear(np x){\n        if(x->l != nt::nil){\n\
    \            _clear(x->l);\n            delete(x->l);\n            x->l = nt::nil;\n\
    \        }\n        if(x->r != nt::nil){\n            _clear(x->r);\n        \
    \    delete(x->r);\n            x->r = nt::nil;\n        }\n    }\n\n    void\
    \ push_front(T val){\n        root = _merge(new nt(val, OU), root);\n    }\n\n\
    \    void push_back(T val){\n        root = _merge(root, new nt(val, OU));\n \
    \   }\n\n    void pop_front(){\n        root = _split(root, 1).second;\n    }\n\
    \n    void pop_back(){\n        root = _split(root, _size(root) - 1).first;\n\
    \    }\n\n    // [0, k)\u3068[k, size)\u306B\u5206\u5272\u3057\u3066, [k, size)\u5074\
    \u3092\u8FD4\u3059\n    Treap split_left(int k){\n        np p;\n        tie(root,\
    \ p) = _split(root, k);\n        return decltype(this)(f, g, h, p);\n    }\n\n\
    \    // [0, k)\u3068[k, size)\u306B\u5206\u5272\u3057\u3066, [0, k)\u5074\u3092\
    \u8FD4\u3059\n    Treap split_right(int k){\n        np p;\n        tie(p, root)\
    \ = _split(root, k);\n        return decltype(this)(f, g, h, p);\n    }\n\n  \
    \  // root\u3092\u542B\u3081\u305F\u30B5\u30A4\u30BA\u306E\u51FA\u529B\n    int\
    \ size(){\n        return (root == nt::nil ? 0 : root->size);\n    }\n\n    //\
    \ k\u756A\u76EE\u3078\u306E\u4EE3\u5165\n    void set(int k, T val){\n       \
    \ return _set(root, k, val);\n    }\n\n    // k\u756A\u76EE\u3078\u306E\u52A0\u7B97\
    \n    void add(int k, U val){\n        assert(is_list);\n        return _add(root,\
    \ k, k + 1, val);\n    }\n\n    // [l, r)\u3078\u306E\u4E00\u69D8\u52A0\u7B97\n\
    \    void add(int l, int r, U val){\n        assert(is_list);\n        return\
    \ _add(root, l, r, val);\n    }\n\n    // k\u756A\u76EE\u306E\u53D6\u5F97\n  \
    \  T get(int k){\n        return _get(root, k);\n    }\n\n    // [l, r)\u306E\u7DCF\
    \u548C (\u540C\u69D8\u306E\u5B9F\u88C5\u3067RMQ\u7B49\u3082\u53EF\u80FD)\n   \
    \ T get(int l, int r){\n        return _rangesum(root, l, r);\n    }\n\n    //\
    \ k\u756A\u76EE\u3078\u306E\u633F\u5165\n    void insert(int k, T val){\n    \
    \    assert(is_list);\n        root = _insert(root, k, val);\n    }\n\n    //\
    \ \u9069\u5207\u306A\u4F4D\u7F6E\u3078\u306E\u633F\u5165\n    void insert(T val){\n\
    \        root = _insert(root, val);\n    }\n\n    // val <= get(k) \u3068\u306A\
    \u308B\u3088\u3046\u306A\u6700\u5C0F\u306Ek\n    int lowerbound(T val){\n    \
    \    return _lowerbound(root, val);\n    }\n\n    // val < get(k) \u3068\u306A\
    \u308B\u3088\u3046\u306A\u6700\u5C0F\u306Ek\n    int upperbound(T val){\n    \
    \    return _upperbound(root, val);\n    }\n\n    // k\u756A\u76EE\u306E\u8981\
    \u7D20\u524A\u9664\n    void erase(int k){\n        root = _erase(root, k);\n\
    \    }\n\n    void clear(){\n        if(root != nt::nil){\n            _clear(root);\n\
    \            delete(root);\n            root = nt::nil;\n        }\n    }\n};\n\
    \nconst i64 val = 0;\nconst i64 op = -1e9;\nusing node_type = Node<i64, i64>;\n\
    template<> node_type* node_type::nil = new node_type(0, op, 0);\n"
  dependsOn: []
  isVerificationFile: false
  path: lib/classes/treap.cpp
  requiredBy: []
  timestamp: '2020-05-31 22:27:15+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: lib/classes/treap.cpp
layout: document
redirect_from:
- /library/lib/classes/treap.cpp
- /library/lib/classes/treap.cpp.html
title: lib/classes/treap.cpp
---
