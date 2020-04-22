template <typename T, typename U>
struct RedBlackTree{

    struct Node;
    using Index = typename MemoryPool<Node>::Index;

    struct Node{
        int siz, level;
        T sum;
        U lazy;
        bool red;
        typename MemoryPool<Node>::Index l, r;
        Node(){}
        Node(T val, U lazy, bool red, bool leaf, int li = -1, int ri = -1) : sum(val), lazy(lazy), siz(leaf), level(0), red(red){
            l = {li};
            r = {ri};
        }
    };

    MemoryPool<Node> pool;
    Index nil;
    function<T(T, T)> f;
    function<T(T, U, int)> g;
    function<U(U, U)> h;
    T op_t;
    U op_u;
    RedBlackTree(function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t, U op_u) : f(f), g(g), h(h), op_t(op_t), op_u(op_u){
        nil = pool.alloc();
        pool[nil] = Node(op_t, op_u, false, false);
        pool[nil].l = pool[nil].r = nil;
    }

    Index build(vector<T>& a){
        nil = pool.alloc();
        pool[nil] = Node(op_t, op_u, false, false);
        pool[nil].l = pool[nil].r = nil;
        int siz = a.size();
        vector<Index> v(siz);
        for(int i = 0; i < siz; ++i)
            v[i] = make(a[i]);
        while(siz != 1){
            int nex_siz = (siz + 1) >> 1;
            vector<Index> nex(nex_siz);
            for(int i = 0; i < (siz >> 1); ++i)
                nex[i] = merge(v[2 * i], v[2 * i + 1]);
            if(siz & 1)
                nex.back() = v.back();
            siz = nex_siz;
            v = move(nex);
        }
        return v[0];
    }

    void clear(){
        while(!pool.st.empty())
            pool.st.pop();
        for(int i = 1; i <= pool.idx; ++i)
            pool.st.push(i);
    }


    Index index(int x){return {x};}

    T get_val(Index pi){
        auto& p = get(pi);
        return g(p.sum, p.lazy, p.siz);
    }

    T get_val(Index pi, int k){
        pi = access(pi, k);
        auto& p = get(pi);
        return g(p.sum, p.lazy, p.siz);
    }

    void eval(Index pi){
        if(pi == nil)
            return;
        auto& p = get(pi);
        if(p.lazy == op_u)
            return;
        if(p.l != nil){
            auto& l = get(p.l);
            l.lazy = h(l.lazy, p.lazy);
            auto& r = get(p.r);
            r.lazy = h(r.lazy, p.lazy);
        }
        p.sum = get_val(pi);
        p.lazy = op_u;
    }

    void update(Index pi){
        if(pi == nil)
            return;
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        p.siz = l.siz + r.siz;
        if(p.l != nil || p.r != nil)
            p.sum = f(get_val(p.l), get_val(p.r));
        p.level = l.level + !l.red;
        assert(p.level == r.level + !r.red);
    }

    Index make(T val){
        Index idx = pool.alloc();
        pool[idx] = Node(val, op_u, false, true, nil.idx, nil.idx);
        pool[idx].level = 1;
        return idx;
    }

    Index mergeSub(Index ai, Index bi){
        eval(ai);
        eval(bi);
        auto& a = get(ai);
        auto& b = get(bi);
        assert(ai != nil && bi != nil);
        if(a.level < b.level){
            Index ci = mergeSub(ai, b.l);
            auto& c = get(ci);
            if(!b.red && c.red && get(c.l).red){
                if(!get(b.r).red){
                    b.l = c.l;
                    c.l = c.r;
                    c.r = b.r;
                    b.r = ci;
                    update(ci);
                    update(bi);
                    return bi;
                }
                else{
                    b.l = ci;
                    b.red ^= 1;
                    get(b.l).red ^= 1;
                    get(b.r).red ^= 1;
                    update(bi);
                    return bi;
                }
            }
            b.l = ci;
            update(bi);
            return bi;
        }
        else if(a.level > b.level){
            Index ci = mergeSub(a.r, bi);
            auto& c = get(ci);
            if(!a.red && c.red && get(c.r).red){
                if(!get(a.l).red){
                    a.r = c.r;
                    c.r = c.l;
                    c.l = a.l;
                    a.l = ci;
                    update(ci);
                    update(ai);
                    return ai;
                }
                else{
                    a.r = ci;
                    a.red ^= 1;
                    get(a.l).red ^= 1;
                    get(a.r).red ^= 1;
                    update(ai);
                    return ai;
                }
            }
            a.r = ci;
            update(ai);
            return ai;
        }
        else{
            a.red = false;
            b.red = false;
            Index d = pool.alloc();
            get(d) = Node(op_t, op_u, true, false, ai.idx, bi.idx);
            update(d);
            return d;
        }
    }

    Index merge(Index ai, Index bi){
        if(ai == nil)
            return bi;
        if(bi == nil)
            return ai;
        Index ci = mergeSub(ai, bi);
        get(ci).red = false;
        return ci;
    }

    pair<Index, Index> split(Index ai, int k){
        if(ai == nil)
            return make_pair(nil, nil);
        eval(ai);
        auto& a = get(ai);
        if(k == 0)
            return make_pair(nil, ai);
        if(k == a.siz)
            return make_pair(ai, nil);
        Index li = a.l;
        Index ri = a.r;
        auto& l = get(li);
        pool.free(ai);
        if(k < l.siz){
            auto res = split(li, k);
            return make_pair(res.first, merge(res.second, ri));
        }
        else if(k > get(a.l).siz){
            auto res = split(ri, k - l.siz);
            return make_pair(merge(li, res.first), res.second);
        }
        else{
            return make_pair(li, ri);
        }
    }

    pair<T, Index> range_get(Index pi, int l, int r){
        auto res = split(pi, r);
        auto res2 = split(res.first, l);
        T val = get_val(res2.second);
        return make_pair(val, merge(merge(res2.first, res2.second), res.second));
    }

    Index range_update(Index pi, int l, int r, U val){
        if(l == r)
            return pi;
        auto res = split(pi, r);
        auto res2 = split(res.first, l);
        auto& mid = get(res2.second);
        mid.lazy = h(mid.lazy, val);
        eval(res2.second);
        return merge(merge(res2.first, res2.second), res.second);
    }

    Index insert(Index pi, int k, T val){
        auto res = split(pi, k);
        return merge(res.first, merge(make(val), res.second));
    }

    Index erase(Index pi, int k){
        auto res = split(pi, k + 1);
        auto res2 = split(res.first, k);
        pool.free(res2.second);
        return merge(res2.first, res.second);
    }

    Index access(Index pi, int k){
        while(get(pi).l != nil || get(pi).r != nil){
            eval(pi);
            auto& p = get(pi);
            assert(p.l != nil && p.r != nil);
            if(get(p.l).siz <= k){
                k -= get(p.l).siz;
                pi = p.r;
            }
            else{
                pi = p.l;
            }
        }
        return pi;
    }

    void set(Index pi, int k, T val, function<T(T, T)> af = [](T x, T y){return y;}){
        stack<Index> st;
        while(get(pi).l != nil || get(pi).r != nil){
            eval(pi);
            auto& p = get(pi);
            st.push(pi);
            assert(p.l != nil && p.r != nil);
            if(get(p.l).siz <= k){
                k -= get(p.l).siz;
                pi = p.r;
            }
            else{
                pi = p.l;
            }
        }
        auto& p = get(pi);
        eval(pi);
        p.sum = af(p.sum, val);
        while(!st.empty()){
            update(st.top());
            st.pop();
        }
    }

    Node& get(Index k){return pool[k];}
    Node& operator[](Index k){return pool[k];}
};

