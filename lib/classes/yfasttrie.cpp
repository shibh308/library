// 乱択で挿入先を決めるy-fast trie
template <typename T, int W = 31, T HASHMAP_NULL = (1LL << W) - 1, T HASHMAP_DEL = (1LL << W) - 2>
struct YFastTrie{

    static uint32_t rnd(){
        static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 0; // time(0);
        uint32_t t = x ^ (x << 11);
        x = y, y = z, z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    }

    using SplayNode = typename SplayTree<T>::NodePtr;
    int n;
    XFastTrie_yft<T, W, HASHMAP_NULL, HASHMAP_DEL> xft;
    SplayTree<T> splay;

    YFastTrie() : n(1), xft(), splay(){
        SplayNode node = splay.make((1LL << W) - 1);
        xft.insert(node);
    }

    SplayNode lower_bound(T key){
        auto xft_ptr = xft.lower_bound(key);
        assert(xft_ptr != xft.back);
        return xft_ptr->node = splay.lower_bound(xft_ptr->node, key).first;
    }

    bool insert(T key){
        auto xft_ptr = xft.lower_bound(key);
         pair<SplayNode , bool> res;
        if(xft_ptr->val == key)
            return false;
        if(rnd() % W == 0){
            res = splay.lower_bound(xft_ptr->node, key);
            assert(res.second);
            SplayNode l;
            tie(l, xft_ptr->node) = splay.split(res.first);
            assert(xft_ptr->node != splay.nil);
            res = splay.insert(l, key);
            n += res.second;
            assert(res.first != splay.nil);
            xft.insert(splay.access(res.first, res.first->size - 1));
        }
        else{
            res = splay.insert(xft_ptr->node, key);
            n += res.second;
            xft_ptr->node = res.first;
        }
        return res.second;
    }

    bool erase(T key){
        pair<SplayNode, bool> res;
        auto xft_ptr = xft.lower_bound(key);
        if(xft_ptr->val == key){
            auto r = xft_ptr->c[1];
            r->node = splay.merge(xft_ptr->node, r->node);
            res = splay.erase(r->node, key);
            r->node = res.first;
            if(res.second){
                xft_ptr->node = nullptr;
                xft.erase(xft_ptr->val);
            }
        }
        else{
            res = splay.erase(xft_ptr->node, key);
            xft_ptr->node = res.first;
        }
        n -= res.second;
        return res.second;
    }
};
