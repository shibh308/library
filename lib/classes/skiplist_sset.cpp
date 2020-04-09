template <typename T>
struct SSet{

    static uint32_t rnd(){
        static uint32_t x = 123456789, y = 362436069, z = 521288629, w = time(0);
        uint32_t t = x ^(x << 11);
        x = y, y = z, z = w;
        w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
        return w;
    }

    struct Node{
        int height;
        T val;
        vector<Node *> next, prev;
        vector<int> size;
        Node(T val, int height) : val(val), height(height), next(height, nullptr), prev(height, nullptr), size(height, 1){}
    };

    using NodePtr = Node*;
    int max_height;
    NodePtr front, back;

    SSet(Node* fr = nullptr, Node* ba = nullptr) : max_height(0), front(fr), back(ba){
        if(front == nullptr){
            front = new Node(T(), 21);
            back = new Node(T(), 21);
            front->next[0] = back;
            back->prev[0] = front;
        }
    }

    int size(){
        return front->size[max_height] - 1;
    }

    void insert_next(NodePtr pre, T key, int height = -1){
        if(height == -1){
            uint32_t r = max(rnd(), uint32_t(1));
            height = min(20, __builtin_ffs(r));
        }
        while(max_height < height){
            ++max_height;
            front->size[max_height] = front->size[max_height - 1];
            front->next[max_height] = back;
            back->prev[max_height] = front;
        }
        NodePtr node = new Node(key, height);

        int pre_size = 1;
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
                node->size[i] = range_size - pre_size;
            }
            for(; pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i])
                pre_size += pre->prev[i]->size[i];
            for(; nex->height == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]);
        }
    }

    void insert(T key){
        NodePtr pre = lower_bound(key)->prev[0];
        insert_next(pre, key);
    }

    void erase(NodePtr target){
        // メモリ解放はしない(してもいいけど)
        int height = target->height;
        NodePtr pre = target->prev[0];
        NodePtr nex = target->next[0];
        for(int i = 0; i <= max_height; ++i){
            --pre->size[i];
            if(i < height){
                pre->next[i] = nex;
                nex->prev[i] = pre;
                pre->size[i] += target->size[i];
            }
            for(; pre->height == i + 1 && pre->prev[i] != nullptr; pre = pre->prev[i]);
            for(; nex->height == i + 1 && nex->next[i] != nullptr; nex = nex->next[i]);
        }
    }

    void erase_index(int idx){
        NodePtr target = access(idx);
        erase(target);
    }

    void erase_key(T key){
        NodePtr target = lower_bound(key);
        if(target == back || target->val != key)
            return;
        erase(target);
    }

    NodePtr lower_bound(T key){
        NodePtr pre = front;
        for(int i = max_height; i >= 0; --i)
            for(; i < pre->next.size() && pre->next[i] != back && pre->next[i]->val < key; pre = pre->next[i]);
        return pre->next[0];
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

    // [0, k), [k, n)で分割し、[k, n)を返す
    SSet<T> split(int k){
        int max_h = max_height;
        NodePtr pre = access(k - 1);
        insert_next(pre, T(), 21);
        NodePtr l_back = pre->next[0];
        insert_next(l_back, T(), 21);
        NodePtr r_front = l_back->next[0];
        NodePtr l_front = front, r_back = back;
        for(int i = 0; i < l_back->height; ++i){
            l_back->next[i] = nullptr;
            r_front->prev[i] = nullptr;
            l_back->size[i] = 1;
        }
        max_height = max_h;
        NodePtr ptr = l_back;
        int size = 1;
        for(int i = 0; i <= max_height; ++i){
            ptr->size[i] = size;
            for(; ptr->height == i + 1 && ptr->prev[i] != nullptr; ptr = ptr->prev[i])
                size += ptr->prev[i]->size[i];
        }
        back = l_back;
        SSet<T> sset(r_front, r_back);
        sset.max_height = max_h;
        return sset;
    }

    // thisの末尾にslistを結合する
    void merge(SSet<T>& slist){
        while(max_height < slist.max_height){
            ++max_height;
            front->size[max_height] = front->size[max_height - 1];
            front->next[max_height] = back;
            back->prev[max_height] = front;
        }
        while(slist.max_height < max_height){
            ++slist.max_height;
            slist.front->size[slist.max_height] = slist.front->size[slist.max_height - 1];
            slist.front->next[slist.max_height] = slist.back;
            slist.back->prev[slist.max_height] = slist.front;
        }
        NodePtr a = back, b = slist.front;
        for(int i = 0; i < back->height; ++i){
            a->next[i] = b;
            b->prev[i] = a;
        }
        back = slist.back;
        erase(a);
        erase(b);
    }
};

