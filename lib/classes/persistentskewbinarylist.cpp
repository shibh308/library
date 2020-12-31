template<typename T>
struct PersistentSkewBinaryList{
    using ListPtr = const PersistentSkewBinaryList<T>*;

    struct Node{
        Node *l, *r;
        T x;
        int dep;
        Node(T x) : l(nullptr), r(nullptr), x(x), dep(1){}
        Node(T x, Node *l, Node *r) : l(l), r(r), x(x), dep(l->dep + 1){}
    };

    long long siz;
    ListPtr nex;
    Node* node;
    PersistentSkewBinaryList() : nex(nullptr), siz(0), node(nullptr){}
    PersistentSkewBinaryList(Node* node, ListPtr nex) : nex(nex), siz((1LL << node->dep) - 1 + (nex == nullptr ? 0 : nex->siz)), node(node){}
    PersistentSkewBinaryList(T val, ListPtr nex = nullptr) : nex(nex), siz(1 + (nex == nullptr ? 0 : nex->siz)), node(new Node(val)){}
    ListPtr push_front(T val) const{
        if(siz == 0){
            return new PersistentSkewBinaryList<T>(val, nullptr);
        }
        else if(nex != nullptr && node->dep == nex->node->dep){
            Node* new_node = new Node(val, node, nex->node);
            return new PersistentSkewBinaryList<T>(new_node, nex->nex);
        }
        else{
            return new PersistentSkewBinaryList<T>(val, this);
        }
    }
    T access(Node* x, long long k) const{
        long long ch_siz = (1LL << (x->dep - 1)) - 1;
        if(k == 0)
            return x->x;
        else if(k - 1 < ch_siz)
            return access(x->l, k - 1);
        else
            return access(x->r, k - 1 - ch_siz);
    }
    T access(long long k) const{
        long long node_siz = (1LL << node->dep) - 1;
        if(k < node_siz)
            return access(node, k);
        else
            return nex->access(k - node_siz);
    }
};

