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


# :heavy_check_mark: lib/classes/xfasttrie_yft.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/xfasttrie_yft.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-11 13:43:20+09:00




## Verified with

* :heavy_check_mark: <a href="../../../verify/verify/yfastttrie2_itp.test.cpp.html">verify/yfastttrie2_itp.test.cpp</a>
* :heavy_check_mark: <a href="../../../verify/verify/yfastttrie_itp.test.cpp.html">verify/yfastttrie_itp.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
// y-fast trie用のx-fast trie
template <typename T, int W = 31, T HASHMAP_NULL = (1LL << W) - 1, T HASHMAP_DEL = (1LL << W) - 2>
struct XFastTrie_yft{
    using SplayNode = typename SplayTree<T>::NodePtr;
    struct Node{
        T val;
        int exist;
        Node* c[2];
        SplayNode node;
        Node(T val) : val(val), exist(0), node(nullptr){
            // 子が存在するなら子へのポインタを持つ
            // 葉なら左右はそれぞれprev,next
            // 左の子が存在しないなら左はprevへのショートカット
            // 右のが存在しないなら右はnextへのショートカット
            c[0] = nullptr;
            c[1] = nullptr;
        }
    };
    int n;
    Node* root;
    Node* front;
    Node* back;
    array<HashMap<T, Node*, HASHMAP_NULL, HASHMAP_DEL>, W> hashmap;

    XFastTrie_yft() : n(0), hashmap(){
        root = new Node(0);
        front = new Node(0);
        back = new Node(0);
        front->exist = 2;
        front->c[1] = back;
        back->exist = 1;
        back->c[0] = front;
        root->c[0] = back;
        root->c[1] = front;
    }

    Node* insert(SplayNode node){
        T key = node->val;
        // 存在しているノードは全部葉があると仮定する
        T val = 0;
        Node* ptr = root;
        Node* nex = nullptr;
        Node* pre = nullptr;
        bool make_flag = false;
        for(int i = W - 1; i >= 0; --i){
            bool fl = (key >> i) & 1;
            bool exist = (ptr->exist >> fl) & 1;
            if(fl)
                val += (1LL << i);
            if(!exist){
                if(!nex){
                    if(fl){
                        pre = ptr->c[1];
                        nex = pre->c[1];
                    }
                    else{
                        nex = ptr->c[0];
                        pre = nex->c[0];
                    }
                }
                make_flag = true;
                ptr->exist |= (1 << fl);
                ptr->c[fl] = new Node(val);
                hashmap[i].add(val, ptr->c[fl]);
                ptr->c[fl]->c[0] = back;
                ptr->c[fl]->c[1] = front;
            }
            ptr = ptr->c[fl];
        }
        if(!make_flag)
            return nullptr;
        ++n;
        assert(nex == back || key < nex->val);
        assert(pre == front || pre->val < key);

        ptr->node = node;
        pre->c[1] = ptr;
        ptr->c[1] = nex;
        nex->c[0] = ptr;
        ptr->c[0] = pre;
        assert(val == key && ptr->val == key);

        Node* new_node = ptr;
        ptr = root;
        for(int i = W - 1; i >= 0; --i){
            if(!(ptr->exist & 1) && (ptr->c[0] == back || key < ptr->c[0]->val)){
                ptr->c[0] = new_node;
            }
            if(!(ptr->exist & 2) && (ptr->c[1] == front || ptr->c[1]->val < key)){
                ptr->c[1] = new_node;
            }
            ptr = ptr->c[(key >> i) & 1];
        }
        return new_node;
    }

    bool erase(T key){
        Node* ptr = root;
        Node* cut_ptr = nullptr;
        bool cut_fl = false;
        stack<Node*> node_stack;
        for(int i = W - 1; i >= 0; --i){
            bool fl = (key >> i) & 1;
            if(!((ptr->exist >> fl) & 1))
                return false;
            if((ptr->exist >> (!fl)) & 1){
                while(!node_stack.empty())node_stack.pop();
                cut_ptr = ptr;
                cut_fl = fl;
            }
            else if(i != W - 1)
                node_stack.push(ptr);
            ptr = ptr->c[fl];
        }
        Node* target = ptr;
        Node* pre = target->c[0];
        Node* nex = target->c[1];
        pre->c[1] = nex;
        nex->c[0] = pre;
        int h = 0;
        for(int i = 0; !node_stack.empty(); ++i){
            Node* node = node_stack.top();
            hashmap[i + 1].erase(node->val);
            node_stack.pop();
            assert(node != target);
        }
        hashmap[0].erase(key);
        if(!cut_ptr){
            *this = XFastTrie_yft();
            return true;
        }
        cut_ptr->c[cut_fl] = cut_fl ? pre : nex;
        cut_ptr->exist &= ~(1 << cut_fl);
        ptr = root;
        if(target->val != key)
            return false;
        for(int i = W - 1; i >= 0; --i){
            bool fl = (key >> i) & 1;
            if(ptr->c[0] == target){
                ptr->c[0] = nex;
            }
            if(ptr->c[1] == target){
                ptr->c[1] = pre;
            }
            if(!(ptr->exist & (1 << fl)))
                break;
            ptr = ptr->c[fl];
        }
        --n;
        delete(target);
        return true;
    }

    Node* lower_bound(T key){
        Node* ptr = root;
        int lb = W, rb = -1;
        while(lb - rb > 1){
            int mid = (lb + rb) >> 1;
            bool fl;
            Node* res;
            tie(res, fl) = hashmap[mid].find(key & ~((1LL << mid) - 1));
            if(fl)
                ptr = res;
            (fl ? lb : rb) = mid;
        }
        if(!lb)return ptr;
        int fl = (key >> rb) & 1;
        return fl ? ptr->c[fl]->c[1] : ptr->c[fl];
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/xfasttrie_yft.cpp"
// y-fast trie用のx-fast trie
template <typename T, int W = 31, T HASHMAP_NULL = (1LL << W) - 1, T HASHMAP_DEL = (1LL << W) - 2>
struct XFastTrie_yft{
    using SplayNode = typename SplayTree<T>::NodePtr;
    struct Node{
        T val;
        int exist;
        Node* c[2];
        SplayNode node;
        Node(T val) : val(val), exist(0), node(nullptr){
            // 子が存在するなら子へのポインタを持つ
            // 葉なら左右はそれぞれprev,next
            // 左の子が存在しないなら左はprevへのショートカット
            // 右のが存在しないなら右はnextへのショートカット
            c[0] = nullptr;
            c[1] = nullptr;
        }
    };
    int n;
    Node* root;
    Node* front;
    Node* back;
    array<HashMap<T, Node*, HASHMAP_NULL, HASHMAP_DEL>, W> hashmap;

    XFastTrie_yft() : n(0), hashmap(){
        root = new Node(0);
        front = new Node(0);
        back = new Node(0);
        front->exist = 2;
        front->c[1] = back;
        back->exist = 1;
        back->c[0] = front;
        root->c[0] = back;
        root->c[1] = front;
    }

    Node* insert(SplayNode node){
        T key = node->val;
        // 存在しているノードは全部葉があると仮定する
        T val = 0;
        Node* ptr = root;
        Node* nex = nullptr;
        Node* pre = nullptr;
        bool make_flag = false;
        for(int i = W - 1; i >= 0; --i){
            bool fl = (key >> i) & 1;
            bool exist = (ptr->exist >> fl) & 1;
            if(fl)
                val += (1LL << i);
            if(!exist){
                if(!nex){
                    if(fl){
                        pre = ptr->c[1];
                        nex = pre->c[1];
                    }
                    else{
                        nex = ptr->c[0];
                        pre = nex->c[0];
                    }
                }
                make_flag = true;
                ptr->exist |= (1 << fl);
                ptr->c[fl] = new Node(val);
                hashmap[i].add(val, ptr->c[fl]);
                ptr->c[fl]->c[0] = back;
                ptr->c[fl]->c[1] = front;
            }
            ptr = ptr->c[fl];
        }
        if(!make_flag)
            return nullptr;
        ++n;
        assert(nex == back || key < nex->val);
        assert(pre == front || pre->val < key);

        ptr->node = node;
        pre->c[1] = ptr;
        ptr->c[1] = nex;
        nex->c[0] = ptr;
        ptr->c[0] = pre;
        assert(val == key && ptr->val == key);

        Node* new_node = ptr;
        ptr = root;
        for(int i = W - 1; i >= 0; --i){
            if(!(ptr->exist & 1) && (ptr->c[0] == back || key < ptr->c[0]->val)){
                ptr->c[0] = new_node;
            }
            if(!(ptr->exist & 2) && (ptr->c[1] == front || ptr->c[1]->val < key)){
                ptr->c[1] = new_node;
            }
            ptr = ptr->c[(key >> i) & 1];
        }
        return new_node;
    }

    bool erase(T key){
        Node* ptr = root;
        Node* cut_ptr = nullptr;
        bool cut_fl = false;
        stack<Node*> node_stack;
        for(int i = W - 1; i >= 0; --i){
            bool fl = (key >> i) & 1;
            if(!((ptr->exist >> fl) & 1))
                return false;
            if((ptr->exist >> (!fl)) & 1){
                while(!node_stack.empty())node_stack.pop();
                cut_ptr = ptr;
                cut_fl = fl;
            }
            else if(i != W - 1)
                node_stack.push(ptr);
            ptr = ptr->c[fl];
        }
        Node* target = ptr;
        Node* pre = target->c[0];
        Node* nex = target->c[1];
        pre->c[1] = nex;
        nex->c[0] = pre;
        int h = 0;
        for(int i = 0; !node_stack.empty(); ++i){
            Node* node = node_stack.top();
            hashmap[i + 1].erase(node->val);
            node_stack.pop();
            assert(node != target);
        }
        hashmap[0].erase(key);
        if(!cut_ptr){
            *this = XFastTrie_yft();
            return true;
        }
        cut_ptr->c[cut_fl] = cut_fl ? pre : nex;
        cut_ptr->exist &= ~(1 << cut_fl);
        ptr = root;
        if(target->val != key)
            return false;
        for(int i = W - 1; i >= 0; --i){
            bool fl = (key >> i) & 1;
            if(ptr->c[0] == target){
                ptr->c[0] = nex;
            }
            if(ptr->c[1] == target){
                ptr->c[1] = pre;
            }
            if(!(ptr->exist & (1 << fl)))
                break;
            ptr = ptr->c[fl];
        }
        --n;
        delete(target);
        return true;
    }

    Node* lower_bound(T key){
        Node* ptr = root;
        int lb = W, rb = -1;
        while(lb - rb > 1){
            int mid = (lb + rb) >> 1;
            bool fl;
            Node* res;
            tie(res, fl) = hashmap[mid].find(key & ~((1LL << mid) - 1));
            if(fl)
                ptr = res;
            (fl ? lb : rb) = mid;
        }
        if(!lb)return ptr;
        int fl = (key >> rb) & 1;
        return fl ? ptr->c[fl]->c[1] : ptr->c[fl];
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

