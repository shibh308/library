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


# :warning: lib/classes/convexhulltrick.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a2816715ae26fbd9c4a8d3f916105a3">lib/classes</a>
* <a href="{{ site.github.repository_url }}/blob/master/lib/classes/convexhulltrick.cpp">View this file on GitHub</a>
    - Last commit date: 2019-11-30 20:08:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
template <typename T, typename U>
struct ConvexHullTrick{
    // 任意の2関数で共有点が高々1個ならElmの中身を適切に変えれば通る

    struct Elm{
        T a, b;
        U operator()(T x){
            return a * x + b;
        }
    };

    struct Node{
        Elm f;
        Node* l;
        Node* r;
        Node(Elm elm) : f(elm), l(nullptr), r(nullptr){}
    };

    U _min, _max, _inf;
    Node* root;

    ConvexHullTrick(U _min, U _max, U _inf) :
        _min(_min),
        _max(_max),
        _inf(_inf),
        root(nullptr)
    {
    }

    Node* _insert(Node* p, T st, T en, Elm f){
        if(!p)
            return new Node(f);
        if(p->f(st) <= f(st) && p->f(en) <= f(en))
            return p;
        if(p->f(st) >= f(st) && p->f(en) >= f(en)){
            p->f = f;
            return p;
        }
        T mid = (st + en) / 2;
        if(p->f(mid) > f(mid))
            swap(p->f, f);
        if(p->f(st) >= f(st))
            p->l = _insert(p->l, st, mid, f);
        else
            p->r = _insert(p->r, mid, en, f);
        return p;
    }

    U _query(Node* p, T st, T en, T x){
        if(!p)
            return _inf;
        if(st == en)
            return p->f(x);
        T mid = (st + en) / 2;
        if(x <= mid)
            return min(p->f(x), _query(p->l, st, mid, x));
        else
            return min(p->f(x), _query(p->r, mid, en, x));
    }

    void insert(Elm f){
        root = _insert(root, _min, _max, f);
    }

    U query(T x){
        return _query(root, _min, _max, x);
    }
};


```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "lib/classes/convexhulltrick.cpp"
template <typename T, typename U>
struct ConvexHullTrick{
    // 任意の2関数で共有点が高々1個ならElmの中身を適切に変えれば通る

    struct Elm{
        T a, b;
        U operator()(T x){
            return a * x + b;
        }
    };

    struct Node{
        Elm f;
        Node* l;
        Node* r;
        Node(Elm elm) : f(elm), l(nullptr), r(nullptr){}
    };

    U _min, _max, _inf;
    Node* root;

    ConvexHullTrick(U _min, U _max, U _inf) :
        _min(_min),
        _max(_max),
        _inf(_inf),
        root(nullptr)
    {
    }

    Node* _insert(Node* p, T st, T en, Elm f){
        if(!p)
            return new Node(f);
        if(p->f(st) <= f(st) && p->f(en) <= f(en))
            return p;
        if(p->f(st) >= f(st) && p->f(en) >= f(en)){
            p->f = f;
            return p;
        }
        T mid = (st + en) / 2;
        if(p->f(mid) > f(mid))
            swap(p->f, f);
        if(p->f(st) >= f(st))
            p->l = _insert(p->l, st, mid, f);
        else
            p->r = _insert(p->r, mid, en, f);
        return p;
    }

    U _query(Node* p, T st, T en, T x){
        if(!p)
            return _inf;
        if(st == en)
            return p->f(x);
        T mid = (st + en) / 2;
        if(x <= mid)
            return min(p->f(x), _query(p->l, st, mid, x));
        else
            return min(p->f(x), _query(p->r, mid, en, x));
    }

    void insert(Elm f){
        root = _insert(root, _min, _max, f);
    }

    U query(T x){
        return _query(root, _min, _max, x);
    }
};


```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

