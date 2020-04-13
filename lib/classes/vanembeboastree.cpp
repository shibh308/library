template <uint32_t W, uint32_t NULL_FLAG = ~0u>
struct VanEmdeBoasTree{

    // サイズ2^(2^U)のノード
    // U=0からでサイズが2, 4, 16, 256, 65536, となる
    struct Node{
        uint32_t u, ma, mi;
        Node* aux;
        vector<Node*> c;
        Node(int u, int n) : u(u), mi(NULL_FLAG), ma(0){
            if(u){
                while(n){
                    int d = min(1 << (1 << (u - 1)), n);
                    Node *node = new Node(u - 1, d);
                    c.push_back(node);
                    n -= d;
                }
                aux = new Node(u - 1, c.size());
            }
        }
    };
    Node* root;
    VanEmdeBoasTree(){
        root = new Node(32 - __builtin_clz(W - 1), 1 << W);
        insert((1 << W) - 1, root);
    }

    bool insert(uint32_t key, Node* ptr = nullptr){
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
        uint32_t idx = uint64_t(key) >> shift_cnt;
        uint32_t next_key = key & ((1uLL << shift_cnt) - 1u);

        assert(idx < ptr->c.size());

        if(ptr->c[idx]->mi > ptr->c[idx]->ma){
            insert(idx, ptr->aux);
        }
        return insert(next_key, ptr->c[idx]);
    }

    bool erase(uint32_t key, Node* ptr = nullptr){
        if(ptr == nullptr)
            ptr = root;
        if(ptr->mi > ptr->ma){
            return false;
        }
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
            i64 x = ptr->mi == key ? ptr->ma : ptr->mi;
            ptr->mi = ptr->ma = x;
            return true;
        }
        int shift_cnt = 1 << (ptr->u - 1);
        if(ptr->mi == key)
            ptr->mi = key = ((ptr->aux->mi << shift_cnt) | ptr->c[ptr->aux->mi]->mi);

        uint32_t idx = uint64_t(key) >> shift_cnt;
        uint32_t next_key = key & ((1uLL << shift_cnt) - 1u);
        auto nex = ptr->c[idx];
        if(erase(next_key, nex)){
            if(nex->mi > nex->ma)
                erase(idx, ptr->aux);
            if(ptr->ma == key){
                if(ptr->aux->mi > ptr->aux->ma)
                    ptr->ma = ptr->mi;
                else
                    ptr->ma = ((ptr->aux->ma << shift_cnt) | ptr->c[ptr->aux->ma]->ma);
            }
            return true;
        }
        else
            return false;
    }

    uint32_t lower_bound(uint32_t key, Node* ptr = nullptr){
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
        uint32_t idx = uint64_t(key) >> shift_cnt;
        uint32_t next_key = key & ((1uLL << shift_cnt) - 1u);
        assert(idx < ptr->c.size());

        auto nex = ptr->c[idx];
        if(nex->mi != NULL_FLAG && next_key <= nex->ma){
            return (idx << shift_cnt) | lower_bound(next_key, nex);
        }

        uint64_t i = lower_bound(idx + 1, ptr->aux);
        return (i << shift_cnt) | ptr->c[i]->mi;
    }
};

