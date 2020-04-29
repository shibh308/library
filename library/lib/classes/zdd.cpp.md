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


# :heavy_check_mark: lib/classes/zdd.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/zdd.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-29 13:15:47+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/zdd_knapsack.test.cpp.html">verify/zdd_knapsack.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
struct ZDD{
    struct Node{
        int label;
        using Index = typename MemoryPool<Node>::Index;
        Index c[2];
        Node(){}
        Node(int label, Index nil) : label(label){
            c[0] = c[1] = nil;
        }
        Node(int label, Index l, Index r) : label(label){
            c[0] = l;
            c[1] = r;
        }
    };
    using Index = typename MemoryPool<Node>::Index;
    Index nil, true_idx, false_idx;
    MemoryPool<Node> pool;
    // 引数は(Data, label, 最後どう進んだか)
    // secondが-1ならDataを表す, 0/1なら終端状態を表す
    ZDD(){
        nil = {-1};
        true_idx = {-2};
        false_idx = {-3};
    }
    template<typename Data>
    Index build(function<pair<Data, int>(Data, int, bool)> f, Data init){
        unordered_map<int, map<Data, Index>> node_map;
        Index root = pool.alloc();
        pool[root] = Node(0, nil);
        node_map[0][init] = root;
        build<Data>(root, init, f, node_map);
        return compress(root);
    }
    template<typename Data>
    void build(Index pi, Data& d, function<pair<Data, int>(Data, int, bool)>& f, unordered_map<int, map<Data, Index>>& node_map){
        auto& x = pool[pi];
        for(int i = 0; i < 2; ++i){
            int fl;
            Data y;
            tie(y, fl) = f(d, x.label, i);
            if(fl == 0){
                x.c[i] = false_idx;
            }
            else if(fl == 1){
                x.c[i] = true_idx;
            }
            else if(node_map[x.label + 1].find(y) == node_map[x.label + 1].end()){
                Index new_idx = pool.alloc();
                pool[new_idx] = Node(x.label + 1, nil);
                node_map[x.label + 1][y] = new_idx;
                x.c[i] = new_idx;
                build(node_map[x.label + 1][y], y, f, node_map);
            }else{
                x.c[i] = node_map[x.label + 1][y];
            }
        }
    }
    Index compress(Index pi, unordered_map<int, unordered_map<uint64_t, Index>>& node_map, unordered_map<int, Index>& replace_map){
        // 同型で子が一致する頂点を破滅
        if(pi == true_idx || pi == false_idx)
            return pi;
        if(replace_map.find(pi.idx) != replace_map.end())
            return replace_map[pi.idx];
        auto& p = pool[pi];
        Index li = compress(p.c[0], node_map, replace_map);
        Index ri = compress(p.c[1], node_map, replace_map);
        p.c[0] = li;
        p.c[1] = ri;
        uint64_t h = uint32_t(li.idx) | ((1uLL * uint32_t(ri.idx)) << 32);
        if(node_map[p.label].find(h) == node_map[p.label].end())
            node_map[p.label][h] = pi;
        else
            pool.free(pi);
        return replace_map[pi.idx] = node_map[p.label][h];
    }
    Index compress(Index pi){
        unordered_map<int, unordered_map<uint64_t, Index>> node_map;
        unordered_map<int, Index> replace_map;
        return compress(pi, node_map, replace_map);
    }
    i64 linear_func_max(Index pi, vector<i64>& a, unordered_map<int, i64>& res){
        if(pi == true_idx)
            return 0;
        if(pi == false_idx)
            return -INF;
        if(res.find(pi.idx) == res.end())
            res[pi.idx] = max(linear_func_max(pool[pi].c[0], a, res), linear_func_max(pool[pi].c[1], a, res) + a[pool[pi].label]);
        return res[pi.idx];
    }
    i64 linear_func_max(Index root, vector<i64> a){
        unordered_map<int, i64> res;
        return linear_func_max(root, a, res);
    }
    i64 count(Index pi, unordered_map<int, i64>& res){
        if(pi == true_idx)
            return 1;
        if(pi == false_idx)
            return 0;
        if(res.find(pi.idx) == res.end())
            res[pi.idx] = count(pool[pi].c[0], res) + count(pool[pi].c[1], res);
        return res[pi.idx];
    }
    i64 count(Index root){
        unordered_map<int, i64> res;
        return count(root, res);
    }
    double get_per(Index pi, vector<double>& a, unordered_map<int, double>& res){
        if(pi == true_idx)
            return 1;
        if(pi == false_idx)
            return 0;
        if(res.find(pi.idx) == res.end())
            res[pi.idx] = a[pool[pi].label] * get_per(pool[pi].c[0], a, res) + (1.0 - a[pool[pi].label]) * get_per(pool[pi].c[1], a, res);
        return res[pi.idx];
    }
    double get_per(Index root, vector<double>& a){
        unordered_map<int, double> res;
        return get_per(root, a, res);
    }
    Index apply(Index li, Index ri, function<Index(Index, Index)>& f, unordered_map<uint64_t, Index>& node_map){
        Index res = f(li, ri);
        if(res != nil)
            return res;
        int lidx, ridx;
        tie(lidx, ridx) = minmax(li.idx, ri.idx);
        uint64_t h = lidx | ((1uLL * ridx) << 32);
        if(node_map.find(h) != node_map.end())
            return node_map[h];
        if(pool[li].label < pool[ri].label)
            swap(li, ri);
        auto& l = pool[li];
        auto& r = pool[ri];
        Index idx = pool.alloc();
        if(l.label == r.label)
            pool[idx] = Node(l.label, apply(l.c[0], r.c[0], f, node_map), apply(l.c[1], r.c[1], f, node_map));
        else
            pool[idx] = Node(l.label, apply(l.c[0], ri, f, node_map), apply(l.c[1], ri, f, node_map));
        return node_map[h] = idx;
    }
    Index apply_and(Index li, Index ri){
        unordered_map<uint64_t, Index> node_map;
        function<Index(Index, Index)> f = [&](Index li, Index ri){
            if(li == true_idx)
                return ri;
            if(ri == true_idx)
                return li;
            if(li == false_idx || ri == false_idx)
                return false_idx;
            else
                return nil;
        };
        return apply(li, ri, f, node_map);
    }
    Index apply_or(Index li, Index ri){
        unordered_map<uint64_t, Index> node_map;
        function<Index(Index, Index)> f = [&](Index li, Index ri){
            if(li == false_idx)
                return ri;
            if(ri == false_idx)
                return li;
            if(li == true_idx || ri == true_idx)
                return true_idx;
            else
                return nil;
        };
        return apply(li, ri, f, node_map);
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/zdd.cpp"
struct ZDD{
    struct Node{
        int label;
        using Index = typename MemoryPool<Node>::Index;
        Index c[2];
        Node(){}
        Node(int label, Index nil) : label(label){
            c[0] = c[1] = nil;
        }
        Node(int label, Index l, Index r) : label(label){
            c[0] = l;
            c[1] = r;
        }
    };
    using Index = typename MemoryPool<Node>::Index;
    Index nil, true_idx, false_idx;
    MemoryPool<Node> pool;
    // 引数は(Data, label, 最後どう進んだか)
    // secondが-1ならDataを表す, 0/1なら終端状態を表す
    ZDD(){
        nil = {-1};
        true_idx = {-2};
        false_idx = {-3};
    }
    template<typename Data>
    Index build(function<pair<Data, int>(Data, int, bool)> f, Data init){
        unordered_map<int, map<Data, Index>> node_map;
        Index root = pool.alloc();
        pool[root] = Node(0, nil);
        node_map[0][init] = root;
        build<Data>(root, init, f, node_map);
        return compress(root);
    }
    template<typename Data>
    void build(Index pi, Data& d, function<pair<Data, int>(Data, int, bool)>& f, unordered_map<int, map<Data, Index>>& node_map){
        auto& x = pool[pi];
        for(int i = 0; i < 2; ++i){
            int fl;
            Data y;
            tie(y, fl) = f(d, x.label, i);
            if(fl == 0){
                x.c[i] = false_idx;
            }
            else if(fl == 1){
                x.c[i] = true_idx;
            }
            else if(node_map[x.label + 1].find(y) == node_map[x.label + 1].end()){
                Index new_idx = pool.alloc();
                pool[new_idx] = Node(x.label + 1, nil);
                node_map[x.label + 1][y] = new_idx;
                x.c[i] = new_idx;
                build(node_map[x.label + 1][y], y, f, node_map);
            }else{
                x.c[i] = node_map[x.label + 1][y];
            }
        }
    }
    Index compress(Index pi, unordered_map<int, unordered_map<uint64_t, Index>>& node_map, unordered_map<int, Index>& replace_map){
        // 同型で子が一致する頂点を破滅
        if(pi == true_idx || pi == false_idx)
            return pi;
        if(replace_map.find(pi.idx) != replace_map.end())
            return replace_map[pi.idx];
        auto& p = pool[pi];
        Index li = compress(p.c[0], node_map, replace_map);
        Index ri = compress(p.c[1], node_map, replace_map);
        p.c[0] = li;
        p.c[1] = ri;
        uint64_t h = uint32_t(li.idx) | ((1uLL * uint32_t(ri.idx)) << 32);
        if(node_map[p.label].find(h) == node_map[p.label].end())
            node_map[p.label][h] = pi;
        else
            pool.free(pi);
        return replace_map[pi.idx] = node_map[p.label][h];
    }
    Index compress(Index pi){
        unordered_map<int, unordered_map<uint64_t, Index>> node_map;
        unordered_map<int, Index> replace_map;
        return compress(pi, node_map, replace_map);
    }
    i64 linear_func_max(Index pi, vector<i64>& a, unordered_map<int, i64>& res){
        if(pi == true_idx)
            return 0;
        if(pi == false_idx)
            return -INF;
        if(res.find(pi.idx) == res.end())
            res[pi.idx] = max(linear_func_max(pool[pi].c[0], a, res), linear_func_max(pool[pi].c[1], a, res) + a[pool[pi].label]);
        return res[pi.idx];
    }
    i64 linear_func_max(Index root, vector<i64> a){
        unordered_map<int, i64> res;
        return linear_func_max(root, a, res);
    }
    i64 count(Index pi, unordered_map<int, i64>& res){
        if(pi == true_idx)
            return 1;
        if(pi == false_idx)
            return 0;
        if(res.find(pi.idx) == res.end())
            res[pi.idx] = count(pool[pi].c[0], res) + count(pool[pi].c[1], res);
        return res[pi.idx];
    }
    i64 count(Index root){
        unordered_map<int, i64> res;
        return count(root, res);
    }
    double get_per(Index pi, vector<double>& a, unordered_map<int, double>& res){
        if(pi == true_idx)
            return 1;
        if(pi == false_idx)
            return 0;
        if(res.find(pi.idx) == res.end())
            res[pi.idx] = a[pool[pi].label] * get_per(pool[pi].c[0], a, res) + (1.0 - a[pool[pi].label]) * get_per(pool[pi].c[1], a, res);
        return res[pi.idx];
    }
    double get_per(Index root, vector<double>& a){
        unordered_map<int, double> res;
        return get_per(root, a, res);
    }
    Index apply(Index li, Index ri, function<Index(Index, Index)>& f, unordered_map<uint64_t, Index>& node_map){
        Index res = f(li, ri);
        if(res != nil)
            return res;
        int lidx, ridx;
        tie(lidx, ridx) = minmax(li.idx, ri.idx);
        uint64_t h = lidx | ((1uLL * ridx) << 32);
        if(node_map.find(h) != node_map.end())
            return node_map[h];
        if(pool[li].label < pool[ri].label)
            swap(li, ri);
        auto& l = pool[li];
        auto& r = pool[ri];
        Index idx = pool.alloc();
        if(l.label == r.label)
            pool[idx] = Node(l.label, apply(l.c[0], r.c[0], f, node_map), apply(l.c[1], r.c[1], f, node_map));
        else
            pool[idx] = Node(l.label, apply(l.c[0], ri, f, node_map), apply(l.c[1], ri, f, node_map));
        return node_map[h] = idx;
    }
    Index apply_and(Index li, Index ri){
        unordered_map<uint64_t, Index> node_map;
        function<Index(Index, Index)> f = [&](Index li, Index ri){
            if(li == true_idx)
                return ri;
            if(ri == true_idx)
                return li;
            if(li == false_idx || ri == false_idx)
                return false_idx;
            else
                return nil;
        };
        return apply(li, ri, f, node_map);
    }
    Index apply_or(Index li, Index ri){
        unordered_map<uint64_t, Index> node_map;
        function<Index(Index, Index)> f = [&](Index li, Index ri){
            if(li == false_idx)
                return ri;
            if(ri == false_idx)
                return li;
            if(li == true_idx || ri == true_idx)
                return true_idx;
            else
                return nil;
        };
        return apply(li, ri, f, node_map);
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

