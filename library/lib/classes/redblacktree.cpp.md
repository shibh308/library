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


# :heavy_check_mark: lib/classes/redblacktree.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/redblacktree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-21 23:33:53+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/redblacktree_rsq.test.cpp.html">verify/redblacktree_rsq.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// merge/split ベースの赤黒木(葉木)
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

    Index clear(){
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

    void update(Index pi){
        if(pi == nil)
            return;
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        p.siz = l.siz + r.siz;
        if(p.l != nil || p.r != nil)
            p.sum = f(l.sum, r.sum);
        p.level = l.level + !l.red;
        assert(p.level == r.level + !r.red);
    }

    Index make(T val){
        Index idx = pool.alloc();
        pool[idx] = Node(val, false, true, nil.idx, nil.idx);
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
            get(d) = Node(op, true, false, ai.idx, bi.idx);
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
        pool.free(res2.second);
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

    void set(Index pi, int k, T val, function<T(T, T)> g = [](T x, T y){return y;}){
        stack<Index> st;
        while(get(pi).l != nil || get(pi).r != nil){
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
        p.sum = g(p.sum, val);
        while(!st.empty()){
            update(st.top());
            st.pop();
        }
    }

    Node& get(Index k){return pool[k];}
    Node& operator[](Index k){return pool[k];}
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/redblacktree.cpp"
// merge/split ベースの赤黒木(葉木)
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

    Index clear(){
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

    void update(Index pi){
        if(pi == nil)
            return;
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        p.siz = l.siz + r.siz;
        if(p.l != nil || p.r != nil)
            p.sum = f(l.sum, r.sum);
        p.level = l.level + !l.red;
        assert(p.level == r.level + !r.red);
    }

    Index make(T val){
        Index idx = pool.alloc();
        pool[idx] = Node(val, false, true, nil.idx, nil.idx);
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
            get(d) = Node(op, true, false, ai.idx, bi.idx);
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
        pool.free(res2.second);
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

    void set(Index pi, int k, T val, function<T(T, T)> g = [](T x, T y){return y;}){
        stack<Index> st;
        while(get(pi).l != nil || get(pi).r != nil){
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
        p.sum = g(p.sum, val);
        while(!st.empty()){
            update(st.top());
            st.pop();
        }
    }

    Node& get(Index k){return pool[k];}
    Node& operator[](Index k){return pool[k];}
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

