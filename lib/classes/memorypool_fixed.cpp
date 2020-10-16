template <typename T, int SIZE = 1000000>
struct MemoryPool{
    int idx;
    stack<int> st;
    T pool[SIZE];
    struct Index{
        int idx;
        friend bool operator==(const Index& a, const Index& b){return a.idx == b.idx;}
        friend bool operator!=(const Index& a, const Index& b){return a.idx != b.idx;}
    };
    MemoryPool() : idx(0){}
    Index alloc(){
        if(!st.empty()){
            int res = st.top();
            st.pop();
            return {res};
        }
        assert(++idx != SIZE);
        return {idx};
    }
    void free(Index x){st.push(x.idx);}
    int used(){return idx - st.size();}

    T& operator[](Index x){return pool[x.idx];}
};
