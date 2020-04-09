// y-fast trie用のSplayTree
template <typename T>
struct SplayTree{
    struct Node{
        int size;
        T val;
        Node* par;
        Node* c[2];
        Node(){}
        Node(T val, Node* nil) : val(val), size(1), par(nil){c[0] = nil; c[1] = nil;}
    };
    using NodePtr = Node*;
    NodePtr nil;

    SplayTree(){
        nil = new Node(T(), nullptr);
        nil->size = 0;
        nil->par = nil->c[0] = nil->c[1] = nil;
    }

    NodePtr make(T val){
        return new Node(val, nil);
    }

    void _update(NodePtr x){
        if(x == nil)
            return;
        assert(x != x->c[0]);
        assert(x != x->c[1]);
        assert(x->c[0] == nil || x->c[0] != x->c[1]);
        x->size = x->c[0]->size + x->c[1]->size + 1;
        assert(x->size > 0);
    }

    // idx側の子を上に持っていく
    void rotate(NodePtr p, bool p_right){
        NodePtr x = p->c[p_right];
        NodePtr q = p->par;
        // xに元々ついてた辺をpに張り替え
        assert(p->c[p_right] == x);
        p->c[p_right] = x->c[p_right ^ 1];
        if(x->c[p_right ^ 1] != nil){
            p->c[p_right]->par = p;
            assert(p != p->c[p_right]);
        }
        // xp間の辺の張り替え
        p->par = x;
        x->c[p_right ^ 1] = p;
        // pq間の辺の張り替え
        x->par = q;
        if(q != nil){
            bool q_right = (q->c[1] == p);
            assert(q->c[q_right] == p);
            q->c[q_right] = x;
        }
        _update(p), _update(x), _update(q);
    }

    void reroot(NodePtr x){
        while(x->par != nil){
            NodePtr p = x->par;
            NodePtr q = p->par;
            bool q_right = (q->c[1] == p);
            bool p_right = (p->c[1] == x);
            if(p->par == nil){
                rotate(p, p_right);
                break;
            }
            // 同じ向きの二回回転
            if(q_right == p_right){
                rotate(q, q_right), rotate(p, p_right);
            }
            else{
                rotate(p, p_right), rotate(q, q_right);
            }
        }
    }

    pair<NodePtr, bool> _lower_bound(NodePtr p, T key){
        if(p == nil)
            return make_pair(nil, false);
        if(p->val < key){
            auto res = _lower_bound(p->c[1], key);
            return res.second ? res : make_pair(p, false);
        }
        else{
            auto res = _lower_bound(p->c[0], key);
            return res.second ? res : make_pair(p, true);
        }
    }

    pair<NodePtr, bool> lower_bound(NodePtr p, T key){
        assert(p != nil);
        auto res = _lower_bound(p, key);
        reroot(res.first);
        return res;
    }

    NodePtr access(NodePtr p, int idx){
        while(p->c[0]->size != idx){
            if(p->c[0]->size < idx)
                idx -= p->c[0]->size + 1, p = p->c[1];
            else
                p = p->c[0];
            assert(p != nil);
        }
        assert(p != nil);
        reroot(p);
        return p;
    }

    NodePtr next(NodePtr p){
        reroot(p);
        p = p->c[1];
        while(p->c[0] != nil)
            p = p->c[0];
       if(p != nil)
           reroot(p);
       return p;
    }

    NodePtr prev(NodePtr p){
        reroot(p);
        p = p->c[0];
        while(p->c[1] != nil)
            p = p->c[1];
        if(p != nil)
            reroot(p);
        return p;
    }

    NodePtr insert(NodePtr root, T key){
        if(root == nil)
            return make(key);
        NodePtr l, r, np;
        bool exist;
        // lower_boundの結果からsplitする時、lower_boundの結果がnilだとバグるので注意
        tie(np, exist) = lower_bound(root, key);
        if(exist){
            tie(l, r) = split(np);
            return merge(merge(l, make(key)), r);
        }
        else{
            return merge(np, make(key));
        }
    }

    NodePtr erase(NodePtr root, T key){
        NodePtr p = lower_bound(root, key).first;
        assert(p != nil && p->val == key);
        reroot(p);
        NodePtr l = p->c[0], r = p->c[1];
        l->par = r->par = nil;
        delete(p);
        return merge(l, r);
    }

    // [0, p), [p, n)でsplist
    pair<NodePtr, NodePtr> split(NodePtr p){
        if(p == nil)
            return make_pair(nil, nil);
        reroot(p);
        NodePtr l = p->c[0];
        l->par = nil;
        p->c[0] = nil;
        _update(p);
        return make_pair(l, p);
    }

    NodePtr merge(NodePtr p, NodePtr q){
        assert(p != nil || q != nil);
        reroot(p);
        reroot(q);
        if(q == nil)
            return p;
        if(p == nil)
            return q;
        while(p->c[1] != nil)
            p = p->c[1];
        reroot(p);
        assert(p->c[1] == nil);
        p->c[1] = q;
        q->par = p;
        _update(p);
        assert(p != nil);
        return p;
    }

    void print(NodePtr x, int p = 0){
        if(x == nil)return;
        if(p == 0)
            cout << "----print----" << endl;
        print(x->c[0], p + 8);
        for(int i = 0; i < p; ++i)
            cout << " ";
        cout << "val:" << x->val << " ";
        cout << "size:" << x->size << endl;
        print(x->c[1], p + 8);
        if(p == 0)
            cout << "-------------" << endl;
    }
};

