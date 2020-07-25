// verify: https://yukicoder.me/submissions/518134
struct EerTree{
    struct Node{
        Node(int len) : len(len), sdep(0), slink(nullptr){}
        int len, sdep;
        map<char, Node*> ch;
        Node* slink;
    };
    pair<Node*, Node*> root;
    Node* active_point;
    string s;
    EerTree(){
        root.second = new Node(0);
        root.second->slink = root.first = active_point = new Node(-1);
        root.first->slink = root.first;
    }
    EerTree(string inp) : EerTree(){
        for(auto c : inp)
            add(c);
    }
    Node* make(Node* par, char c){
        if(par->ch.find(c) == par->ch.end()){
            par->ch[c] = new Node(par->len + 2);
            Node* sl = par->slink;
            if(par->len == -1)
                sl = root.second;
            else{
                while(1){
                    if(s[s.size() - sl->len - 2] == c){
                        sl = sl->ch[c];
                        break;
                    }else if(sl->len < 0){
                        sl = root.second;
                        break;
                    }else
                        sl = sl->slink;
                }
            }
            par->ch[c]->slink = sl;
            par->ch[c]->sdep = sl->sdep + 1;
        }
        return par->ch[c];
    }
    void add(char c){
        for(s += c; s[s.size() - active_point->len - 2] != c; active_point = active_point->slink);
        active_point = make(active_point, c);
    }
};
