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


# :warning: lib/classes/primaldual.cpp
* category: lib/classes


[Back to top page](../../../index.html)



## Code
```cpp
template <typename T, typename U>
struct PrimalDual{
    struct Edge{
        int to, rev;
        U cap;
        T cost;
        Edge(int to, U cap, T cost, int rev) :
            to(to), rev(rev), cap(cap), cost(cost){}
    };
    vector<vector<Edge>> edges;
    T _inf;
    vector<T> potential, min_cost;
    vector<int> prev_v, prev_e;

    PrimalDual(int n) : edges(n), _inf(numeric_limits<T>::max()){}

    void add(int from, int to, U cap, T cost){
        edges[from].emplace_back(to, cap, cost, static_cast<int>(edges[to].size()));
        edges[to].emplace_back(from, 0, -cost, static_cast<int>(edges[from].size()) - 1);
    }

    T solve(int s, int t, U flow){
        int n = edges.size();
        T ret = 0;
        priority_queue<pair<T,int>, vector<pair<T,int>>, greater<pair<T,int>>> que;
        potential.assign(n, 0);
        prev_v.assign(n, -1);
        prev_e.assign(n, -1);
        while(flow > 0){
            min_cost.assign(n, _inf);
            que.emplace(0, s);
            min_cost[s] = 0;
            while(!que.empty()){
                T fl;
                int pos;
                tie(fl, pos) = que.top();
                que.pop();
                if(min_cost[pos] != fl)
                    continue;
                for(int i = 0; i < edges[pos].size(); ++i){
                    auto& ed = edges[pos][i];
                    T nex = fl + ed.cost + potential[pos] - potential[ed.to];
                    if(ed.cap > 0 && min_cost[ed.to] > nex){
                        min_cost[ed.to] = nex;
                        prev_v[ed.to] = pos;
                        prev_e[ed.to] = i;
                        que.emplace(min_cost[ed.to], ed.to);
                    }
                }
            }
            if(min_cost[t] == _inf)
                return -1;
            for(int i = 0; i < n; ++i)
                potential[i] += min_cost[i];
            T add_flow = flow;
            for(int x = t; x != s; x = prev_v[x])
                add_flow = min(add_flow, edges[prev_v[x]][prev_e[x]].cap);
            flow -= add_flow;
            ret += add_flow * potential[t];
            for(int x = t; x != s; x = prev_v[x]){
                auto& ed = edges[prev_v[x]][prev_e[x]];
                ed.cap -= add_flow;
                edges[x][ed.rev].cap += add_flow;
            }
        }
        return ret;
    }
};


```

[Back to top page](../../../index.html)

