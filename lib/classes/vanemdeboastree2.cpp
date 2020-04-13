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

