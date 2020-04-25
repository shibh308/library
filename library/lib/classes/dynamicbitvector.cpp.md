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


# :heavy_check_mark: lib/classes/dynamicbitvector.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/dynamicbitvector.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-25 21:27:24+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/dynamicwaveletmatrix_kthmin.test.cpp.html">verify/dynamicwaveletmatrix_kthmin.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/dynamicwaveletmatrix_rmq.test.cpp.html">verify/dynamicwaveletmatrix_rmq.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct DynamicBitVector{
    struct Node;
    using Index = MemoryPool<Node>::Index;
    MemoryPool<Node> pool;
    struct Node{
        int siz, cnt, height;
        short len;
        uint64_t val;
        MemoryPool<Node>::Index l, r;
        Node(){}
        Node(int siz, int cnt, int height, short len, uint64_t val, MemoryPool<Node>::Index nil) :
                siz(siz), cnt(cnt), height(height), len(len), val(val), l(nil), r(nil){}
    };
    Index root, nil;

    int rank_val;
    bool erase_fl;

    DynamicBitVector(){
        nil = pool.alloc();
        auto& p = get(nil);
        p.cnt = p.val = p.siz = p.height = p.len = 0;
        p.l = p.r = nil;
    }

    Index build(int n, vector<uint64_t>& a, int l, int r){
        assert(n >= 0);
        int mid = (l + r) / 2;
        Index l_idx = l == mid ? nil : build(n, a, l, mid);
        Index r_idx = mid + 1 == r ? nil : build(n, a, mid + 1, r);
        Index idx = pool.alloc();
        pool[idx] = Node(0, 0, 0, mid + 1 == a.size() ? n - (a.size() - 1) * 32 : 32, a[mid], nil);
        pool[idx].l = l_idx;
        pool[idx].r = r_idx;
        update(idx);

        return idx;
    }

    void update(Index pi){
        if(pi == nil)
            return;
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        p.siz = l.siz + r.siz + p.len;
        p.height = max(l.height, r.height) + 1;
        p.cnt = l.cnt + r.cnt + __builtin_popcountll(p.val);
    }

    int balance_factor(Index pi){return get(get(pi).l).height - get(get(pi).r).height;}

    Index rotl(Index pi){
        assert(pi != nil);
        auto& p = get(pi);
        Index qi = p.r;
        assert(qi != nil);
        auto& q = get(qi);
        p.r = q.l;
        q.l = pi;
        update(pi);
        update(qi);
        return qi;
    }

    Index rotr(Index pi){
        assert(pi != nil);
        auto& p = get(pi);
        Index qi = p.l;
        assert(qi != nil);
        auto& q = get(qi);
        p.l = q.r;
        q.r = pi;
        update(pi);
        update(qi);
        return qi;
    }

    Index balance(Index pi){
        if(balance_factor(pi) == 2){
            auto& p = get(pi);
            if(balance_factor(p.l) < 0)
                p.l = rotl(p.l);
            return rotr(pi);
        }
        if(balance_factor(pi) == -2){
            auto& p = get(pi);
            if(balance_factor(p.r) > 0)
                p.r = rotr(p.r);
            return rotl(pi);
        }
        update(pi);
        return pi;
    }

    Index _insert(Index pi, Index new_idx){
        if(pi == nil)
            return new_idx;
        auto& p = get(pi);
        p.l = _insert(p.l, new_idx);
        return balance(pi);
    }

    Index insert(Index pi, int k, bool fl){
        if(pi == nil){
            Index idx = pool.alloc();
            pool[idx] = Node(1, fl, 1, 1, fl, nil);
            return idx;
        }
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        if(k <= l.siz && p.l != nil){
            p.l = insert(p.l, k, fl);
        }
        else if(k <= l.siz + p.len){
            k -= l.siz;
            rank_val += get(p.l).cnt + __builtin_popcountll(p.val & ((1uLL << k) - 1));
            p.val = (p.val & ((1uLL << k) - 1)) | ((p.val & ~((1uLL << k) - 1)) << 1) | (uint64_t(fl) << k);
            if(++p.len == 64){
                uint64_t vl = p.val & ((1uLL << 32) - 1);
                uint64_t vr = p.val >> 32;
                p.val = vl;
                p.len = 32;
                Index r_idx = pool.alloc();
                pool[r_idx] = Node(32, __builtin_popcountll(vr), 1, 32, vr, nil);
                p.r = _insert(p.r, r_idx);
            }
        }
        else{
            rank_val += get(p.l).cnt + __builtin_popcountll(p.val);
            p.r = insert(p.r, k - p.len - l.siz, fl);
        }
        return balance(pi);
    }

    Index _erase_left(Index pi, Index root_idx){
        auto& p = get(pi);
        if(p.l == nil){
            if(!merge(root_idx, pi, true)){
                Index qi = p.r;
                pool.free(pi);
                return qi;
            }
        }
        else
            p.l = _erase_left(p.l, root_idx);
        return balance(pi);
    }

    Index _erase_right(Index pi, Index root_idx){
        auto& p = get(pi);
        if(p.r == nil){
            if(!merge(root_idx, pi, false)){
                Index qi = p.l;
                pool.free(pi);
                return qi;
            }
        }
        else{
            p.r = _erase_right(p.r, root_idx);
        }
        return balance(pi);
    }

    // aiとbiをマージして, もし1つにできるならaiを残す
    bool merge(Index ai, Index bi, bool a_left){
        auto& a = get(ai);
        auto& b = get(bi);
        if(!a_left){
            swap(a.val, b.val);
            swap(a.len, b.len);
        }
        short len_sum = a.len + b.len;
        if(len_sum <= 64){
            a.val = a.val | (b.val << a.len);
            a.len = len_sum;
            update(ai);
            return false;
        }
        else{
            uint32_t mid = (a.len + b.len) >> 1;
            uint64_t av, bv;
            if(a.len >= mid){
                av = a.val & ((1uLL << mid) - 1);
                bv = (a.val >> mid) | (b.val << (a.len - mid));
            }
            else{
                av = (a.val | (b.val << a.len)) & ((1uLL << mid) - 1);
                bv = b.val >> (mid - a.len);
            }

            a.val = av;
            b.val = bv;
            a.len = mid;
            b.len = len_sum - mid;
            if(!a_left){
                swap(a.val, b.val);
                swap(a.len, b.len);
            }
            return true;
        }
    }

    Index erase(Index pi, int k, Index par = {-1}){
        if(par.idx == -1)
            par = nil;
        if(pi == nil)
            return nil;
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        if(k < l.siz)
            p.l = erase(p.l, k);
        else if(k < l.siz + p.len){
            k -= l.siz;
            --p.len;
            rank_val += get(p.l).cnt + __builtin_popcountll(p.val & ((1uLL << k) - 1));
            erase_fl = (p.val >> k) & 1;
            p.val = (p.val & ((1uLL << k) - 1)) | ((p.val & ~((1uLL << (k + 1)) - 1)) >> 1);

            if(p.len <= 16){
                if(p.l != nil){
                    p.l = _erase_right(p.l, pi);
                }
                else if(p.r != nil){
                    p.r = _erase_left(p.r, pi);
                }
                else{
                    if(par == nil){
                        if(p.len == 0){
                            pool.free(pi);
                            return nil;
                        }
                        update(pi);
                        return pi;
                    }
                    else{
                        auto& parent = get(par);
                        if(parent.l == pi){
                            if(!merge(par, pi, false)){
                                pool.free(pi);
                                return nil;
                            }
                        }
                        else{
                            assert(parent.r == pi);
                            if(!merge(par, pi, true)){
                                pool.free(pi);
                                return nil;
                            }
                        }
                    }
                }
            }
        }
        else{
            rank_val += get(p.l).cnt + __builtin_popcountll(p.val);
            p.r = erase(p.r, k - p.len - l.siz);
        }
        return balance(pi);
    }

    int rank(Index pi, int k){
        if(pi == nil)
            return 0;
        auto& p = get(pi);
        auto& l = get(p.l);
        if(k < l.siz)
            return rank(p.l, k);
        else if(k < l.siz + p.len)
            return l.cnt + __builtin_popcountll(p.val & ((1uLL << (k - l.siz)) - 1));
        else
            return l.cnt + __builtin_popcountll(p.val) + rank(p.r, k - l.siz - p.len);
    }

    bool access(Index pi, int k){
        assert(pi != nil);
        auto& p = get(pi);
        assert(0 <= k && k < p.siz);
        auto& l = get(p.l);
        assert(p.siz == p.len + l.siz + get(p.r).siz);
        if(k < l.siz)
            return access(p.l, k);
        else if(k < l.siz + p.len)
            return (p.val >> (k - l.siz)) & 1;
        else
            return access(p.r, k - l.siz - p.len);
    }

    Node& get(Index k){return pool[k];}
    Node& operator[](Index k){return pool[k];}

    void build(int n, vector<uint64_t>& a){
        root = build(n, a, 0, a.size());
        assert(get(root).siz == n);
    }

    void insert(int k, bool fl){
        rank_val = 0;
        root = insert(root, k, fl);
    }

    void erase(int k){
        rank_val = 0;
        root = erase(root, k);
    }

    int rank(int k, bool fl = true){
        return fl ? rank(root, k) : k - rank(root, k);
    }

    bool access(int k){
        return access(root, k);
    }

    int zero_cnt(){
        return get(root).siz - get(root).cnt;
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/dynamicbitvector.cpp"
struct DynamicBitVector{
    struct Node;
    using Index = MemoryPool<Node>::Index;
    MemoryPool<Node> pool;
    struct Node{
        int siz, cnt, height;
        short len;
        uint64_t val;
        MemoryPool<Node>::Index l, r;
        Node(){}
        Node(int siz, int cnt, int height, short len, uint64_t val, MemoryPool<Node>::Index nil) :
                siz(siz), cnt(cnt), height(height), len(len), val(val), l(nil), r(nil){}
    };
    Index root, nil;

    int rank_val;
    bool erase_fl;

    DynamicBitVector(){
        nil = pool.alloc();
        auto& p = get(nil);
        p.cnt = p.val = p.siz = p.height = p.len = 0;
        p.l = p.r = nil;
    }

    Index build(int n, vector<uint64_t>& a, int l, int r){
        assert(n >= 0);
        int mid = (l + r) / 2;
        Index l_idx = l == mid ? nil : build(n, a, l, mid);
        Index r_idx = mid + 1 == r ? nil : build(n, a, mid + 1, r);
        Index idx = pool.alloc();
        pool[idx] = Node(0, 0, 0, mid + 1 == a.size() ? n - (a.size() - 1) * 32 : 32, a[mid], nil);
        pool[idx].l = l_idx;
        pool[idx].r = r_idx;
        update(idx);

        return idx;
    }

    void update(Index pi){
        if(pi == nil)
            return;
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        p.siz = l.siz + r.siz + p.len;
        p.height = max(l.height, r.height) + 1;
        p.cnt = l.cnt + r.cnt + __builtin_popcountll(p.val);
    }

    int balance_factor(Index pi){return get(get(pi).l).height - get(get(pi).r).height;}

    Index rotl(Index pi){
        assert(pi != nil);
        auto& p = get(pi);
        Index qi = p.r;
        assert(qi != nil);
        auto& q = get(qi);
        p.r = q.l;
        q.l = pi;
        update(pi);
        update(qi);
        return qi;
    }

    Index rotr(Index pi){
        assert(pi != nil);
        auto& p = get(pi);
        Index qi = p.l;
        assert(qi != nil);
        auto& q = get(qi);
        p.l = q.r;
        q.r = pi;
        update(pi);
        update(qi);
        return qi;
    }

    Index balance(Index pi){
        if(balance_factor(pi) == 2){
            auto& p = get(pi);
            if(balance_factor(p.l) < 0)
                p.l = rotl(p.l);
            return rotr(pi);
        }
        if(balance_factor(pi) == -2){
            auto& p = get(pi);
            if(balance_factor(p.r) > 0)
                p.r = rotr(p.r);
            return rotl(pi);
        }
        update(pi);
        return pi;
    }

    Index _insert(Index pi, Index new_idx){
        if(pi == nil)
            return new_idx;
        auto& p = get(pi);
        p.l = _insert(p.l, new_idx);
        return balance(pi);
    }

    Index insert(Index pi, int k, bool fl){
        if(pi == nil){
            Index idx = pool.alloc();
            pool[idx] = Node(1, fl, 1, 1, fl, nil);
            return idx;
        }
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        if(k <= l.siz && p.l != nil){
            p.l = insert(p.l, k, fl);
        }
        else if(k <= l.siz + p.len){
            k -= l.siz;
            rank_val += get(p.l).cnt + __builtin_popcountll(p.val & ((1uLL << k) - 1));
            p.val = (p.val & ((1uLL << k) - 1)) | ((p.val & ~((1uLL << k) - 1)) << 1) | (uint64_t(fl) << k);
            if(++p.len == 64){
                uint64_t vl = p.val & ((1uLL << 32) - 1);
                uint64_t vr = p.val >> 32;
                p.val = vl;
                p.len = 32;
                Index r_idx = pool.alloc();
                pool[r_idx] = Node(32, __builtin_popcountll(vr), 1, 32, vr, nil);
                p.r = _insert(p.r, r_idx);
            }
        }
        else{
            rank_val += get(p.l).cnt + __builtin_popcountll(p.val);
            p.r = insert(p.r, k - p.len - l.siz, fl);
        }
        return balance(pi);
    }

    Index _erase_left(Index pi, Index root_idx){
        auto& p = get(pi);
        if(p.l == nil){
            if(!merge(root_idx, pi, true)){
                Index qi = p.r;
                pool.free(pi);
                return qi;
            }
        }
        else
            p.l = _erase_left(p.l, root_idx);
        return balance(pi);
    }

    Index _erase_right(Index pi, Index root_idx){
        auto& p = get(pi);
        if(p.r == nil){
            if(!merge(root_idx, pi, false)){
                Index qi = p.l;
                pool.free(pi);
                return qi;
            }
        }
        else{
            p.r = _erase_right(p.r, root_idx);
        }
        return balance(pi);
    }

    // aiとbiをマージして, もし1つにできるならaiを残す
    bool merge(Index ai, Index bi, bool a_left){
        auto& a = get(ai);
        auto& b = get(bi);
        if(!a_left){
            swap(a.val, b.val);
            swap(a.len, b.len);
        }
        short len_sum = a.len + b.len;
        if(len_sum <= 64){
            a.val = a.val | (b.val << a.len);
            a.len = len_sum;
            update(ai);
            return false;
        }
        else{
            uint32_t mid = (a.len + b.len) >> 1;
            uint64_t av, bv;
            if(a.len >= mid){
                av = a.val & ((1uLL << mid) - 1);
                bv = (a.val >> mid) | (b.val << (a.len - mid));
            }
            else{
                av = (a.val | (b.val << a.len)) & ((1uLL << mid) - 1);
                bv = b.val >> (mid - a.len);
            }

            a.val = av;
            b.val = bv;
            a.len = mid;
            b.len = len_sum - mid;
            if(!a_left){
                swap(a.val, b.val);
                swap(a.len, b.len);
            }
            return true;
        }
    }

    Index erase(Index pi, int k, Index par = {-1}){
        if(par.idx == -1)
            par = nil;
        if(pi == nil)
            return nil;
        auto& p = get(pi);
        auto& l = get(p.l);
        auto& r = get(p.r);
        if(k < l.siz)
            p.l = erase(p.l, k);
        else if(k < l.siz + p.len){
            k -= l.siz;
            --p.len;
            rank_val += get(p.l).cnt + __builtin_popcountll(p.val & ((1uLL << k) - 1));
            erase_fl = (p.val >> k) & 1;
            p.val = (p.val & ((1uLL << k) - 1)) | ((p.val & ~((1uLL << (k + 1)) - 1)) >> 1);

            if(p.len <= 16){
                if(p.l != nil){
                    p.l = _erase_right(p.l, pi);
                }
                else if(p.r != nil){
                    p.r = _erase_left(p.r, pi);
                }
                else{
                    if(par == nil){
                        if(p.len == 0){
                            pool.free(pi);
                            return nil;
                        }
                        update(pi);
                        return pi;
                    }
                    else{
                        auto& parent = get(par);
                        if(parent.l == pi){
                            if(!merge(par, pi, false)){
                                pool.free(pi);
                                return nil;
                            }
                        }
                        else{
                            assert(parent.r == pi);
                            if(!merge(par, pi, true)){
                                pool.free(pi);
                                return nil;
                            }
                        }
                    }
                }
            }
        }
        else{
            rank_val += get(p.l).cnt + __builtin_popcountll(p.val);
            p.r = erase(p.r, k - p.len - l.siz);
        }
        return balance(pi);
    }

    int rank(Index pi, int k){
        if(pi == nil)
            return 0;
        auto& p = get(pi);
        auto& l = get(p.l);
        if(k < l.siz)
            return rank(p.l, k);
        else if(k < l.siz + p.len)
            return l.cnt + __builtin_popcountll(p.val & ((1uLL << (k - l.siz)) - 1));
        else
            return l.cnt + __builtin_popcountll(p.val) + rank(p.r, k - l.siz - p.len);
    }

    bool access(Index pi, int k){
        assert(pi != nil);
        auto& p = get(pi);
        assert(0 <= k && k < p.siz);
        auto& l = get(p.l);
        assert(p.siz == p.len + l.siz + get(p.r).siz);
        if(k < l.siz)
            return access(p.l, k);
        else if(k < l.siz + p.len)
            return (p.val >> (k - l.siz)) & 1;
        else
            return access(p.r, k - l.siz - p.len);
    }

    Node& get(Index k){return pool[k];}
    Node& operator[](Index k){return pool[k];}

    void build(int n, vector<uint64_t>& a){
        root = build(n, a, 0, a.size());
        assert(get(root).siz == n);
    }

    void insert(int k, bool fl){
        rank_val = 0;
        root = insert(root, k, fl);
    }

    void erase(int k){
        rank_val = 0;
        root = erase(root, k);
    }

    int rank(int k, bool fl = true){
        return fl ? rank(root, k) : k - rank(root, k);
    }

    bool access(int k){
        return access(root, k);
    }

    int zero_cnt(){
        return get(root).siz - get(root).cnt;
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

