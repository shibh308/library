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


# :warning: lib/classes/redblacktree_persistent_lazy.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/redblacktree_persistent_lazy.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-22 12:46:51+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// verify: https://atcoder.jp/contests/arc030/submissions/12211957/
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
        Node(T val, U lazy, bool red, bool leaf, Index l, Index r) : sum(val), lazy(lazy), siz(leaf), level(0), red(red), l(l), r(r){}
    };

    MemoryPool<Node> pool;
    Index nil;
    function<T(T, T)> f;
    function<U(T, U, int)> g;
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

    pair<T, Index> get_val(Index pi, int k){
        Index root;
        tie(pi, root) = access(pi, k);
        return make_pair(get_val(pi), root);
    }

    pair<Index, bool> eval(Index pi){
        if(pi == nil)
            return {pi, false};
        if(get(pi).lazy == op_u)
            return {pi, false};
        pi = clone(pi);
        auto& p = get(pi);
        if(p.l != nil){
            p.l = clone(p.l);
            p.r = clone(p.r);
            auto& l = get(p.l);
            l.lazy = h(l.lazy, p.lazy);
            auto& r = get(p.r);
            r.lazy = h(r.lazy, p.lazy);
        }
        p.sum = get_val(pi);
        p.lazy = op_u;
        return {pi, true};
    }

    Index make(T val){
        Index idx = pool.alloc();
        pool[idx] = Node(val, op_u, false, true, nil, nil);
        pool[idx].level = 1;
        return idx;
    }

    Index clone(Index pi){
        if(pi == nil)
            return pi;
        Index qi = pool.alloc();
        auto& p = get(pi);
        pool[qi] = Node(p.sum, p.lazy, p.red, false, p.l, p.r);
        pool[qi].siz = (p.l == nil ? 1 : pool[p.l].siz + pool[p.r].siz);
        pool[qi].level = pool[p.l].level + !pool[p.l].red;
        return qi;
    }

    Index makeInternal(Index l, Index r, bool red){
        Index idx = pool.alloc();
        pool[idx] = Node(op_t, op_u, red, false, l, r);
        pool[idx].sum = f(get_val(l), get_val(r));
        pool[idx].siz = pool[l].siz + pool[r].siz;
        pool[idx].level = pool[l].level + !pool[l].red;
        return idx;
    }

    Index mergeSub(Index ai, Index bi){
        ai = eval(ai).first;
        bi = eval(bi).first;
        auto& a = get(ai);
        auto& b = get(bi);
        assert(ai != nil && bi != nil);
        if(a.level < b.level){
            Index ci = mergeSub(ai, b.l);
            auto& c = get(ci);
            if(!b.red && c.red && get(c.l).red){
                if(!get(b.r).red)
                    return makeInternal(c.l, makeInternal(c.r, b.r, true), false);
                else{
                    b.r = eval(b.r).first;
                    return makeInternal(makeInternal(c.l, c.r, false), makeInternal(get(b.r).l, get(b.r).r, false), true);
                }
            }
            return makeInternal(ci, b.r, b.red);
        }
        else if(a.level > b.level){
            Index ci = mergeSub(a.r, bi);
            auto& c = get(ci);
            if(!a.red && c.red && get(c.r).red){
                if(!get(a.l).red)
                    return makeInternal(makeInternal(a.l, c.l, true), c.r, false);
                else{
                    a.l = eval(a.l).first;
                    return makeInternal(makeInternal(get(a.l).l, get(a.l).r, false), makeInternal(c.l, c.r, false), true);
                }
            }
            return makeInternal(a.l, ci, a.red);
        }
        else{
            if(a.red)
                ai = makeInternal(a.l, a.r, false);
            if(b.red)
                bi = makeInternal(b.l, b.r, false);
            return makeInternal(ai, bi, true);
        }
    }

    Index merge(Index ai, Index bi){
        if(ai == nil)
            return bi;
        if(bi == nil)
            return ai;
        Index ci = mergeSub(ai, bi);
        auto& c = get(ci);
        if(c.red){
            pool.free(ci);
            return makeInternal(c.l, c.r, false);
        }
        return ci;
    }

    pair<Index, Index> split(Index ai, int k){
        if(ai == nil)
            return make_pair(nil, nil);
        bool fl;
        tie(ai, fl) = eval(ai);
        auto& a = get(ai);
        if(k == 0)
            return make_pair(nil, ai);
        if(k == a.siz)
            return make_pair(ai, nil);
        Index li = a.l;
        Index ri = a.r;
        if(fl)
            pool.free(ai);
        auto& l = get(li);
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
        Index mi = clone(res2.second);
        auto& mid = get(mi);
        mid.lazy = h(mid.lazy, val);
        Index nex_mi;
        bool fl;
        tie(nex_mi, fl) = eval(mi);
        if(fl)
            pool.free(mi);

        return merge(merge(res2.first, nex_mi), res.second);
    }

    Index insert(Index pi, int k, T val){
        auto res = split(pi, k);
        return merge(res.first, merge(make(val), res.second));
    }

    Index erase(Index pi, int k){
        auto res = split(pi, k + 1);
        auto res2 = split(res.first, k);
        return merge(res2.first, res.second);
    }

    pair<Index, Index> access(Index pi, int k){
        auto res = split(pi, k + 1);
        auto res2 = split(res.first, k);
        return make_pair(res2.second, merge(merge(res2.first, res2.second), res.second));
    }

    Index set(Index pi, int k, T val, function<T(T, T)> af = [](T x, T y){return y;}){
        auto res = split(pi, k + 1);
        auto res2 = split(res.first, k);
        Index qi = eval(res2.second);
        get(qi).sum = af(get_val(qi), val);
        return make_pair(qi, merge(merge(res2.first, qi), res.second));
    }

    void dump(Index pi, vector<T>& v){
        Index qi = eval(pi).first;
        auto& q = get(qi);
        if(q.l != nil){
            dump(q.l, v);
            dump(q.r, v);
        }
        else
            v.emplace_back(get_val(pi));
    }

    vector<T> dump(Index pi){
        vector<T> v;
        dump(pi, v);
        return v;
    }

    Index rebuild(Index pi){
        auto v = dump(pi);
        clear();
        return build(v);
    }

    Node& get(Index k){return pool[k];}
    Node& operator[](Index k){return pool[k];}
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/redblacktree_persistent_lazy.cpp"
// verify: https://atcoder.jp/contests/arc030/submissions/12211957/
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
        Node(T val, U lazy, bool red, bool leaf, Index l, Index r) : sum(val), lazy(lazy), siz(leaf), level(0), red(red), l(l), r(r){}
    };

    MemoryPool<Node> pool;
    Index nil;
    function<T(T, T)> f;
    function<U(T, U, int)> g;
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

    pair<T, Index> get_val(Index pi, int k){
        Index root;
        tie(pi, root) = access(pi, k);
        return make_pair(get_val(pi), root);
    }

    pair<Index, bool> eval(Index pi){
        if(pi == nil)
            return {pi, false};
        if(get(pi).lazy == op_u)
            return {pi, false};
        pi = clone(pi);
        auto& p = get(pi);
        if(p.l != nil){
            p.l = clone(p.l);
            p.r = clone(p.r);
            auto& l = get(p.l);
            l.lazy = h(l.lazy, p.lazy);
            auto& r = get(p.r);
            r.lazy = h(r.lazy, p.lazy);
        }
        p.sum = get_val(pi);
        p.lazy = op_u;
        return {pi, true};
    }

    Index make(T val){
        Index idx = pool.alloc();
        pool[idx] = Node(val, op_u, false, true, nil, nil);
        pool[idx].level = 1;
        return idx;
    }

    Index clone(Index pi){
        if(pi == nil)
            return pi;
        Index qi = pool.alloc();
        auto& p = get(pi);
        pool[qi] = Node(p.sum, p.lazy, p.red, false, p.l, p.r);
        pool[qi].siz = (p.l == nil ? 1 : pool[p.l].siz + pool[p.r].siz);
        pool[qi].level = pool[p.l].level + !pool[p.l].red;
        return qi;
    }

    Index makeInternal(Index l, Index r, bool red){
        Index idx = pool.alloc();
        pool[idx] = Node(op_t, op_u, red, false, l, r);
        pool[idx].sum = f(get_val(l), get_val(r));
        pool[idx].siz = pool[l].siz + pool[r].siz;
        pool[idx].level = pool[l].level + !pool[l].red;
        return idx;
    }

    Index mergeSub(Index ai, Index bi){
        ai = eval(ai).first;
        bi = eval(bi).first;
        auto& a = get(ai);
        auto& b = get(bi);
        assert(ai != nil && bi != nil);
        if(a.level < b.level){
            Index ci = mergeSub(ai, b.l);
            auto& c = get(ci);
            if(!b.red && c.red && get(c.l).red){
                if(!get(b.r).red)
                    return makeInternal(c.l, makeInternal(c.r, b.r, true), false);
                else{
                    b.r = eval(b.r).first;
                    return makeInternal(makeInternal(c.l, c.r, false), makeInternal(get(b.r).l, get(b.r).r, false), true);
                }
            }
            return makeInternal(ci, b.r, b.red);
        }
        else if(a.level > b.level){
            Index ci = mergeSub(a.r, bi);
            auto& c = get(ci);
            if(!a.red && c.red && get(c.r).red){
                if(!get(a.l).red)
                    return makeInternal(makeInternal(a.l, c.l, true), c.r, false);
                else{
                    a.l = eval(a.l).first;
                    return makeInternal(makeInternal(get(a.l).l, get(a.l).r, false), makeInternal(c.l, c.r, false), true);
                }
            }
            return makeInternal(a.l, ci, a.red);
        }
        else{
            if(a.red)
                ai = makeInternal(a.l, a.r, false);
            if(b.red)
                bi = makeInternal(b.l, b.r, false);
            return makeInternal(ai, bi, true);
        }
    }

    Index merge(Index ai, Index bi){
        if(ai == nil)
            return bi;
        if(bi == nil)
            return ai;
        Index ci = mergeSub(ai, bi);
        auto& c = get(ci);
        if(c.red){
            pool.free(ci);
            return makeInternal(c.l, c.r, false);
        }
        return ci;
    }

    pair<Index, Index> split(Index ai, int k){
        if(ai == nil)
            return make_pair(nil, nil);
        bool fl;
        tie(ai, fl) = eval(ai);
        auto& a = get(ai);
        if(k == 0)
            return make_pair(nil, ai);
        if(k == a.siz)
            return make_pair(ai, nil);
        Index li = a.l;
        Index ri = a.r;
        if(fl)
            pool.free(ai);
        auto& l = get(li);
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
        Index mi = clone(res2.second);
        auto& mid = get(mi);
        mid.lazy = h(mid.lazy, val);
        Index nex_mi;
        bool fl;
        tie(nex_mi, fl) = eval(mi);
        if(fl)
            pool.free(mi);

        return merge(merge(res2.first, nex_mi), res.second);
    }

    Index insert(Index pi, int k, T val){
        auto res = split(pi, k);
        return merge(res.first, merge(make(val), res.second));
    }

    Index erase(Index pi, int k){
        auto res = split(pi, k + 1);
        auto res2 = split(res.first, k);
        return merge(res2.first, res.second);
    }

    pair<Index, Index> access(Index pi, int k){
        auto res = split(pi, k + 1);
        auto res2 = split(res.first, k);
        return make_pair(res2.second, merge(merge(res2.first, res2.second), res.second));
    }

    Index set(Index pi, int k, T val, function<T(T, T)> af = [](T x, T y){return y;}){
        auto res = split(pi, k + 1);
        auto res2 = split(res.first, k);
        Index qi = eval(res2.second);
        get(qi).sum = af(get_val(qi), val);
        return make_pair(qi, merge(merge(res2.first, qi), res.second));
    }

    void dump(Index pi, vector<T>& v){
        Index qi = eval(pi).first;
        auto& q = get(qi);
        if(q.l != nil){
            dump(q.l, v);
            dump(q.r, v);
        }
        else
            v.emplace_back(get_val(pi));
    }

    vector<T> dump(Index pi){
        vector<T> v;
        dump(pi, v);
        return v;
    }

    Index rebuild(Index pi){
        auto v = dump(pi);
        clear();
        return build(v);
    }

    Node& get(Index k){return pool[k];}
    Node& operator[](Index k){return pool[k];}
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

