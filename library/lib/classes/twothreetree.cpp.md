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


# :heavy_check_mark: lib/classes/twothreetree.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/twothreetree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-20 22:13:13+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/twothreetree.test.cpp.html">verify/twothreetree.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T>
struct TwoThreeTree{
    struct Node{
        int siz;
        bool leaf;
        T mi;
        vector<T> v;
        vector<int> c;
        Node(T val) : siz(1), leaf(true), v(1, val), c(0), mi(val){}
        Node() : siz(0), leaf(false), v(0), c(0){}
    };
    MemoryPool<Node> pool;
    int root;
    TwoThreeTree() : root(-1){}

    int size(){return root == -1 ? 0 : pool[root].siz;}

    int insert(T x, int idx){
        Node& node = pool[idx];
        if(node.leaf){
            // 葉は無視するため
            int ins = 0;
            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);
            for(; ins < node.v.size(); ++ins)
                swap(x, node.v[ins]);
            node.v.emplace_back(x);
            node.mi = node.v[0];
        }
        else{
            int ins = 0;
            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);
            int ret = insert(x, node.c[ins]);
            if(ret != -1){
                T key = pool[ret].mi;
                for(; ins < node.v.size(); ++ins){
                    swap(key, node.v[ins]);
                    swap(ret, node.c[ins + 1]);
                }
                node.v.emplace_back(key);
                node.c.emplace_back(ret);
            }
            node.mi = pool[node.c[0]].mi;
        }
        ++node.siz;
        if(node.v.size() > 2){
            assert(node.v.size() == 3);
            assert(node.leaf || node.c.size() == 4);
            int new_idx = pool.alloc();
            auto& new_node = pool[new_idx];
            new_node.c.clear();
            new_node.c.shrink_to_fit();
            assert(new_node.c.empty());
            new_node.leaf = node.leaf;
            if(node.leaf){
                new_node.v = {node.v[2]};
                new_node.mi = node.v[2];
                node.v.pop_back();
                new_node.siz = 1;
                --node.siz;
            }
            else{
                node.v = {node.v[0]};
                new_node.v = {node.v[2]};
                new_node.c = {node.c[2], node.c[3]};
                new_node.mi = pool[node.c[2]].mi;
                node.c = {node.c[0], node.c[1]};

                new_node.siz = pool[new_node.c[0]].siz + pool[new_node.c[1]].siz;
                node.siz -= new_node.siz;
            }
            assert(!node.leaf || node.c.empty());
            return new_idx;
        }
        return -1;
    }

    void insert(T x){
        if(root == -1){
            root = pool.alloc();
            pool[root] = Node(x);
            assert(pool[root].c.empty());
        }
        else{
            int res = insert(x, root);
            if(res != -1){
                int new_idx = pool.alloc();
                auto& new_node = pool[new_idx];
                new_node.leaf = false;
                new_node.v = {pool[res].mi};
                new_node.c = {root, res};
                new_node.mi = pool[root].mi;
                new_node.siz = pool[root].siz + pool[res].siz;
                assert(new_node.v.size() == 1);
                assert(new_node.c.size() == 2);
                root = new_idx;
            }
        }
        int idx = root;
        while(!pool[idx].leaf)
            idx = pool[idx].c[0];
    }

    // (削除できたか, 該当ノードが削除されたか)
    short erase(T x, int idx){
        Node& node = pool[idx];
        if(node.leaf){
            if(node.v.size() == 1){
                if(node.v[0] != x)
                    return 0;
                return 2;
            }
            else{
                assert(node.v.size() == 2);
                bool fl = (node.v[1] == x);
                if(node.v[fl] != x)
                    return 0;
                node.v = {node.v[fl ^ 1]};
                node.mi = node.v[0];
                --node.siz;
                return 1;
            }
        }
        else{
            int ins = 0;
            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);
            short res = erase(x, node.c[ins]);
            node.mi = pool[node.c[0]].mi;
            if(res)
                --node.siz;
            if(res == 3){
                // 子はまだ削除されてないので, 兄弟で併合する処理を書く
                assert(node.c.size() == 2 || node.c.size() == 3);
                // 兄弟からノードを取ってくる
                if(ins + 1 < node.c.size() && pool[node.c[ins + 1]].v.size() == 2){
                    // 右とマージ
                    Node& target = pool[node.c[ins]];
                    Node& bro = pool[node.c[ins + 1]];
                    assert(target.v.size() == 1);
                    // target.v = {target.v[0]};
                    target.v = {pool[bro.c[0]].mi};
                    bro.v = {bro.v[1]};
                    bro.siz -= pool[bro.c[0]].siz;
                    target.siz += pool[bro.c[0]].siz;
                    target.c = {target.c[0], bro.c[0]};
                    bro.c = {bro.c[1], bro.c[2]};
                    node.v[ins] = bro.mi = pool[bro.c[0]].mi;
                }
                else if(ins && pool[node.c[ins - 1]].v.size() == 2){
                    // 左とマージ
                    Node& bro = pool[node.c[ins - 1]];
                    Node& target = pool[node.c[ins]];
                    bro.siz -= pool[bro.c[2]].siz;
                    target.siz += pool[bro.c[2]].siz;
                    target.c = {bro.c[2], target.c[0]};
                    target.v[0] = pool[target.c[1]].mi;
                    bro.v.pop_back();
                    bro.c.pop_back();
                    node.v[ins - 1] = target.mi = pool[target.c[0]].mi;
                }
                else{
                    // 親のノードが2つなので削除して解決するパターン
                    if(node.v.size() == 2){
                        // マージした後に解決するパターン
                        if(ins + 1 < node.v.size()){
                            // 右とマージして解決させる
                            Node& target = pool[node.c[ins]];
                            Node& bro = pool[node.c[ins + 1]];
                            assert(target.v.size() == 1 && target.c.size() == 1);
                            if(!(bro.v.size() == 1 && bro.c.size() == 2)){
                                print();
                            }
                            assert(bro.v.size() == 1 && bro.c.size() == 2);
                            target.siz += bro.siz;
                            target.v = {pool[bro.c[0]].mi, pool[bro.c[1]].mi};
                            target.c = {target.c[0], bro.c[0], bro.c[1]};
                        }
                        else{
                            --ins;
                            Node& target = pool[node.c[ins + 1]];
                            Node& bro = pool[node.c[ins]];
                            assert(target.v.size() == 1 && target.c.size() == 1);
                            assert(bro.v.size() == 1 && bro.c.size() == 2);
                            bro.siz += target.siz;
                            bro.v = {pool[bro.c[1]].mi, pool[target.c[0]].mi};
                            bro.c.emplace_back(target.c[0]);
                        }
                        ++ins;
                        for(; ins < node.v.size(); ++ins){
                            if(ins + 1 != node.v.size())
                                swap(node.v[ins], node.v[ins + 1]);
                            swap(node.c[ins], node.c[ins + 1]);
                        }
                        pool.free(node.c.back());
                        node.v.pop_back();
                        node.c.pop_back();
                        assert(node.v.size() == 1);
                    }
                    else{
                        // 2つをマージするパターン
                        Node& l = pool[node.c[0]];
                        Node& r = pool[node.c[1]];
                        assert(l.c.size() + r.c.size() == 3);
                        l.c.insert(l.c.end(), r.c.begin(), r.c.end());
                        assert(l.c.size() == 3);
                        l.siz += r.siz;
                        l.v = {pool[l.c[1]].mi, pool[l.c[2]].mi};
                        pool.free(node.c[1]);
                        node.c.pop_back();
                        assert(node.c.size() == 1);
                        node.v = {pool[l.c[1]].mi};
                        node.mi = l.mi;
                        node.siz = l.siz;
                        return 3;
                    }
                }
                node.v[0] = pool[node.c[1]].mi;
                node.mi = pool[node.c[0]].mi;
                return 1;
            }
            else if(res == 2){
                if(node.v.size() == 2){
                    pool.free(node.c[ins]);
                    for(; ins < node.v.size(); ++ins){
                        if(ins + 1 != node.v.size())
                            swap(node.v[ins], node.v[ins + 1]);
                        swap(node.c[ins], node.c[ins + 1]);
                    }
                    node.v.pop_back();
                    node.c.pop_back();
                    node.mi = pool[node.c[0]].mi;
                    return 1;
                }
                else{
                    assert(node.v.size() == 1);
                    assert(node.c.size() == 2);
                    // 兄弟ノード分の処理を親に任せるようにする
                    Node& ch = pool[node.c[ins ^ 1]];
                    if(ch.v.size() == 2){
                        vector<int> vs = ch.v;
                        vector<int> cs = ch.c;
                        pool[node.c[0]].siz = pool[node.c[1]].siz = 1;
                        pool[node.c[0]].v = {vs[0]};
                        pool[node.c[1]].v = {vs[1]};
                        pool[node.c[0]].mi = pool[node.c[0]].v[0];
                        node.v[0] = pool[node.c[1]].mi = pool[node.c[1]].v[0];
                        node.siz = 2;
                        node.mi = pool[node.c[0]].mi;
                        return 1;
                    }
                    node.c = {node.c[ins ^ 1]};
                    assert(ch.v.size() == 1);
                    node.v = {ch.mi};
                    node.mi = ch.mi;
                    node.siz = ch.siz;
                    assert(node.c.size() == 1);
                    return 3;
                }
            }
            if(ins)
                node.v[ins - 1] = pool[node.c[ins]].mi;
            return res;
        }
    }

    bool erase(T x){
        if(root == -1)
            return false;
        int res = erase(x, root);
        if(res == 2)
            root = -1;
        if(res == 3){
            // 親を見る処理で詰まってる(高さが減る)
            assert(pool[root].v.size() == 1);
            assert(pool[root].c.size() == 1);
            int new_root = pool[root].c[0];
            pool.free(root);
            root = new_root;
        }
        return res;
    }

    pair<T, bool> lower_bound(T x, int idx = -1){
        if(idx == -1)
            idx = root;
        if(root == -1)
            return make_pair(T(), false);
        bool fl = false;
        T nex_val;
        while(1){
            Node& node = pool[idx];
            int ins = 0;
            if(node.leaf){
                for(; node.v[ins] < x && ins < node.v.size(); ++ins);
                assert(node.c.empty());
                if(ins == node.v.size())
                    return make_pair(fl ? nex_val : T(), fl);
                return make_pair(pool[idx].v[ins], true);
            }
            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);
            idx = node.c[ins];
            if(ins + 1 < node.c.size()){
                fl = true;
                nex_val = pool[node.c[ins + 1]].mi;
            }
        }
    }

    void print(int idx = -1, int cnt = 0){
        if(idx == -1)
            idx = root;
        if(idx == -1){
            cout << "nil(0)[0]" << endl;
            return;
        }
        string cs = "";
        for(int i = 0; i < cnt; ++i)
            cs += ' ';
        auto& node = pool[idx];
        // cout << cs << "idx: " << idx << " val: " << node.v[0] <<  " / leaf: " << node.leaf << endl;
        for(int i = 0; i < max(node.v.size(), node.c.size()); ++i){
            if(!node.leaf){
                if(i < node.c.size()){
                    print(node.c[i], cnt + 8);
                }
            }
            if(i < node.v.size()){
                if(i == 0){
                    cout << cs << " " << node.v[i] << " (" << node.mi << "){" << node.siz << "}[" << idx << "]";
                    if(node.leaf){
                        cout << "[";
                        for(int i = 0; i < node.c.size(); ++i){
                            cout << node.c[i];
                            if(i)
                                cout << "/";
                        }
                        cout << "]" << endl;
                    }
                    else
                        cout << endl;
                }
                else
                    cout << cs << " " << node.v[i] << endl;
            }
        }
    }

    void check(int idx = -2){
        if(idx == -2){
            idx = root;
        }
        if(idx == -1)
            return;
        Node& node = pool[idx];
        if(!node.leaf){
            int siz = 0;
            assert(node.v.size() == 1 || node.v.size() == 2);
            assert(node.v.size() + 1 == node.c.size());
            T mi = pool[node.c[0]].mi;
            for(int i = 0; i < node.c.size(); ++i){
                int ch = node.c[i];
                check(ch);
                siz += pool[ch].siz;
                assert(i == 0 || mi < pool[ch].mi);
                mi = min(mi, pool[ch].mi);
				assert(i - 1 >= node.v.size() || (i ? node.v[i - 1] : node.mi) <= pool[node.c[i]].mi);
				assert(i >= node.v.size() || pool[node.c[i]].v.back() < node.v[i]);
            }
            assert(siz == node.siz);
            assert(mi == node.mi);
        }
        else{
            assert(node.c.empty());
            assert(node.mi == node.v[0]);
        }
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/twothreetree.cpp"
template <typename T>
struct TwoThreeTree{
    struct Node{
        int siz;
        bool leaf;
        T mi;
        vector<T> v;
        vector<int> c;
        Node(T val) : siz(1), leaf(true), v(1, val), c(0), mi(val){}
        Node() : siz(0), leaf(false), v(0), c(0){}
    };
    MemoryPool<Node> pool;
    int root;
    TwoThreeTree() : root(-1){}

    int size(){return root == -1 ? 0 : pool[root].siz;}

    int insert(T x, int idx){
        Node& node = pool[idx];
        if(node.leaf){
            // 葉は無視するため
            int ins = 0;
            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);
            for(; ins < node.v.size(); ++ins)
                swap(x, node.v[ins]);
            node.v.emplace_back(x);
            node.mi = node.v[0];
        }
        else{
            int ins = 0;
            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);
            int ret = insert(x, node.c[ins]);
            if(ret != -1){
                T key = pool[ret].mi;
                for(; ins < node.v.size(); ++ins){
                    swap(key, node.v[ins]);
                    swap(ret, node.c[ins + 1]);
                }
                node.v.emplace_back(key);
                node.c.emplace_back(ret);
            }
            node.mi = pool[node.c[0]].mi;
        }
        ++node.siz;
        if(node.v.size() > 2){
            assert(node.v.size() == 3);
            assert(node.leaf || node.c.size() == 4);
            int new_idx = pool.alloc();
            auto& new_node = pool[new_idx];
            new_node.c.clear();
            new_node.c.shrink_to_fit();
            assert(new_node.c.empty());
            new_node.leaf = node.leaf;
            if(node.leaf){
                new_node.v = {node.v[2]};
                new_node.mi = node.v[2];
                node.v.pop_back();
                new_node.siz = 1;
                --node.siz;
            }
            else{
                node.v = {node.v[0]};
                new_node.v = {node.v[2]};
                new_node.c = {node.c[2], node.c[3]};
                new_node.mi = pool[node.c[2]].mi;
                node.c = {node.c[0], node.c[1]};

                new_node.siz = pool[new_node.c[0]].siz + pool[new_node.c[1]].siz;
                node.siz -= new_node.siz;
            }
            assert(!node.leaf || node.c.empty());
            return new_idx;
        }
        return -1;
    }

    void insert(T x){
        if(root == -1){
            root = pool.alloc();
            pool[root] = Node(x);
            assert(pool[root].c.empty());
        }
        else{
            int res = insert(x, root);
            if(res != -1){
                int new_idx = pool.alloc();
                auto& new_node = pool[new_idx];
                new_node.leaf = false;
                new_node.v = {pool[res].mi};
                new_node.c = {root, res};
                new_node.mi = pool[root].mi;
                new_node.siz = pool[root].siz + pool[res].siz;
                assert(new_node.v.size() == 1);
                assert(new_node.c.size() == 2);
                root = new_idx;
            }
        }
        int idx = root;
        while(!pool[idx].leaf)
            idx = pool[idx].c[0];
    }

    // (削除できたか, 該当ノードが削除されたか)
    short erase(T x, int idx){
        Node& node = pool[idx];
        if(node.leaf){
            if(node.v.size() == 1){
                if(node.v[0] != x)
                    return 0;
                return 2;
            }
            else{
                assert(node.v.size() == 2);
                bool fl = (node.v[1] == x);
                if(node.v[fl] != x)
                    return 0;
                node.v = {node.v[fl ^ 1]};
                node.mi = node.v[0];
                --node.siz;
                return 1;
            }
        }
        else{
            int ins = 0;
            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);
            short res = erase(x, node.c[ins]);
            node.mi = pool[node.c[0]].mi;
            if(res)
                --node.siz;
            if(res == 3){
                // 子はまだ削除されてないので, 兄弟で併合する処理を書く
                assert(node.c.size() == 2 || node.c.size() == 3);
                // 兄弟からノードを取ってくる
                if(ins + 1 < node.c.size() && pool[node.c[ins + 1]].v.size() == 2){
                    // 右とマージ
                    Node& target = pool[node.c[ins]];
                    Node& bro = pool[node.c[ins + 1]];
                    assert(target.v.size() == 1);
                    // target.v = {target.v[0]};
                    target.v = {pool[bro.c[0]].mi};
                    bro.v = {bro.v[1]};
                    bro.siz -= pool[bro.c[0]].siz;
                    target.siz += pool[bro.c[0]].siz;
                    target.c = {target.c[0], bro.c[0]};
                    bro.c = {bro.c[1], bro.c[2]};
                    node.v[ins] = bro.mi = pool[bro.c[0]].mi;
                }
                else if(ins && pool[node.c[ins - 1]].v.size() == 2){
                    // 左とマージ
                    Node& bro = pool[node.c[ins - 1]];
                    Node& target = pool[node.c[ins]];
                    bro.siz -= pool[bro.c[2]].siz;
                    target.siz += pool[bro.c[2]].siz;
                    target.c = {bro.c[2], target.c[0]};
                    target.v[0] = pool[target.c[1]].mi;
                    bro.v.pop_back();
                    bro.c.pop_back();
                    node.v[ins - 1] = target.mi = pool[target.c[0]].mi;
                }
                else{
                    // 親のノードが2つなので削除して解決するパターン
                    if(node.v.size() == 2){
                        // マージした後に解決するパターン
                        if(ins + 1 < node.v.size()){
                            // 右とマージして解決させる
                            Node& target = pool[node.c[ins]];
                            Node& bro = pool[node.c[ins + 1]];
                            assert(target.v.size() == 1 && target.c.size() == 1);
                            if(!(bro.v.size() == 1 && bro.c.size() == 2)){
                                print();
                            }
                            assert(bro.v.size() == 1 && bro.c.size() == 2);
                            target.siz += bro.siz;
                            target.v = {pool[bro.c[0]].mi, pool[bro.c[1]].mi};
                            target.c = {target.c[0], bro.c[0], bro.c[1]};
                        }
                        else{
                            --ins;
                            Node& target = pool[node.c[ins + 1]];
                            Node& bro = pool[node.c[ins]];
                            assert(target.v.size() == 1 && target.c.size() == 1);
                            assert(bro.v.size() == 1 && bro.c.size() == 2);
                            bro.siz += target.siz;
                            bro.v = {pool[bro.c[1]].mi, pool[target.c[0]].mi};
                            bro.c.emplace_back(target.c[0]);
                        }
                        ++ins;
                        for(; ins < node.v.size(); ++ins){
                            if(ins + 1 != node.v.size())
                                swap(node.v[ins], node.v[ins + 1]);
                            swap(node.c[ins], node.c[ins + 1]);
                        }
                        pool.free(node.c.back());
                        node.v.pop_back();
                        node.c.pop_back();
                        assert(node.v.size() == 1);
                    }
                    else{
                        // 2つをマージするパターン
                        Node& l = pool[node.c[0]];
                        Node& r = pool[node.c[1]];
                        assert(l.c.size() + r.c.size() == 3);
                        l.c.insert(l.c.end(), r.c.begin(), r.c.end());
                        assert(l.c.size() == 3);
                        l.siz += r.siz;
                        l.v = {pool[l.c[1]].mi, pool[l.c[2]].mi};
                        pool.free(node.c[1]);
                        node.c.pop_back();
                        assert(node.c.size() == 1);
                        node.v = {pool[l.c[1]].mi};
                        node.mi = l.mi;
                        node.siz = l.siz;
                        return 3;
                    }
                }
                node.v[0] = pool[node.c[1]].mi;
                node.mi = pool[node.c[0]].mi;
                return 1;
            }
            else if(res == 2){
                if(node.v.size() == 2){
                    pool.free(node.c[ins]);
                    for(; ins < node.v.size(); ++ins){
                        if(ins + 1 != node.v.size())
                            swap(node.v[ins], node.v[ins + 1]);
                        swap(node.c[ins], node.c[ins + 1]);
                    }
                    node.v.pop_back();
                    node.c.pop_back();
                    node.mi = pool[node.c[0]].mi;
                    return 1;
                }
                else{
                    assert(node.v.size() == 1);
                    assert(node.c.size() == 2);
                    // 兄弟ノード分の処理を親に任せるようにする
                    Node& ch = pool[node.c[ins ^ 1]];
                    if(ch.v.size() == 2){
                        vector<int> vs = ch.v;
                        vector<int> cs = ch.c;
                        pool[node.c[0]].siz = pool[node.c[1]].siz = 1;
                        pool[node.c[0]].v = {vs[0]};
                        pool[node.c[1]].v = {vs[1]};
                        pool[node.c[0]].mi = pool[node.c[0]].v[0];
                        node.v[0] = pool[node.c[1]].mi = pool[node.c[1]].v[0];
                        node.siz = 2;
                        node.mi = pool[node.c[0]].mi;
                        return 1;
                    }
                    node.c = {node.c[ins ^ 1]};
                    assert(ch.v.size() == 1);
                    node.v = {ch.mi};
                    node.mi = ch.mi;
                    node.siz = ch.siz;
                    assert(node.c.size() == 1);
                    return 3;
                }
            }
            if(ins)
                node.v[ins - 1] = pool[node.c[ins]].mi;
            return res;
        }
    }

    bool erase(T x){
        if(root == -1)
            return false;
        int res = erase(x, root);
        if(res == 2)
            root = -1;
        if(res == 3){
            // 親を見る処理で詰まってる(高さが減る)
            assert(pool[root].v.size() == 1);
            assert(pool[root].c.size() == 1);
            int new_root = pool[root].c[0];
            pool.free(root);
            root = new_root;
        }
        return res;
    }

    pair<T, bool> lower_bound(T x, int idx = -1){
        if(idx == -1)
            idx = root;
        if(root == -1)
            return make_pair(T(), false);
        bool fl = false;
        T nex_val;
        while(1){
            Node& node = pool[idx];
            int ins = 0;
            if(node.leaf){
                for(; node.v[ins] < x && ins < node.v.size(); ++ins);
                assert(node.c.empty());
                if(ins == node.v.size())
                    return make_pair(fl ? nex_val : T(), fl);
                return make_pair(pool[idx].v[ins], true);
            }
            for(; node.v[ins] <= x && ins < node.v.size(); ++ins);
            idx = node.c[ins];
            if(ins + 1 < node.c.size()){
                fl = true;
                nex_val = pool[node.c[ins + 1]].mi;
            }
        }
    }

    void print(int idx = -1, int cnt = 0){
        if(idx == -1)
            idx = root;
        if(idx == -1){
            cout << "nil(0)[0]" << endl;
            return;
        }
        string cs = "";
        for(int i = 0; i < cnt; ++i)
            cs += ' ';
        auto& node = pool[idx];
        // cout << cs << "idx: " << idx << " val: " << node.v[0] <<  " / leaf: " << node.leaf << endl;
        for(int i = 0; i < max(node.v.size(), node.c.size()); ++i){
            if(!node.leaf){
                if(i < node.c.size()){
                    print(node.c[i], cnt + 8);
                }
            }
            if(i < node.v.size()){
                if(i == 0){
                    cout << cs << " " << node.v[i] << " (" << node.mi << "){" << node.siz << "}[" << idx << "]";
                    if(node.leaf){
                        cout << "[";
                        for(int i = 0; i < node.c.size(); ++i){
                            cout << node.c[i];
                            if(i)
                                cout << "/";
                        }
                        cout << "]" << endl;
                    }
                    else
                        cout << endl;
                }
                else
                    cout << cs << " " << node.v[i] << endl;
            }
        }
    }

    void check(int idx = -2){
        if(idx == -2){
            idx = root;
        }
        if(idx == -1)
            return;
        Node& node = pool[idx];
        if(!node.leaf){
            int siz = 0;
            assert(node.v.size() == 1 || node.v.size() == 2);
            assert(node.v.size() + 1 == node.c.size());
            T mi = pool[node.c[0]].mi;
            for(int i = 0; i < node.c.size(); ++i){
                int ch = node.c[i];
                check(ch);
                siz += pool[ch].siz;
                assert(i == 0 || mi < pool[ch].mi);
                mi = min(mi, pool[ch].mi);
				assert(i - 1 >= node.v.size() || (i ? node.v[i - 1] : node.mi) <= pool[node.c[i]].mi);
				assert(i >= node.v.size() || pool[node.c[i]].v.back() < node.v[i]);
            }
            assert(siz == node.siz);
            assert(mi == node.mi);
        }
        else{
            assert(node.c.empty());
            assert(node.mi == node.v[0]);
        }
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

