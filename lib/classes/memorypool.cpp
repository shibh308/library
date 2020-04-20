template <typename T>
struct MemoryPool{
    int siz, idx;
    stack<int> st;
    vector<T*> pool;
    MemoryPool() : siz(1), idx(0){}
    void resize(){
        pool.emplace_back(new T[siz]);
        siz <<= 1;
    }
    int alloc(){
        if(!st.empty()){
            int res = st.top();
            st.pop();
            return res;
        }
        if(++idx == siz)
            resize();
        return idx;
    }
    void free(int x){
        st.push(x);
    }
    T& operator[](int x){return pool[31 - __builtin_clz(x)][x & ~(1 << (31 - __builtin_clz(x)))];}
};

