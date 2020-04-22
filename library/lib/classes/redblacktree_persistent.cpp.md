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


# :warning: lib/classes/redblacktree_persistent.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/redblacktree_persistent.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-22 12:46:51+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// verify: https://atcoder.jp/contests/joisc2012/submissions/12202620/
template <typename T>
struct RedBlackTree{

    struct Node;
    using Index = typename MemoryPool<Node>::Index;

    struct Node{
        int siz, level;
        T sum;
        bool red;
        typename MemoryPool<Node>::Index l, r;
        Node(){}
        Node(T val, bool red, bool leaf, int li = -1, int ri = -1) : sum(val), siz(leaf), level(0), red(red){
            l = {li};
            r = {ri};
        }
        Node(T val, bool red, bool leaf, Index l, Index r) : sum(val), siz(leaf), level(0), red(red), l(l), r(r){}
    };

    MemoryPool<Node> pool;
    Index nil;
    function<T(T, T)> f;
    T op;
    RedBlackTree(function<T(T, T)> f = [](auto x, auto y){return x + y;}, T op = T()) : f(f), op(op){
        nil = pool.alloc();
        pool[nil] = Node(op, false, false);
        pool[nil].l = pool[nil].r = nil;
    }

    Index build(vector<T>& a){
        nil = pool.alloc();
        pool[nil] = Node(op, false, false);
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

    T get_val(Index pi, int k){
        pi = access(pi, k);
        return get(pi).sum;
    }

    Index make(T val){
        Index idx = pool.alloc();
        pool[idx] = Node(val, false, true, nil.idx, nil.idx);
        pool[idx].level = 1;
        return idx;
    }

    Index makeInternal(Index l, Index r, bool red){
        auto idx = pool.alloc();
        pool[idx] = Node(op, red, false, l, r);
        pool[idx].sum = f(pool[l].sum, pool[r].sum);
        pool[idx].siz = pool[l].siz + pool[r].siz;
        pool[idx].level = pool[l].level + !pool[l].red;
        return idx;
    }

    Index makeLeaf(T val, bool red){
        auto idx = pool.alloc();
        pool[idx] = Node(val, red, true);
        pool[idx].l = pool[idx].r = nil;
        pool[idx].level = 1;
        return idx;
    }

    Index mergeSub(Index ai, Index bi){
        auto& a = get(ai);
        auto& b = get(bi);
        assert(ai != nil && bi != nil);
        if(a.level < b.level){
            Index ci = mergeSub(ai, b.l);
            auto& c = get(ci);
            if(!b.red && c.red && get(c.l).red){
                if(!get(b.r).red)
                    return makeInternal(c.l, makeInternal(c.r, b.r, true), false);
                else
                    return makeInternal(makeInternal(c.l, c.r, false), makeInternal(get(b.r).l, get(b.r).r, false), true);
            }
            return makeInternal(ci, b.r, b.red);
        }
        else if(a.level > b.level){
            Index ci = mergeSub(a.r, bi);
            auto& c = get(ci);
            if(!a.red && c.red && get(c.r).red){
                if(!get(a.l).red)
                    return makeInternal(makeInternal(a.l, c.l, true), c.r, false);
                else
                    return makeInternal(makeInternal(get(a.l).l, get(a.l).r, false), makeInternal(c.l, c.r, false), true);
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
        auto& a = get(ai);
        if(k == 0)
            return make_pair(nil, ai);
        if(k == a.siz)
            return make_pair(ai, nil);
        Index li = a.l;
        Index ri = a.r;
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
        T val = get(res2.second).sum;
        return make_pair(val, merge(merge(res2.first, res2.second), res.second));
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

    Index access(Index pi, int k){
        while(get(pi).l != nil || get(pi).r != nil){
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

    Index set(Index pi, int k, T val, function<T(T, T)> g = [](T x, T y){return y;}){
        stack<pair<Index, bool>> st;
        while(get(pi).l != nil || get(pi).r != nil){
            auto& p = get(pi);
            assert(p.l != nil && p.r != nil);
            if(get(p.l).siz <= k){
                k -= get(p.l).siz;
                st.emplace(pi, true);
                pi = p.r;
            }
            else{
                st.emplace(pi, false);
                pi = p.l;
            }
        }
        Index new_idx = makeLeaf(g(get(pi).sum, val), get(pi).red);
        while(!st.empty()){
            Index idx;
            bool is_right;
            tie(idx, is_right) = st.top();
            auto& p = get(idx);
            if(is_right)
                new_idx = makeInternal(p.l, new_idx, p.red);
            else
                new_idx = makeInternal(new_idx, p.r, p.red);
            st.pop();
        }
        return new_idx;
    }

    void dump(Index pi, vector<T>& v){
        auto& p = get(pi);
        if(p.l != nil)
            dump(p.l, v);
        v.emplace_back(get_val(pi));
        if(p.r != nil)
            dump(p.r, v);
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
#line 1 "lib/classes/redblacktree_persistent.cpp"
// verify: https://atcoder.jp/contests/joisc2012/submissions/12202620/
template <typename T>
struct RedBlackTree{

    struct Node;
    using Index = typename MemoryPool<Node>::Index;

    struct Node{
        int siz, level;
        T sum;
        bool red;
        typename MemoryPool<Node>::Index l, r;
        Node(){}
        Node(T val, bool red, bool leaf, int li = -1, int ri = -1) : sum(val), siz(leaf), level(0), red(red){
            l = {li};
            r = {ri};
        }
        Node(T val, bool red, bool leaf, Index l, Index r) : sum(val), siz(leaf), level(0), red(red), l(l), r(r){}
    };

    MemoryPool<Node> pool;
    Index nil;
    function<T(T, T)> f;
    T op;
    RedBlackTree(function<T(T, T)> f = [](auto x, auto y){return x + y;}, T op = T()) : f(f), op(op){
        nil = pool.alloc();
        pool[nil] = Node(op, false, false);
        pool[nil].l = pool[nil].r = nil;
    }

    Index build(vector<T>& a){
        nil = pool.alloc();
        pool[nil] = Node(op, false, false);
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

    T get_val(Index pi, int k){
        pi = access(pi, k);
        return get(pi).sum;
    }

    Index make(T val){
        Index idx = pool.alloc();
        pool[idx] = Node(val, false, true, nil.idx, nil.idx);
        pool[idx].level = 1;
        return idx;
    }

    Index makeInternal(Index l, Index r, bool red){
        auto idx = pool.alloc();
        pool[idx] = Node(op, red, false, l, r);
        pool[idx].sum = f(pool[l].sum, pool[r].sum);
        pool[idx].siz = pool[l].siz + pool[r].siz;
        pool[idx].level = pool[l].level + !pool[l].red;
        return idx;
    }

    Index makeLeaf(T val, bool red){
        auto idx = pool.alloc();
        pool[idx] = Node(val, red, true);
        pool[idx].l = pool[idx].r = nil;
        pool[idx].level = 1;
        return idx;
    }

    Index mergeSub(Index ai, Index bi){
        auto& a = get(ai);
        auto& b = get(bi);
        assert(ai != nil && bi != nil);
        if(a.level < b.level){
            Index ci = mergeSub(ai, b.l);
            auto& c = get(ci);
            if(!b.red && c.red && get(c.l).red){
                if(!get(b.r).red)
                    return makeInternal(c.l, makeInternal(c.r, b.r, true), false);
                else
                    return makeInternal(makeInternal(c.l, c.r, false), makeInternal(get(b.r).l, get(b.r).r, false), true);
            }
            return makeInternal(ci, b.r, b.red);
        }
        else if(a.level > b.level){
            Index ci = mergeSub(a.r, bi);
            auto& c = get(ci);
            if(!a.red && c.red && get(c.r).red){
                if(!get(a.l).red)
                    return makeInternal(makeInternal(a.l, c.l, true), c.r, false);
                else
                    return makeInternal(makeInternal(get(a.l).l, get(a.l).r, false), makeInternal(c.l, c.r, false), true);
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
        auto& a = get(ai);
        if(k == 0)
            return make_pair(nil, ai);
        if(k == a.siz)
            return make_pair(ai, nil);
        Index li = a.l;
        Index ri = a.r;
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
        T val = get(res2.second).sum;
        return make_pair(val, merge(merge(res2.first, res2.second), res.second));
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

    Index access(Index pi, int k){
        while(get(pi).l != nil || get(pi).r != nil){
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

    Index set(Index pi, int k, T val, function<T(T, T)> g = [](T x, T y){return y;}){
        stack<pair<Index, bool>> st;
        while(get(pi).l != nil || get(pi).r != nil){
            auto& p = get(pi);
            assert(p.l != nil && p.r != nil);
            if(get(p.l).siz <= k){
                k -= get(p.l).siz;
                st.emplace(pi, true);
                pi = p.r;
            }
            else{
                st.emplace(pi, false);
                pi = p.l;
            }
        }
        Index new_idx = makeLeaf(g(get(pi).sum, val), get(pi).red);
        while(!st.empty()){
            Index idx;
            bool is_right;
            tie(idx, is_right) = st.top();
            auto& p = get(idx);
            if(is_right)
                new_idx = makeInternal(p.l, new_idx, p.red);
            else
                new_idx = makeInternal(new_idx, p.r, p.red);
            st.pop();
        }
        return new_idx;
    }

    void dump(Index pi, vector<T>& v){
        auto& p = get(pi);
        if(p.l != nil)
            dump(p.l, v);
        v.emplace_back(get_val(pi));
        if(p.r != nil)
            dump(p.r, v);
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

