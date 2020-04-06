template <typename T, typename U>
struct SkipList{

    static uint32_t rnd(){
        static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 0; // time(0);
        uint32_t t = x ^ (x << 11);
        x = y, y = z, z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    }

    struct Node{
        int height;
        vector<Node*> next, prev;
        vector<T> sum;
        vector<U> lazy;
        vector<int> size;
        Node(T val, int height, U op_u) : height(height), next(height, nullptr), prev(height, nullptr), sum(height, val), lazy(height, op_u), size(height, 1){}
    };

    using NodePtr = Node*;
    int max_height;
    NodePtr front, back;
    function<T(T, T)> f;
    function<T(T, U, int)> g;
    function<U(U, U)> h;
    T op_t;
    U op_u;

    SkipList(function<T(T, T)> f, function<T(T, U, int)> g, function<U(U, U)> h, T op_t, U op_u) : max_height(0), f(f), g(g), h(h), op_t(op_t), op_u(op_u){
        front = new Node(op_t, 32, op_u);
        back = new Node(op_t, 32, op_u);
        front->next[0] = back;
        back->prev[0] = front;
    }

    int size(){
        return front->size[max_height] - 1;
    }

    T get_val(NodePtr ptr, int height){
        return ptr->lazy[height] == op_u ? ptr->sum[height] : g(ptr->sum[height], ptr->lazy[height], ptr->size[height]);
    }

    NodePtr insert_next(NodePtr pre, T key){
        uint32_t r = max(rnd(), uint32_t(1));
        int height = __builtin_ffs(r);
        while(max_height < height){
            ++max_height;
            front->size[max_height] = front->size[max_height - 1];
            front->next[max_height] = back;
            back->prev[max_height] = front;
            front->sum[max_height] = front->sum[max_height - 1];
            front->lazy[max_height] = front->lazy[max_height - 1];
            front->lazy[max_height - 1] = op_u;
        }
        NodePtr node = new Node(key, height, op_u);
        vector<pair<NodePtr, int>> node_list = get_list(pre);
        for(int i = node_list.size() - 1; i >= 0; --i)
            eval(node_list[i].first, node_list[i].second);
        int pre_size = 1;
        T pre_sum = pre->sum[0];
        T nex_sum = key;
        NodePtr nex = pre->next[0];
        for(int i = 0; i <= max_height; ++i){
            ++pre->size[i];
            if(i < height){
                pre->next[i] = node;
                node->next[i] = nex;
                nex->prev[i] = node;
                node->prev[i] = pre;
                int range_size = pre->size[i];
                pre->size[i] = pre_size;
                pre->sum[i] = pre_sum;
                node->size[i] = range_size - pre_size;
                node->sum[i] = nex_sum;
            }
            else{
                pre->sum[i] = f(pre_sum, nex_sum);
            }
            for(; pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i]){
                pre_sum = f(get_val(pre->prev[i], i), pre_sum);
                pre_size += pre->prev[i]->size[i];
            }
            for(; nex->height == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]){
                nex_sum = f(nex_sum, get_val(nex, i));
            }
        }
		return node;
    }

    // idx番目(idx=0なら先頭)に挿入する
    NodePtr insert_index(int idx, T key){
        NodePtr pre = access(idx - 1);
        return insert_next(pre, key);
    }

    NodePtr insert_key(T key){
        NodePtr pre = lower_bound(key)->prev[0];
        return insert_next(pre, key);
    }

    NodePtr erase(NodePtr target){
        // メモリ解放はしない(してもいいけど)
        int height = target->height;
        NodePtr pre = target->prev[0];
        NodePtr nex = target->next[0];
		NodePtr ret = nex;
        vector<pair<NodePtr, int>> node_list = get_list(pre, target);
        for(int i = node_list.size() - 1; i >= 0; --i)
            eval(node_list[i].first, node_list[i].second);
        T sum = pre->sum[0];
        for(int i = 0; i <= max_height; ++i){
            pre->sum[i] = sum;
            --pre->size[i];
            if(i < height){
                pre->next[i] = nex;
                nex->prev[i] = pre;
                pre->size[i] += target->size[i];
            }
            for(; pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i])
                sum = f(get_val(pre->prev[i], i), sum);
            for(; nex->height == i + 1 && nex->next[i] != nullptr; nex = nex->next[i])
                sum = f(sum, get_val(nex, i));
        }
		return ret;
    }

    NodePtr erase_index(int idx){
        NodePtr target = access(idx);
        return erase(target);
    }

    NodePtr erase_key(T key){
        NodePtr target = lower_bound(key);
        if(target == back || target->sum[0] != key)
            return target;
        return erase(target);
    }

    NodePtr lower_bound(T key){
        NodePtr pre = front;
        for(int i = max_height; i >= 0; --i)
            for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->sum[0] < key; pre = pre->next[i]);
        return pre->next[0];
    }

    NodePtr upper_bound(T key){
        NodePtr pre = front;
        for(int i = max_height; i >= 0; --i)
            for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->sum[0] <= key; pre = pre->next[i]);
        return pre->next[0];
    }

    bool contains(T key){
        NodePtr ptr = lower_bound(key);
        return ptr != back && ptr->key == key;
    }

    // (k個先のノード, [ptr, ptr + k)を覆う区間のリスト)を返す
    pair<NodePtr, vector<pair<NodePtr, int>>> kth_next(NodePtr ptr, int k){
        vector<pair<NodePtr, int>> node_list;
        for(; ptr->size[ptr->height - 1] <= k; ptr = ptr->next[ptr->height - 1]){
            k -= ptr->size[ptr->height - 1];
            node_list.emplace_back(ptr, ptr->height - 1);
        }
        for(int i = ptr->height - 2; k; --i)
            for(; ptr->size[i] <= k; ptr = ptr->next[i]){
                k -= ptr->size[i];
                node_list.emplace_back(ptr, i);
            }
        return make_pair(ptr, node_list);
    }

    // 0-indexedでアクセスする
    NodePtr access(int idx){
        ++idx;
        assert(0 <= idx && idx <= size());
        NodePtr ptr = front;
        for(int i = max_height; i >= 0; --i)
            for(; i < ptr->next.size() && ptr->next[i] != back && ptr->size[i] <= idx; idx -= ptr->size[i], ptr = ptr->next[i]);
        return ptr;
    }

    vector<pair<NodePtr, int>> get_list(NodePtr ptr){
        vector<pair<NodePtr, int>> node_list;
        for(int i = 0; i <= max_height; ++i){
            node_list.emplace_back(ptr, i);
            for(; ptr->height == i + 1 && ptr->prev[i] != nullptr; ptr = ptr->prev[i]);
        }
        return node_list;
    }

    vector<pair<NodePtr, int>> get_list(NodePtr l_ptr, NodePtr r_ptr){
        NodePtr ptr = l_ptr;
        vector<pair<NodePtr, int>> ptr_list;
        for(int i = 0; i <= max_height; ++i){
            ptr_list.emplace_back(l_ptr, i);
            if(l_ptr != r_ptr)
                ptr_list.emplace_back(r_ptr, i);
            for(; l_ptr->height == i + 1 && l_ptr->prev[i] != nullptr; l_ptr = l_ptr->prev[i]);
            for(; r_ptr->height == i + 1 && r_ptr->prev[i] != nullptr; r_ptr = r_ptr->prev[i]);
        }
        return ptr_list;
    }

    vector<NodePtr> get_child(NodePtr ptr, int height){
        vector<NodePtr> node_vec;
        if(height == 0)
            return node_vec;
        int diff = ptr->size[height];
        for(; diff; ptr = ptr->next[height - 1]){
            diff -= ptr->size[height - 1];
            node_vec.emplace_back(ptr);
        }
        return node_vec;
    }

    void eval(NodePtr ptr, int height){
        U lazy = ptr->lazy[height];
        if(lazy == op_u)
            return;
        ptr->sum[height] = get_val(ptr, height);
        vector<NodePtr> child_list = get_child(ptr, height);
        for(auto child : child_list)
            child->lazy[height - 1] = h(child->lazy[height - 1], lazy);
        ptr->lazy[height] = op_u;
    }

    T get(int idx){
        NodePtr ptr = access(idx);
        vector<pair<NodePtr, int>> node_list = get_list(ptr);
        T sum = node_list[0].first->sum[0];
        for(int i = node_list.size() - 1; i >= 0; --i){
            NodePtr node = node_list[i].first;
            int height = node_list[i].second;
            sum = g(sum, node->lazy[height], node->size[height]);
        }
        return sum;
    }

    T get(int l, int r){
        NodePtr l_ptr = access(l);
        NodePtr r_ptr;
        vector<pair<NodePtr, int>> segment_list;
        tie(r_ptr, segment_list) = kth_next(l_ptr, r - l);
        r_ptr = r_ptr->prev[0];
        vector<pair<NodePtr, int>> ptr_list = get_list(l_ptr, r_ptr);
        for(int i = ptr_list.size() - 1; i >= 0; --i)
            eval(ptr_list[i].first, ptr_list[i].second);
        T sum = op_t;
        for(auto p : segment_list){
            NodePtr ptr = p.first;
            int height = p.second;
            sum = f(sum, get_val(ptr, height));
        }
        return sum;
    }

    void update(int l, int r, U val){
        NodePtr l_ptr = access(l);
        NodePtr r_ptr;
        vector<pair<NodePtr, int>> segment_list;
        tie(r_ptr, segment_list) = kth_next(l_ptr, r - l);
        r_ptr = r_ptr->prev[0];
        vector<pair<NodePtr, int>> ptr_list = get_list(l_ptr, r_ptr);
        for(int i = ptr_list.size() - 1; i >= 0; --i)
            eval(ptr_list[i].first, ptr_list[i].second);
        for(auto p : segment_list){
            int height = p.second;
            NodePtr ptr = p.first;
            ptr->lazy[height] = h(ptr->lazy[height], val);
        }
        for(auto p : ptr_list){
            NodePtr node = p.first;
            int height = p.second;
            if(!height)
                continue;
            vector<NodePtr> child_list = get_child(node, height);
            T sum = op_t;
            for(auto child : child_list)
                sum = f(sum, get_val(child, height - 1));
            node->sum[height] = sum;
        }
    }

    void print(bool eval_flag = false){
        int idx = -1;
        for(NodePtr node = front; node != nullptr; node = node->next[0], ++idx){
            if(node == front || node == back)
                printf("  null: ");
            else
                printf("%6d: ", eval_flag ? get(idx) : node->sum[0]);
            for(int i = 0; i < node->height; ++i)
                printf("%2d: ", eval_flag ? get_val(node, i) : node->sum[i]);
                // cout << node->size[i] << " ";
            cout << endl;
        }
        cout << endl;
    }
};
