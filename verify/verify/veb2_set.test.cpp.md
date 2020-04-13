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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :heavy_check_mark: verify/veb2_set.test.cpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#e8418d1d706cd73548f9f16f1d55ad6e">verify</a>
* <a href="{{ site.github.repository_url }}/blob/master/verify/veb2_set.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-13 20:50:20+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B</a>


## Depends on

* :heavy_check_mark: <a href="../../library/lib/classes/hashmap.cpp.html">lib/classes/hashmap.cpp</a>
* :heavy_check_mark: <a href="../../library/lib/classes/vanemdeboastree2.cpp.html">lib/classes/vanemdeboastree2.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#include "../lib/classes/hashmap.cpp"
#include "../lib/classes/vanemdeboastree2.cpp"

signed main(){
    int n;
    cin >> n;
    VanEmdeBoasTree<32> b;
    vector<int> type(n);
    vector<int> v(n, 0);
    for(int i = 0; i < n; ++i)
        scanf("%d%d", &type[i], &v[i]);

    int m = 0;

    for(int i = 0; i < n; ++i){
        int x = v[i];
        if(type[i] == 0){
            m += b.insert(x);
            printf("%d\n", m);
        }
        else if(type[i] == 1){
            printf("%d\n", b.lower_bound(x) == x);
        }
        else if(type[i] == 2){
            m -= b.erase(x);
        }
    }
}


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "verify/veb2_set.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP2_7_B"
#include <bits/stdc++.h>

using namespace std;

using i64 = long long;

#line 1 "lib/classes/hashmap.cpp"
template <typename T, typename U, T del = numeric_limits<T>::max(), T null = numeric_limits<T>::max() - 1>
struct HashMap{
    static constexpr __int128_t z = 0xf332ac987401cba5;
    uint64_t n, q, d;

    vector<pair<T, U>> v;

    HashMap() : n(0), q(0), d(1),  v(2, make_pair(null, U())){
    }

    inline uint64_t hash(T key){return uint64_t((z * __int128_t(key)) >> (64 - d)) & ((1LL << d) - 1);}

    pair<U, bool> find(T x){
        for(uint64_t i = hash(x); v[i].first != null; i = (i + 1) & ((1 << d) - 1))
            if(v[i].first == x)
                return make_pair(v[i].second, true);
        return make_pair(U(), false);
    }

    bool add(T x, U val){
        if(find(x).second)
            return false;
        if(((q + 1) << 1) > (1 << d) || (1 << d) < 3 * n)
            resize();
        uint64_t i = hash(x);
        for(; v[i].first != null && v[i].first != del; i = (i + 1) & ((1 << d) - 1));
        q += (v[i].first == null);
        ++n;
        v[i] = make_pair(x, val);
        return true;
    }

    bool erase(T x){
        uint64_t i = hash(x);
        for(; v[i].first != null && v[i].first != x; i = (i + 1) & ((1 << d) - 1));
        if(v[i].first == null)
            return false;
        --n;
        v[i] = make_pair(del, U());
        return true;
    }

    void resize(){
        ++d;
        vector<pair<T, U>> old_table;
        q = n;
        swap(old_table, v);
        v.assign(1 << d, make_pair(null, U()));
        n = 0;
        for(int i = 0; i < old_table.size(); ++i)
            if(old_table[i].first != null && old_table[i].first != del)
                add(old_table[i].first, old_table[i].second);
    }
};

#line 1 "lib/classes/vanemdeboastree2.cpp"
// 必要な所だけ作るvEB木
template <uint32_t W, uint64_t NULL_FLAG = ~0uLL>
struct VanEmdeBoasTree{

    struct Node{
        uint64_t u, ma, mi;
        Node* aux;
        HashMap<int, Node*> c;
        Node(int u) : u(u), mi(NULL_FLAG), ma(0){
            if(u)
                aux = new Node(u - 1);
        }
    };
    Node* root;
    VanEmdeBoasTree(){
        root = new Node(64 - __builtin_clzll(W - 1));
        insert((1uLL << W) - 1, root);
    }

    Node* child(Node* ptr, uint64_t idx){
        assert(ptr->u > 0);
        auto res = ptr->c.find(idx);
        if(res.second)
            return res.first;
        ptr->c.add(idx, new Node(ptr->u - 1));
        return ptr->c.find(idx).first;
    }

    bool insert(uint64_t key, Node* ptr = nullptr){
        if(ptr == nullptr)
            ptr = root;
        if(ptr->u == 0){
            bool fl = (ptr->ma < key) || (key < ptr->mi);
            ptr->ma = max(ptr->ma, key);
            ptr->mi = min(ptr->mi, key);
            return fl;
        }
        if(ptr->mi > ptr->ma){
            ptr->mi = ptr->ma = key;
            return true;
        }
        if(key < ptr->mi){
            swap(key, ptr->mi);
        }
        else if(ptr->mi == key)
            return false;
        if(ptr->ma < key)
            ptr->ma = key;

        int shift_cnt = 1 << (ptr->u - 1);
        uint64_t idx = key >> shift_cnt;
        uint64_t next_key = key & ((1uLL << shift_cnt) - 1);

        if(child(ptr, idx)->mi > child(ptr, idx)->ma)
            insert(idx, ptr->aux);
        return insert(next_key, child(ptr, idx));
    }

    bool erase(uint64_t key, Node* ptr = nullptr){
        if(ptr == nullptr)
            ptr = root;
        if(ptr->mi > ptr->ma)
            return false;
        if(ptr->mi == ptr->ma){
            if(ptr->mi == key){
                ptr->mi = NULL_FLAG;
                ptr->ma = 0;
                return true;
            }
            return false;
        }
        if(ptr->u == 0){
            // 2要素あるうちの1要素が残る
            assert(ptr->mi == key || ptr->ma == key);
            uint64_t x = ptr->mi == key ? ptr->ma : ptr->mi;
            ptr->mi = ptr->ma = x;
            return true;
        }
        int shift_cnt = 1 << (ptr->u - 1);
        if(ptr->mi == key)
            ptr->mi = key = ((ptr->aux->mi << shift_cnt) | child(ptr, ptr->aux->mi)->mi);

        uint64_t idx = uint64_t(key) >> shift_cnt;
        uint64_t next_key = key & ((1uLL << shift_cnt) - 1);
        auto nex = child(ptr, idx);
        if(erase(next_key, nex)){
            if(nex->mi > nex->ma)
                erase(idx, ptr->aux);
            if(ptr->ma == key){
                if(ptr->aux->mi > ptr->aux->ma)
                    ptr->ma = ptr->mi;
                else
                    ptr->ma = ((ptr->aux->ma << shift_cnt) | child(ptr, ptr->aux->ma)->ma);
            }
            return true;
        }
        else
            return false;
    }

    uint32_t lower_bound(uint64_t key, Node* ptr = nullptr){
        if(ptr == nullptr)
            ptr = root;
        if(ptr->u == 0){
            assert(key <= ptr->ma);
            return key <= ptr->mi ? ptr->mi : ptr->ma;
        }
        if(key <= ptr->mi){
            assert(ptr->mi != NULL_FLAG);
            return ptr->mi;
        }
        int shift_cnt = 1 << (ptr->u - 1);
        uint64_t idx = uint64_t(key) >> shift_cnt;
        uint64_t next_key = key & ((1uLL << shift_cnt) - 1);

        auto nex = child(ptr, idx);
        if(nex->mi != NULL_FLAG && next_key <= nex->ma){
            return (idx << shift_cnt) | lower_bound(next_key, nex);
        }

        uint64_t i = lower_bound(idx + 1, ptr->aux);
        return (i << shift_cnt) | child(ptr, i)->mi;
    }
};

#line 10 "verify/veb2_set.test.cpp"

signed main(){
    int n;
    cin >> n;
    VanEmdeBoasTree<32> b;
    vector<int> type(n);
    vector<int> v(n, 0);
    for(int i = 0; i < n; ++i)
        scanf("%d%d", &type[i], &v[i]);

    int m = 0;

    for(int i = 0; i < n; ++i){
        int x = v[i];
        if(type[i] == 0){
            m += b.insert(x);
            printf("%d\n", m);
        }
        else if(type[i] == 1){
            printf("%d\n", b.lower_bound(x) == x);
        }
        else if(type[i] == 2){
            m -= b.erase(x);
        }
    }
}


```
{% endraw %}

<a href="../../index.html">Back to top page</a>

