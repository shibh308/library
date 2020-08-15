---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :warning: lib/classes/eertree.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/eertree.cpp">View this file on GitHub</a>
    - Last commit date: 2020-08-15 20:44:23+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
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
        for(s += c; int(s.size()) - active_point->len - 2 < 0 || s[s.size() - active_point->len - 2] != c; active_point = active_point->slink);
        active_point = make(active_point, c);
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/eertree.cpp"
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
        for(s += c; int(s.size()) - active_point->len - 2 < 0 || s[s.size() - active_point->len - 2] != c; active_point = active_point->slink);
        active_point = make(active_point, c);
    }
};

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

