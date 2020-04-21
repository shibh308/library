template <typename T>
struct MemoryPool{
    int siz, idx;
    stack<int> st;
    vector<T*> pool;
    struct Index{
        int idx;
        friend bool operator==(const Index& a, const Index& b){return a.idx == b.idx;}
        friend bool operator!=(const Index& a, const Index& b){return a.idx != b.idx;}
    };
    MemoryPool() : siz(1), idx(0){}
    void resize(){
        pool.emplace_back(new T[siz]);
        siz <<= 1;
    }
    Index alloc(){
        if(!st.empty()){
            int res = st.top();
            st.pop();
            return {res};
        }
        if(++idx == siz)
            resize();
        return {idx};
    }
    void free(Index x){
        st.push(x.idx);
    }
    T& operator[](Index x){return pool[31 - __builtin_clz(x.idx)][x.idx & ~(1 << (31 - __builtin_clz(x.idx)))];}
};

