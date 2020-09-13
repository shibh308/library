template <typename T, typename U>
struct AVL_map{
    struct Node{
        int height;
        T key;
        U val;
        Node(T key, U val) : key(key), val(val), height(1){c[0] = 0; c[1] = 0;}
        int c[2];
    };
    vector<Node> nodes;
    stack<int> st;
    AVL_map(){
        nodes.emplace_back(T(), U());
        nodes[0].height = 0;
    }
    template <bool inv>
    int balance_factor(int x){return (nodes[nodes[x].c[0]].height - nodes[nodes[x].c[1]].height) * (inv ? -1 : 1);}
    void _update(int x){
        if(x == 0)
            return;
        nodes[x].height = max(nodes[nodes[x].c[0]].height, nodes[nodes[x].c[1]].height) + 1;
    }
    template <bool is_right>
    int rotate(int x){
        int y = nodes[x].c[1 ^ is_right];
        nodes[x].c[1 ^ is_right] = nodes[y].c[0 ^ is_right];
        nodes[y].c[0 ^ is_right] = x;
        _update(x);
        _update(y);
        return y;
    }
    template <bool inv>
    int _balance(int x){
        if(balance_factor<inv>(x) == 2){
            if(balance_factor<inv>(nodes[x].c[0 ^ inv]) < 0)
                nodes[x].c[0 ^ inv] = rotate<inv>(nodes[x].c[0 ^ inv]);
            x = rotate<1 ^ inv>(x);
        }
        return x;
    }
    int balance(int x){
        x = _balance<false>(x);
        x = _balance<true>(x);
        _update(x);
        return x;
    }
    int add(int x, T key, U val){
        if(x == 0){
            if(st.empty()){
                nodes.emplace_back(key, val);
                return nodes.size() - 1;
            }
            else{
                int y = st.top();
                st.pop();
                nodes[y] = Node(key, val);
                return y;
            }
        }
        else if(key == nodes[x].key)
            nodes[x].val = val;
        else if(key < nodes[x].key)
            nodes[x].c[0] = add(nodes[x].c[0], key, val);
        else
            nodes[x].c[1] = add(nodes[x].c[1], key, val);
        x = balance(x);
        return x;
    }
    // 子が片方しかない時にノードを削除する
    int _erase_top(int x, bool del){
        for(int i = 0; i < 2; ++i){
            if(nodes[x].c[i] == 0){
                int y = nodes[x].c[i ^ 1];
                if(del)
                    st.push(x);
                return y;
            }
        }
    }
    // 最小の要素をdstにコピーしてから削除する
    int _copy_erase(int x, int dst, bool del){
        if(nodes[x].c[0] == 0){
            nodes[dst].val = nodes[x].val;
            return _erase_top(x, del);
        }
        nodes[x].c[0] = _copy_erase(nodes[x].c[0], dst, del);
        x = balance(x);
        return x;
    }
    int erase(int x, T key, bool del = true){
        if(key < nodes[x].key)
            nodes[x].c[0] = erase(nodes[x].c[0], key, del);
        else if(nodes[x].key < key)
            nodes[x].c[1] = erase(nodes[x].c[1], key, del);
        else{
            if(nodes[x].c[0] == 0 || nodes[x].c[1] == 0)
                return _erase_top(x, del);
            nodes[x].c[1] = _copy_erase(nodes[x].c[1], x, del);
        }
        x = balance(x);
        return x;
    }
    pair<U, bool> get(int x, T key){
        if(x == 0)
            return {U(), false};
        else if(key == nodes[x].key)
            return {nodes[x].val, true};
        else if(key < nodes[x].key)
            return get(nodes[x].c[0], key);
        else
            return get(nodes[x].c[1], key);
    }
    vector<pair<T, U>> list(int x){
        vector<pair<T, U>> v;
        stack<pair<int,bool>> sta;
        sta.emplace(x, false);
        bool add;
        while(!sta.empty()){
            tie(x, add) = sta.top();
            sta.pop();
            if(x == 0)
                continue;
            if(add)
                v.emplace_back(nodes[x].key, nodes[x].val);
            else{
                if(nodes[x].c[1])
                    sta.emplace(nodes[x].c[1], false);
                sta.emplace(x, true);
                if(nodes[x].c[0])
                    sta.emplace(nodes[x].c[0], false);
            }
        }
        return v;
    }
};
