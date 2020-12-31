struct SLP{
    SLP *l, *r;
    long long size, left, right;
    char c;
    bool left_heavy;
    const PersistentSkewBinaryList<SLP*>* heavy_path;

    struct PairHashing{
        size_t operator()(const pair<SLP*, SLP*>& p) const{
            return hash<SLP*>()(p.first) ^ (hash<SLP*>()(p.second) << 1);
        }
    };

    static unordered_map<char, SLP*> terminal_map;
    static unordered_map<pair<SLP*, SLP*>, SLP*, PairHashing> nonterminal_map;
    bool is_terminal(){ return l == nullptr; }
private:
    SLP(char c) : l(nullptr), r(nullptr), size(1), c(c), left(0), right(1){
        heavy_path = new PersistentSkewBinaryList<SLP*>(this);
    }
    SLP(SLP *l, SLP *r) : l(l), r(r), size(l->size + r->size), left_heavy(l->size >= r->size){
        heavy_path = (left_heavy ? l : r)->heavy_path->push_front(this);
        if(left_heavy){
            left = l->left;
            right = l->right + r->size;
        }
        else{
            left = r->left - l->size;
            right = r->right;
        }
    }
    bool check(long long k){
        return left <= k && k < right;
    }
    SLP* find_lowest(PersistentSkewBinaryList<SLP*>::Node* ptr, long long k){
        if(ptr->dep == 1){
            return ptr->x->check(k) ? ptr->x : nullptr;
        }
        if(ptr->r->x->check(k))
            return find_lowest(ptr->r, k);
        else if(ptr->l->x->check(k))
            return find_lowest(ptr->l, k);
        else
            return ptr->x->check(k) ? ptr->x : nullptr;
    }
    SLP* find_lowest(const PersistentSkewBinaryList<SLP*>* ptr, long long k){
        if(ptr == nullptr || !ptr->node->x->check(k))
            return nullptr;
        auto res = find_lowest(ptr->nex, k);
        if(res != nullptr)
            return res;
        return find_lowest(ptr->node, k);
    }
    // heavyからの相対位置
    char _access(long long k){
        auto ptr = find_lowest(heavy_path, k);
        if(ptr->is_terminal())
            return ptr->c;
        // ptrの左端からの相対位置
        long long left_pos = k - ptr->left;
        if(ptr->left_heavy){
            return ptr->r->_access(left_pos - ptr->l->size + ptr->r->left);
        }
        else{
            return ptr->l->_access(left_pos + ptr->l->left);
        }
    }

public:
    static SLP* make(char c){
        if(terminal_map.find(c) == terminal_map.end())
            return terminal_map[c] = new SLP(c);
        else
            return terminal_map[c];
    }
    static SLP* make(SLP* l, SLP* r){
        auto p = make_pair(l, r);
        if(nonterminal_map.find(p) == nonterminal_map.end())
            return nonterminal_map[p] = new SLP(l, r);
        else
            return nonterminal_map[p];
    }
    char access(long long k){
        return _access(k + left);
    }
};

unordered_map<char, SLP*> SLP::terminal_map;
unordered_map<pair<SLP*, SLP*>, SLP*, SLP::PairHashing> SLP::nonterminal_map;
