// サイズを保つようにsplit/mergeをするy-fast trie
template <typename T, int W = 31, T HASHMAP_NULL = (1LL << W) - 1, T HASHMAP_DEL = (1LL << W) - 2>
struct YFastTrie2{

    using SplayNode = typename SplayTree<T>::NodePtr;
    int n;
    XFastTrie_yft<T, W> xft;
    SplayTree<T> splay;

    YFastTrie2() : n(1), xft(), splay(){
        SplayNode node = splay.make((1LL << W) - 1);
        xft.insert(node);
    }

    SplayNode lower_bound(T key){
        auto xft_ptr = xft.lower_bound(key);
        assert(xft_ptr != xft.back);
        auto res = splay.lower_bound(xft_ptr->node, key);
        xft_ptr->node = res.first;
        if(!res.second){
            xft_ptr = xft_ptr->c[1];
            xft_ptr->node = splay.access(xft_ptr->node, 0);
        }
        return xft_ptr->node;
    }

    bool insert(T key){
        auto xft_ptr = xft.lower_bound(key);
        auto res = splay.insert(xft_ptr->node, key);
        xft_ptr->node = res.first;
        n += res.second;
        split(xft_ptr);
        return res.second;
    }

    bool erase(T key){
        auto xft_ptr = xft.lower_bound(key);
        auto res = splay.erase(xft_ptr->node, key);
        assert(res.first != splay.nil);
        xft_ptr->node = res.first;
        n -= res.second;
        merge(xft_ptr);
        return res.second;
    }

    void split(typename XFastTrie_yft<T>::Node* xft_node){
        if(xft_node->node->size <= (W << 1))
            return;
        SplayNode l, r;
        tie(l, r) = splay.split(splay.access(xft_node->node, xft_node->node->size >> 1));
        xft_node->node = r;
        l = splay.access(l, l->size - 1);
        xft.insert(l);
    }

    void merge(typename XFastTrie_yft<T>::Node* xft_ptr){
        if(xft_ptr->node->size >= (W >> 2))
            return;
        if(xft_ptr->c[0] != xft.front)
            merge(xft_ptr->c[0], xft_ptr);
        else if(xft_ptr->c[1] != xft.back)
            merge(xft_ptr, xft_ptr->c[1]);
    }

    void merge(typename XFastTrie_yft<T>::Node* xft_l, typename XFastTrie_yft<T>::Node* xft_r){
        xft_r->node = splay.merge(xft_l->node, xft_r->node);
        xft_l->node = nullptr;
        xft.erase(xft_l->val);
        split(xft_r);
    }
};
